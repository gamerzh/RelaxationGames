#include "GameGuiLayer.h"
#include "GamePauseLayer.h"
#include"GameData.h"
#include"Matrix.h"
#include"Audio.h"
#include "LobbyScene.h"
#include "GameConfig.h"
#include "CallAndroidMethod.h"
#include "DreamLayer.h"

GameGuiLayer * GameGuiLayer::_instance = nullptr;


GameGuiLayer * GameGuiLayer::getInstance()
{
	if (_instance == 0)
	{
		_instance = new GameGuiLayer();
	}
	return _instance;
}
bool GameGuiLayer::init(){
	
	if (!Node::init())
	{
		return false;
	}

	 visibleSize = Director::getInstance()->getVisibleSize();
	 origin = Director::getInstance()->getVisibleOrigin();


	////add pause btn to this layer
	 MenuItemImage* start_btn = MenuItemImage::create("pause.png", "pause.png", CC_CALLBACK_0(GameGuiLayer::pauseGame, this));
	 Menu* start_game = Menu::create(start_btn, NULL);
	 start_game->setPosition(45, visibleSize.height - 40);
	 start_btn->setScale(0.8);
	 this->addChild(start_game);

	auto menu = Menu::create();
	menu->setPosition(0, 0);
	menu->setVisible(true);
	auto helptip = MenuItemImage::create("Tip_nor.png", "Tip_click.png", CC_CALLBACK_0(GameGuiLayer::helpTip, this));
	helptip->setVisible(true);
	helptip->setPosition(visibleSize.width*0.28, visibleSize.height*0.09);
	helptip->retain();
	menu->addChild(helptip, 5);

	auto refresh_btn = MenuItemImage::create("refresh_nor.png", "refresh_click.png", CC_CALLBACK_0(GameGuiLayer::refreshBtn, this));
	refresh_btn->setPosition(visibleSize.width*0.72, visibleSize.height*0.09);
	refresh_btn->retain();

	menu->addChild(refresh_btn);
	auto addtime = Menu::create();
	auto _normal = Sprite::create("addtime.png");
	auto _rect = Rect(_normal->getPositionX(), _normal->getPositionY(), _normal->getContentSize().width, _normal->getContentSize().height);
	auto select = Sprite::createWithTexture(_normal->getTexture(), _rect, false);
	select->setScale(1.1);
	auto _menuItem = MenuItemSprite::create(_normal, select, CC_CALLBACK_0(GameGuiLayer::addTimeBtn, this));
	_menuItem->setPosition(visibleSize.width*0.88, visibleSize.height*0.94);
	addtime->addChild(_menuItem);
	addtime->setPosition(Point(0, 0));
	addChild(addtime, 2);

	//ÌáÊ¾
	Sprite* helpbg = Sprite::create("numBG.png");
	helpbg->setPosition(145, 97);
	label1 = LabelAtlas::create("0", "prop_num.png", 16, 20, '0');
	label1->setAnchorPoint(Vec2(0.5, 0.5));
	label1->setPosition(helpbg->getContentSize() / 2);
	helpbg->addChild(label1);

	helptip->addChild(helpbg);





	//Ë¢ÐÂ
	Sprite* refreshbg = Sprite::create("numBG.png");
	refreshbg->setPosition(145, 97);
	label2 = LabelAtlas::create("0", "prop_num.png", 16, 20, '0');
	label2->setAnchorPoint(Vec2(0.5, 0.5));
	label2->setPosition(refreshbg->getContentSize() / 2);
	refreshbg->addChild(label2);
	refresh_btn->addChild(refreshbg);

	addChild(menu);




	Sprite* timebg = Sprite::create("numBG.png");
	timebg->setPosition(visibleSize.width*0.94, visibleSize.height*0.96);
	label = CCLabelAtlas::create("","prop_num.png",16,20,'0');
	label->setAnchorPoint(Vec2(0.5, 0.5));
	label->setPosition(timebg->getContentSize() / 2);
	timebg->addChild(label);
	addChild(timebg,2);

	

	notime = Sprite::create("no_time_hint.png");
	notime->setPosition(240, 398);
	notime->setOpacity(0);
	addChild(notime);




	
	Ascore = LabelAtlas::create("0", "percent.png", 32, 44, '0');
	Ascore->setAnchorPoint(Vec2(0.5, 0.5));
	Ascore->setPosition(Vec2(visibleSize.width/2, visibleSize.height*0.938));
	Ascore->setScale(0.7);
	this->addChild(Ascore);

	right = ProgressTimer::create(Sprite::create("progressbar.png"));
	right->setType(ProgressTimer::Type::BAR);
	right->setScaleY(0.95f);
	right->setPosition(240, 690);
	
	right->setMidpoint(ccp(0, 0));
	right->setBarChangeRate(ccp(1, 0));
	right->setPercentage(GAMEDATA::getInstance()->gettime() * 10);
	this->addChild(right);
	

	label_timer = LabelAtlas::create("0", "time_num.png", 18, 21, '0');
	label_timer->setAnchorPoint(Vec2(0.5, 0.5));
	label_timer->setPosition(visibleSize.width/2,  690);
	this->addChild(label_timer);
	schedule(schedule_selector(GameGuiLayer::updateTime), 1);

	
	char* num_char = new char[100];
	sprintf(num_char, "%d", GAMEDATA::getInstance()->getTimeNum());
	label->setString(num_char);

	sprintf(num_char, "%d", GAMEDATA::getInstance()->getTipNum());
	label1->setString(num_char);

	sprintf(num_char, "%d", GAMEDATA::getInstance()->getResetNum());
	label2->setString(num_char);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
			//Audio::getInstance()->playBtnEffect();
			//this->removeFromParentAndCleanup(true);
			//auto scene = GameConfig::getInstance()->getSceneOfChangeStyleByName(LobbyScene::createScene(), "GameToStart");
			//Director::getInstance()->replaceScene(scene);
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	scheduleUpdate();
	return true;
}

