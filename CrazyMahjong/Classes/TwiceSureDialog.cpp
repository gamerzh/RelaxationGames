#include "TwiceSureDialog.h"

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
void TwiceSureDialog::setSureButtonCallback(const ccMenuCallback& surecallback)
{
	sure->setCallback(surecallback);
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
		auto bg = Sprite::create("bg_TipDialog.png");
		bg->setPosition(400, 240);
		addChild(bg, 1,"bg");

		close = MenuItemImage::create("SetSound/Close_0.png", "SetSound/Close_1.png", CC_CALLBACK_1(TwiceSureDialog::closeButtonCallBack, this));
		close->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
		close->setPosition(bg->getContentSize()+Size(0,-13));
		
		
		sure = MenuItemImage::create("Btn_queding_1.png", "btn_queding_2.png");
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
		label->setColor(Color3B(255, 252, 243));
		label->setAnchorPoint(Point::ANCHOR_MIDDLE);
		label->setDimensions(Size(261, 0));
		label->setPosition(bg->getContentSize().width / 2, 122);
			bg->addChild(label);

		auto listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = CC_CALLBACK_2(TwiceSureDialog::onTouchBegan, this);
		listenr1->setSwallowTouches(true);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);

	
		/////////µ¯³ö¶¯»­
		bg->setScale(0);
		bg->runAction(Sequence::create(ScaleTo::create(0.2f, 1.0f), ScaleTo::create(0.07f, 0.8f), ScaleTo::create(0.07f, 1.0f), nullptr));
		bRet = true;
	} while (0);


	return bRet;
}

void TwiceSureDialog::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}
