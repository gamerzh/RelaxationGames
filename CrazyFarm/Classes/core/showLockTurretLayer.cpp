#include "showLockTurretLayer.h"
#include "widget/MyTableView.h"
#include "showTurretCell.h"
#include "config/ConfigVipTurrent.h"
#include "lobby/shop/payLayer.h"
#include "domain/user/User.h"
#include "domain/game/GameManage.h"
#include "config/ConfigTurrent.h"
#include "domain/logevent/LogEventPageChange.h"



bool showLockTurretLayer::init()
{
	bool bRet = false;
	do 
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		auto colorlayer = LayerColor::create();
		colorlayer->setColor(ccc3(0, 0, 0));
		colorlayer->setOpacity(180);
		addChild(colorlayer, -1);
		auto bg1 = Sprite::create("lockPao.png");
		bg1->setPosition(visibleSize / 2);
		addChild(bg1);

		auto viewdata = ConfigTurrent::getInstance()->getCurrentShowTurrentIndexs();
		for (int i = 0; i < viewdata.size();i++)
		{

			auto turret = ConfigTurrent::getInstance()->getTurrentByIndex(viewdata[i]);
			auto bg = Sprite::create("ShowPaobg.png");
			bg->setPosition(100+168.5*i, bg1->getContentSize().height*0.45);
			bg1->addChild(bg);
			auto size = bg->getContentSize();
			auto propSprite = Sprite::create();
			propSprite->setPosition(size.width / 2, size.height / 2 + 20);
			bg->addChild(propSprite);
			if (turret.multiple > 30)
			{
				propSprite->setTexture("pao_2.png");
			}
			else
			{
				propSprite->setTexture("pao_1.png");
			}
			
			auto ShowPaoshade = Sprite::create("ShowPaoshade.png");
			ShowPaoshade->setPosition(size / 2);
			bg->addChild(ShowPaoshade);
			ShowPaoshade->setVisible(false);



			auto muptleTTF = LabelAtlas::create(Value(turret.multiple).asString(), "multipleNum.png", 15, 21, '0');
			muptleTTF->setAnchorPoint(Point::ANCHOR_MIDDLE);
			muptleTTF->setPosition(size.width*0.51, size.height*0.9 + 3);
			bg->addChild(muptleTTF);



			auto button = MenuItemImage::create("btn_big_1.png", "btn_big_2.png", CC_CALLBACK_1(showLockTurretLayer::ButtonCallback, this));
			button->setPosition(size.width / 2, size.height*0.18 - 5);
			auto diamondNumTTF = LabelAtlas::create("0", "multipleNum.png", 15, 21, '0');
			diamondNumTTF->setAnchorPoint(Point::ANCHOR_MIDDLE);
			diamondNumTTF->setPosition(button->getContentSize() / 2 +Size(0,2));
			button->addChild(diamondNumTTF, 1, 10);

			auto menu = Menu::create(button, nullptr);
			menu->setPosition(0, 0);
			bg->addChild(menu);

			auto ShowPaolight = Sprite::create("ShowPaolight.png");
			ShowPaolight->setPosition(size / 2);
			bg->addChild(ShowPaolight);

			auto lock = Sprite::create("smalllock.png");
			lock->setPosition(Vec2(77, 86));
			propSprite->addChild(lock);
		

			auto lockTTf = Sprite::create("locksuccessTTf.png");
			lockTTf->setPosition(button->getPosition());
			bg->addChild(lockTTf);
	

			auto SendCoin = Sprite::create("sendCoin.png");
			SendCoin->setPosition(size.width / 2, 90);
			bg->addChild(SendCoin);
		

			auto zengCoinTTf = LabelAtlas::create("0", "multipleNum.png", 15, 21, '0');
			zengCoinTTf->setAnchorPoint(Point::ANCHOR_MIDDLE);
			zengCoinTTf->setPosition(size.width / 2, 90);
			bg->addChild(zengCoinTTf);
			auto quex3 = Sprite::create("quex3.png");
			quex3->setPosition(zengCoinTTf->getPosition());
			bg->addChild(quex3);



			auto quexprice3 = Sprite::create("quex3.png");
			quexprice3->setPosition(button->getContentSize() / 2 + Size(8, 3));
			button->addChild(quexprice3, 1);
			

			auto maxlevl = User::getInstance()->getMaxTurrentLevel();
			auto nowIndex = ConfigTurrent::getInstance()->getIndexByMaxlv(maxlevl);
			
		
			diamondNumTTF->setString(Value(turret.unlockPrice).asString().c_str());
			ShowPaolight->setVisible(false);


			ShowPaolight->setVisible(false);
			if (nowIndex >= viewdata[i]) //已解锁
			{
				button->setScale(0.8);
				bg->setScale(0.8);
				lock->setVisible(false);
				button->setVisible(false);
				lockTTf->setVisible(true);
				ShowPaoshade->setVisible(false);

				quexprice3->setVisible(false);
				zengCoinTTf->setVisible(false);
				SendCoin->setVisible(false);
				quex3->setVisible(false);
			}
			else if ((nowIndex + 1) == viewdata[i])//下一级
			{
				button->setScale(1);
				bg->setScale(1);
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
				button->setScale(0.8);
				bg->setScale(0.8);
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
				if (nowIndex < (viewdata[i] - 3))
				{

				}

			}
		
		}
		

	


		auto listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = CC_CALLBACK_2(showLockTurretLayer::onTouchBegan, this);
		listenr1->setSwallowTouches(true);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);


		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(showLockTurretLayer::closeButtonCallBack, this));
		close->setPosition(890, 410);
		auto menu = Menu::create(close, nullptr);
		menu->setPosition(Point::ZERO);
		addChild(menu);


	//添加系统返回键监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
			removeFromParentAndCleanup(1);
			break;
		default:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
		bRet = true;
	} while (0);
	

	return bRet;
}

void showLockTurretLayer::closeButtonCallBack(Ref*psend)
{
	GameManage::getInstance()->getGameLayer()->GetMyTurret()->changeDataByBtnType();
	removeFromParentAndCleanup(1);
}

void showLockTurretLayer::chankanCallBack(Ref*pesend)
{

}
void showLockTurretLayer::ButtonCallback(Ref* psend)
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