void GameGuiLayer::updateTime(float delta){
	if (GAMEDATA::getInstance()->gameState != GAMEDATA::GameState::Playing)
		return;

	GAMEDATA::getInstance()->settime(GAMEDATA::getInstance()->gettime() - 1);
	if (GAMEDATA::getInstance()->gettime() == 4){
		GAMEDATA::getInstance()->showWaring = true;
	}

	if (GAMEDATA::getInstance()->gettime() >= 1 && GAMEDATA::getInstance()->gettime() <= 5){
		Audio::getInstance()->playSound(TIME_LEAVE);
	}
	char* mtime = new char[100];
	int s = (GAMEDATA::getInstance()->gettime() + 1) % 60;
	int m = GAMEDATA::getInstance()->gettime() / 60;
	if (s < 0){
		s = 00;
	}
	if (m < 0){
		m = 00;
	}
	sprintf(mtime, "%.2d:%.2d", m, s);
	label_timer->setString(mtime);
}

void GameGuiLayer:: updateScore(){
	//add Ascore
	int Ascores = GAMEDATA::getInstance()->getAchievescore();
	int count = 0;
	int i = 1;
	do
	{
		++count;
		i *= 10;
	} while (i <= Ascores);
	Ascore->setString(String::createWithFormat("%d", (int)Ascores)->_string);

}

void GameGuiLayer::pauseGame(){
	//stop layer
	Audio::getInstance()->playBtnEffect();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Layer* pause_layer = GamePauseLayer::create();
	pause_layer->setAnchorPoint(Point(0.5,0.5));
	pause_layer->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(pause_layer,2);
	GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Pause;
	
}

void GameGuiLayer::updateBtnInfo(){

	char* num_char = new char[100];
	sprintf(num_char, "%d", GAMEDATA::getInstance()->getTimeNum());
	label->setString(num_char);

	sprintf(num_char, "%d", GAMEDATA::getInstance()->getTipNum());
	label1->setString(num_char);

	sprintf(num_char, "%d", GAMEDATA::getInstance()->getResetNum());
	label2->setString(num_char);
}
void GameGuiLayer::update(float dt){
	if (GAMEDATA::getInstance()->gameState == GAMEDATA::GameState::Playing){
		right->resume();
		
		if (GAMEDATA::getInstance()->updateScore){
			GAMEDATA::getInstance()->updateScore = false;
			updateScore();
		}

		if (GAMEDATA::getInstance()->useTipProp){
			GAMEDATA::getInstance()->useTipProp = false;
			helpTip();
		}
		if (GAMEDATA::getInstance()->useAddProps){
			GAMEDATA::getInstance()->useAddProps = false;
			addTimeBtn();
		}

		if (GAMEDATA::getInstance()->useResetProp){
			GAMEDATA::getInstance()->useResetProp = false;
			refreshBtn();
		}
		if (GAMEDATA::getInstance()->showWaring){
			GAMEDATA::getInstance()->showWaring = false;
			schedule(schedule_selector(GameGuiLayer::showWaring), 0.1);
		}

		if (GAMEDATA::getInstance()->updateProcess){
			GAMEDATA::getInstance()->updateProcess = false;
			auto to4 = ProgressTo::create(GAMEDATA::getInstance()->gettime(), 0);
			right->setPercentage(GAMEDATA::getInstance()->gettime() * 10);
			right->runAction(to4);
		}

		if (GAMEDATA::getInstance()->updateBtnInfo){
			GAMEDATA::getInstance()->updateBtnInfo = false;
			updateBtnInfo();
		}
		char* mtime = new char[100];
		if (GAMEDATA::getInstance()->updateTimeInfo){
			GAMEDATA::getInstance()->updateTimeInfo = false;
			
			int s = (GAMEDATA::getInstance()->gettime() + 1) % 60;
			int m = GAMEDATA::getInstance()->gettime() / 60;
			if (s < 0){
				s = 00;
			}
			if (m < 0){
				m = 00;
			}
			sprintf(mtime, "%.2d:%.2d", m, s);
			label_timer->setString(mtime);
		}
	}
	else{
		right->pause();	
	}
	
}



