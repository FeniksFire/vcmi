/*
 * CIntObject.cpp, part of VCMI engine
 *
 * Authors: listed in file AUTHORS in main folder
 *
 * License: GNU General Public License v2.0 or later
 * Full text of license available in license.txt file, in main folder
 *
 */
#include "StdInc.h"
#include "View.h"

#include "../CGuiHandler.h"
#include "../SDL_Extensions.h"
#include "../../CMessage.h"

IShowActivatable::IShowActivatable()
{
	type = 0;
}

View::View(ui16 used_, Point pos_):
	active_m(0),
	active(active_m),
	pos(pos_.x, pos_.y),
	used(used_),
	hovered(false),
	captureAllKeys(false),
	strongInterest(false),
	toNextTick(0),
	timerDelay(0),
	defActions(GH.defActionsDef),
	recActions(GH.defActionsDef)
{
	if(GH.captureChildren)
		GH.createdObj.front()->addChild(this, true);
}

View::~View()
{
	if(active_m)
		deactivate();

	while(!children.empty())
	{
		if((defActions & DISPOSE) && (children.front()->recActions & DISPOSE))
			delete children.front();
		else
			removeChild(children.front());
	}

	if(parent_m)
		parent_m->removeChild(this);
}

void View::setTimer(int msToTrigger)
{
	if (!(active & TIME))
		activate(TIME);
	toNextTick = timerDelay = msToTrigger;
	used |= TIME;
}

void View::onTimer(int timePassed)
{
	toNextTick -= timePassed;
	if (toNextTick < 0)
	{
		toNextTick += timerDelay;
		tick();
	}
}

void View::show(SDL_Surface * to)
{
	if(defActions & UPDATE)
		for(auto & elem : children)
			if(elem->recActions & UPDATE)
				elem->show(to);
}

void View::showAll(SDL_Surface * to)
{
	if(defActions & SHOWALL)
	{
		for(auto & elem : children)
			if(elem->recActions & SHOWALL)
				elem->showAll(to);

	}
}

void View::activate()
{
	if (active_m)
	{
		if ((used | GENERAL) == active_m)
			return;
		else
		{
			logGlobal->warn("Warning: IntObject re-activated with mismatching used and active");
			deactivate(); //FIXME: better to avoid such possibility at all
		}
	}

	active_m |= GENERAL;
	activate(used);

	if(defActions & ACTIVATE)
		for(auto & elem : children)
			if(elem->recActions & ACTIVATE)
				elem->activate();
}

void View::activate(ui16 what)
{
	GH.handleElementActivate(this, what);
}

void View::deactivate()
{
	if (!active_m)
		return;

	active_m &= ~ GENERAL;
	deactivate(active_m);

	assert(!active_m);

	if(defActions & DEACTIVATE)
		for(auto & elem : children)
			if(elem->recActions & DEACTIVATE)
				elem->deactivate();
}

void View::deactivate(ui16 what)
{
	GH.handleElementDeActivate(this, what);
}

void View::click(EIntObjMouseBtnType btn, tribool down, bool previousState)
{
	switch(btn)
	{
	case EIntObjMouseBtnType::LEFT:
		clickLeft(down, previousState);
		break;
	case EIntObjMouseBtnType::MIDDLE:
		clickMiddle(down, previousState);
		break;
	case EIntObjMouseBtnType::RIGHT:
		clickRight(down, previousState);
		break;
	}
}

void View::printAtMiddleLoc(const std::string & text, int x, int y, EFonts font, SDL_Color kolor, SDL_Surface * dst)
{
	printAtMiddleLoc(text, Point(x,y), font, kolor, dst);
}

void View::printAtMiddleLoc(const std::string & text, const Point &p, EFonts font, SDL_Color kolor, SDL_Surface * dst)
{
	graphics->fonts[font]->renderTextCenter(dst, text, kolor, pos.topLeft() + p);
}

void View::blitAtLoc( SDL_Surface * src, int x, int y, SDL_Surface * dst )
{
	blitAt(src, pos.x + x, pos.y + y, dst);
}

void View::printAtMiddleWBLoc( const std::string & text, int x, int y, EFonts font, int charpr, SDL_Color kolor, SDL_Surface * dst)
{
	graphics->fonts[font]->renderTextLinesCenter(dst, CMessage::breakText(text, static_cast<size_t>(charpr), font), kolor, Point(pos.x + x, pos.y + y));
}

