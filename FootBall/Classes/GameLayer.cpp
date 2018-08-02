#include "GameLayer.h"
#include "GameStatus.h"
#include "math.h"
#include "Setting.h"
#include "FootballTeam.h"
#include "GlobalProperty.h"
#include "GeometryTools.h"
#include "UserData.h"
#include "DreamLayer.h"
USING_NS_CC;

bool GameLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
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
    footBall->setPosition(1000, 680);
    footBall->setCameraMask((int)CameraFlag::USER1);
    addChild(footBall, FOOTBALL_LOCAL_ZORDER);
    GameStatus::getInstance()->setGameBall(footBall);//HACK:为了FootMan类可以获取到ball的位置
    GameStatus::getInstance()->setGameState(GameStatus::GameState::game_start);//游戏等待开始
    
    loadGameLayerUI();
    
    auto dream = DreamLayer::create(5);
    addChild(dream,300);
    
    scheduleUpdate();
    
    return true;
}

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
    playerTeam = FootballTeam::create(PLAYER_TEAM_ID,true);
    addChild(playerTeam,FOOTBALL_LOCAL_ZORDER*2);
    GameStatus::getInstance()->setPlayerTeam(playerTeam);
    
    for (auto var: playerTeam->getFootManVector())
    {
        var->setCameraMask((int)CameraFlag::USER1);
        var->changeFootManState(FootMan::FootManState::waiting);
        addChild(var);
    }
    computerTeam = FootballTeam::create(GameStatus::getInstance()->getCurrentSelectedLevel()+2,false);
    addChild(computerTeam,FOOTBALL_LOCAL_ZORDER*2);
    GameStatus::getInstance()->setComputerTeam(computerTeam);
    for (auto var2: computerTeam->getFootManVector())
    {
        var2->setCameraMask((int)CameraFlag::USER1);
        var2->changeFootManState(FootMan::FootManState::waiting);
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
    auto skillBg = Sprite::create("skill_bg.png");
    skillBg->setPosition(1220, 280);
    addChild(skillBg,50);
    auto num = Label::createWithSystemFont(StringUtils::format("%d",UserData::getInstance()->getPlayerSkillNum()), "arial", 22);
    num->setColor(Color3B::BLACK);
    num->setAnchorPoint(Point::ANCHOR_MIDDLE);
    num->setPosition(1220, 280);
    addChild(num,50);
}


void GameLayer::passAndTackle() {
    if(GameStatus::getInstance()->getGameState() == GameStatus::GameState::game_start){
        GameStatus::getInstance()->setGameState(GameStatus::GameState::game_playing);
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(foot_ball_game_start);
    }
    //传球和铲球
    if(playerTeam->m_pControllingPlayer == footBall->getOwerMan()){
        //玩家在控球,传出：离自己最近的己方球员
        //传球动作由球队来进行,
        auto mate = playerTeam->m_pSupportingPlayer;
        if(NULL != mate){
            //            log("Pass target pos (%f,%f)",mate->getPositionX(),mate->getPositionY());
            footBall->setBallPass(mate->getPosition());
        }
    }else{
        //铲球
        playerTeam->m_pControllingPlayer->doSlideTackle();
    }
}

void GameLayer::shoot() {
    if(GameStatus::getInstance()->getGameState() == GameStatus::GameState::game_start){
        GameStatus::getInstance()->setGameState(GameStatus::GameState::game_playing);
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(foot_ball_game_start);
    }
    if(NULL != playerTeam->m_pControllingPlayer && playerTeam->m_pControllingPlayer == footBall->getOwerMan()){
        playerTeam->doTeamShoot();
    }
}

void GameLayer::speedMan() {
    //球队的控球队员短距离加速
    playerTeam->manSpeedUp();
    if(GameStatus::getInstance()->getGameState() == GameStatus::GameState::game_start){
        GameStatus::getInstance()->setGameState(GameStatus::GameState::game_playing);
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(foot_ball_game_start);
    }
}

