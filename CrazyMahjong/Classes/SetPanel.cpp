#include "SetPanel.h"
#include "MahjongAnim.h"
#include "Audio.h"
bool SetPanel::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->setVisible(false);

	Sprite* frame = Sprite::create("SetSound/Frame.png");
	this->addChild(frame);

	LayerColor* layerColor = CCLayerColor::create();
	layerColor->setColor(ccc3(0, 0, 0));
	layerColor->setOpacity(180);
	layerColor->setPosition(-400, -240);
	layerColor->setContentSize(CCSizeMake(800, 480));
	this->addChild(layerColor, -1);


	auto close = MenuItemImage::create("SetSound/Close_0.png", "SetSound/Close_1.png", CC_CALLBACK_1(SetPanel::hidePanel,this));
	close->setPosition(205, 130);

	
	auto menu = Menu::create(close,nullptr);
	menu->setPosition(0, 0);
	addChild(menu);
	//Button* button = Button::create();
	//button->loadTextures("SetSound/Close_0.png", "SetSound/Close_1.png");
	//button->addTouchEventListener(this, toucheventselector(SetPanel::hidePanel));
	//button->setSwallowTouches(true);
	//button->setPosition(Vec2(205.0f, 130.0f));
	//this->addChild(button,10);

	// »¬¶¯Ìõ
	Slider* slider = Slider::create();
	slider->loadBarTexture("SetSound/Slider_0.png");
	slider->loadProgressBarTexture("SetSound/Slider_1.png");
	slider->loadSlidBallTextures("SetSound/Block_0.png", "SetSound/Block_1.png");
	slider->addEventListenerSlider(this, sliderpercentchangedselector(SetPanel::slderEvent));


	this->addChild(slider);
	slider->setPosition(Vec2(45.0f, 30));

	float curValue = Audio::getInstance()->getSoundValue() *80+10;
	slider->setPercent(curValue);
	Sprite* yinLiang = Sprite::create("SetSound/Sound.png");
	yinLiang->setPosition(Vec2(-150.0f, 30));
	this->addChild(yinLiang);

	// 4¸öÑ¡¿ò
	CheckBox* boxes[2];
	Sprite* sprs[2];
	// ÒôÐ§
	boxes[0] = CheckBox::create();
	boxes[0]->loadTextures("SetSound/BoxBkg.png", "SetSound/BoxBkg.png", "SetSound/BoxCross.png", "", "");
	boxes[0]->addEventListenerCheckBox(this, checkboxselectedeventselector(SetPanel::boxEventY));
	boxes[0]->setSelected(Audio::getInstance()->isOpenEffect());
	this->addChild(boxes[0]);
	sprs[0] = Sprite::create("SetSound/YinXiao.png");
	this->addChild(sprs[0]);

	// ±³¾°ÒôÀÖ
	boxes[1] = CheckBox::create();
	boxes[1]->loadTextures("SetSound/BoxBkg.png", "SetSound/BoxBkg.png", "SetSound/BoxCross.png", "", "");
	boxes[1]->addEventListenerCheckBox(this, checkboxselectedeventselector(SetPanel::boxEventB));
	boxes[1]->setSelected(Audio::getInstance()->isOpenBgm());
	this->addChild(boxes[1]);
	sprs[1] = Sprite::create("SetSound/BkgSound.png");
	this->addChild(sprs[1]);

	float w = 180.0f;
	float h = 60.0f;
	Vec2 startPos = Vec2(-30.0f, -80.0f);

	for (int i = 0; i < 2; i++)
	{
		Vec2 pos = Vec2(w * i,0) + startPos;
		boxes[i]->setPosition(pos);
		sprs[i]->setPosition(pos + Vec2(-80.0f, .0f));

	}

	this->setPosition(400.0f, 240.0f);
	showPanel();

	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(SetPanel::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//´¥ÃþÆÁ±Î
	auto listenr1 = EventListenerTouchOneByOne::create();
	listenr1->onTouchBegan = [=](Touch*touch, Event*event){return true; };
	listenr1->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);
	return true;
}

void SetPanel::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (EventKeyboard::KeyCode::KEY_BACKSPACE == keyCode)
	{
	/*	btn->setEnabled(true);*/
		removeFromParentAndCleanup(1);
	}
}

void SetPanel::slderEvent(Ref* pSender, SliderEventType type)
{
	if (type == SLIDER_PERCENTCHANGED)
	{
		Slider* slider = dynamic_cast<Slider*>(pSender);
		float percent = slider->getPercent();
		if (percent <= 10.0)
		{
			slider->setPercent(10.0);
			percent = 10.0;
		}
		else if (percent >= 90.0)
		{
			slider->setPercent(90.0);
			percent = 90.0;

		}
		float curValue = (percent - 10.0) / 80.0;
		CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(curValue);
		CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(curValue);
		Audio::getInstance()->setSoundValue(curValue);
	}
}

// ËÄ¸öÑ¡Ôñ¿ò£¬
void SetPanel::boxEventS(Ref* pSender, SliderEventType type)	//Ê¡µç
{
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);

}

void SetPanel::boxEventB(Ref* pSender, SliderEventType type)	//±³¾°ÒôÀÖ
{
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);
	switch (type)
	{
	case CHECKBOX_STATE_EVENT_SELECTED:
	{
		Audio::getInstance()->setOpenBgm(true);
		break;
	}
	case CHECKBOX_STATE_EVENT_UNSELECTED:
	{
		Audio::getInstance()->setOpenBgm(false);
		break;
	}
	}
}

void SetPanel::boxEventY(Ref* pSender, SliderEventType type)	//ÒôÐ§
{
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);
	switch (type)
	{
	case CHECKBOX_STATE_EVENT_SELECTED:
	{
		Audio::getInstance()->setOpenEffect(true);
										  break;
	}
	case CHECKBOX_STATE_EVENT_UNSELECTED:
	{
		Audio::getInstance()->setOpenEffect(false);
											break;
	}
	}
}

void SetPanel::boxEventZ(Ref* pSender, SliderEventType type)	// Õð¶¯
{
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);

}

//ÏÔÊ¾Òþ²ØÉèÖÃÃæ°å
void SetPanel::showPanel()
{

	this->setScale(.0f);
	this->setVisible(true);
	this->runAction(ScaleTo::create(time, 1.0f));
}
void SetPanel::hidePanel(Ref* pSender)
{
	//btn->setEnabled(true);
	/*this->runAction(Sequence::create(ScaleTo::create(time, .0f), [this](){
		this->setVisible(false);
		}, NULL));*/
	//if (type = TouchEventType::TOUCH_EVENT_ENDED)
	//{
		
	/*}*/
removeFromParentAndCleanup(1);
}
