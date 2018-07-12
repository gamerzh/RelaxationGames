#pragma once
#include "cocos2d.h"
#include "FootMan.h"

//考虑到球员的图层问题,球员会统一添加到GameLayer上

class FootballTeam : public cocos2d::Node {
public:
	static FootballTeam* create(int teamId);
	virtual bool init(int teamid);
	std::vector<FootMan*> getFootManVector();

private:
	FootMan* m_pControllingPlayer;//当前控球的队员
	FootMan* m_pSupportingPlayer;//支援的队员
	FootMan* m_pReceivingPlayer;//接球的队员
	FootMan* m_pPlayerClosestToBall;//离球最近的队员
	int teamId = 0;//球队编号
	std::vector<FootMan*> footManVector;//球员队列
};