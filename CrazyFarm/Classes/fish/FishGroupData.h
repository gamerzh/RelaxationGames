#pragma once
#include "cocos2d.h"

using namespace cocos2d;

struct singleTypefishGroup
{
	int fishID;
	int fishCount;
	int fishRoute;
	float IntervalCreateTime;
	Vec2 startPos;
};

struct FishGroup
{
	int tag;
	std::vector <singleTypefishGroup>  singleTypefishGroups;
};

class FishGroupData{
public:
	static FishGroupData* getInstance();
	static void destroyInstance();
	bool loadConfig();
	FishGroup getGroupBytag(int tag);
private:
	std::map<int, FishGroup> map_TagToFishGroup;
	static FishGroupData* _pInstance;

};