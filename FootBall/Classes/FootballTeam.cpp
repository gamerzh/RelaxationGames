#include "FootballTeam.h"
#include "GameStatus.h"
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
    //    Size visibleSize = Director::getInstance()->getVisibleSize();
    this->teamInLeftField = teamInLeftField;
    this->teamId = teamid;
    
    auto teamIcon1 = Sprite::create("team_icon_1.png");
    
    addChild(teamIcon1);
    
    auto score1 = LabelAtlas::create("00","num_gold.png",71,81,'0');
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
    energy_timer_1->setPercentage(50);
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
    
    
    //    auto score2 = LabelAtlas::create("00", "num_gold.png", 71, 81, '0');
    //    score2->setAnchorPoint(Point::ANCHOR_MIDDLE);
    //
    //    addChild(score2);
    //
    //    auto energy_bg_2 = Sprite::create("energy_bg.png");
    //
    //    addChild(energy_bg_2);
    //    auto energy_content_2 = Sprite::create("energy_pro.png");
    //    auto energy_timer_2 = ProgressTimer::create(energy_content_2);
    //
    //    energy_timer_2->setMidpoint(Vec2(0, 1));
    //    energy_timer_2->setBarChangeRate(Point(1, 0));
    //    energy_timer_2->setType(ProgressTimer::Type::BAR);
    //    addChild(energy_timer_2);
    //    energy_timer_2->setPercentage(50);
    //
    //    auto teamIcon2 = Sprite::create("team_icon_1.png");
    //
    //    addChild(teamIcon2);
    
    return true;
}


std::vector<FootMan*> FootballTeam::getFootManVector() {
    auto currentPlayerTeamProperty = TeamInfoFactory::getInstance()->getTeamPropertyById(this->teamId);
    for (int i = 0; i < currentPlayerTeamProperty.footManVec.size(); i++) {
        auto var1 = currentPlayerTeamProperty.footManVec.at(i);
        auto foot1 = FootMan::create(var1);
        if(teamInLeftField){
            foot1->setPosition(getLeftFieldVec2().at(i));
        }else{
            foot1->setPosition(getRightFieldVec2().at(i));
            foot1->moveLeft();
        }
        footManVector.push_back(foot1);
    }
    return footManVector;
}

void FootballTeam::setTeamInLeftField(bool b) {
    this->teamInLeftField = b;
}

std::vector<Vec2> FootballTeam::getLeftFieldVec2() {
    std::vector<Vec2> left;
    left.push_back(Vec2(1000,675));
    left.push_back(Vec2(710,850));
    left.push_back(Vec2(710,350));
    //    left.push_back(Vec2(400,675));
    return left;
}

std::vector<Vec2> FootballTeam::getRightFieldVec2() {
    std::vector<Vec2> right;
    right.push_back(Vec2(1200,675));
    right.push_back(Vec2(1500,850));
    right.push_back(Vec2(1500,350));
    //    right.push_back(Vec2(1700,675));
    return right;
}
