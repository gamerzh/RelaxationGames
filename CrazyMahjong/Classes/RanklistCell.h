#pragma once
#include "cocos2d.h"
#include "RanklistManager.h"
USING_NS_CC;

class RanklistCell : public Sprite
{
public:
	static RanklistCell*create(RankListItem item, int rank);
private:
	bool init(RankListItem item,int rank);

};