void GameLayer::replacementAll(){
    footBall->replacement();
    for (auto var1 : playerTeam->getFootManVector()) {
        var1->replacement();
    }
    for (auto var2 : computerTeam->getFootManVector()) {
        var2->replacement();
    }
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
    for (auto var1 :  playerTeam->getFootManVector()) {
        float dis = GeometryTools::calculateDistance(var1->getPosition(),footBall->getPosition());
        if (dis < owner_ball_max_dis) {
            alternativeMan.push_back(var1);
        }
    }
    for (auto var2 : computerTeam->getFootManVector()) {
        float dis = GeometryTools::calculateDistance(var2->getPosition(),footBall->getPosition());
        if (dis < owner_ball_max_dis) {
            alternativeMan.push_back(var2);
        }
    }
    if (alternativeMan.size() == 0) {
        return;
    }
    //关于球权的获取
    for(auto man : alternativeMan){
        if(man->getCanObtainBall()){
            footBall->setOwnerMan(man);
            if(man->getFootManTeamId() == playerTeam->getFootBallTeamId()){
                playerTeam->setControllingMan(man);
                playerTeam->setTeamStatus(TeamStatus::attack);
                computerTeam->setTeamStatus(TeamStatus::defend);
            }else{
                computerTeam->setControllingMan(man);
                playerTeam->setTeamStatus(TeamStatus::defend);
                computerTeam->setTeamStatus(TeamStatus::attack);
            }
            return;
        }
    }
}


void GameLayer::update(float dt) {
    special_time += dt;
    if(special_time>DREAM_SPECIAL_TIME){
        auto dream = DreamLayer::create(6);
        addChild(dream,300);
        special_time = 0;
    }
    
    if(!canChangeControlMan){
        changeControlManInterval -= dt;
        if(changeControlManInterval<0){
            canChangeControlMan = true;
            changeControlManInterval = 1.5f;
        }
    }
    
    if (footBall->getBallState() == ball_is_free) {
        manLootBall();
    }
    FootMan* controlMan = nullptr;
    int min = INT_FAST32_MAX;
    for (auto mine : playerTeam->getFootManVector()) {
        auto dis = GeometryTools::calculateDistance(footBall->getPosition(), mine->getPosition());
        if (dis < min && !mine->isGoalkeeper && canChangeControlMan) {
            controlMan = mine;
            min = dis;
        }
    }
    if(nullptr != controlMan){
        controlingFootman = controlMan;
        for (auto var :playerTeam->getFootManVector()) {
            if(var == controlingFootman){
                var->showControlCircle(true);
            }else{
                var->showControlCircle(false);
            }
        }
    }
    if (nullptr != controlingFootman && nullptr != heroRocker) {
        canChangeControlMan = false;
        auto angle = heroRocker->getRockerAngle();
        if (angle != 0) {
            controlingFootman->changeFootManState(FootMan::FootManState::running);
            controlingFootman->openSimpleAI(false);
            controlingFootman->setFootManAngle(angle);
        }
    }
    
}

void GameLayer::onEnter() {
    Layer::onEnter();
    addCustomEvent();
}


void GameLayer::onExit() {
    Layer::onExit();
    removeCustomEvent();
}

void GameLayer::addCustomEvent() {
    auto footballInGoal = EventListenerCustom::create(foot_ball_in_goal, [=](EventCustom* event) {
        //收到足球进门的消息
        auto result = static_cast<char*>(event->getUserData());
        if(playerTeam->getTeamAttackDirection() == result){
            playerTeam->teamScore += 1;
            auto dream = DreamLayer::create(8);
            addChild(dream);
        }
        if(computerTeam->getTeamAttackDirection() == result){
            computerTeam->teamScore += 1;
        }
        //延迟2秒,2秒后重置场景,球员和球回到初始位置
        schedule([=](float dt){
            GameStatus::getInstance()->setGameState(GameStatus::GameState::game_start);
            replacementAll();
            if(playerTeam->getTeamAttackDirection() == result){
                footBall->setPositionX(1200);
            }
            if(computerTeam->getTeamAttackDirection() == result){
                footBall->setPositionX(1000);
            }
        }, 0, 1, 2,"rest_game");
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(footballInGoal, 1);
    
    auto trackleSuccess = EventListenerCustom::create(foot_man_trackle_success, [=](EventCustom* event){
        //铲球成功,控球队员摔倒
        auto man = footBall->getOwerMan();
        if(NULL != man){
            man->doTumble();
        }
        footBall->setBallFree();
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(trackleSuccess, 1);
    
    auto gameStart = EventListenerCustom::create(foot_ball_game_start, [=](EventCustom* event) {
        //收到通知开始开球,除了目前被玩家选中的球员,其余的球员打开AI
        playerTeam->setFootballTeamAI(playerTeam->m_pControllingPlayer);
        computerTeam->setFootballTeamAI();
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(gameStart, 1);
}

void GameLayer::removeCustomEvent() {
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(foot_ball_in_goal);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(foot_man_trackle_success);
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(foot_ball_game_start);
}
