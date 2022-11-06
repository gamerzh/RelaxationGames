#include "LobbyScene.h"
#include"Audio.h"
#include"GameData.h"
#include "GameScene.h"
#include "GameConfig.h"
#include "SimpleAudioEngine.h"
#include "CallAndroidMethod.h"

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
    GAMEDATA::getInstance()->gameState = GAMEDATA::Start;
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
               quitGame();//quit game
                break;
            default:
                break;
        }
    };
    EventListenerTouchOneByOne* listener1 = EventListenerTouchOneByOne::create();
    
    listener1->onTouchBegan = CC_CALLBACK_2(LobbyScene::onTouchBegan, this);
    listener1->onTouchMoved = CC_CALLBACK_2(LobbyScene::onTouchMoved, this);
    listener1->onTouchEnded = CC_CALLBACK_2(LobbyScene::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //add game bg to layer
    Sprite* lobby_bg = Sprite::create("lobby_bg.jpg");
    lobby_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(lobby_bg, -1);
    //add start menu to layer
    int val = getDayCnt("PayMonthFlag");
    if (val == 0)
    {
        if (GAMEDATA::getInstance()->getMonthCard()){
            GAMEDATA::getInstance()->setTipNum(GAMEDATA::getInstance()->getTipNum() + 2);
            addDayCnt("PayMonthFlag");
        }
        
    }
    //add music
    MenuItemImage *open = MenuItemImage::create("open.png", "open.png");
    MenuItemImage *close = MenuItemImage::create("close.png", "close.png");
    MenuItemToggle *music = MenuItemToggle::createWithCallback(CC_CALLBACK_1(LobbyScene::musicCallback, this), open, close, NULL);
   
    Menu* itemToggleMenu = Menu::create(music, NULL);
    itemToggleMenu->setPosition(Vec2(430, 50));
    this->addChild(itemToggleMenu, 1);
    if (!GAMEDATA::getInstance()->getMusicState()){
        music->setSelectedIndex(1);
    }
    
    //add quit btn
    auto quitImg = MenuItemImage::create("back_normal.png", "back_click.png",  CC_CALLBACK_0(LobbyScene::quitGame, this));
    auto quitMenu = Menu::create(quitImg,NULL);
    quitMenu->setPosition(Vec2(50, 50));
    this->addChild(quitMenu);
    
    
    start_btn = MenuItemImage::create("start_game_btn_normal.png", "start_game_btn_clicked.png", CC_CALLBACK_0(LobbyScene::startGame, this));
    start_btn->setPosition(visibleSize.width / 2, visibleSize.height * 0.3);
    Menu* start_game = Menu::create();
    start_game->setPosition(Point::ZERO);
    start_btn->retain();
    start_game->addChild(start_btn);
    this->addChild(start_game,1);
    
    auto scaleani = Sequence::create(ScaleTo::create(0.2, 1.05, 0.95),
                                     ScaleTo::create(0.2, 0.95, 1.05), ScaleTo::create(0.2, 1.0, 1.0), ScaleTo::create(0.2, 1.05, 0.95), ScaleTo::create(0.2, 0.95, 1.05), ScaleTo::create(0.2, 1.0, 1.0), nullptr);
    //more game btn
    start_btn->runAction(RepeatForever::create(scaleani));
    GameConfig::getInstance()->LoadConfig();
    this->schedule(schedule_selector(LobbyScene::ShowPayPoints), 0.0f);
    
    this->scheduleUpdate();
    
    return true;
}

void LobbyScene::quitGame(){
    CallAndroidMethod::getInstance()->quit();
}

void LobbyScene::showMoreGame(){
    Audio::getInstance()->playBtnEffect();
}

void LobbyScene::payTehui(){
    Audio::getInstance()->playBtnEffect();
}

void LobbyScene::startGame(){
    start_btn->stopAllActions();
    start_btn->selected();
    auto scene = GameConfig::getInstance()->getSceneOfChangeStyleByName(GameScene::create(), "StartToGame");
    Director::getInstance()->replaceScene(scene);
    Audio::getInstance()->playBtnEffect();
    GAMEDATA::getInstance()->setisfirsttimegame(false);
    GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Ready;
}


void LobbyScene::music(){
    
    
}

void LobbyScene::musicCallback(Ref* pSender)
{
    Audio::getInstance()->playBtnEffect();
    if (GAMEDATA::getInstance()->getMusicState()){
        CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
        GAMEDATA::getInstance()->setMusicState(false);
        GAMEDATA::getInstance()->setSoundState(false);
    }
    else{
        GAMEDATA::getInstance()->setMusicState(true);
        GAMEDATA::getInstance()->setSoundState(true);
        Audio::getInstance()->playBGM();
    }
    
}


