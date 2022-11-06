#include "GamePauseLayer.h"
#include"GameGuiLayer.h"
#include"GameResultScene.h"
#include"GameData.h"
#include"LobbyScene.h"
#include"Audio.h"
#include"CallAndroidMethod.h"
#include "DreamLayer.h"
#include "GameConfig.h"

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
    //add sprite to this scene
    
    auto bg = Sprite::create("pay_bg.png");
    bg->setAnchorPoint(Vec2(0.5, 0.5));
    bg->setPosition(0,0);
    addChild(bg);
    
    
    //add daoju gift pic
    auto daoju = Menu::create();
    auto sp = Sprite::create("gift_package.png");
    Rect _rect = Rect(sp->getPositionX(), sp->getPositionY(), sp->getContentSize().width, sp->getContentSize().height);
    auto sp1 = Sprite::createWithTexture(sp->getTexture(), _rect, false);
    sp1->setScale(1.1);
    auto daojuBtn = MenuItemSprite::create(sp, sp1, nullptr, CC_CALLBACK_0(GamePauseLayer::getGift, this));
    daojuBtn->setPosition(Point(0, 20));
    daoju->addChild(daojuBtn);
    daoju->setPosition(0, 0);
    this->addChild(daoju);
    
    auto achieve_game = Menu::create();
    auto achieve = MenuItemImage::create("achieve_nor.png", "achieve_click.png", CC_CALLBACK_0(GamePauseLayer::getGift, this));
    achieve->setPosition(Point(0,0));
    achieve_game->addChild(achieve);
    achieve_game->setPosition(Point(0,-220));
    this->addChild(achieve_game);
    
    //add resume btn to this layer
    auto resume_btn = Menu::create();
    auto resume = MenuItemImage::create("game_resume_nor.png", "game_resume_click.png", CC_CALLBACK_0(GamePauseLayer::resumeGame, this));
    resume->setAnchorPoint(Point(0.5,0.5));
    resume->setPosition(Point(-120, -320));
    resume_btn->addChild(resume);
    resume_btn->setPosition(Point(0,0));
    this->addChild(resume_btn);
    
    //add delay
    auto delay_btn = Menu::create();
    auto delay = MenuItemImage::create("delay_nor.png", "delay_click.png", CC_CALLBACK_0(GamePauseLayer::delayTen, this));
    delay->setAnchorPoint(Point(0.5, 0.5));
    delay->setPosition(Point(120, -320));
    delay_btn->setPosition(Point(0, 0));
    delay_btn->addChild(delay);
    this->addChild(delay_btn);
    
    auto labelgift = Sprite::create("labelgift.png");
    labelgift->setPosition(0, -110);
    addChild(labelgift);
    
    MenuItemImage* close_btn = MenuItemImage::create("close_nomal.png", "close_click.png", CC_CALLBACK_0(GamePauseLayer::resumeGame, this));
    close_btn->setScale(0.7);
    Menu* close_game = Menu::create(close_btn, NULL);
    close_game->setPosition(215, 370);
    
    auto menu1 = Menu::create();
    auto settingBtnOkItem1 = MenuItemImage::create("back_normal.png", "back_click.png",  CC_CALLBACK_0(GamePauseLayer::quitGame, this));
    settingBtnOkItem1->setPosition(Point(-200, 360));
    menu1->addChild(settingBtnOkItem1);
    menu1->setPosition(Point(0, 0));
    this->addChild(menu1);
    
    this->addChild(close_game);
    return true;
}

void GamePauseLayer::quitGame(){
    Audio::getInstance()->playBtnEffect();
    auto scene = GameConfig::getInstance()->getSceneOfChangeStyleByName(LobbyScene::createScene(), "ResultToStart");
    Director::getInstance()->replaceScene(scene);
    GAMEDATA::getInstance()->setAchievescore(0);
}

void GamePauseLayer::resumeGame(){
    Audio::getInstance()->playBtnEffect();
    this->resume();
    this->removeFromParentAndCleanup(true);
    GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Playing;
}


void GamePauseLayer::getGift(){
    Audio::getInstance()->playBtnEffect();
    int i = 3 * CCRANDOM_0_1();
    switch (i)
    {
        case 0:
            //        CallAndroidMethod::getInstance()->requestEvent(11);
        {
            DreamLayer* ly = DreamLayer::create(3);
            getParent()->addChild(ly,100);
        }
            break;
        case 1:
            //        CallAndroidMethod::getInstance()->requestEvent(34);
        {
            DreamLayer* ly = DreamLayer::create(4);
            getParent()->addChild(ly,100);
        }
            break;
        case 2:
            //        CallAndroidMethod::getInstance()->requestEvent(35);
        {
            DreamLayer* ly = DreamLayer::create(5);
            getParent()->addChild(ly,100);
        }
            break;
        default:
            //        CallAndroidMethod::getInstance()->requestEvent(11);
        {
            DreamLayer* ly = DreamLayer::create(3);
            getParent()->addChild(ly,100);
        }
            break;
    }
    
    this->removeFromParentAndCleanup(true);
}
void GamePauseLayer::goBack(){
    Audio::getInstance()->playBtnEffect();
    this->removeFromParentAndCleanup(true);
    auto lvstr = StringUtils::format("%d", GAMEDATA::getInstance()->getLevel());
    Director::getInstance()->replaceScene(TransitionFade::create(1, LobbyScene::createScene()));
}

void GamePauseLayer::delayTen(){
    Audio::getInstance()->playBtnEffect();
    if (GAMEDATA::getInstance()->getTimeNum()>0){
        GAMEDATA::getInstance()->useAddProps = true;
        GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Playing;
    }
    else{
        DreamLayer* ly = DreamLayer::create(5);
        getParent()->addChild(ly,100);
        //#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
        //        CallAndroidMethod::getInstance()->requestEvent(10);
        //#endif
        //#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        //
        //        GAMEDATA::getInstance()->setTimeNum(GAMEDATA::getInstance()->getTimeNum()+5);
        //        GAMEDATA::getInstance()->useAddProps = true;
        //        GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Playing;
        //#endif
    }
    
    
    
    this->removeFromParentAndCleanup(true);
    
}
bool GamePauseLayer::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
    return true;
}
