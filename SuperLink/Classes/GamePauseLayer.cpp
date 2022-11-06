#include "GamePauseLayer.h"
#include"GameGuiLayer.h"
#include"GameResultScene.h"
#include"GameData.h"
#include"LobbyScene.h"
#include"Audio.h"
#include"CallAndroidMethod.h"
using namespace cocos2d;
GamePauseLayer* GamePauseLayer::create(){
	GamePauseLayer* ret = new GamePauseLayer();
	if(ret && ret->init()){
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}


bool GamePauseLayer::init(){
if ( !Layer::init() )
	{
		return false;
	}

EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();

listener->setSwallowTouches(true);

listener->onTouchBegan = CC_CALLBACK_2(GamePauseLayer::onTouchBegan, this);
listener->onTouchMoved = CC_CALLBACK_2(GamePauseLayer::onTouchMoved, this);
listener->onTouchEnded = CC_CALLBACK_2(GamePauseLayer::onTouchEnded, this);

_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
setTouchEnabled(true);
  //add sprite to this scene
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//Vec2 origin = Director::getInstance()->getVisibleOrigin();


	Sprite* pause_bg = Sprite::create("pause_bg.png");
	this->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(pause_bg);

	//add daoju gift pic
	auto daoju = Menu::create();
	auto sp = Sprite::create("gift_package.png");
	Rect _rect = Rect(sp->getPositionX(), sp->getPositionY(), sp->getContentSize().width, sp->getContentSize().height);
	auto sp1 = Sprite::createWithTexture(sp->getTexture(), _rect, false);
	sp1->setScale(1.1);
	auto daojuBtn = MenuItemSprite::create(sp, sp1, nullptr, CC_CALLBACK_0(GamePauseLayer::getGift, this));
	daojuBtn->setPosition(Point(0, 0));
	daoju->addChild(daojuBtn);
	daoju->setPosition(0, 100);
	this->addChild(daoju);

	
	//add  achieve
	auto achieve_game = Menu::create();
	auto spriteNormal = Sprite::create("achieve.png");
	_rect = Rect(spriteNormal->getPositionX(), spriteNormal->getPositionY(), spriteNormal->getContentSize().width, spriteNormal->getContentSize().height);
	auto spriteSelected = Sprite::createWithTexture(spriteNormal->getTexture(), _rect, false);
	spriteSelected->setScale(1.1);
	auto achieve = MenuItemSprite::create(spriteNormal, spriteSelected, nullptr, CC_CALLBACK_0(GamePauseLayer::getGift, this));
	achieve->setPosition(Point(0,0));
	achieve_game->addChild(achieve);
	achieve_game->setPosition(Point(0,-200));
	this->addChild(achieve_game);
	
	//add resume btn to this layer
	auto resume_btn = Menu::create();
	auto spriteNormal1 = Sprite::create("game_resume.png");
	_rect = Rect(spriteNormal1->getPositionX(), spriteNormal1->getPositionY(), spriteNormal1->getContentSize().width, spriteNormal1->getContentSize().height);
	auto spriteSelected1 = Sprite::createWithTexture(spriteNormal1->getTexture(), _rect, false);
	spriteSelected1->setScale(1.1);

	auto resume = MenuItemSprite::create(spriteNormal1, spriteSelected1, CC_CALLBACK_0(GamePauseLayer::resumeGame, this));
	resume->setAnchorPoint(Point(0.5,0.5));
	resume->setPosition(Point(-120, -300));
	resume_btn->addChild(resume);
	resume_btn->setPosition(Point(0,0));
	this->addChild(resume_btn);

	//add delay
	auto delay_btn = Menu::create();
	auto spriteNormal2 = Sprite::create("delay.png");
	_rect = Rect(spriteNormal2->getPositionX(), spriteNormal2->getPositionY(), spriteNormal2->getContentSize().width, spriteNormal2->getContentSize().height);
	auto spriteSelected2 = Sprite::createWithTexture(spriteNormal2->getTexture(), _rect, false);
	spriteSelected2->setScale(1.1);
	auto delay = MenuItemSprite::create(spriteNormal2, spriteSelected2, CC_CALLBACK_0(GamePauseLayer::delayTen, this));
	delay->setAnchorPoint(Point(0.5, 0.5));
	delay->setPosition(Point(120, -300));
	delay_btn->setPosition(Point(0, 0));
	delay_btn->addChild(delay);
	

	this->addChild(delay_btn);

	MenuItemImage* close_btn = MenuItemImage::create("close_nomal.png", "close_click.png", CC_CALLBACK_0(GamePauseLayer::resumeGame, this));
	Menu* close_game = Menu::create(close_btn, NULL);
	close_game->setPosition(200, 350);

	this->addChild(close_game);
	return true;
}



void GamePauseLayer::resumeGame(){
	Audio::getInstance()->playBtnEffect();
	this->resume();
	this->removeFromParentAndCleanup(true);
	GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Playing;
}


void GamePauseLayer::getGift(){
	Audio::getInstance()->playBtnEffect();
	CallAndroidMethod::getInstance()->requestEvent(11);
	//this->removeFromParentAndCleanup(true);
}
void GamePauseLayer::goBack(){
	Audio::getInstance()->playBtnEffect();
	this->removeFromParentAndCleanup(true);
	Director::getInstance()->replaceScene(TransitionFade::create(1,LobbyScene::createScene()));
}

void GamePauseLayer::delayTen(){
	Audio::getInstance()->playBtnEffect();
	if (GAMEDATA::getInstance()->getTimeNum()>0){
		GAMEDATA::getInstance()->useAddProps = true;
		GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Playing;
	}
	else{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
		CallAndroidMethod::getInstance()->requestEvent(10);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) 
		
		GAMEDATA::getInstance()->setTimeNum(GAMEDATA::getInstance()->getTimeNum()+5);
		GAMEDATA::getInstance()->useAddProps = true;
		GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Playing;
#endif
	}


	
	this->removeFromParentAndCleanup(true);

}
bool GamePauseLayer::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	return true;
}
