#include "LightEffect.h"

LightEffect* LightEffect::create()
{
	LightEffect* bRet = new LightEffect();
	if (bRet&&bRet->init())
	{
		bRet->autorelease(); 
			return bRet; 
	}
	else 
	{ 
	  delete bRet; 
	  bRet = NULL; 
	  return NULL; 
	} 
}

bool LightEffect::init()
{
	Node::init();
	bool bRet = false;
	while (!bRet)
	{
		scheduleOnce([=](float interval)
		{
			auto sp = Sprite::create("smallLightPoint.png");
			sp->setScale(0.8);
			sp->setPosition(13, 17);
			sp->runAction(RepeatForever::create(Sequence::create(FadeOut::create(1.0f),DelayTime::create(2.5f), FadeIn::create(0.0001f), DelayTime::create(0.1f), nullptr)));
			addChild(sp);
		}, 0.1f, "11");
		scheduleOnce([=](float interval)
		{
			auto sp1 = Sprite::create("smallLightPoint.png");
			sp1->setPosition(32, 32);
			sp1->setScale(0.8);
			sp1->runAction(RepeatForever::create(Sequence::create(FadeOut::create(1.0f), DelayTime::create(2.5f), FadeIn::create(0.0001f), DelayTime::create(0.1f), nullptr)));
			addChild(sp1);
		}, 0.3f, "111");
		scheduleOnce([=](float interval)
		{
			auto sp2 = Sprite::create("smallLightPoint.png");
			sp2->setPosition(12, 35);
			sp2->runAction(RepeatForever::create(Sequence::create(FadeOut::create(1.0f), DelayTime::create(2.5f), FadeIn::create(0.0001f), DelayTime::create(0.1f), nullptr)));
			addChild(sp2);
		}, 0.5f, "1111");
		scheduleOnce([=](float interval)
		{

			auto sp3 = Sprite::create("smallLightPoint.png");
			sp3->setPosition(30, 17);
			sp3->runAction(RepeatForever::create(Sequence::create(FadeOut::create(1.0f), DelayTime::create(2.5f), FadeIn::create(0.0001f), DelayTime::create(0.1f), nullptr)));
			addChild(sp3);
		}, 0.47f, "1");

		
	
		bRet = true;
	}
	return bRet;
}

