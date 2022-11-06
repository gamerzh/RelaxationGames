#include "NotarizeExitDialog.h"
#include "lobby/LobbyScene.h"
#include  "domain/bankrupt/BankruptManager.h"
#include "domain/logevent/LogEventPageChange.h"
#include "data/GameData.h"
#include "domain/logevent/LogEventMannger.h"
#include "utill/FunUtil.h"
bool NotarizeExitDialog::init()
{
	Layer::init();
	bool bRet = false;
	do
	{  
		auto colorLayer = LayerColor::create();
		colorLayer->setColor(ccc3(0, 0, 0));
		colorLayer->setOpacity(180);
		colorLayer->setPosition(0, 0);
		addChild(colorLayer, -1);
		auto bg = Sprite::create("TwiceSureDialog.png");
		bg->setPosition(480, 270);
		addChild(bg, 1, "bg");

		auto size = Director::getInstance()->getVisibleSize();  
	/*	auto sp = Sprite::create("tuichuyouxiTXT.png");
		sp->setPosition(size.width / 2, 405);
		bg->addChild(sp);*/
		auto sp = Sprite::create("likaiyouxiTXT.png");
		sp->setPosition(bg->getContentSize().width/2,bg->getContentSize().height*0.6);
		bg->addChild(sp);
		sp->setScale(0.85);
		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(NotarizeExitDialog::closeButtonCallBack, this));
		close->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
		close->setPosition(bg->getContentSize() + Size(10, 10));


		auto sure = MenuItemImage::create("btn_queding.png", "btn_queding_2.png", CC_CALLBACK_1(NotarizeExitDialog::querenCallback, this));
		sure->setPosition(bg->getContentSize().width / 2, 48);
	
		auto menu = Menu::create(close, sure, nullptr);
		menu->setPosition(0, 0);
		bg->addChild(menu);
		



		auto listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = CC_CALLBACK_2(NotarizeExitDialog::onTouchBegan, this);
		listenr1->setSwallowTouches(true);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);

		//添加系统返回键监听
		auto listener = EventListenerKeyboard::create();
		listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
			switch (code)
			{
			case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
				break;
			default:
				break;
			}
		};
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
		/////////弹出动画
		bg->setScale(0);
		bg->runAction(Sequence::create(ScaleTo::create(0.2f, 1.0f), ScaleTo::create(0.07f, 0.8f), ScaleTo::create(0.07f, 1.0f), nullptr));
		showRandonBubbleAni();
		bRet = true;
	} while (0);


	return bRet;
}
void NotarizeExitDialog::querenCallback(Ref*psend)
{
	auto node = BankruptManager::getInstance()->getgetRewardNode();
	if (node)
	{
		node->retain();
		node->removeFromParentAndCleanup(false);
	
	}
	LogEventPageChange::getInstance()->addEventItems(2, 1, 0);
	Director::getInstance()->replaceScene(LobbyScene::createScene());
	GameData::getInstance()->setisOnGameScene(false);
}


void NotarizeExitDialog::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}

void NotarizeExitDialog::showRandonBubbleAni()
{
	auto node = getChildByName("bg");

	auto aniNode = Sprite::create();
	aniNode->setPosition(20, 100);
	node->addChild(aniNode, 5);
	aniNode->runAction(getForeverAcByNameAndInterval("aniBubble", 0));

	aniNode = Sprite::create();
	aniNode->setPosition(node->getContentSize().width - 20, 100);
	node->addChild(aniNode, 5);
	aniNode->runAction(getForeverAcByNameAndInterval("aniBubble", 0));

}