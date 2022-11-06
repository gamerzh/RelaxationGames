#include "UserSetting.h"
#include "Audio.h"
#include "GameRuleDialog.hpp"
#include "GameFeedDialog.hpp"
#include "RulePanel.h"

bool UserSetting::init(){
	if (!BaseDialog::init()){
		return false;
	}
	return true;
}

void UserSetting::drawDialog(){
    MenuItem* item1 = MenuItem::create();
    item1->setContentSize(Size(1280, 720));
    Menu* menu1 = Menu::create(item1, NULL);
    this->addChild(menu1);
        
    auto  dialogBg = Sprite::create("common/dialog_bg.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(UserSetting::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(980, 580);
    addChild(closeMenu);
    
    auto paodai = Sprite::create("common/piaodai_zi.png");
    paodai->setPosition(640, 590);
    this->addChild(paodai);
    auto titleIcon = Sprite::create("setting/settting_title.png");
    titleIcon->setPosition(640, 615);
    addChild(titleIcon);

    auto musicBg = Sprite::create("setting/setting_bg.png");
    musicBg->setPosition(640,380);
    addChild(musicBg);
    
    auto soudnText = Sprite::create("setting/sound.png");
    soudnText->setPosition(385,440);
    addChild(soudnText);

	// 滑动条
	Slider* slider = Slider::create();
	slider->loadBarTexture("setting/progress_1.png");
	slider->loadProgressBarTexture("setting/progress_2.png");
	slider->loadSlidBallTextures("setting/slide_btn_1.png", "setting/slide_btn_1.png");
	slider->addEventListenerSlider(this, sliderpercentchangedselector(UserSetting::slderEvent));
	this->addChild(slider);
	slider->setPosition(Vec2(720, 440));
	float curValue = Audio::getInstance()->getSoundValue() * 90 + 5;
	slider->setPercent(curValue);
    

	slider = Slider::create();
	slider->loadBarTexture("setting/progress_1.png");
	slider->loadProgressBarTexture("setting/progress_2.png");
	slider->loadSlidBallTextures("setting/slide_btn_1.png", "setting/slide_btn_1.png");
	slider->addEventListenerSlider(this, sliderpercentchangedselector(UserSetting::slderEvent));
	this->addChild(slider);
	slider->setPosition(Vec2(720, 345));
	curValue = Audio::getInstance()->getSoundValue() * 90+ 5;
	slider->setPercent(curValue);

   
    
    auto musicText = Sprite::create("setting/music.png");
    musicText->setPosition(385,342);
    addChild(musicText);
    
  
    
    auto helpImage = MenuItemImage::create("setting/game_help_btn_1.png","setting/game_help_btn_2.png",
                                           CC_CALLBACK_0(UserSetting::showGameHelp, this));
    auto feedImage = MenuItemImage::create("setting/feedback_btn_1.png","setting/feedback_btn_2.png",
                                           CC_CALLBACK_0(UserSetting::feedBack, this));
    
    Menu* myMneu = Menu::create(helpImage,feedImage,NULL);
    myMneu->setPosition(650,185);
    myMneu->alignItemsHorizontallyWithPadding(20);
    addChild(myMneu);

}



void UserSetting::slderEvent(Ref* pSender, SliderEventType type)
{
	if (type == SLIDER_PERCENTCHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(pSender);
		float percent = slider->getPercent();
		if (percent <= 5.0)
		{
			slider->setPercent(5.0);
			percent = 5.0;
		}
		else if (percent >=95.0)
		{
			slider->setPercent(95.0);
			percent = 95.0;

		}
		float curValue = (percent - 5.0) / 90.0;
		Audio::getInstance()->setSoundValue(curValue);
	}
}

void UserSetting::showGameHelp(){
	RulePanel* rule = RulePanel::create();
    addChild(rule);
}


void UserSetting::feedBack(){
    GameFeedDialog* feed = GameFeedDialog::create();
    addChild(feed);
}