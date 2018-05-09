#pragma once
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

#define defult_tmx_x_num 18
#define defult_tmx_y_num 40
#define default_tmx_width 80//默认的每一格TiledMap宽度
#define default_tmx_height 74//默认的每一格TiledMap高度

enum WoodType
{
	wood_short = 1,
	wood_long = 2,
	leaf = 5,
	water
};

enum DirectionType
{
	move_left = 1,
	move_rigth
};

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
	float width;
	float height;
	Point position;
};

struct TMWoodInfo
{
	int type;
	int direction;
	float time;
	Point position;
};

struct TMGoldInfo
{
	int type;
	Point pos;
	Size size;
};

class MapNode : public Node {
 
public:
	static MapNode* create(int type);
	static int getTMXPerGradutaionLength();
	virtual bool init(int type);
	Point getHeroStartPos();
	vector<TMCarInfo> getEnemyInfoList();
	vector<TMBlockInfo> getBlockInfoList();
	vector<TMWoodInfo> getWoodInfoList();
	vector<TMGoldInfo> getGoldInfoList();
	vector<int> getWaterLineNumber();
	CC_SYNTHESIZE(int, mapNodeType, MapNodeType);
private:
	TMXTiledMap* _tileMap = NULL;
	string  getFileNameByType(int type);
};