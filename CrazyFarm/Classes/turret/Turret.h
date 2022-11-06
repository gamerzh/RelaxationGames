#ifndef __TURRET_H__
#define __TURRET_H__

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class Turret: public Sprite{
public:
      virtual bool init();
	  CREATE_FUNC(Turret);
	  void initWithType(int type); 
	  void upgradeTurret();
	  void degradeTurret();


	  void changeToNewTurret(int uiid);

	  void changeToLightTurret();
	  void changeToNormalTurret();
	  void shoot();
	  Point getTampionPos(){ return emptySp->convertToWorldSpace(Point(0, 0)); }

	  Point getLightLaughPos(){ return lightSp->convertToWorldSpace(Point(0, 0)); }
private:
	  int turretType;
	  Sprite* emptySp;

	  Sprite*lightSp;
	  CC_SYNTHESIZE(bool, isrobot, IsRobot);
	
	  

};
#endif