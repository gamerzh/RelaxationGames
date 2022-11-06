#include "GameGuiLayer.h"
#include "GamePauseLayer.h"
#include"GameData.h"
#include"Matrix.h"
#include"Audio.h"
#include "CallAndroidMethod.h"
#include "LobbyScene.h"

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


	//add pause btn to this layer
	MenuItemImage* start_btn = MenuItemImage::create("btn_bg_normal.png", "btn_bg_click.png", CC_CALLBACK_0(GameGuiLayer::pauseGame, this));
	Menu* start_game = Menu::create(start_btn, NULL);
	start_game->setPosition(50, visibleSize.height - 30);
	start_btn->setScale(0.8);
	this->addChild(start_game);

	auto stop = Sprite::create("stop.png");
	stop->setPosition(50, visibleSize.height - 30);
	stop->setScale(0.8);
	addChild(stop);

	auto addtime = Menu::create();
	auto _normal = Sprite::create("addtime.png");
	Rect _rect = Rect(_normal->getPositionX(), _normal->getPositionY(), _normal->getContentSize().width, _normal->getContentSize().height);
	auto select = Sprite::createWithTexture(_normal->getTexture(), _rect, false);
	select->setScale(1.1);
	auto _menuItem = MenuItemSprite::create(_normal, select, CC_CALLBACK_0(GameGuiLayer::addTimeBtn, this));
	_menuItem->setPosition(400, visibleSize.height - 80);
	addtime->addChild(_menuItem);
	addtime->setPosition(Point(0, 0));
	this->addChild(addtime, 2);

	Sprite* timebg = Sprite::create("numBG.png");
	timebg->setPosition(435+20, visibleSize.height - 85+20);
	timebg->setScale(0.8);
	addChild(timebg,2);

	label = CCLabelTTF::create();
	ccColor3B color;
	color.r = 240;
	color.g = 255;
	color.b = 255;
	label->setColor(color);
	label->setScale(1.2);
	label->setPosition(435+20, visibleSize.height - 85+20);

	this->addChild(label,2);

	auto tree = Sprite::create("tree.png");
	tree->setPosition(70, visibleSize.height - 140);
	tree->setScale(0.8);
	addChild(tree,1);

	float stime = GAMEDATA::getInstance()->gettime();
	//add help
	auto help = Menu::create();
	auto spriteNomal1 = Sprite::create("help.png");
	_rect = Rect(spriteNomal1->getPositionX(), spriteNomal1->getPositionY(), spriteNomal1->getContentSize().width, spriteNomal1->getContentSize().height);
	auto spriteSelect1 = Sprite::createWithTexture(spriteNomal1->getTexture(), _rect, false);
	spriteSelect1->setScale(1.1);
	auto helptip = MenuItemSprite::create(spriteNomal1, spriteSelect1, CC_CALLBACK_0(GameGuiLayer::helpTip, this));
	helptip->setPosition(80, 55);
	help->addChild(helptip);
	help->setPosition(Point(0, 0));
	this->addChild(help);

	Sprite* helpbg = Sprite::create("numBG.png");
	helpbg->setPosition(100+10, 90+10);
	helpbg->setScale(0.8);
	addChild(helpbg);

	label1 = CCLabelTTF::create();
	ccColor3B color1;
	color1.r = 240;
	color1.g = 255;
	color1.b = 255;
	label1->setColor(color1);
	label1->setScale(1.2);
	label1->setPosition(100+10, 90+10);
	this->addChild(label1);

	notime = Sprite::create("no_time_hint.png");
	notime->setPosition(240, 360);
	notime->setOpacity(0);
	addChild(notime);

	//add refresh
	auto refresh = Menu::create();
	auto spriteNomal2 = Sprite::create("refresh.png");
	_rect = Rect(spriteNomal2->getPositionX(), spriteNomal2->getPositionY(), spriteNomal2->getContentSize().width, spriteNomal2->getContentSize().height);
	auto spriteSelect2 = Sprite::createWithTexture(spriteNomal2->getTexture(), _rect, false);
	spriteSelect2->setScale(1.1);
	auto refresh_btn = MenuItemSprite::create(spriteNomal2, spriteSelect2, CC_CALLBACK_0(GameGuiLayer::refreshBtn, this));
	refresh_btn->setPosition(390, 55);
	refresh->addChild(refresh_btn);
	refresh->setPosition(Point(0, 0));
	this->addChild(refresh);

	Sprite*refreshbg = Sprite::create("numBG.png");
	refreshbg->setPosition(410+10, 90+10);
	refreshbg->setScale(0.8);
	addChild(refreshbg);


	label2 = CCLabelTTF::create();
	ccColor3B color2;
	color2.r = 240;
	color2.g = 255;
	color2.b = 255;
	label2->setColor(color2);
	label2->setScale(1.2);
	label2->setPosition(410+10, 90+10);
	this->addChild(label2);


	
	Ascore = LabelAtlas::create(String::createWithFormat("%d", 0)->_string, "percent.png", 16, 22, '0');
	Ascore->setPosition(Vec2(visibleSize.width/2-8, 35));
	this->addChild(Ascore);

	//显示进度条
	right = ProgressTimer::create(Sprite::create("progressbar.png"));
	right->setType(ProgressTimer::Type::BAR);
	right->setScaleY(0.95f);
	right->setPosition(240, 715);
	
	right->setMidpoint(ccp(0, 0));
	right->setBarChangeRate(ccp(1, 0));
	right->setPercentage(GAMEDATA::getInstance()->gettime() * 10);
	this->addChild(right);
	
	//显示时间
	label_timer = CCLabelTTF::create();
	label_timer->setColor(color);
	label_timer->setScale(1.5);
	label_timer->setPosition(240, origin.y + visibleSize.height / 2 + 270);
	this->addChild(label_timer);
	schedule(schedule_selector(GameGuiLayer::updateTime), 1);

	//显示道具个数-加时
	char* num_char = new char[100];
	sprintf(num_char, "%d", GAMEDATA::getInstance()->getTimeNum());
	label->setString(num_char);
	//提示
	sprintf(num_char, "%d", GAMEDATA::getInstance()->getTipNum());
	label1->setString(num_char);
	//重排
	sprintf(num_char, "%d", GAMEDATA::getInstance()->getResetNum());
	label2->setString(num_char);

	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
			/*	Audio::getInstance()->playBtnEffect();
				this->removeFromParentAndCleanup(true);
				Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::createScene()));*/
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
	sprintf(mtime, "%.2d : %.2d", m, s);
	label_timer->setString(mtime);
}

