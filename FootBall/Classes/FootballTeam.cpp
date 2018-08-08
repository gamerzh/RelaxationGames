#include "FootballTeam.h"
#include "GameStatus.h"
#include "GeometryTools.h"
#include "GlobalProperty.h"
#include "UserData.h"
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
    
    auto teamIcon1 = Sprite::create(getTeamIconName(teamid));
    addChild(teamIcon1);
    
    auto score1 = LabelAtlas::create(StringUtils::format("0%d",teamScore),"num_gold.png",71,81,'0');
    score1->setTag(1000);
    score1->setAnchorPoint(Point::ANCHOR_MIDDLE);
    addChild(score1);
    
    //engery
    auto energy_bg_1 = Sprite::create("energy_bg.png");
    addChild(energy_bg_1);
    energy_content_1 = Sprite::create("energy_pro.png");
    energy_content_1->setTag(100);
    auto energy_timer_1 = ProgressTimer::create(energy_content_1);
    
    energy_timer_1->setMidpoint(Vec2(0, 1));
    energy_timer_1->setBarChangeRate(Point(1, 0));
    energy_timer_1->setType(ProgressTimer::Type::BAR);
    addChild(energy_timer_1);
    energy_timer_1->setPercentage(0);
    energy_timer_1->setTag(2000);
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

std::string FootballTeam::getTeamIconName(int tid){
    if(tid == PLAYER_TEAM_ID){
        return "team_icon_1.png";
    }
    if(GameStatus::getInstance()->getCurrentGameType() == GameStatus::GameType::worldCup){
        if(UserData::getInstance()->getWorldCupLevel() == 0){
            return "team_icon_3.png";
        }
        else if(UserData::getInstance()->getWorldCupLevel() == 1){
            return "team_icon_7.png";
        } else {
            return "team_icon_4.png";
        }
    }else{
        if(tid == 8){
            return "team_icon_master.png";
        }else{
            return  StringUtils::format("team_icon_%d.png",tid);
        }
    }
}

void FootballTeam::generateFootballTeam(){
    auto id = this->teamId;
    auto currentPlayerTeamProperty = TeamInfoFactory::getInstance()->getTeamPropertyById(id);
    this->teamEnergyRate = currentPlayerTeamProperty.energyRate;
    //HACK:球队资源被删减过,给出一个不需要修改资源的方案
    if(GameStatus::getInstance()->getCurrentGameType() == GameStatus::GameType::masterCup && teamId != PLAYER_TEAM_ID){
        int team[3] = {ENEMY_TEAM_1,ENEMY_TEAM_2,ENEMY_TEAM_3};
        id = team[random(0, 2)];
    }
    for (int i = 0; i < currentPlayerTeamProperty.footManVec.size(); i++) {
        auto var1 = currentPlayerTeamProperty.footManVec.at(i);
        auto foot1 = FieldMan::create(id,var1);
        foot1->setOriginPosition(getFootmanFieldVec2().at(i));
        if(!teamInLeftField){
            foot1->moveLeft();
        }
        footManVector.push_back(foot1);
    }
    //创建守门员
    this->goalkeeper = Goalkeeper::create(id);
    this->goalkeeper->setOriginPosition(teamInLeftField?Vec2(250,675):Vec2(1880,675));
    if(!teamInLeftField){
        goalkeeper->moveLeft();
    }
}


std::vector<FieldMan*> FootballTeam::getFootManVector() {
    return this->footManVector;
}

int FootballTeam::getFootBallTeamId(){
    return this->teamId;
}

void FootballTeam::setTeamInLeftField(bool b) {
    this->teamInLeftField = b;
}

Goalkeeper* FootballTeam::getGoalkeeper(){
    return goalkeeper;
}

