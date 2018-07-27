#include "FootballTeam.h"
#include "GameStatus.h"
#include "GeometryTools.h"
#include "GlobalProperty.h"
USING_NS_CC;


FootballTeam* FootballTeam::create(int teamId,bool teamInLeftField) {
    auto team = new FootballTeam();
    if (team && team->init(teamId,teamInLeftField)) {
        team->autorelease();
        return team;
    }
    else {
        CC_SAFE_DELETE(team);
        return NULL;
    }
}

bool FootballTeam::init(int teamid,bool teamInLeftField) {
    if (!Node::init()) {
        return false;
    }
    this->teamInLeftField = teamInLeftField;
    this->teamId = teamid;
    
    generateFootballTeam();
    
    auto teamIcon1 = Sprite::create("team_icon_1.png");
    addChild(teamIcon1);
    
    auto score1 = LabelAtlas::create(StringUtils::format("0%d",teamScore),"num_gold.png",71,81,'0');
    score1->setTag(1000);
    score1->setAnchorPoint(Point::ANCHOR_MIDDLE);
    addChild(score1);
    
    //engery
    auto energy_bg_1 = Sprite::create("energy_bg.png");
    addChild(energy_bg_1);
    auto energy_content_1 = Sprite::create("energy_pro.png");
    auto energy_timer_1 = ProgressTimer::create(energy_content_1);
    
    energy_timer_1->setMidpoint(Vec2(0, 1));
    energy_timer_1->setBarChangeRate(Point(1, 0));
    energy_timer_1->setType(ProgressTimer::Type::BAR);
    addChild(energy_timer_1);
    energy_timer_1->setPercentage(0);
    if(teamInLeftField){
        teamIcon1->setPosition(220,655);
        score1->setPosition(430, 660);
        energy_bg_1->setPosition(430, 610);
        energy_timer_1->setPosition(430, 610);
    }else{
        teamIcon1->setPosition(1020, 655);
        score1->setPosition(850, 660);
        energy_bg_1->setPosition(850, 610);
        
        energy_timer_1->setPosition(850, 610);
    }
    schedule(schedule_selector(FootballTeam::logicUpdate), 0.5f);
    scheduleUpdate();
    return true;
}

void FootballTeam::generateFootballTeam(){
    auto currentPlayerTeamProperty = TeamInfoFactory::getInstance()->getTeamPropertyById(this->teamId);
    for (int i = 0; i < currentPlayerTeamProperty.footManVec.size(); i++) {
        auto var1 = currentPlayerTeamProperty.footManVec.at(i);
        auto foot1 = FootMan::create(this->teamId,var1,currentPlayerTeamProperty.footManVec.at(i).goalkeeper);
        if(teamInLeftField){
            foot1->setOriginPosition(getLeftFieldVec2().at(i));
            foot1->setPosition(getLeftFieldVec2().at(i));
        }else{
            foot1->setOriginPosition(getRightFieldVec2().at(i));
            foot1->setPosition(getRightFieldVec2().at(i));
            foot1->moveLeft();
        }
        footManVector.push_back(foot1);
    }
}


std::vector<FootMan*> FootballTeam::getFootManVector() {
    return this->footManVector;
}

int FootballTeam::getFootBallTeamId(){
    return this->teamId;
}

void FootballTeam::setTeamInLeftField(bool b) {
    this->teamInLeftField = b;
}

cocos2d::Vec2 FootballTeam::getGoalkeeperVec2(){
    for(auto man:footManVector){
        if(man->isGoalkeeper){
            return man->getPosition();
        }
    }
    return Vec2(0,0);
}

std::vector<Vec2> FootballTeam::getLeftFieldVec2() {
    std::vector<Vec2> left;
    left.push_back(Vec2(1000,675));
    left.push_back(Vec2(710,850));
    left.push_back(Vec2(710,350));
    left.push_back(Vec2(250,675));
    return left;
}

std::vector<Vec2> FootballTeam::getRightFieldVec2() {
    std::vector<Vec2> right;
    right.push_back(Vec2(1200,675));
    right.push_back(Vec2(1500,850));
    right.push_back(Vec2(1500,350));
    right.push_back(Vec2(1880,675));
    return right;
}

cocos2d::Vec2 FootballTeam::getTeamShootPoint(){
    // 射门的位置随机
    if(!teamInLeftField){
        Rect rect1 = Rect(100,450,60,400);//球门区域1
        return Vec2(random(rect1.getMinX(), rect1.getMaxX()),random(rect1.getMinY(),rect1.getMaxY()));
    }else{
        Rect rect2 = Rect(2000,550,60,400);//球门区域2
        return Vec2(random(rect2.getMinX(), rect2.getMaxX()),random(rect2.getMinY(),rect2.getMaxY()));
    }
}


Rect FootballTeam::getAttackShootRect(){
    if(!teamInLeftField){
        return Rect(240,200,500,900);
    }else{
        return Rect(1400,200,500,900);
    }
}

TeamStatus FootballTeam::getTeamStatus(){
    return this->teamState;
}

void FootballTeam::setTeamStatus(TeamStatus s){
    this->teamState = s;
}