void GameGuiLayer::showWaring(float dt){
	if (GAMEDATA::getInstance()->gameState != GAMEDATA::GameState::Playing){
		return;
	}
	count++;
	if (count % 8 == 0){
		notime->setOpacity(55);
	}
	else if (count % 8 == 1){
		notime->setOpacity(105);
	}
	else if (count % 8 == 2){
		notime->setOpacity(155);
	}
	else if (count % 8 == 3){
		notime->setOpacity(205);
	}
	else if (count % 8 == 4){
		notime->setOpacity(255);
	}
	else if (count % 8 == 5){
		notime->setOpacity(205);
	}
	else if (count % 8 == 6){
		notime->setOpacity(155);
	}
	else if (count % 8 == 7){
		notime->setOpacity(105);
	}

	if (GAMEDATA::getInstance()->gettime()>4){
		notime->setOpacity(0);
		this->unschedule(schedule_selector(GameGuiLayer::showWaring));
	}
}

void GameGuiLayer::addTimeBtn(){
	Audio::getInstance()->playBtnEffect();
	if (GAMEDATA::getInstance()->getTimeNum()>0){
		GAMEDATA::getInstance()->setTimeNum(GAMEDATA::getInstance()->getTimeNum() - 1);
		//addTime = true;
		GAMEDATA::getInstance()->settime(GAMEDATA::getInstance()->gettime() + 10);
		auto to4 = ProgressTo::create(GAMEDATA::getInstance()->gettime(), 0);
		right->setPercentage(GAMEDATA::getInstance()->gettime() * 10);
		right->runAction(to4);
		updateTime(0);
		char* num_char = new char[100];
		sprintf(num_char, "%d", GAMEDATA::getInstance()->getTimeNum());
		label->setString(num_char);
	}
	else{
	//	addTime = false;
        DreamLayer* de = DreamLayer::create(5);
        addChild(de,1000);
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//        CallAndroidMethod::getInstance()->requestEvent(10);
//#endif
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//        GAMEDATA::getInstance()->settime(GAMEDATA::getInstance()->gettime() + 10);
//        auto to4 = ProgressTo::create(GAMEDATA::getInstance()->gettime(), 0);
//        right->setPercentage(GAMEDATA::getInstance()->gettime() * 10);
//        right->runAction(to4);
//        updateTime(0);
//        GAMEDATA::getInstance()->setTimeNum(GAMEDATA::getInstance()->getTimeNum() +5);
//#endif
		
	}
}

void GameGuiLayer::helpTip(){
	Audio::getInstance()->playBtnEffect();
	if (GAMEDATA::getInstance()->getTipNum()>0){
		GAMEDATA::getInstance()->setTipNum(GAMEDATA::getInstance()->getTipNum()-1);
		GAMEDATA::getInstance()->needTipPos = true;
		char* num_char = new char[100];
		sprintf(num_char, "%d", GAMEDATA::getInstance()->getTipNum());
		label1->setString(num_char);
		
	}
	else{
        DreamLayer* de = DreamLayer::create(3);
        addChild(de,1000);
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
////        CallAndroidMethod::getInstance()->requestEvent(8);
//        DreamLayer* de = DreamLayer::create(3);
//        addChild(de);
//#endif
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//        GAMEDATA::getInstance()->needTipPos = true;
//        GAMEDATA::getInstance()->setTipNum(GAMEDATA::getInstance()->getTipNum() +5);
//#endif
		
	}
}



void GameGuiLayer::refreshBtn(){
	Audio::getInstance()->playBtnEffect();
	if(GAMEDATA::getInstance()->getResetNum()>0){
		GAMEDATA::getInstance()->setResetNum(GAMEDATA::getInstance()->getResetNum() - 1);
		Sprite*sprite = Sprite::create("fresh.png");
		sprite->setPosition(240, 380);
		auto sp = Sequence::create(
			RotateBy::create(2.0f, 360), FadeOut::create(0),
			nullptr);
		addChild(sprite, 2);
		sprite->runAction(sp);
		GAMEDATA::getInstance()->needResetMap = true;
		char* num_char = new char[100];
		sprintf(num_char, "%d", GAMEDATA::getInstance()->getResetNum());
		label2->setString(num_char);
	} else{
        DreamLayer* de = DreamLayer::create(4);
        addChild(de,1000);
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//        CallAndroidMethod::getInstance()->requestEvent(9);
//#endif
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//        GAMEDATA::getInstance()->needResetMap = true;
//        GAMEDATA::getInstance()->setResetNum(GAMEDATA::getInstance()->getResetNum() + 5);
//#endif
	}

}