std::vector<Vec2> FootballTeam::getFootmanFieldVec2() {
    std::vector<Vec2> pos;
    if(teamInLeftField){
        pos.push_back(Vec2(1000,675));
        pos.push_back(Vec2(710,850));
        pos.push_back(Vec2(710,350));
    }else{
        pos.push_back(Vec2(1150,675));
        pos.push_back(Vec2(1500,850));
        pos.push_back(Vec2(1500,350));
    }
    return pos;
}

cocos2d::Vec2 FootballTeam::getTeamShootPoint(){
    // 射门的位置随机
    if(!teamInLeftField){
        Rect rect1 = Rect(80,550,50,300);//球门区域1
        return Vec2(random(rect1.getMinX(), rect1.getMaxX()),random(rect1.getMinY(),rect1.getMaxY()));
    }else{
        Rect rect2 = Rect(2000,550,60,300);//球门区域2
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

void FootballTeam::setControllingMan(FieldMan* man){
    this->m_pControllingPlayer = man;
}

std::string FootballTeam::getTeamAttackDirection(){
    if(this->teamInLeftField){
        return "right";
    }else{
        return "left";
    }
}


void FootballTeam::doTeamShoot(){
    //控球的队员播放射门动画
    if(NULL != m_pControllingPlayer){
        m_pControllingPlayer->playFootManShoot();
        //确认是否有球
        if(checkShootResult()){
            if(this->teamEnergy>= 100){
                this->teamEnergy = 0;
                GameStatus::getInstance()->getGameBall()->showBallEffect(1,this->teamId == PLAYER_TEAM_ID ? false:true);
            }
            GameStatus::getInstance()->getGameBall()->setBallShoot(getTeamShootPoint());
            goalkeeperSnapBall(false);
            footManAttackPos = Vec2(0,0);
            this->teamState = TeamStatus::neutrality;
        }else{
            //射门失败
            if(this->teamId == PLAYER_TEAM_ID){
                goalkeeperSnapBall(true);
                GameStatus::getInstance()->getPlayerTeam()->setTeamStatus(TeamStatus::defend);
                GameStatus::getInstance()->getComputerTeam()->setTeamStatus(TeamStatus::attack);
            }else{
                goalkeeperSnapBall(true);
                GameStatus::getInstance()->getPlayerTeam()->setTeamStatus(TeamStatus::attack);
                GameStatus::getInstance()->getComputerTeam()->setTeamStatus(TeamStatus::defend);
            }
        }
    }
}

void FootballTeam::goalkeeperSnapBall(bool shot){
    //射门失败,被守门员扑救成功
    auto man = GameStatus::getInstance()->getComputerTeam()->getGoalkeeper();
    if(shot){
        GameStatus::getInstance()->getGameBall()->setBallShoot(man->getFootballVec2());
    }
    schedule([=](float dt){
        man->playFootManSnap();
    }, 0, 0, 0.5,"goalkeeper");
}

bool FootballTeam::checkShootResult(){
    //判断这次射门是否成功
    if(this->teamEnergy >= 100){
        return true;
    }
    //守门员默认为防守队员
    auto ballPos = GameStatus::getInstance()->getGameBall()->getPosition();
    float per  = 60;//守门员的防守值默认40，球员为30
    if(teamId == PLAYER_TEAM_ID){
        for(auto var :GameStatus::getInstance()->getComputerTeam()->getFootManVector()){
            if(GeometryTools::calculateDistance(ballPos, var->getPosition())<200){
                per -= 30;
            }
        }
    }else{
        for(auto var :GameStatus::getInstance()->getPlayerTeam()->getFootManVector()){
            if(GeometryTools::calculateDistance(ballPos, var->getPosition())<200){
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

void FootballTeam::manSpeedUp(){
    for(auto var : footManVector){
        var->speedUp();
    }
}

void FootballTeam::logicUpdate(float dt){
    //能量条
    if(GameStatus::getInstance()->getGameState() == GameStatus::GameState::game_playing){
        if(GameStatus::getInstance()->getAddEnergy()){
            teamEnergy = 100;
            GameStatus::getInstance()->setAddEnergy(false);
        }
        if(teamEnergy <100){
            teamEnergy += teamEnergyRate*0.5;
            if(NULL != getChildByTag(2000)){
                ((ProgressTimer*)getChildByTag(2000))->setPercentage(teamEnergy);
            }
            energy_content_1->setTexture("energy_pro.png");
            
        }else{
            ((ProgressTimer*)getChildByTag(2000))->setPercentage(100);
            energy_content_1->setTexture("energy_full.png");
        }
    }
    //判断队伍目前的状态
    if(m_pControllingPlayer != NULL && this->teamState == TeamStatus::attack){
        //带球队员开始跑向对方球门
        //attack 进攻状态,简单判断,离自己最近的球员为最佳接应队员
        Vec2 a = m_pControllingPlayer->getPosition();
        float max = 10000;
        for (auto  var : footManVector) {
            Vec2 b = var->getPosition();
            if(GeometryTools::calculateDistance(a, b)<max && var != m_pControllingPlayer){
                m_pSupportingPlayer = var;
            }
        }
//        if(!m_pControllingPlayer->isGoalkeeper){
//            goalkeeperReady = true;
//        }
    }
    auto ball = GameStatus::getInstance()->getGameBall();
    int max = 10000;
    for(auto var : footManVector){
        float dis = GeometryTools::calculateDistance(ball->getPosition(), var->getPosition());
        if(dis<max){
            m_pCloseingPlayer  = var;
            max = dis;
        }
    }
}

void FootballTeam::update(float dt){
    if(NULL != getChildByTag(1000)){
        ((LabelAtlas*)getChildByTag(1000))->setString(StringUtils::format("0%d",teamScore));
    }
    if(GameStatus::getInstance()->getGameState() != GameStatus::GameState::game_playing){
        return;
    }
    //球队进攻
    if(m_pControllingPlayer != NULL && this->teamState == TeamStatus::attack){
        //让自己的球队进行进攻
        for(auto att : footManVector){
            if(att != m_pControllingPlayer){
                //持球队员跑向去前场，其余队员到中场和前场接应
                auto pos = GameStatus::getInstance()->getGameBall();
                att->manRunToTargetX(Vec2(pos->getPosition()));
            }
        }
        //在射门区域里随机一个位置,持球队员成功跑到位置后射门
        auto rect = getAttackShootRect();//获得射门区域
        if(footManAttackPos == Vec2(0,0)){
            footManAttackPos = Vec2(random(rect.getMinX(), rect.getMaxX()),random(rect.getMinY(), rect.getMaxY()));
        }
        if(m_pControllingPlayer->getSimpleAI() && GameStatus::getInstance()->getGameBall()->getOwerMan() == m_pControllingPlayer){
            m_pControllingPlayer->manRunToTarget(footManAttackPos,20,CallFunc::create([=](){
                //到达指定位置射门
                doTeamShoot();
            }));
        }
    }
    //球队防守
    if(this->teamState == TeamStatus::defend && GameStatus::getInstance()->getGameState() == GameStatus::GameState::game_playing){
        //计算除守门员以外的球员和对方控球队员的距离
        auto cman = GameStatus::getInstance()->getGameBall()->getOwerMan();//控球队员
        if(NULL != cman){
            int max = 10000;
            FieldMan* dman = nullptr;
            for(auto var : footManVector){
                float dis = GeometryTools::calculateDistance(cman->getPosition(), var->getPosition());
                if(dis<max && var->getSimpleAI()){
                    dman = var;
                    max = dis;
                }
            }
            //对防守队员下达指令,去追球
            if(nullptr != dman && dman->getSimpleAI()){
                dman->doDefend(cman->getPosition());
                for(auto var : footManVector){
                    if(dman != var){
                        var->manRunToTarget(var->getManDefendVec2(), DEFEND_BACK_OFFSET);
                    }
                }
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
