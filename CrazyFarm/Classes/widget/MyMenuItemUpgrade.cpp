#include "MyMenuItemUpgrade.h"
#include "domain/user/User.h"
#include "config/ConfigTurrent.h"
#include "domain/bag/BagManager.h"
#include "data/GameData.h"
#include "core/showTurretLayer.h"
#include "domain/logevent/LogEventTurrentUpgrade.h"
#include "domain/globalschedule/GlobalSchedule.h"
#include "domain/game/GameManage.h"
#include "core/showLockTurretLayer.h"
enum 
{
	kTagMutpleLabel = 10,
	kTagExeDec = 11,
	kTagExeBar = 12,
	kTagCoinLabel=13

};

MyMenuItemUpgrade * MyMenuItemUpgrade::create()
{
	MyMenuItemUpgrade *ret = new (std::nothrow) MyMenuItemUpgrade();
	if (ret && ret->initWithNormalImage("UnlockFrame_1.png", "UnlockFrame_1.png", "", CC_CALLBACK_1(MyMenuItemUpgrade::ItemCallBack, ret)))
	{
		ret->initItem();
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}
void MyMenuItemUpgrade::ItemCallBack(Ref* psend)
{
	auto node = GameManage::getInstance()->getGuiLayer()->getChildByName("tipUpGradenode");
	if (node)
	{
		node->removeFromParentAndCleanup(1);
		GameManage::getInstance()->getGuiLayer()->setLayerAlpha(0);
	}



	if (User::getInstance()->getMaxTurrentLevel()>=1000)
	{
		removeBlinkAni();
		return;
	}
	if (isElongate)
	{
		commonNode->setVisible(false);
		unfinishedNode->setVisible(false);
		nodeZeng->setVisible(false);
		setEnabled(false);
		runAction(Sequence::create(MoveBy::create(0.5f, Vec2(177, 0)), CallFunc::create([=]{setEnabled(true); }), nullptr));
		isElongate = false;
		removeBlinkAni();
		if (isFinish)
		{
			
			GameManage::getInstance()->getGameLayer()->GetMyTurret()->onLockTheTurrent();
		}
		else
		{
			auto layer = showLockTurretLayer::create();
			layer->setPosition(Point::ZERO);
			getParent()->getParent()->addChild(layer,20,50);
			///////弹出充值
		}
		
	}
	else
	{
		isElongate = true;
		setValue();
		setEnabled(false);
		runAction(Sequence::create(MoveBy::create(0.5f, Vec2(-177, 0)), CallFunc::create([=]{setEnabled(true); }), nullptr));
		runAction(Sequence::create(DelayTime::create(4.0f), CallFunc::create([&]{
			if (isElongate==false)
			{
				return;
			}
			setEnabled(false);
			runAction(Sequence::create(MoveBy::create(0.5f, Vec2(177, 0)), CallFunc::create([=]{setEnabled(true); }), nullptr));
			commonNode->setVisible(false);
			unfinishedNode->setVisible(false);
			nodeZeng->setVisible(false);
			isElongate = false;
		}), nullptr));
	}
}
void MyMenuItemUpgrade::anastole()
{
	if (isElongate == false)
	{
		return;
	}
	setEnabled(false);
	runAction(Sequence::create(MoveBy::create(0.5f, Vec2(177, 0)), CallFunc::create([=]{setEnabled(true); }), nullptr));
	commonNode->setVisible(false);
	unfinishedNode->setVisible(false);
	nodeZeng->setVisible(false);
	isElongate = false;
}

void MyMenuItemUpgrade::initItem()
{


	nodeZeng = Node::create();
	nodeZeng->setPosition(11,0);
	unfinishedNode = Node::create();
	unfinishedNode->setPosition(11, 0);
	addChild(unfinishedNode,1);
	addChild(nodeZeng,1);
	commonNode = Node::create();
	commonNode->setPosition(11, 0);
	addChild(commonNode,1);
	nodeZeng->setVisible(false);
	unfinishedNode->setVisible(false);
	auto size = getContentSize();
	auto unLockTxt = Sprite::create("clickLockTXT.png");
	unLockTxt->setPosition(size.width*0.41-3, 38);
	commonNode->addChild(unLockTxt);
	auto mutpleLabel = LabelAtlas::create("0", "unLockNumTTF.png", 13, 19, '0');
	mutpleLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	mutpleLabel->setPosition(size.width*0.440+2,55);
	commonNode->addChild(mutpleLabel, 1, kTagMutpleLabel);

	//已经满足条件
	auto zeng = Sprite::create("zeng.png");
	zeng->setPosition(size.width*0.14+3, size.height*0.29);
	nodeZeng->addChild(zeng, 1);
	auto coinNum = LabelAtlas::create("", "bonusNumTTF.png", 14, 21, '0');
	coinNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
	coinNum->setPosition(size.width*0.28+23, size.height*0.29+1.5);
	nodeZeng->addChild(coinNum, 1,kTagCoinLabel);
	auto coin = Sprite::create("smallCoin.png");
	coin->setPosition(size.width*0.6, size.height*0.29+1.5);
	nodeZeng->addChild(coin);
	//不满足条件
	auto diamond = Sprite::create("smallDiamond.png");
	diamond->setPosition(size.width*0.15+2, size.height*0.29+1.5);
	unfinishedNode->addChild(diamond);
	//经验条
	auto exeBarFrame = Sprite::create("exeBarFrameDiamond.png");
	exeBarFrame->setPosition(size.width*0.40+10, size.height*0.29+1.5);
	unfinishedNode->addChild(exeBarFrame,1,"exeFrame");
	auto exeBar = Sprite::create("exeBarDiamond.png");
	exeBar->setPosition(0+2,exeBarFrame->getContentSize().height/2);
	exeBar->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	exeBarFrame->addChild(exeBar,1,kTagExeBar);

	auto exeDec = LabelAtlas::create("0", "bonusNumTTF.png", 14, 21, '0');
	exeDec->setScale(0.8);
	exeDec->setAnchorPoint(Point::ANCHOR_MIDDLE);
	exeDec->setPosition(exeBarFrame->getContentSize() / 2);
	exeBarFrame->addChild(exeDec,1,kTagExeDec);

	isElongate = false;
	commonNode->setVisible(false);
	unfinishedNode->setVisible(false);
	nodeZeng->setVisible(false);
}

void MyMenuItemUpgrade::setValue()
{

	commonNode->setVisible(true);
	auto maxlevel = User::getInstance()->getMaxTurrentLevel();
	auto turretData = ConfigTurrent::getInstance()->getNextTurrent(maxlevel);	
	auto zengList = turretData.rewardList;
	auto diamondNum = User::getInstance()->getDiamonds();
	isFinish = diamondNum >= turretData.unlockPrice ? true : false;
	auto str = String::createWithFormat("%d:%d", diamondNum, turretData.unlockPrice);
	auto scalex = ((float)diamondNum)/((float)turretData.unlockPrice);
	int coinnum;
	for (auto zeng : zengList)
	{
		if (zeng.itemId == 1001)
		{
			coinnum = zeng.num;
			break;
		}
	}

	auto node = (LabelAtlas*)commonNode->getChildByTag(kTagMutpleLabel);
	node->setString(Value(turretData.multiple).asString().c_str());
	if (isFinish)
	{
		nodeZeng->setVisible(true);
		node = (LabelAtlas*)nodeZeng->getChildByTag(kTagCoinLabel);
		node->setString(Value(coinnum).asString().c_str());
		showBlinkAni();
	}
	else
	{
		unfinishedNode->setVisible(true);
		auto frame = unfinishedNode->getChildByName("exeFrame");
		node = (LabelAtlas*)frame->getChildByTag(kTagExeDec);
		node->setString(str->getCString());

		auto node1 = frame->getChildByTag(kTagExeBar);
		((Sprite*)node1)->setTextureRect(Rect(0, 0, scalex * 93, 20));
	}
}

void MyMenuItemUpgrade::showBlinkAni()
{
	removeBlinkAni();
	auto node = Sprite::create("UnlockFrame_2.png");
	node->setPosition(getContentSize() / 2);
	addChild(node, 0, "blinkAni");
	node->runAction(RepeatForever::create(Sequence::create(FadeOut::create(0.25f), FadeIn::create(0.25f), nullptr)));
}
void MyMenuItemUpgrade::showPopup()
{
	if (User::getInstance()->getMaxTurrentLevel() >= 1000)
	{
		removeBlinkAni();
		return;
	}
	if (isElongate == true)
	{
		return;
	}
	else
	{
		isElongate = true;
		setValue();
		setEnabled(false);
		runAction(Sequence::create(MoveBy::create(0.5f, Vec2(-177, 0)), CallFunc::create([=]{setEnabled(true); }),nullptr));

		if (isFinish)
		{
			showBlinkAni();
		}
		else
		{
			runAction(Sequence::create(DelayTime::create(4.0f), CallFunc::create([&]{
				if (isElongate == true)
				{
					auto pNode = getChildByName("blinkAni");
					if (pNode)
					{
						pNode->removeFromParentAndCleanup(1);
					}
					commonNode->setVisible(false);
					unfinishedNode->setVisible(false);
					nodeZeng->setVisible(false);
					setEnabled(false);
					runAction(Sequence::create(MoveBy::create(0.5f, Vec2(177, 0)), CallFunc::create([=]{setEnabled(true); }), nullptr));
					isElongate = false;
				};

			}), nullptr));
		}
	}
	
}


void MyMenuItemUpgrade::removeBlinkAni()
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