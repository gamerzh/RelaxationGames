#include "WaitCircle.h"
#include "domain/pay/Pay.h"

WaitCircle*  WaitCircle::ShowPayWaitCircle()
{
	auto circle = WaitCircle::create();
	circle->setPosition(480, 270);
	Director::getInstance()->getRunningScene()->addChild(circle, 30);
	return circle;
}
void WaitCircle::RemovePayWaitCircle(std::string prepayid)
{

	auto circle = Director::getInstance()->getRunningScene()->getChildByName(prepayid);
		if (circle)
		{
			circle->removeFromParentAndCleanup(1);
		}
		else
		{
			return;
		}
	

}

void WaitCircle::sendRequestWaitCirCle(std::string prepayid)
{
	auto circle = Director::getInstance()->getRunningScene()->getChildByTag(888)->getChildByName(prepayid);
	if (circle)
	{
		auto node = (WaitCircle*)(circle); 
		node->runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create([=]{node->DemandEntry(); }), nullptr));
	}
}

bool WaitCircle::init()
{
	bool k = initWithFile("waitcircle.png");
	runAction(RepeatForever::create(RotateBy::create(2.0f, 360)));

	auto listenr1 = EventListenerTouchOneByOne::create();
	listenr1->onTouchBegan = CC_CALLBACK_2(WaitCircle::onTouchBegan, this);
	listenr1->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);


	runAction(Sequence::create(DelayTime::create(2.0f), CallFunc::create([=]{DemandEntry(); }),nullptr));
	return true;
}
void WaitCircle::DemandEntry()
{
	Pay::getInstance()->DemandEntry(++reqnum,m_prepayid);
	log("demandentry preid = %s,reqnum = %d", m_prepayid.c_str(), reqnum);

}


