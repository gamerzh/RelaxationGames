#include "showTurretCell.h"
#include "utill/Chinese.h"
#include "config/ConfigTurrent.h"
#include "domain/user/User.h"
#include "lobby/shop/payLayer.h"
#include "domain/logevent/LogEventPageChange.h"
#include "lobby/viplayer/VipLayer.h"
#include "domain/game/GameManage.h"
#include "domain/logevent/LogEventTurrentUpgrade.h"
#include "domain/bag/BagManager.h"
bool showTurretCell::init(){

	setAnchorPoint(Point::ANCHOR_MIDDLE);


	bg = Sprite::create();
	bg->setPosition(88, 121.5);
	bg->setContentSize(Size(176, 243));
	addChild(bg);
	auto size = bg->getContentSize();

	propSprite = Sprite::create();
	propSprite->setPosition(size.width / 2, size.height / 2 - 20);
	addChild(propSprite);

	auto bottom = Sprite::create("VIPbottomFrame.png");
	bottom->setPosition(0, 0);
	bottom->setAnchorPoint(Point::ZERO);
	addChild(bottom,0,"bottom");

	

	ShowPaoshade = Sprite::create("ShowPaoshade.png");
	ShowPaoshade->setPosition(size/2);
	addChild(ShowPaoshade);
	ShowPaoshade->setVisible(false);

	
	
	muptleTTF = LabelAtlas::create("0", "multipleNum.png", 15, 21, '0');
	muptleTTF->setAnchorPoint(Point::ANCHOR_MIDDLE);
	muptleTTF->setPosition(size.width*0.52, size.height*0.9+3);
	addChild(muptleTTF);
	muptleTTF->setVisible(false);



	button = MenuItemImage::create();
	button->setContentSize(Size(161, 74));
	button->setPosition(size.width / 2, size.height*0.18-5);
	button->setCallback(CC_CALLBACK_1(showTurretCell::ButtonCallback,this));
	auto diamondNumTTF = LabelAtlas::create("0", "unLockNumTTF.png", 13, 19, '0');
	diamondNumTTF->setPosition(Point::ANCHOR_MIDDLE);
	diamondNumTTF->setPosition(button->getContentSize()/2+Size(0,-2));
	diamondNumTTF->setVisible(false);
	button->addChild(diamondNumTTF,1,10);

	auto menu = Menu::create(button, nullptr);
	menu->setPosition(0, 0);
	addChild(menu);


	showVipPaoName = Sprite::create();
	showVipPaoName->setPosition(size.width / 2, size.height*0.95-30);
	addChild(showVipPaoName);
	showVipPaoName->setVisible(false);


	ShowPaolight = Sprite::create("ShowPaolight.png");
	ShowPaolight->setPosition(size / 2);
	addChild(ShowPaolight);
	ShowPaolight->setVisible(false);


	lock = Sprite::create("smalllock.png");
	lock->setPosition(Vec2(77,86));
	propSprite->addChild(lock);
	lock->setVisible(false);

	lockTTf = Sprite::create("locksuccessTTf.png");
	lockTTf->setPosition(button->getPosition());
	addChild(lockTTf);
	lockTTf->setVisible(false);

	SendCoin = Sprite::create("sendCoin.png");
	SendCoin->setPosition(size.width / 2, 99);
	addChild(SendCoin);
	SendCoin->setVisible(false);

	zengCoinTTf = LabelAtlas::create("0", "unLockNumTTF.png", 13, 19, '0');
	zengCoinTTf->setAnchorPoint(Point::ANCHOR_MIDDLE);
	zengCoinTTf->setPosition(size.width/2,99);
	zengCoinTTf->setVisible(false);
	addChild(zengCoinTTf);
	quex3 = Sprite::create("quex3.png");
	quex3->setPosition(zengCoinTTf->getPosition());
	addChild(quex3);
	quex3->setVisible(false);


	quexprice3 = Sprite::create("quex3.png");
	quexprice3->setPosition(button->getContentSize()/2+Size(8,3));
	button->addChild(quexprice3,1);
	quexprice3->setVisible(false);
	return true;
}



