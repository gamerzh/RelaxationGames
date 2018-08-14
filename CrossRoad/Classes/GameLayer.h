#pragma once
#include "cocos2d.h"
#include "MapNode.h"
#include "Player.h"
#include "Automobile.h"
#include "Block.h"
#include "Wood.h"
#include "GoldIcon.h"
#include "Train.h"
USING_NS_CC;

//#define MapLayerZorder 10
#define PlayerZorder 2
#define MaxZorder 5000
#define SCHEDULE_CAMERA_X "carema_move_x"

enum Gesture
{
	forward,
	backwards,
	left,
	right
};

class GameLayer : public Layer {
public:
	static GameLayer* create(Camera* ca);
	virtual bool init(Camera* ca);
	void addTouchListener();
	bool onTouchBegan(Touch *touch, Event  *event) override;
	void onTouchMoved(Touch *touch, Event  *event) override;
	void onTouchEnded(Touch *touch, Event  *event) override;
private:
	Size win = Director::getInstance()->getWinSize();
	int used_map_node = 0;
	bool needAddMap = false;
	bool isShowGameOver = false;
	bool playerInWaterRect = false;
	const float originalPlayerOffsetX = default_tmx_width*4.5;
	const float originalPlayerOffsetY = default_tmx_height*4;
	float cruentPlayerOffsetX = 0;
	float cruentPlayerOffsetY = 0;
	float cameraMoveX= 0;
	float cameraMoveY = 0;
	float cameraMoveStepX = 1.2;
	float cameraMoveStepY = 2.0;
	float playerStayTime = 0;
	bool allowJump = true;
	float jumpInterval = 0.30f;
	const float randomPrideTime = 25;
	float  randomPassTime = 0;
	float invincibleTime = 10;
	Camera* _camera;
	Vec2 preTouchPoint;
	Gesture playerGesture;
	Player* player;
	vector<MapNode*> mapList;
	vector<Automobile*> autoList;
	vector<Wood*> woodList;
	vector<Block*> treeList;
	vector<GoldIcon*> goldList;
	vector<Train*> trainList;
	void cameraMoveCheck();
	void initGameMap();
	void addGameMap();
	void createAutomoblie(Camera* camera,int type, int direction, int speed, int interval, Point pos);
	void createHouseAndTree(int type, Size size,Point pos);
	void createWood(int type, int dir, int speed, Point pos);
	void createGold(Point position);
	void createTrain(Point position);
	void checkMapInScene(float dt);
    void update(float dt);
	void changeCameraMoveStep();
	void moveCameraX();//在X轴上移动相机
	void cancelMoveCameraX();
	void showGameOver(int type);
	void hawkKillPlayer();
	void goldPickCheck();
	void recycleResource();
};
