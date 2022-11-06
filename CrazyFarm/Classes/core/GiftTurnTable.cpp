#include "GiftTurnTable.h"


GiftTurnTable* GiftTurnTable::create()
{
	GiftTurnTable *pRet = new GiftTurnTable();
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

bool GiftTurnTable::init()
{
	bool bRet = false;
	do 
	{	
		auto listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = CC_CALLBACK_2(GiftTurnTable::onTouchBegan, this);
		listenr1->setSwallowTouches(true);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);

		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(GiftTurnTable::closeButtonCallBack, this));
		close->setPosition(800, 480);
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

void GiftTurnTable::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}