void showTurretCell::setMultipleValue(int index)
{
	getChildByName("bottom")->setVisible(false);
	auto size = bg->getContentSize();
	propSprite->setPosition(size.width / 2, size.height / 2 +20);

	m_type = 2;
	button->setScale(0.9);
	//setScale(0.9);
	
	bg->setTexture("ShowPaobg.png");
	auto maxlevl = User::getInstance()->getMaxTurrentLevel();
	auto turret = ConfigTurrent::getInstance()->getTurrentByIndex(index);
	auto nowIndex = ConfigTurrent::getInstance()->getIndexByMaxlv(maxlevl);
	muptleTTF->setString(Value(turret.multiple).asString().c_str());
	muptleTTF->setVisible(true);
	button->setNormalSpriteFrame(SpriteFrame::create("btn_big_1.png",Rect(0,0,161,74)));
	button->setSelectedSpriteFrame(SpriteFrame::create("btn_big_2.png", Rect(0, 0, 161, 74)));
	auto diamondNumTTF = (LabelAtlas*)button->getChildByTag(10);
	diamondNumTTF->setVisible(true);
	diamondNumTTF->setString(Value(turret.unlockPrice).asString().c_str());
	ShowPaolight->setVisible(false);


	ShowPaolight->setVisible(false);
	if (nowIndex>=index) //已解锁
	{
		lock->setVisible(false);
		button->setVisible(false);
		lockTTf->setVisible(true);
		ShowPaoshade->setVisible(false);
		
		quexprice3->setVisible(false); 
		zengCoinTTf->setVisible(false);
		SendCoin->setVisible(false);
		quex3->setVisible(false);
	}
	else if ((nowIndex+1) == index)//下一级
	{
		quexprice3->setVisible(false);
		diamondNumTTF->setVisible(true);
		lock->setVisible(true);
		button->setVisible(true);
		button->setEnabled(true);
		lockTTf->setVisible(false);
		ShowPaoshade->setVisible(false);
		ShowPaolight->setVisible(true);

		SendCoin->setVisible(true);
		zengCoinTTf->setVisible(true);
		zengCoinTTf->setString(Value(turret.rewardList.at(0).num).asString());
		quex3->setVisible(false);
	}
	else//未解锁
	{
		quexprice3->setVisible(true);
		diamondNumTTF->setVisible(false);	
		lock->setVisible(true);
		button->setVisible(true);
		button->setEnabled(false);
		lockTTf->setVisible(false);
		ShowPaoshade->setVisible(true);
		ShowPaolight->setVisible(false);

		SendCoin->setVisible(true);
	
		zengCoinTTf->setVisible(false);
		quex3->setVisible(true);
		if (nowIndex<(index-3))
		{
			
		}
		
	}
	if (turret.multiple>30)
	{
		propSprite->setTexture("pao_2.png");
	}
	else
	{
		propSprite->setTexture("pao_1.png");
	}
}
void showTurretCell::setVippaoValue(int index)
{
	m_type = 1;
	auto viplv = User::getInstance()->getVipLevel();
	bg->setTexture("VIPFrame.png");
	
	showVipPaoName->setVisible(true);
	auto path = String::createWithFormat("VIPname_%d.png", index);
	showVipPaoName->setTexture(path->getCString());

	button->setNormalSpriteFrame(SpriteFrame::create("btn_huoqu_1.png", Rect(0, 0, 161, 74)));
	button->setSelectedSpriteFrame(SpriteFrame::create("btn_huoqu_2.png", Rect(0, 0, 161, 74)));
	path = String::createWithFormat("pao_%d.png", index+2);
	propSprite->setTexture(path->getCString());
	setAnchorPoint(Point::ANCHOR_MIDDLE);	
	button->setScale(0.9);
	setScale(0.9);
	

	if (index>viplv)
	{
		button->setVisible(true);
		lockTTf->setVisible(false);
		lock->setVisible(true);
		ShowPaoshade->setVisible(true);
	}
	else
	{
		button->setVisible(false);
		lockTTf->setVisible(true);
		lock->setVisible(false); 
		ShowPaoshade->setVisible(false);
	}
	if (index == (viplv+1))
	{
		ShowPaoshade->setVisible(false);
		ShowPaolight->setVisible(true);
	}
	else
	{
		ShowPaolight->setVisible(false);
	
	}
}


void showTurretCell::IsBeToued()
{

}




void showTurretCell::ButtonCallback(Ref* psend)
{

	if (m_type == 1)
	{
		///VIP充值	
		auto layer = VIPLayer::create();
		layer->setPosition(0, 0);
		GameManage::getInstance()->getGuiLayer()->addChild(layer, 20);
		GameManage::getInstance()->getGuiLayer()->getChildByTag(50)->removeFromParentAndCleanup(1);
		LogEventPageChange::getInstance()->addEventItems(2, 7, 0);
	}
	else
	{
		auto maxlevel = User::getInstance()->getMaxTurrentLevel();
		auto turretData = ConfigTurrent::getInstance()->getNextTurrent(maxlevel);
		auto zengList = turretData.rewardList;
		auto diamondNum = User::getInstance()->getDiamonds();
		bool isFinish = diamondNum >= turretData.unlockPrice ? true : false;
		if (isFinish)
		{
			GameManage::getInstance()->getGameLayer()->GetMyTurret()->onLockTheTurrent();
			Director::getInstance()->getRunningScene()->getChildByTag(888)->getChildByTag(50)->removeFromParentAndCleanup(1);
		}
		else
		{
			auto layer = payLayer::createLayer(2);
			layer->setPosition(0, 0);
			layer->setEventPont(12);
			Director::getInstance()->getRunningScene()->getChildByTag(888)->addChild(layer, 20);
			Director::getInstance()->getRunningScene()->getChildByTag(888)->getChildByTag(50)->removeFromParentAndCleanup(1);
			LogEventPageChange::getInstance()->addEventItems(2, 13, 5);
		}
	}

}