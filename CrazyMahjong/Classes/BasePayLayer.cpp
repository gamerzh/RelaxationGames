#include "BasePayLayer.h"
#include "PxPayMannger.h"
#include "Jniutill.h"
BasePayLayer* BasePayLayer::create(PAYPOINT paypoint)
{
	BasePayLayer *pRet = new(std::nothrow) BasePayLayer();
	if (pRet && pRet->init(paypoint))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}
bool BasePayLayer::init(PAYPOINT paypoint)
{
	if (!Layer::init())
	{
		return false;
	}
	auto VisibleSize = Director::getInstance()->getVisibleSize();
	_paypoint =paypoint;
	LayerColor* layerColor = LayerColor::create();
	layerColor->setColor(ccc3(0, 0, 0));
	layerColor->setOpacity(153);
	layerColor->setContentSize(Size(800, 480));
	addChild(layerColor);

	auto str = String::createWithFormat("pui/PayUI_%d.png",(int)paypoint);
	auto bg = Sprite::create(str->getCString());
	bg->setPosition(VisibleSize / 2);
	addChild(bg);

	auto button = Button::create("pui/x1.png", "pui/x2.png");
	button->setPosition(Vec2(668,381));
	button->setAnchorPoint(Point(1, 1));
	button->addTouchEventListener(this,toucheventselector(BasePayLayer::quxiaoButton));
	addChild(button);

	button = Button::create("pui/Btn_lingqu_1.png", "pui/Btn_lingqu_2.png");
	button->setPosition(Vec2(bg->getContentSize() / 2) + bg->getPosition());
	button->addTouchEventListener(this,toucheventselector(BasePayLayer::quedingButton));
	addChild(button);
	switch (paypoint)
	{
	case FIRSTPAYGFIT:
		button->setPosition(Vec2(444, 200));
		break;
	case VIPGIFT:
		button->setPosition(Vec2(400, 89));
		break;
	case COINGIFT:
		button->setPosition(Vec2(328, 200));
		break;
	default:
		break;
	}


	//´¥ÃþÆÁ±Î
	auto listenr1 = EventListenerTouchOneByOne::create();
	listenr1->onTouchBegan = [=](Touch*touch, Event*event){return true; };
	listenr1->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);

	auto listern2 = EventListenerKeyboard::create();
	listern2->onKeyReleased = [=](EventKeyboard::KeyCode  keyCode, Event *event)
	{
		event->stopPropagation();		
		if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
		{
			quxiaoButton(this, TouchEventType::TOUCH_EVENT_ENDED);

		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listern2, this);
	return true;
}



void BasePayLayer::quedingButton(Ref* pSender, TouchEventType type)
{
	if (type == TouchEventType::TOUCH_EVENT_ENDED)
    {
		PxPayMannger::getInstance()->doWxPay(_paypoint, getPayCallBack());
		removeFromParentAndCleanup(1);
    }
	
}
void BasePayLayer::quxiaoButton(Ref* pSender, TouchEventType type)
{
	if (type == TouchEventType::TOUCH_EVENT_ENDED)
	{
		Jniutill::getInstance()->logEventShowPayPanel(_paypoint, 3);
		removeFromParentAndCleanup(1);
	}
	
}
