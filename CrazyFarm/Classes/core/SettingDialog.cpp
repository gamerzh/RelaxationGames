#include "SettingDialog.h"

bool SettingDialog::init()
{
	MyDialog::init();
	bool bRet = false;
	do
	{  
		auto size = Director::getInstance()->getVisibleSize();  
		auto sp = Sprite::create("youxishezhiTXT.png");
		sp->setPosition(size.width / 2, 405);
		addChild(sp);
		sp = Sprite::create("beijingyinyueTXT.png");
		sp->setPosition(308, 332);
		addChild(sp);
		sp = Sprite::create("youxiyinxiaoTXT.png");
		sp->setPosition(308, 220);
		addChild(sp);
		//ÒôÀÖ
		Slider* slider = Slider::create();
		slider->loadBarTexture("audioFrame.png");
		slider->loadSlidBallTextures("slider2.png", "slider2.png", "");
		slider->loadProgressBarTexture("audioBar.png");
		slider->setPosition(Vec2(540,332));
		slider->setTag(1);
		slider->addEventListener(CC_CALLBACK_2(SettingDialog::sliderEvent, this));
		addChild(slider);
		slider->setPercent(Audio::getInstance()->getBgmPercent() * 70.0+15.0);


		//ÒôÐ§
		slider = Slider::create();
		slider->loadBarTexture("audioFrame.png");
		slider->loadSlidBallTextures("slider1.png", "slider1.png", "");
		slider->loadProgressBarTexture("audioBar.png");
		slider->setPosition(Vec2(540, 220));
		slider->setTag(2);
		slider->addEventListener(CC_CALLBACK_2(SettingDialog::sliderEvent, this));
		addChild(slider);
		slider->setPercent(Audio::getInstance()->getSoundPercent() * 70.0+15.0);
		//slider->setCapInsetProgressBarRebderer()

		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(SettingDialog::closeButtonCallBack, this));
		close->setPosition(736, 405);
		auto menu = Menu::create(close, nullptr);
		menu->setPosition(Point::ZERO);
		addChild(menu);
		bRet = true;
	} while (0);


	return bRet;
}
void SettingDialog::lingquCallback(Ref*psend)
{
	//auto vec = NobilityManager::getInstance()->getNobilityRewadItems();
	//for (auto var:vec)
	//{
	//	if (var.item_id == 1001)
	//	{
	//		User::getInstance()->addCoins(var.num);
	//	}
	//	if (var.item_id == 1002)
	//	{
	//		User::getInstance()->addDiamonds(var.num);
	//	}
	//	BagManager::getInstance()->changeItemCount(var.item_id, var.num);

	//}
	removeFromParentAndCleanup(1);
}

void SettingDialog::sliderEvent(Ref *pSender, Slider::EventType type)
{
	if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		
		Slider* slider = dynamic_cast<Slider*>(pSender);
		auto  percent = (float)slider->getPercent();
		if (percent <= 15.0)
		{
			slider->setPercent(15.0);
			percent = 15.0;
		}
		else if (percent>=85.0)
		{
			slider->setPercent(85.0);
			percent = 85.0;

		}
		float curValue = (percent-15.0) / 70.0;
		int tag = slider->getTag();
		if (tag==1)
		{
			Audio::getInstance()->setBGMValue(curValue);
		}
		else
		{
			Audio::getInstance()->setEffectValue(curValue);
		}
        
	}
}
void SettingDialog::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}