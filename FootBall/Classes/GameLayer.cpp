#include "GameLayer.h"
#include "GameStatus.h"
#include "math.h"
#include "Setting.h"
#include "FootballTeam.h"
#include "GlobalProperty.h"
#include "GeometryTools.h"
USING_NS_CC;

bool GameLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    GameStatus::getInstance()->setPlayerTeamId(1);
    
    createFootballFild();
    
    createFootBallTeam();
    
    heroRocker = Rocker::create(Vec2(visibleSize.width / 8, visibleSize.height / 5));
    addChild(heroRocker);
    heroRocker->openRocker();
    
    playerCamera = Camera::createOrthographic(visibleSize.width, visibleSize.height, 1024, -1024);
    playerCamera->setCameraFlag(CameraFlag::USER1);
    playerCamera->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    addChild(playerCamera);
    
    footBall = Ball::create(playerCamera);
    footBall->setPosition(1080, 680);
    footBall->setCameraMask((int)CameraFlag::USER1);
    addChild(footBall, FOOTBALL_LOCAL_ZORDER);
    GameStatus::getInstance()->setGameBall(footBall);//HACK 为了FootMan类可以获取到ball的位置
    
    loadGameLayerUI();
    
    scheduleUpdate();
    
//    auto listener = EventListenerTouchAllAtOnce::create();
//    listener->onTouchesBegan = CC_CALLBACK_2(GameLayer::onTouchesBegan, this);
//    listener->onTouchesMoved = CC_CALLBACK_2(GameLayer::onTouchesMoved, this);
//    listener->onTouchesEnded = CC_CALLBACK_2(GameLayer::onTouchesEnded, this);
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

//void GameLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event  *event)
//{
//    for ( auto &item: touches )
//    {
//        auto touch = item;
//        auto location = touch->getLocation();
//    }
//}
//
//void GameLayer::onTouchesMoved(const std::vector<Touch*>& touches, Event  *event)
//{
//    for( auto &item: touches)
//    {
//        auto touch = item;
//         auto location = touch->getLocation();
//    }
//}
//
//void GameLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event  *event)
//{
//    for ( auto &item: touches )
//    {
//        auto touch = item;
//         auto location = touch->getLocation();
//    }
//}

void GameLayer::createFootballFild() {
    auto black = Sprite::create("green.jpg");
    black->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    black->setPosition(0, 0);
    black->setCameraMask((int)CameraFlag::USER1);
    addChild(black, FOOTBALL_LOCAL_ZORDER-1);
    
    auto leftGoal = Sprite::create("door_left.png");
    leftGoal->setPosition(145,750);
    leftGoal->setCameraMask((int)CameraFlag::USER1);
    addChild(leftGoal, FOOTBALL_LOCAL_ZORDER+1);
    
    auto rightGoal = Sprite::create("door_right.png");
    rightGoal->setCameraMask((int)CameraFlag::USER1);
    rightGoal->setPosition(1990, 750);
    addChild(rightGoal, FOOTBALL_LOCAL_ZORDER + 1);
}

void GameLayer::createFootBallTeam() {
    playerTeam = FootballTeam::create(1,true);
    addChild(playerTeam,FOOTBALL_LOCAL_ZORDER*2);
    GameStatus::getInstance()->currentPlayerTeam = playerTeam->getFootManVector();
    for (auto var:  GameStatus::getInstance()->currentPlayerTeam)
    {
        var->setCameraMask((int)CameraFlag::USER1);
        var->changeFootManState(FootManState::waiting);
        addChild(var);
    }
    computerTeam = FootballTeam::create(2,false);
    addChild(computerTeam,FOOTBALL_LOCAL_ZORDER*2);
    GameStatus::getInstance()->currentComputerTeam = computerTeam->getFootManVector();
    for (auto var2:  GameStatus::getInstance()->currentComputerTeam)
    {
        var2->setCameraMask((int)CameraFlag::USER1);
        var2->changeFootManState(FootManState::waiting);
        addChild(var2);
    }
}


void GameLayer::loadGameLayerUI() {
    auto btn1 = MenuItemImage::create("pass_ball_1.png","pass_ball_2.png",CC_CALLBACK_0(GameLayer::passAndTackle,this));
    auto btn2 = MenuItemImage::create("shoot_ball_1.png", "shoot_ball_2.png", CC_CALLBACK_0(GameLayer::shoot, this));
    auto btn3 = MenuItemImage::create("speed_ball_1.png", "speed_ball_2.png", CC_CALLBACK_0(GameLayer::speedMan, this));
    auto menu = Menu::create(btn1, btn2, btn3, NULL);
    btn1->setPosition(1070, 80);
    btn2->setPosition(1160, 190);
    btn3->setPosition(1190, 320);
    menu->setPosition(0,0);
    addChild(menu,50);
    auto set = Setting::create();
    addChild(set, 100);
//    ui::Button
}


