#pragma once
#include "cocos2d.h"

USING_NS_CC;

class Wood : public Sprite
{

public:
	static Wood* create(Camera* ca, int type ,int direction, float time,Point position);
	virtual bool init(Camera* ca, int type, int direction, float time, Point position);
	float getSpeedX();
	std::vector<Sprite*> getBoardList();
	CC_SYNTHESIZE(int, mapIndex, MapIndex);
private:
	Size win = Director::getInstance()->getWinSize();
	std::vector<Sprite*> boardList;
	Camera* myCamera = nullptr;
	Point position;
	int woodType;
	int woodDir;
	float passtime;
	float woodTime = 0;
	float woodSpeed = 0;
	void initSpeed();
	void update(float dt);
	std::string getFileNameByType(int type);
	void drawWoods();
};