void GameGuiLayer:: updateScore(){
	//add Ascore
	int Ascores = GAMEDATA::getInstance()->getAchievescore();
	int count = 0;//储存位数
	int i = 1;
	do
	{
		++count;
		i *= 10;
	} while (i <= Ascores);
	Ascore->setString(String::createWithFormat("%d", (int)Ascores)->_string);
	Ascore->setPosition(Vec2(visibleSize.width / 2-count*8 , 35));
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
	//显示道具个数-加时
	char* num_char = new char[100];
	sprintf(num_char, "%d", GAMEDATA::getInstance()->getTimeNum());
	label->setString(num_char);
	//提示
	sprintf(num_char, "%d", GAMEDATA::getInstance()->getTipNum());
	label1->setString(num_char);
	//重排
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

		if (GAMEDATA::getInstance()->updateTimeInfo){
			GAMEDATA::getInstance()->updateTimeInfo = false;
			char* mtime = new char[100];
			int s = (GAMEDATA::getInstance()->gettime() + 1) % 60;
			int m = GAMEDATA::getInstance()->gettime() / 60;
			if (s < 0){
				s = 00;
			}
			if (m < 0){
				m = 00;
			}
			sprintf(mtime, "%.2d : %.2d", m, s);
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
		//显示道具个数-加时
		char* num_char = new char[100];
		sprintf(num_char, "%d", GAMEDATA::getInstance()->getTimeNum());
		label->setString(num_char);
	}
	else{
	//	addTime = false;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
		CallAndroidMethod::getInstance()->requestEvent(10);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) 
		GAMEDATA::getInstance()->settime(GAMEDATA::getInstance()->gettime() + 10);
		auto to4 = ProgressTo::create(GAMEDATA::getInstance()->gettime(), 0);
		right->setPercentage(GAMEDATA::getInstance()->gettime() * 10);
		right->runAction(to4);
		updateTime(0);
		GAMEDATA::getInstance()->setTimeNum(GAMEDATA::getInstance()->getTimeNum() +5);
#endif
		
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
		
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
		CallAndroidMethod::getInstance()->requestEvent(8);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) 
		GAMEDATA::getInstance()->needTipPos = true;
		GAMEDATA::getInstance()->setTipNum(GAMEDATA::getInstance()->getTipNum() +5);
#endif
		
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
		//显示道具个数-重排
		char* num_char = new char[100];
		sprintf(num_char, "%d", GAMEDATA::getInstance()->getResetNum());
		label2->setString(num_char);
	} else{

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
		CallAndroidMethod::getInstance()->requestEvent(9);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) 
		GAMEDATA::getInstance()->needResetMap = true;
		GAMEDATA::getInstance()->setResetNum(GAMEDATA::getInstance()->getResetNum() + 5);
#endif
		
	}

}