void View::addUsedEvents(ui16 newActions)
{
	if (active_m)
		activate(~used & newActions);
	used |= newActions;
}

void View::removeUsedEvents(ui16 newActions)
{
	if (active_m)
		deactivate(used & newActions);
	used &= ~newActions;
}

void View::disable()
{
	if(active)
		deactivate();

	recActions = DISPOSE;
}

void View::enable()
{
	if(!active_m && (!parent_m || parent_m->active))
		activate();

	recActions = 255;
}

void View::fitToScreen(int borderWidth, bool propagate)
{
	Point newPos = pos.topLeft();
	vstd::amax(newPos.x, borderWidth);
	vstd::amax(newPos.y, borderWidth);
	vstd::amin(newPos.x, screen->w - borderWidth - pos.w);
	vstd::amin(newPos.y, screen->h - borderWidth - pos.h);
	if (newPos != pos.topLeft())
		moveTo(newPos, propagate);
}

void View::moveBy(const Point & p, bool propagate)
{
	pos.x += p.x;
	pos.y += p.y;
	if(propagate)
		for(auto & elem : children)
			elem->moveBy(p, propagate);
}

void View::moveTo(const Point & p, bool propagate)
{
	moveBy(Point(p.x - pos.x, p.y - pos.y), propagate);
}

void View::addChild(View * child, bool adjustPosition)
{
	if (vstd::contains(children, child))
	{
		return;
	}
	if (child->parent_m)
	{
		child->parent_m->removeChild(child, adjustPosition);
	}
	children.push_back(child);
	child->parent_m = this;
	if(adjustPosition)
		child->pos += pos;

	if (!active && child->active)
		child->deactivate();
	if (active && !child->active)
		child->activate();
}

void View::removeChild(View * child, bool adjustPosition)
{
	if (!child)
		return;

	if(!vstd::contains(children, child))
		throw std::runtime_error("Wrong child object");

	if(child->parent_m != this)
		throw std::runtime_error("Wrong child object");

	children -= child;
	child->parent_m = nullptr;
	if(adjustPosition)
		child->pos -= pos;
}

void View::redraw()
{
	//currently most of calls come from active objects so this check won't affect them
	//it should fix glitches when called by inactive elements located below active window
	if (active)
	{
		if (parent_m && (type & REDRAW_PARENT))
		{
			parent_m->redraw();
		}
		else
		{
			showAll(screenBuf);
			if(screenBuf != screen)
				showAll(screen);
		}
	}
}

const Rect & View::center( const Rect &r, bool propagate )
{
	pos.w = r.w;
	pos.h = r.h;
	return center(Point(screen->w/2, screen->h/2), propagate);
}

const Rect & View::center( bool propagate )
{
	return center(pos, propagate);
}

const Rect & View::center(const Point & p, bool propagate)
{
	moveBy(Point(p.x - pos.w/2 - pos.x,
		p.y - pos.h/2 - pos.y),
		propagate);
	return pos;
}

bool View::captureThisEvent(const SDL_KeyboardEvent & key)
{
	return captureAllKeys;
}

View *View::getParent() const
{
	return parent;
}

void View::setParent(View *parent)
{
	View::parent = parent;
}

CKeyShortcut::CKeyShortcut()
{}

CKeyShortcut::CKeyShortcut(int key)
{
	if (key != SDLK_UNKNOWN)
		assignedKeys.insert(key);
}

CKeyShortcut::CKeyShortcut(std::set<int> Keys)
	:assignedKeys(Keys)
{}

void CKeyShortcut::keyPressed(const SDL_KeyboardEvent & key)
{
	if(vstd::contains(assignedKeys,key.keysym.sym)
	 || vstd::contains(assignedKeys, CGuiHandler::numToDigit(key.keysym.sym)))
	{
		bool prev = mouseState(EIntObjMouseBtnType::LEFT);
		updateMouseState(EIntObjMouseBtnType::LEFT, key.state == SDL_PRESSED);
		clickLeft(key.state == SDL_PRESSED, prev);

	}
}

WindowBase::WindowBase(int used_, Point pos_)
	: View(used_, pos_)
{

}

void WindowBase::close()
{
	if(GH.topInt().get() != this)
		logGlobal->error("Only top interface must be closed");
	GH.popInts(1);
}
