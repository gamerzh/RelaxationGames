#pragma once
#include "cocos2d.h"
#include "FootMan.h"


class FootballTeam : public cocos2d::Node {
public:
	static FootballTeam* create(int teamId,bool teamInLeftField = true);
	virtual bool init(int teamid,bool teamInLeftField);
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
