#include "NobilityLayer.h"
#include "domain/nobility/NobilityManager.h"
#include "domain/pay/Pay.h"
#include "data/GameData.h"
bool NobilityLayer::init()
{
	if (!BaseLayer::init()){
		return false;
	}	

	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	
	auto bg = Sprite::create("NobilityBG.png");
	bg->setPosition(visibleSize / 2 );
	addChild(bg);


	auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(NobilityLayer::closeButtonCallBack, this));
	close->setPosition(bg->getContentSize()-Size(5,60));

	auto remainingDay = NobilityManager::getInstance()->RemainingNobilityday();
	dayTTF = LabelAtlas::create(Value(remainingDay).asString(), "NobilitydayNum.png", 19, 29, '0');
	dayTTF->setPosition(visibleSize.width*0.49+5, visibleSize.height*0.19);
	addChild(dayTTF);

	int imgIndex = NobilityManager::getInstance()->isNobility() ? 2 : 1;
	auto str1 = String::createWithFormat("payNobilitylayer_%d_%d.png", imgIndex, 1);
	auto str2 = String::createWithFormat("payNobilitylayer_%d_%d.png", imgIndex, 2);
	quickpay = MenuItemImage::create(str1->getCString(), str2->getCString(), CC_CALLBACK_1(NobilityLayer::quickPayCallback, this));
	quickpay->setPosition(bg->getContentSize().width *0.85, bg->getContentSize().height*0.15);
	auto menu = Menu::create(quickpay, close, nullptr);
	menu->setPosition(0, 0);
	bg->addChild(menu);



	auto listenr1 = EventListenerTouchOneByOne::create();
	listenr1->onTouchBegan = CC_CALLBACK_2(NobilityLayer::onTouchBegan, this);
	listenr1->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);



	return true;

}
NobilityLayer * NobilityLayer::createLayer()
{
	NobilityLayer *ret = new  NobilityLayer();
	if (ret && ret->init())
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

void NobilityLayer::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}

void NobilityLayer::quickPayCallback(Ref* psend)
{
	if (lastTouchTime == 0)
	{

	}
	else
	{
		auto nowTime = getCurrentTime();
		if (nowTime - lastTouchTime < 1000)
		{
			return;
		}
	}
	lastTouchTime = getCurrentTime();

	log("touch pay");
	Pay::getInstance()->Overbooking(13, m_eventPoint,this);
	schedule(schedule_selector(NobilityLayer::updata), 1.0f, kRepeatForever, 0);
}

void NobilityLayer::updata(float dt){
	dayTTF->setString(cocos2d::String::createWithFormat("%d", NobilityManager::getInstance()->RemainingNobilityday())->getCString());
	int imgIndex = NobilityManager::getInstance()->isNobility() ? 2 : 1;
	auto str1 = String::createWithFormat("payNobilitylayer_%d_%d.png", imgIndex, 1);
	auto str2 = String::createWithFormat("payNobilitylayer_%d_%d.png", imgIndex, 2);
	quickpay->setNormalImage(Sprite::create(str1->getCString()));
	quickpay->setSelectedImage(Sprite::create(str1->getCString()));
}