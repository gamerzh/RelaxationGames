#pragma once
#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Train : public Sprite
{
public:
	static Train* create(Camera* _camera, Point pos);
	virtual bool init(Camera* _camera,Point pos);
	Rect getTrainObjectBox();
private:
	Camera* _camera;
	int dir = 0;
	float speed = 50;
	float trainInterval = 0;
	float passTime = 0;
	Point position;
	Sprite* myTrain = nullptr;
	void trainLightAnim(CallFunc* call);
	void update(float dt);
	void moveTrain(CallFunc* call);
};