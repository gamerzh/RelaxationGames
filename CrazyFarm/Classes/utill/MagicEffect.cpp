#include "MagicEffect.h"
#include "ui/UIScale9Sprite.h"
using namespace ui;


MagicEffect * MagicEffect::create(const int lightID, bool isBottomRorato)
{
	MagicEffect * t = new MagicEffect;
	if (t && t->init(lightID, isBottomRorato))
	{
		t->autorelease();
		return t;
	}
	CC_SAFE_DELETE(t);
	return NULL;
}

bool MagicEffect::init(const int lightID, bool isBottomRorato)
{
	bool ret = false;
	do 
	{
	    if (isBottomRorato)
	    {
			
			auto path = String::createWithFormat("game/ui/effect/light_%d.png", lightID);
			initWithFile(path->getCString());
			path = String::createWithFormat("game/ui/effect/lightRorate_%d.png", lightID);
			auto sp = Sprite::create(path->getCString());
			sp->setPosition(getContentSize() / 2);
			addChild(sp);
			sp->runAction(RepeatForever::create(RotateBy::create(3.0f, 360.0)));
	    }
		else
		{
			auto path = String::createWithFormat("game/ui/effect/light_%d.png", lightID);
			initWithFile(path->getCString());
			runAction(RepeatForever::create(RotateBy::create(3.0f, 360.0)));
		}
		ret = true;
	} while (0);
	
	return ret;
}
