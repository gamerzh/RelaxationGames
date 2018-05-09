#pragma once
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

#define defult_tmx_x_num 18
#define defult_tmx_y_num 40
#define default_tmx_width 80//默认的每一格TiledMap宽度
#define default_tmx_height 74//默认的每一格TiledMap高度

enum ObjectType
{
	wood_short = 1,
	wood_long ,
	gold,
	light,
	leaf,
	water
};

enum DirectionType
{
	move_left = 1,
	move_rigth
};

enum TreeType {
	tree_1 =1,
	tree_2,
	tree_3,
	tree_4,
	house_1,//4格
	house_2,//6格
	stone
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
	int type;
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
	Point pos;
	Size size;
};

struct TMLightInfo
{
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
	vector<TMLightInfo> getLightInfoList();
	vector<int> getWaterLineNumber();
	CC_SYNTHESIZE(int, mapNodeType, MapNodeType);
private:
	TMXTiledMap* _tileMap = NULL;
	string  getFileNameByType(int type);
};