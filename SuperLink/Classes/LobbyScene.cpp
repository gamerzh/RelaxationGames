#include "LobbyScene.h"
#include "GameScene.h"
#include"Audio.h"
#include"GameData.h"
#include "SimpleAudioEngine.h"
#include"SignInLayer.h"
#include"CallAndroidMethod.h"

Scene* LobbyScene::createScene()
{
	auto scene = Scene::create();

	auto layer = LobbyScene::create();
	scene->addChild(layer);

	return scene;
}

bool LobbyScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Audio::getInstance()->prepare();
	if (GAMEDATA::getInstance()->getMusicState()){
		Audio::getInstance()->playBGM();
	}

	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
			//quitDialog->setVisible(true);
			CallAndroidMethod::getInstance()->quit();
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//add game bg to layer
	Sprite* lobby_bg = Sprite::create("lobby_bg.jpg");
	lobby_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(lobby_bg, -1);

	//add start menu to layer
	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if(GAMEDATA::getInstance()->getLoginTimes()==0){
		GAMEDATA::getInstance()->setLoginTimes(1);
	}else{
		if (!CallAndroidMethod::getInstance()->isSignToday()){
			//TODO:��ʾ�¿���ʾ
			if (GAMEDATA::getInstance()->getMonthCard()){
				GAMEDATA::getInstance()->setTipNum(GAMEDATA::getInstance()->getTipNum() + 2);
				//TODO:SHOW��toast
				CallAndroidMethod::getInstance()->showMonthCardToast();
			}

			//TODO:sign in
			Size visibleSize = Director::getInstance()->getVisibleSize();
			Node* pause_layer1 = SignInLayer::create();
			pause_layer1->setPosition(visibleSize.width / 2, visibleSize.height / 2);
			this->addChild(pause_layer1, 2);
		}
	}

