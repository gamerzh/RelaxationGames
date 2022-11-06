#ifndef __NET_H__
#define __NET_H__
#include "cocos2d.h"
#include "fish/FishManage.h"
#include "bullet/Bullet.h"
using namespace cocos2d;

#define NET_TYPE_0 0
#define NET_TYPE_1 1
#define NET_TYPE_2 2
#define NET_TYPE_3 3
#define NET_TYPE_4 4

class Net :public Sprite{
public:
	virtual bool init();
	CREATE_FUNC(Net);
	void setBullet(Bullet* bullet);
	void initNetByType();
	void checkCatchFish();
	std::vector<OBBEX> getObbs();
private:
	void initAniByType(int ui_type, int net_type);
	std::string getFrameNameByType(int ui_type, int net_type);
	Bullet*m_bullet;
	int m_netType;

	bool isRobot;
};
#endif
