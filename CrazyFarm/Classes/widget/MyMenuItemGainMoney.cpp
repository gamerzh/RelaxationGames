#include "MyMenuItemGainMoney.h"
#include "domain/bonuspool/BonusPoolManager.h"
#include "domain/turntable/TurnTableDialog.h"
#include "domain/logevent/LogEventPageChange.h"
#include "extensions/cocos-ext.h"
enum 
{
	kTagMutpleLabel = 10,
	kTagExeDec = 11,
	kTagExeBar = 12,
	kTagCoinLabel=13

};

MyMenuItemGainMoney * MyMenuItemGainMoney::create()
{
	MyMenuItemGainMoney *ret = new (std::nothrow) MyMenuItemGainMoney();
	if (ret && ret->initWithNormalImage("UnlockFrame_1.png", "UnlockFrame_1.png", "", CC_CALLBACK_1(MyMenuItemGainMoney::ItemCallBack, ret)));
	{
		ret->initItem();
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}
void MyMenuItemGainMoney::ItemCallBack(Ref* psend)
{
	if (isElongate)
	{
		commonNode->setVisible(false);
		runAction(MoveBy::create(0.5f, Vec2(177, 0)));
		isElongate = false;
			auto dioag = TurnTableDialog::create();
			dioag->setPosition(Point::ZERO);
			LogEventPageChange::getInstance()->addEventItems(2, 10, 0);
			getParent()->getParent()->addChild(dioag,30);
			
	}
	else
	{
		isElongate = true;
		setValue();
		runAction(MoveBy::create(0.5f, Vec2(-177, 0)));
		runAction(Sequence::create(DelayTime::create(5.0f), CallFunc::create([&]{
			if (isElongate == false)
			{
				return;
			}
			runAction(MoveBy::create(0.5f, Vec2(177, 0)));
			commonNode->setVisible(false);
			isElongate = false;
		}), nullptr));
	}
}

void MyMenuItemGainMoney::initItem()
{

	commonNode = Node::create();
	commonNode->setPosition(11, 0);
	addChild(commonNode,1);



	commonNode->setVisible(false);
	auto size = getContentSize();
	txt = Sprite::create("fishPoolTxt.png");
	txt->setPosition(size.width*0.38+5, size.height/2);
	commonNode->addChild(txt);

	//¾­ÑéÌõ
	exeBarFrame = Sprite::create("exeBarFrameDiamond.png");
	exeBarFrame->setPosition(size.width*0.40 + 22, 58);
	commonNode->addChild(exeBarFrame, 1, "exeFrame");



	auto exeBar = Sprite::create("exeBarDiamond.png");
	exeBar->setPosition(2, exeBarFrame->getContentSize().height/2);
	exeBar->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	exeBarFrame->addChild(exeBar, 1, kTagExeBar);

	auto exeDec = LabelAtlas::create("0", "bonusNumTTF.png", 14, 21, '0');
	exeDec->setAnchorPoint(Point::ANCHOR_MIDDLE);
	exeDec->setPosition(exeBarFrame->getContentSize() / 2);
	exeBarFrame->addChild(exeDec, 1, kTagExeDec);



	
	auto coinNum = LabelAtlas::create(Value(0).asString().c_str(), "bonusNumTTF.png", 14, 21, '0');
	coinNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
	coinNum->setPosition(size.width*0.28+24, size.height*0.29-1);
	commonNode->addChild(coinNum, 1, kTagCoinLabel);
	auto coin = Sprite::create("smallCoin.png");
	coin->setPosition(size.width*0.6, size.height*0.29);
	commonNode->addChild(coin);
	
	

	isElongate = false;
	commonNode->setVisible(false);


	showBlinkAni();
	scheduleUpdate();
}
void MyMenuItemGainMoney::update(float delta)
{
	auto pNode = getChildByName("blinkAni");
	int nowFish = BonusPoolManager::getInstance()->getFishCounts();
	int alowdFish = BonusPoolManager::getInstance()->getAllowCatchFishCounts();
	if (nowFish >= alowdFish)
	{
		pNode->setVisible(true);
	}
	else
	{
		pNode->setVisible(false);
	}
}

void MyMenuItemGainMoney::setValue()
{

	commonNode->setVisible(true);
	int nowFish = BonusPoolManager::getInstance()->getFishCounts();
	int alowdFish = BonusPoolManager::getInstance()->getAllowCatchFishCounts();
	int poolNum = BonusPoolManager::getInstance()->getCoins();
	auto str = String::createWithFormat("%d:%d", nowFish, alowdFish);
	auto scalex = ((float)nowFish) / ((float)alowdFish);

	
	isFinish = nowFish >= alowdFish ? true : false;
	
	auto node = (LabelAtlas*)commonNode->getChildByTag(kTagCoinLabel);
	node->setString(Value(poolNum).asString().c_str());
	auto frame = commonNode->getChildByName("exeFrame");
	node = (LabelAtlas*)frame->getChildByTag(kTagExeDec);
	node->setString(str->getCString());
	auto node1 = frame->getChildByTag(kTagExeBar);
	((Sprite*)node1)->setTextureRect(Rect(0,0,scalex*93,20));
	/*node1->setContentSize(Size(scalex*77,node1->getContentSize().height));*/

	if (isFinish)
	{
		exeBarFrame->setVisible(false);
		txt->setTexture("fishPoolTxt2.png");
	}
	else
	{
		exeBarFrame->setVisible(true);
		txt->setTexture("fishPoolTxt.png");
	}
	
}
void MyMenuItemGainMoney::showBlinkAni()
{
	auto node = Sprite::create("UnlockFrame_2.png");
	node->setPosition(getContentSize() / 2);
	addChild(node, 0, "blinkAni");
	node->runAction(RepeatForever::create(Sequence::create(FadeOut::create(0.5f), FadeIn::create(0.5f), nullptr)));
}
void MyMenuItemGainMoney::showPopup()
{
	if (isElongate == true)
	{
		return;
	}
	else
	{
		isElongate = true;
		setValue();
		runAction(MoveBy::create(0.5f, Vec2(-177, 0)));
		
		float delaytime;
		if (isFinish)
		{
			delaytime = 6.0f;
		}
		else
		{
			delaytime = 3.0f;
		}
		runAction(Sequence::create(DelayTime::create(delaytime), CallFunc::create([&]{
			if (isElongate == true)
			{
				commonNode->setVisible(false);
				runAction(MoveBy::create(0.5f, Vec2(177, 0)));
				isElongate = false;
			};

		}), nullptr));
	
	}

}
void MyMenuItemGainMoney::removeBlinkAni()
{
	while (1)
	{
		auto pNode = getChildByName("blinkAni");
		if (pNode)
		{
			pNode->removeFromParentAndCleanup(1);
		}
		else
		{
			return;
		}
	}

}