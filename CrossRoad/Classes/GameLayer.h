#pragma once
#include "cocos2d.h"
#include "MapNode.h"
#include "Player.h"
#include "Automobile.h"
#include "Block.h"
#include "Wood.h"

USING_NS_CC;

//#define MapLayerZorder 10
#define PlayerZorder 20
#define MaxZorder 1000
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
	bool needAddMap = false;
	bool playerStandOnWood = false;
	float cameraMoveStep = 1.2;
	float cameraMoveLeft = 0;
	float cameraMoveRight = 0;
	float cameraMoveY = 0;
	Camera* _camera;
	Vec2 preTouchPoint;
	Gesture playerGesture;
	Player* player;
	vector<MapNode*> mapList;
	vector<Automobile*> autoList;
	vector<Wood*> woodList;
	vector<Block*> treeList;
	void initGameMap();
	void addGameMap();
	void createAutomoblie(Camera* camera,int type, int direction, int speed, int interval, Point pos);
	void createHouseAndTree(int type,Size size,Point pos);
	void createWood(int type, int dir, int speed, Point pos);
	void checkMapInScene(float dt);
    void update(float dt);
	void updateTreeZorder();
	void changeCameraMoveStep();
	void moveCameraX();//在X轴上移动相机
	void cancelMoveCameraX();
	
};