void GameLayer::passAndTackle() {
    //传球和铲球
    if(currentControlFootMan == footBall->getOwerMan()){
        //玩家在控球,传出：离自己最近的己方球员
        //传球动作由球队来进行,
        auto mate = playerTeam->getPassBallFootMan();
        if(NULL != mate){
            footBall->setBallPass(mate->getPosition());
        }
        playerTeam->passBallToTeammate(currentControlFootMan,mate);
    }else{
        //铲球
        currentControlFootMan->doSlideTackle();
    }
}

void GameLayer::shoot() {
    
    if(NULL != currentControlFootMan && currentControlFootMan == footBall->getOwerMan()){
        currentControlFootMan->doShoot();
        //设置射门的目标点
        if(playerTeam->getFootBallTeamId() == currentControlFootMan->getFootManTeamId()){
            footBall->setBallShoot(playerTeam->getTeamShootPoint());
        }else{
            footBall->setBallShoot(computerTeam->getTeamShootPoint());
        }
    }
}

void GameLayer::speedMan() {
    //球队的控球队员短距离加速
}


bool GameLayer::checkFootManInShootArea(FootMan* man){
    if(playerTeam->getFootBallTeamId() == man->getFootManTeamId()){
        return playerTeam->getAttackShootRect().containsPoint(man->getPosition());
    }else if(computerTeam->getFootBallTeamId() == man->getFootManTeamId()){
        return computerTeam->getAttackShootRect().containsPoint(man->getPosition());
    }
    return false;
}

void GameLayer::manLootBall() {
    std::vector<FootMan*> alternativeMan;
    for (auto var1 :  GameStatus::getInstance()->currentPlayerTeam) {
        float dis = GeometryTools::calculateDistance(var1->getPosition(),footBall->getPosition());
        if (dis < owner_ball_max_dis) {
            alternativeMan.push_back(var1);
        }
    }
    for (auto var2 :  GameStatus::getInstance()->currentComputerTeam) {
        float dis = GeometryTools::calculateDistance(var2->getPosition(),footBall->getPosition());
        if (dis < owner_ball_max_dis) {
            alternativeMan.push_back(var2);
        }
    }
    if (alternativeMan.size() == 0) {
        return;
    }
    int area = (int)alternativeMan.size();
    auto man = alternativeMan.at(random(0, area - 1));
    footBall->setOwnerMan(man);
    if(man->getFootManTeamId() == playerTeam->getFootBallTeamId()){
        playerTeam->setControllingMan(man);
        currentControlFootMan = man;
    }else{
        computerTeam->setControllingMan(man);
    }
}


void GameLayer::update(float dt) {
    if (footBall->getBallState() == ball_is_free) {
        manLootBall();
    }
    FootMan* controlMan = nullptr;
    int min = INT_FAST32_MAX;
    for (auto mine :  GameStatus::getInstance()->currentPlayerTeam) {
        auto dis = GeometryTools::calculateDistance(footBall->getPosition(), mine->getPosition());
        if (dis < min) {
            controlMan = mine;
            min = dis;
        }
    }
    if (nullptr != controlMan && nullptr != heroRocker) {
        auto angle = heroRocker->getRockerAngle();
        if (angle != 0) {
            if(controlMan->getFootManState() != FootManState::running){
                controlMan->changeFootManState(FootManState::running);
            }
            controlMan->setFootManAngle(angle);
        }
    }
    
}

void GameLayer::onEnter() {
    Layer::onEnter();
    addCustomEvent();
}


void GameLayer::onExit() {
    Layer::onExit();
    
}

void GameLayer::addCustomEvent() {
    auto footballInGoal = EventListenerCustom::create(foot_ball_in_goal, [=](EventCustom* event) {
        //收到足球进门的消息
        auto result = static_cast<char*>(event->getUserData());
        if(playerTeam->getTeamAttackDirection() == result){
            playerTeam->teamScore +=1;
        }
        if(computerTeam->getTeamAttackDirection() == result){
             computerTeam->teamScore +=1;
        }
        //延迟2秒,2秒后重置场景,球员和球回到初始位置 TODO
        schedule([=](float dt){
            footBall->replacement();
            for (auto var1 : GameStatus::getInstance()->currentPlayerTeam) {
                var1->replacement();
            }
            for (auto var2 : GameStatus::getInstance()->currentComputerTeam) {
                var2->replacement();
            }
        }, 0, 1, 2,"rest_game");
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(footballInGoal, 1);
}

void GameLayer::removeCustomEvent() {
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(foot_ball_in_goal);
}
