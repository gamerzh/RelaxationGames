#include "bullet/Laster.h"
#include "utill/FunUtil.h"
bool Laster::init(){

	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!Sprite::initWithFile("game/ui/ani/TX_JiGuang/TX_JiGuang_1.png"));
		setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	


		runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniJiGuangBar")));

		scheduleUpdate();
		bRet = true;
	} while (0);
	return bRet;
}



void Laster::update(float delta)
{
	if (!pPlayerTurret)
	{
		removeFromParentAndCleanup(1);
	}
	if (pPlayerTurret->getisUsingLight()==false)
	{
		removeFromParentAndCleanup(1);
	}
	auto fish = pPlayerTurret->getLightFish();
	if (fish)
	{
		setPosition(pPlayerTurret->getLasterOrginPos());
		Vec2 m_pos = pPlayerTurret->getLasterOrginPos();
		Vec2 targetPos = fish->convertToWorldSpace(fish->getCentrenPos());
		auto distance = m_pos.distance(targetPos);
		setTextureRect(Rect(0, 0, distance, getContentSize().height));
		auto angle = getTurretRotation(m_pos,targetPos);
		setRotation(-90+angle);
	}
	else
	{
		removeFromParentAndCleanup(1); 
	}
}
void Laster::removeFromParentAndCleanup(bool cleanup)
{
	pPlayerTurret = nullptr;
	unscheduleUpdate();
	Node::removeFromParentAndCleanup(cleanup);
}