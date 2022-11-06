#include "fish/FishShader.h"
#include "FishAniMannage.h"



FishShader*FishShader::createShader(Fish*fish)
{ 
	FishShader *pRet = new FishShader();
	if (pRet && pRet->init(fish))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}


bool FishShader::init(Fish*fish){
	auto fishdata = ConfigFish::getInstance()->getFish(fish->getFishID());
	if (!Sprite::initWithSpriteFrame(FishAniMannage::getInstance()->getSpriteById(fishdata.uiId)))
	{
		return false;
	}
	
	target = fish;

	auto acName = String::createWithFormat("swim_%d", fishdata.uiId);
	auto ac = RepeatForever::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()));

	setPosition(target->getPositionX() + target->getContentSize().width*0.15,  target->getPositionY() + target->getContentSize().height*-0.15);
	target->getParent()->addChild(this, 4);
	setColor(Color3B::BLACK);
	setOpacity(GLubyte(150));
	runAction(ac);
	scheduleUpdate();
	return true;
}
void FishShader::update(float dt)
{
	if ( target!= nullptr)
	{
		setPosition(target->getPositionX() + target->getContentSize().width*0.15, target->getPositionY() + target->getContentSize().height*-0.15);
		setRotation(target->getRotation());
	}
}


void FishShader::onDead()
{
	stopAllActions();
	unscheduleAllCallbacks();
	auto acName = String::createWithFormat("dead_%d", ConfigFish::getInstance()->getFish(target->getFishID()).uiId);
	auto ac = Repeat::create(FishAniMannage::getInstance()->getAnimate(acName->getCString()),CC_REPEAT_FOREVER);
	runAction(ac);
}