#endif


	/*
	GAMEDATA::getInstance()->setDay(GAMEDATA::getInstance()->getCurrentTime());
	int a =  GAMEDATA::getInstance()->getDay();
	int n =  GAMEDATA::getInstance()->getCurrentTime();
	int m= GAMEDATA::getInstance()->getLoginTimes();
	if (a == n&&m==0){
		
	}
	if (n == a + 1){
		GAMEDATA::getInstance()->setTimes(GAMEDATA::getInstance()->getTimes() + 1);
		GAMEDATA::getInstance()->setLoginTimes(0);
		if(m==0){
			GAMEDATA::getInstance()->setDay(GAMEDATA::getInstance()->getCurrentTime());
			GAMEDATA::getInstance()->setLoginTimes(GAMEDATA::getInstance()->getLoginTimes() + 1);
			Size visibleSize = Director::getInstance()->getVisibleSize();
			Node* pause_layer1 = SignInLayer::create();
			pause_layer1->setPosition(visibleSize.width / 2, visibleSize.height / 2);
			this->addChild(pause_layer1, 2);
		}
	}
		if (n-a>1)
		{
			GAMEDATA::getInstance()->setLoginTimes(0);
			if(m==0){
			GAMEDATA::getInstance()->setTimes(0);
			GAMEDATA::getInstance()->setLoginTimes(GAMEDATA::getInstance()->getLoginTimes() + 1);
			Size visibleSize = Director::getInstance()->getVisibleSize();
			Node* pause_layer1 = SignInLayer::create();
			pause_layer1->setPosition(visibleSize.width / 2, visibleSize.height / 2);
			this->addChild(pause_layer1, 2);
			GAMEDATA::getInstance()->setDay(GAMEDATA::getInstance()->getCurrentTime());
			}
	}
	*/

	MenuItemImage* start_btn = MenuItemImage::create("start_game_btn_normal.png", "start_game_btn_clicked.png", CC_CALLBACK_0(LobbyScene::startGame, this));
	Menu* start_game = Menu::create(start_btn, NULL);
	start_game->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 95);
	this->addChild(start_game,1);
	//add music
	MenuItemImage* start_btn1 = MenuItemImage::create("btn_bg_normal.png", "btn_bg_click.png", CC_CALLBACK_0(LobbyScene::music, this));
	Menu* start_game1 = Menu::create(start_btn1, NULL);

	start_game1->setPosition(420, 750);

	this->addChild(start_game1);
	MenuItemImage *open = MenuItemImage::create("open.png", "open.png");
	MenuItemImage *close = MenuItemImage::create("close.png", "close.png");
	if (GAMEDATA::getInstance()->getMusicState()){
		MenuItemToggle *close1 = MenuItemToggle::createWithTarget(this, menu_selector(LobbyScene::musicCallback), open, close, NULL);
		close1->setPosition(ccp(182, 353));
		Menu* itemToggleMenu = Menu::create(close1, NULL);
		this->addChild(itemToggleMenu, 1);
	}
	else{
		MenuItemToggle *close1 = MenuItemToggle::createWithTarget(this, menu_selector(LobbyScene::musicCallback), close, open, NULL);
		close1->setPosition(ccp(182, 353));
		Menu* itemToggleMenu = Menu::create(close1, NULL);
		this->addChild(itemToggleMenu, 1);
	}

	
	//more game btn
	if (GAMEDATA::getInstance()->openMoreGame){

		MenuItemImage* more_game_btn = MenuItemImage::create("btn_bg_normal.png", "btn_bg_click.png", CC_CALLBACK_0(LobbyScene::music, this));
		Menu* more_game_btn1 = Menu::create(more_game_btn, NULL);
		more_game_btn1->setPosition(50, 750);
		this->addChild(more_game_btn1);


		auto menu2 = Menu::create();
		auto spriteNormal2 = Sprite::create("more_game.png");
		Rect _rect = Rect(spriteNormal2->getPositionX(), spriteNormal2->getPositionY(), spriteNormal2->getContentSize().width, spriteNormal2->getContentSize().height);
		auto spriteSelected2 = Sprite::createWithTexture(spriteNormal2->getTexture(), _rect, false);
		spriteSelected2->setScale(1.1);
		auto settingBtnOkItem2 = MenuItemSprite::create(spriteNormal2, spriteSelected2, nullptr, CC_CALLBACK_0(LobbyScene::showMoreGame, this));
		settingBtnOkItem2->setPosition(Point(50, 750));
		menu2->addChild(settingBtnOkItem2);
		menu2->setPosition(Point(0, 0));
		this->addChild(menu2);
	}

	if (GAMEDATA::getInstance()->openTehui){
		auto tehui = Menu::create();
		auto spriteNormal_tehui = Sprite::create("te_hui.png");
		Rect _rect1 = Rect(spriteNormal_tehui->getPositionX(), spriteNormal_tehui->getPositionY(), spriteNormal_tehui->getContentSize().width, spriteNormal_tehui->getContentSize().height);
		auto spriteSelected_tehui = Sprite::createWithTexture(spriteNormal_tehui->getTexture(), _rect1, false);
		spriteSelected_tehui->setScale(1.1);
		auto settingBtnOkItem_tehui = MenuItemSprite::create(spriteNormal_tehui, spriteSelected_tehui, nullptr, CC_CALLBACK_0(LobbyScene::payTehui, this));
		settingBtnOkItem_tehui->setPosition(Point(50, 450));
		tehui->addChild(settingBtnOkItem_tehui);
		tehui->setPosition(Point(0, 0));
		this->addChild(tehui);
	}

	return true;


}

void LobbyScene::showMoreGame(){
	Audio::getInstance()->playBtnEffect();
	//TODO:����������?
	CallAndroidMethod::getInstance()->showMoreGame();
}

void LobbyScene::payTehui(){
	Audio::getInstance()->playBtnEffect();
	//�ػ����?
	CallAndroidMethod::getInstance()->requestEvent(32);
}

void LobbyScene::startGame(){

	
	Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::create()));
	Audio::getInstance()->playBtnEffect();
}


void LobbyScene::music(){


}

void LobbyScene::musicCallback(CCObject* pSender)
{
	Audio::getInstance()->playBtnEffect();
	MenuItemToggle* temp = (MenuItemToggle*)pSender;
	if (GAMEDATA::getInstance()->getMusicState()){
		CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		GAMEDATA::getInstance()->setMusicState(false);
		GAMEDATA::getInstance()->setSoundState(false);
	}
	else{
		GAMEDATA::getInstance()->setMusicState(true);
		GAMEDATA::getInstance()->setSoundState(true);
		Audio::getInstance()->playBGM();
	}

}

