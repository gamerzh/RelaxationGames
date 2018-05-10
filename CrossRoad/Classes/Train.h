#pragma once
#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Train : public Sprite
{
public:
	static Train* create(Camera* _camera, Point pos);
	virtual bool init(Camera* _camera,Point pos);
private:
	Camera* _camera;
	int dir = 0;
	float speed = 30;
	float trainInterval = 10;
	float passTime = 0;
	Point position;
	Sprite* myTrain;
	void trainLightAnim(CallFunc* call);
	void update(float dt);
	void moveTrain(CallFunc* call);
};