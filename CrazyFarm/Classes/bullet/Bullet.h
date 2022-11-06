#ifndef __BULLET_H__
#define __BULLET_H__
#include "cocos2d.h" 
#include "turret/PlayerTurret.h"
#include "fish/Fish.h"
#include "utill/OBB.h"
using namespace cocos2d;
using namespace std;

class Bullet:public Sprite{
public:
	virtual bool init();
	CREATE_FUNC(Bullet);
	void initBullet(TurretData turretdata, float rotation);

	CC_SYNTHESIZE(PlayerTurret*, pPlayerTurret, PlayerTurret);
	void getCoinForFish(Vector<Fish*> fishs);
	TurretData getTurretdata(){ return m_turretdata; };

	void moveToLockfish(float time,Fish*fish);
	void moveTolockFishUpadate(float dt);
	std::vector<OBBEX> getObbs();
	std::vector<OBB> getOBBByCocos();

	void stopLock();
private:
	int bulletSpeed;
	int bulletRotation;
	CC_SYNTHESIZE(Fish*, target, target);
	TurretData m_turretdata;
	string getSrcByType(int ui_type, int net_type);
	int getSpeedByType(int type);
	void update(float);
	bool checkHeightBorder(float y);//y边界检查
	bool checkWidthBorder(float x);//x边界检查
	Point getNextPostion(Point pos, float speed, float degree);
};
#endif