void LobbyScene::ShowAni(float dt)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    {
        auto scaleto1 = ScaleTo::create(0.1f, 1.5f, 1.0f);
        auto moveto1 = MoveTo::create(0.1f, Vec2(visibleSize.width *0.45, visibleSize.height * 0.3));
        auto scaleto2 = ScaleTo::create(0.1f, 1.0f, 1.5f);
        auto moveto2 = MoveTo::create(0.1f, Vec2(visibleSize.width *0.55, visibleSize.height * 0.3));
        auto scaleto3 = ScaleTo::create(0.1f, 1.4f, 1.0f);
        auto moveto3 = MoveTo::create(0.1f, Vec2(visibleSize.width *0.50, visibleSize.height * 0.3));
        auto scaleto4 = ScaleTo::create(0.1f, 1.0f, 1.0f);
        start_btn->runAction(Sequence::create(Spawn::create(scaleto1, moveto1, nullptr), Spawn::create(scaleto2, moveto2, nullptr), Spawn::create(scaleto3, moveto3, nullptr), scaleto4, nullptr));
    }
    if (settingBtnOkItem_tehui)
    {
        auto actionUp1 = Sequence::create(ScaleTo::create(0.1, 0.95, 1.05),
                                          ScaleTo::create(0.1, 1.0, 1.0), ScaleTo::create(0.1, 1.05,0.95), ScaleTo::create(0.1, 1.0, 1.0), nullptr);
        settingBtnOkItem_tehui->runAction(RepeatForever::create(actionUp1));
    }
    
    {
        auto dealy = DelayTime::create(0.6f);
        auto moveto = MoveTo::create(0.12f, Vec2(visibleSize.width / 2, visibleSize.height*0.62));
        auto scaleto1 = ScaleTo::create(0.12f, 0.8f, 1.4f);
        
        auto scaleto2 = ScaleTo::create(0.08f, 1.4f, 0.8f);
        
        auto scaleto3 = ScaleTo::create(0.08f, 0.9f, 1.2f);
        
        auto scaleto4 = ScaleTo::create(0.08f, 1.0f, 1.0f);
        
        auto scaleto5 = ScaleTo::create(0.8f, 1.0f, 1.0f);
        
        Title->runAction(Sequence::create(dealy, Spawn::create(moveto, scaleto1, nullptr), scaleto2, scaleto3, scaleto4, scaleto5, nullptr));
    }
    
    ballani(1);
    
}

void LobbyScene::BallAniCallback(Node* pSender)
{
    pSender->setScale(0.9f, 1.1f);
}


void LobbyScene::onTouchEnded(Touch *touch, Event *event)
{
    CCLOG("x:%f,y:%f", touch->getLocation().x, touch->getLocation().y);
}


void LobbyScene::ShowPayPoints(float dt)
{
    auto state = GAMEDATA::getInstance()->gameState;
    if (state == GAMEDATA::GameState::Start&&!GAMEDATA::getInstance()->getispaythiscount() && !GAMEDATA::getInstance()->getispay())
    {
        GAMEDATA::getInstance()->setispaythiscount(true);
        GAMEDATA::getInstance()->gameState = GAMEDATA::GameState::Paying;
    }
}


void LobbyScene::autobegingame(float dt)
{
    
    if (GAMEDATA::getInstance()->gameState == GAMEDATA::GameState::Start)
    {
        GAMEDATA::getInstance()->setisautobegin(false);
        startGame();
    }
    
}
void LobbyScene::update(float delta)
{
    if (GAMEDATA::getInstance()->getisautobegin())
    {
        
        scheduleOnce(schedule_selector(LobbyScene::autobegingame), 1.0f);
        unscheduleUpdate();
        return;
    }
}


void LobbyScene::LogEventOnExit()
{
    if (GAMEDATA::getInstance()->levelvector.size() > 0)
    {
        std::string str;
        for (auto k : GAMEDATA::getInstance()->levelvector)
        {
            str.append(StringUtils::format("%d", k));
        }
        GAMEDATA::getInstance()->levelvector.clear();
    }
    
    
}

void LobbyScene::ballani(float dt)
{
    {
        auto scaleani = Sequence::create(ScaleTo::create(0.08, 1.1, 0.9),
                                         ScaleTo::create(0.08, 0.9, 1.1), ScaleTo::create(0.08, 1.0, 1.0), ScaleTo::create(0.08, 1.1, 0.9), ScaleTo::create(0.08, 0.9, 1.1), ScaleTo::create(0.08, 1.0, 1.0)/*, CallFuncN::create(this, callfuncN_selector(LobbyScene::BallAniCallback))*/, nullptr);
        
        for (int i = 0; i < 5; i++)
        {
            auto node = getChildByTag(i + 20);
            /*node->stopAllActions();*/
            node->runAction(Sequence::create(DelayTime::create(i *0.50), scaleani, nullptr));
        }
    }
    
}


int  LobbyScene::XygGetToday()
{
    int day = 1900;
    time_t rawtime;
    struct tm* timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    
    day += timeinfo->tm_year;
    day = day * 100 + timeinfo->tm_mon + 1;
    day = day * 100 + timeinfo->tm_mday;
    
    return day;
}


int LobbyScene::getDayCnt(const char* key)
{
    int val = UserDefault::getInstance()->getIntegerForKey(key,0);
    if (val <= 0)
    {
        return 0;
    }
    int day = XygGetToday();
    if (val / 100 != day)
    {
        return 0;
    }
    else
    {
        return val % 100;
    }
}

void LobbyScene::addDayCnt(const char* key)
{
    int val = getDayCnt(key);
    UserDefault::getInstance()->setIntegerForKey(key, XygGetToday() * 100 + val + 1);
    UserDefault::getInstance()->flush();
}
