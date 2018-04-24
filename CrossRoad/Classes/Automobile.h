#pragma once
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

enum AutomobileType
{
	car1,
	car2,
	car3
};

class Automobile : public Sprite {
	
public:
	static Automobile* create(AutomobileType type,Point pos);
	virtual bool init(AutomobileType type, Point pos);
private:
	string  getFileNameByType(AutomobileType type);
	string  getSpeedByType(AutomobileType type); 
};