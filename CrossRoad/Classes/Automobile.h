#pragma once
#include "cocos2d.h"
USING_NS_CC;
using namespace std;



//ÐÐÊ»ÎïÌå
class Automobile : public Sprite {
	
public:
	static Automobile* create(Camera* camera ,int type,int direction , float speed, float interval,Point pos);
	virtual bool init(Camera* camera,int type, int direction, float speed, float interval, Point pos);
	vector<Sprite*> getCarList();
private:
	Camera* camera;
	float speed;
	float interval;
	float direction;
	float time;
	int automobileType;
	Point postion;
	vector<Sprite*> carList;
	string  getFileNameByType(int type,int direction);
	void drawCar(int type, int direction);
	
	void update(float dt);
};