void FootballTeam::setControllingMan(FootMan* man){
    this->m_pControllingPlayer = man;
}

void FootballTeam::passBallToTeammate(FootMan* controlMan,FootMan* supportMan){
    //当前有队员在控球
}

std::string FootballTeam::getTeamAttackDirection(){
    if(this->teamInLeftField){
        return "right";
    }else{
        return "left";
    }
}

void FootballTeam::setFootballTeamAI(FootMan* man){
    for (auto  var : footManVector) {
        if(NULL != man && var == man && !var->isGoalkeeper){
            var->openSimpleAI(false);
        }else{
            var->openSimpleAI(true);
        }
    }
}

bool FootballTeam::checkShootResult(){
    //判断这次射门是否成功
    //守门员默认为防守队员
    auto ballPos = GameStatus::getInstance()->getGameBall()->getPosition();
    float per  = 60;//守门员的防守值默认40，球员为30
    if(teamId == 1){
        for(auto var :GameStatus::getInstance()->getComputerTeam()->getFootManVector()){
            if(GeometryTools::calculateDistance(ballPos, var->getPosition())<150){
                per -= 30;
            }
        }
    }else{
        for(auto var :GameStatus::getInstance()->getPlayerTeam()->getFootManVector()){
            if(GeometryTools::calculateDistance(ballPos, var->getPosition())<150){
                per -= 30;
            }
        }
    }
    if(per>0){
        if(random(1, 100)<per){
            return  true;
        }
    }
    return false;
}

void FootballTeam::logicUpdate(float dt){
    //判断队伍目前的状态
    if(m_pControllingPlayer != NULL && this->teamState == TeamStatus::attack){
        //带球队员开始跑向对方球门
        //attack 进攻状态,简单判断,离自己最近的球员为最佳接应队员
        Vec2 a = m_pControllingPlayer->getPosition();
        float max = 10000;
        for (auto  var : footManVector) {
            Vec2 b = var->getPosition();
            if(GeometryTools::calculateDistance(a, b)<max && var != m_pControllingPlayer && !var->isGoalkeeper){
                m_pSupportingPlayer = var;
            }
        }
    }
    if(this->teamState == TeamStatus::defend){
        auto ball = GameStatus::getInstance()->getGameBall();
        int max = 10000;
        for(auto var : footManVector){
            float dis = GeometryTools::calculateDistance(ball->getPosition(), var->getPosition());
            if(dis<max && !var->isGoalkeeper){
                m_pCloseingPlayer  = var;
                max = dis;
            }
        }
    }
}

void FootballTeam::update(float dt){
    if(NULL != getChildByTag(1000)){
        ((LabelAtlas*)getChildByTag(1000))->setString(StringUtils::format("0%d",teamScore));
    }
    //球队进攻
    if(m_pControllingPlayer != NULL && this->teamState == TeamStatus::attack){
        //让自己的球队进行进攻
        //持球队员跑向去前场，其余队员到中场和前场接应
        //在射门区域里随机一个位置,持球队员成功跑到位置后射门
        auto rect = getAttackShootRect();//获得射门区域
        if(footManAttackPos == Vec2(0,0)){
            footManAttackPos = Vec2(random(rect.getMinX(), rect.getMaxX()),random(rect.getMinY(), rect.getMaxY()));
        }
        if(m_pControllingPlayer->getSimpleAI()){
            m_pControllingPlayer->footmanRunToTarget(footManAttackPos,20,CallFunc::create([=](){
                //到达指定位置射门
                m_pControllingPlayer->doShoot();
                if(checkShootResult()){
                    GameStatus::getInstance()->getGameBall()->setBallShoot(getTeamShootPoint());
                    footManAttackPos = Vec2(0,0);
                    this->teamState = TeamStatus::neutrality;
                }else{
                    this->teamState = TeamStatus::defend;
                    if(this->teamId == 1){
                        GameStatus::getInstance()->getGameBall()->setBallShoot(GameStatus::getInstance()->getComputerTeam()->getGoalkeeperVec2());
                    }
                   
                    //TODO:通知球员回到防守位置，球会给到对方守门员
                }
            }));
        }
    }
    //球队防守
    if(this->teamState == TeamStatus::defend && GameStatus::getInstance()->getGameState() == GameState::game_playing){
        //计算除守门员以外的球员和对方控球队员的距离
        auto cman = GameStatus::getInstance()->getGameBall()->getOwerMan();//控球队员
        if(NULL != cman){
            int max = 10000;
            FootMan* dman = nullptr;
            for(auto var : footManVector){
                float dis = GeometryTools::calculateDistance(cman->getPosition(), var->getPosition());
                if(dis<max && !var->isGoalkeeper && var->getSimpleAI()){
                    dman = var;
                    max = dis;
                }
            }
            //对防守队员下达指令,去追球
            if(nullptr != dman && dman->getSimpleAI()){
                dman->doDefend(cman->getPosition());
            }
        }
    }
}

void FootballTeam::onEnter(){
    Node::onEnter();
    
}

void FootballTeam::onExit(){
    Node::onExit();
    
}
