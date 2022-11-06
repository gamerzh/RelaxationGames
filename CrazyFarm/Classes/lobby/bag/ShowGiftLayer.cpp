#include "lobby/bag/ShowGiftLayer.h"
#include "domain/user/User.h"
#include "lobby/bag/BagCell.h"
#include "domain/bag/BagManager.h"
#include "utill/FunUtil.h"
#include "domain/skill/skillManager.h"
#include "lobby/viplayer/VipLayer.h"

ShowGiftLayer*ShowGiftLayer::create()
{
	ShowGiftLayer *pRet = new ShowGiftLayer();
	if (pRet && pRet->init())
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

bool ShowGiftLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	bool bRet = false;
	do 
	{
		auto layer = LayerColor::create();
		layer->setColor(Color3B::BLACK);
		layer->setOpacity(128);
		addChild(layer,-1);
		auto size = Director::getInstance()->getVisibleSize();
		auto bg = Sprite::create("showItemBg.png");
		bg->setPosition(size / 2);
		addChild(bg);


		BagItem item;
		item.itemId = 1012;
		item.num = 1;
		item.type = Prop_upgradeBox;
		auto cell = BagCell::create();
		cell->setValue(item);
		cell->setPosition(480, 373);
		addChild(cell);
		
		Iitem = ConfigItem::getInstance()->getItemById(1012);
		auto str = String::createWithFormat(Iitem.itemName.c_str(), User::getInstance()->getLevelData().levelId + 1);
		auto label = LabelTTF::create(str->getCString(), "arial", 20);
		label->setPosition(480, 298);
		label->setAnchorPoint(Point::ANCHOR_MIDDLE);
		addChild(label);


		label = LabelTTF::create(ChineseWord("jiangliwupin").c_str(), "arail", 18);
		label->setColor(Color3B::YELLOW);
		label->setPosition(480, 246);
		label->setAnchorPoint(Point::ANCHOR_MIDDLE);
		addChild(label);


		//奖励列表
		float startX = 57;
		float startY = 142;
		float diffx = 78;

		auto rewards = ConfigExp::getInstance()->getLevelRewardItemsByLevelId(User::getInstance()->getLevelData().levelId + 1);
		for (int i = 0; i < rewards.size();i++)
		{
			auto cell = GiftCell::create(rewards[i].item_id, rewards[i].num);
			cell->setPosition(startX + diffx*i, startY);
			cell->setScale(0.7);
			bg->addChild(cell);
		}
		auto cell0 = GiftCell::create(1012, User::getInstance()->getLevelData().levelId + 2);
		cell0->setPosition(startX + diffx * 3, startY);
		cell0->setScale(0.7);
		bg->addChild(cell0);
		
		auto BtBuy = MenuItemImage::create("btn_zhidao_1.png", "btn_zhidao_2.png", CC_CALLBACK_1(ShowGiftLayer::quedingcallback, this));
		BtBuy->setPosition(480,80);
		
		

		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(ShowGiftLayer::closeButtonCallBack, this));
		close->setPosition(644,470);



		auto menu = Menu::create(BtBuy, close, nullptr);
		menu->setPosition(0, 0);
		addChild(menu);

		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->setSwallowTouches(true);
		touchListener->onTouchBegan = CC_CALLBACK_2(ShowGiftLayer::onTouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(ShowGiftLayer::onTouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(ShowGiftLayer::onTouchEnded, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
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
bool ShowGiftLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}

void ShowGiftLayer::quedingcallback(Ref*)
{
	removeFromParentAndCleanup(1);
}

void ShowGiftLayer::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}

