#include "GetRewardNode.h"
#include "utill/AnimationUtil.h"
#include "domain/user/User.h"
#include "domain/logevent/LogEventBankrupt.h"
#include "data/GameData.h"

GetRewardNode* GetRewardNode::create(Bankrupt baknrupt)
{
	GetRewardNode *pRet = new GetRewardNode();
	if (pRet && pRet->init(baknrupt))
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

bool GetRewardNode::init(Bankrupt baknrupt)
{
	initWithFile("getRewardsNormal.png");
	bool bRet = false;
	do 
	{	
		m_baknrupt = baknrupt;
		char* mtime = new char[100];
		int s = ((int)m_baknrupt.wait_time + 1) % 60;
		int m = ((int)m_baknrupt.wait_time) / 60;
		sprintf(mtime, "%02d:%02d", m, s);
		auto label = LabelAtlas::create(mtime, "getRewardTimeNum.png", 10, 15, '0');
		label->setPosition(getContentSize().width / 2, 23);
		label->setAnchorPoint(Point::ANCHOR_MIDDLE);
		addChild(label, 0, "time");
		///时间改成0
		label->setVisible(false);
		isTimeOut = true;
		label->setVisible(false);
		runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniGainRewards")));
		////
		/*scheduleUpdate();*/
		auto listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = CC_CALLBACK_2(GetRewardNode::onTouchBegan, this);
		listenr1->setSwallowTouches(true);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);

		///今日很能领取几次救济金
		auto txt = Sprite::create("TXTBankruptCount.png");
		txt->setPosition(getContentSize().width / 2, -15);
		addChild(txt);
		auto countlabel = LabelAtlas::create(Value(baknrupt.time).asString(), "multipleNum.png", 15, 21, '0');
		countlabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
		countlabel->setPosition(1.25 + 152.75, txt->getContentSize().height / 2);
		txt->addChild(countlabel);

		bRet = true;
	} while (0);
	return bRet;
}
void GetRewardNode::update(float dt)
{
	m_baknrupt.wait_time -= dt;
	char* mtime = new char[100];
	int s = (((int)m_baknrupt.wait_time + 1) % 60);
	int m = (((int)m_baknrupt.wait_time )/ 60);
	sprintf(mtime, "%02d:%02d", m, s);
	auto label = (LabelAtlas*)getChildByName("time");
	label->setString(mtime);
	if (m_baknrupt.wait_time<=0)
	{
		isTimeOut = true;
		label->setVisible(false);
		runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniGainRewards")));
		unscheduleUpdate();
	}
}

bool GetRewardNode::onTouchBegan(Touch *touch, Event *unused_event)
{
	if (isTimeOut)
	{
		BankruptManager::getInstance()->RequestServerToRebirth();
		
	}
	return true;
}
