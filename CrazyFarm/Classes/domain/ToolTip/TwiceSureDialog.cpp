#include "TwiceSureDialog.h"
#include "utill/AnimationUtil.h"
#include "utill/FunUtil.h"
TwiceSureDialog* TwiceSureDialog::createDialog(const char* tipStr, const ccMenuCallback& callback)
{
	TwiceSureDialog* ref = new TwiceSureDialog();
	if (ref&&ref->init(tipStr,callback))
	{
		ref->autorelease();
	}
	else
	{
		ref = nullptr;
	}
	return ref;
}

void TwiceSureDialog::setCloseButtonCallback(const ccMenuCallback& closecallback)
{
	close->setCallback(closecallback);
}

bool TwiceSureDialog::init(const  char* tipStr, const ccMenuCallback& callback)
{
	Layer::init();
	bool bRet = false;
	do
	{

		colorLayer = LayerColor::create();
		colorLayer->setColor(ccc3(0, 0, 0));
		colorLayer->setOpacity(180);
		colorLayer->setPosition(0, 0);
		addChild(colorLayer, -1);
		auto bg = Sprite::create("TwiceSureDialog.png");
		bg->setPosition(480, 270);
		addChild(bg, 1,"bg");

		close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(TwiceSureDialog::closeButtonCallBack, this));
		close->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
		close->setPosition(bg->getContentSize()+Size(10,10));
		
		
		sure = MenuItemImage::create("btn_queding.png", "btn_queding_2.png");
		sure->setPosition(bg->getContentSize().width / 2, 48);
		if (callback)
		{
			sure->setCallback(callback);
		}
		else
		{
			sure->setCallback(CC_CALLBACK_1(TwiceSureDialog::closeButtonCallBack, this));
		}
		auto menu = Menu::create(close, sure, nullptr);
		menu->setPosition(0,0);
		bg->addChild(menu);


		auto label = LabelTTF::create(tipStr, "arial", 20);
		label->setColor(Color3B(12, 64, 109));
		label->setAnchorPoint(Point::ANCHOR_MIDDLE);
		label->setDimensions(Size(261, 0));
		label->setPosition(bg->getContentSize().width / 2, 165);
			bg->addChild(label);

		auto listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = CC_CALLBACK_2(TwiceSureDialog::onTouchBegan, this);
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

void TwiceSureDialog::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}

void TwiceSureDialog::showRandonBubbleAni()
{
	auto node = getChildByName("bg");

	auto aniNode = Sprite::create();
	aniNode->setPosition(20,100);
	node->addChild(aniNode, 5);
	aniNode->runAction(getForeverAcByNameAndInterval("aniBubble",0));

	aniNode = Sprite::create();
	aniNode->setPosition(node->getContentSize().width-20, 100);
	node->addChild(aniNode, 5);
	runAction(Sequence::create(DelayTime::create(0.1f), CallFunc::create([=]{aniNode->runAction(getForeverAcByNameAndInterval("aniBubble", 0)); }), nullptr));
	
}