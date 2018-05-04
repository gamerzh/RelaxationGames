#pragma once
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

#define default_tmx_width 80//默认的每一格TiledMap宽度
#define default_tmx_height 74//默认的每一格TiledMap高度

struct TMCarInfo
{
	int type;
	int direction;
	float interval;
	float speed;
	Point position;
};

struct TMBlockInfo
{
	int type;
	float width;
	float height;
	Point position;
};

struct TMWoodInfo
{
	int type;
	float width;
	float height;
	Point position;
};

enum MapNodeType
{
	type1,
	type2,
	type3
};

class MapNode : public Node {
 
public:
	static MapNode* create(MapNodeType type);
	static int getTMXPerGradutaionLength();
	virtual bool init(MapNodeType type);
	TMXLayer* getTMXBackground();
	TMXLayer* getTMXWater();
	Point getHeroStartPos();
	vector<TMCarInfo> getEnemyInfoList();
	vector<TMBlockInfo> getBlockInfoList();
	vector<TMWoodInfo> getWoodInfoList();
	CC_SYNTHESIZE(MapNodeType, mapNodeType, MapNodeType);
private:
	TMXTiledMap* _tileMap = NULL;
	TMXLayer* background = NULL;
	TMXLayer* block = NULL;
	string  getFileNameByType(MapNodeType type);
};