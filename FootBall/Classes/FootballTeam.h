#pragma once
#include "cocos2d.h"
#include "FootMan.h"

//球队状态
enum TeamStatus{
    attack,
    defend,
    neutrality
};

class FootballTeam : public cocos2d::Node {
public:
	static FootballTeam* create(int teamId,bool teamInLeftField = true);
	virtual bool init(int teamid,bool teamInLeftField);
	std::vector<FootMan*> getFootManVector();
	void setTeamInLeftField(bool b);
    cocos2d::Rect getAttackShootRect();
    int getFootBallTeamId();
    FootMan* getPassBallFootMan();//传球的目标
    TeamStatus getTeamStatus();
    void setTeamStatus(TeamStatus s);
    void setControllingMan(FootMan* man);
    void passBallToTeammate(FootMan* controlMan,FootMan* supportMan);//队员之间相互传球
private:
    TeamStatus teamState;
    int teamId = 0;
	bool teamInLeftField = true;
	FootMan* m_pControllingPlayer;//当前控球的球员
	FootMan* m_pSupportingPlayer;//最佳接球人员
	std::vector<FootMan*> footManVector;
	std::vector<cocos2d::Vec2> getLeftFieldVec2();
	std::vector<cocos2d::Vec2> getRightFieldVec2();
    void logicUpdate(float dt);
};
