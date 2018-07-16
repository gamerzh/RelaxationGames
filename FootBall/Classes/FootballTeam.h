#pragma once
#include "cocos2d.h"
#include "FootMan.h"

//考虑到球员的图层问题,球员会统一添加到GameLayer上

class FootballTeam : public cocos2d::Node {
public:
	static FootballTeam* create(int teamId);
	virtual bool init(int teamid);
	std::vector<FootMan*> getFootManVector();
	void setTeamInLeftField(bool b);
private:
	bool teamInLeftField = true;
	FootMan* m_pControllingPlayer;
	FootMan* m_pSupportingPlayer;
	FootMan* m_pReceivingPlayer;
	FootMan* m_pPlayerClosestToBall;
	int teamId = 0;
	std::vector<FootMan*> footManVector;
	std::vector<cocos2d::Vec2> getLeftFieldVec2();
	std::vector<cocos2d::Vec2> getRightFieldVec2();
};
