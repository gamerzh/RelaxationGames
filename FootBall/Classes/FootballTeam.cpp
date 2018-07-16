#include "FootballTeam.h"
#include "GameStatus.h"
USING_NS_CC;


FootballTeam* FootballTeam::create(int teamId,bool teamInLeftField) {
    auto team = new FootballTeam();
    if (team && team->init(teamId,teamInLeftField)) {
        //team->autorelease();
        //team->retain();
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
    left.push_back(Vec2(400,675));
    return left;
}

std::vector<Vec2> FootballTeam::getRightFieldVec2() {
    std::vector<Vec2> right;
    right.push_back(Vec2(1200,675));
    right.push_back(Vec2(1500,850));
    right.push_back(Vec2(1500,850));
    right.push_back(Vec2(1700,675));
    return right;
}
