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
    schedule(schedule_selector(FootballTeam::logicUpdate), 1);
    scheduleUpdate();
    return true;
}


std::vector<FootMan*> FootballTeam::getFootManVector() {
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
    return footManVector;
}

int FootballTeam::getFootBallTeamId(){
    return this->teamId;
}

void FootballTeam::setTeamInLeftField(bool b) {
    this->teamInLeftField = b;
}

std::vector<Vec2> FootballTeam::getLeftFieldVec2() {
    std::vector<Vec2> left;
    left.push_back(Vec2(1000,675));
    left.push_back(Vec2(710,850));
    left.push_back(Vec2(710,350));
    left.push_back(Vec2(400,675));
    return left;
}

std::vector<Vec2> FootballTeam::getRightFieldVec2() {
    std::vector<Vec2> right;
    right.push_back(Vec2(1200,675));
    right.push_back(Vec2(1500,850));
    right.push_back(Vec2(1500,350));
    right.push_back(Vec2(1700,675));
    return right;
}

cocos2d::Vec2 FootballTeam::getTeamShootPoint(){
    if(!teamInLeftField){
        return Vec2(200,650);
    }else{
        return Vec2(2000,650);
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

void FootballTeam::startAttack(){
    this->teamState = attack;
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
    }else{
        //TODO
    }
}

void FootballTeam::update(float dt){
    if(NULL != getChildByTag(1000)){
        ((LabelAtlas*)getChildByTag(1000))->setString(StringUtils::format("0%d",teamScore));
    }
    //发动进攻
    if(m_pControllingPlayer != NULL && this->teamState == TeamStatus::attack){
        //让自己的球队进行进攻
        //持球队员跑向去前场，其余队员到中场和前场接应
        //在射门区域里随机一个位置,持球队员成功跑到位置后射门
        auto rect = getAttackShootRect();//获得射门区域
        if(footManAttackPos == Vec2(0,0)){
            footManAttackPos = Vec2(random(rect.getMinX(), rect.getMaxX()),random(rect.getMinY(), rect.getMaxY()));
        }
        m_pControllingPlayer->runToPositon(footManAttackPos,CallFunc::create([=](){
            //到达指定位置射门
            m_pControllingPlayer->doShoot();
            GameStatus::getInstance()->getGameBall()->setBallShoot(getTeamShootPoint());
            footManAttackPos = Vec2(0,0);
            this->teamState = TeamStatus::neutrality;
        }));
    }
}

void FootballTeam::onEnter(){
    Node::onEnter();
    auto gameStart = EventListenerCustom::create(foot_ball_game_start, [=](EventCustom* event) {
        //收到通知开始开球,除了目前被玩家选中的球员,其余的球员打开AI
        for(auto var :footManVector ){
            if(var != m_pControllingPlayer){
                var->controlSimpleAI(true);
            }
        }
    });
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(gameStart, 1);
}

void FootballTeam::onExit(){
    Node::onExit();
    Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(foot_ball_game_start);
}
