#pragma once
#include "cocos2d.h"

#define HERO_BALL_RADIUS 100
#define HERO_MOVE_PATH 154
#define SPEED_Y 7

class Hero : public cocos2d::Sprite {
public:
	virtual bool init();
	CREATE_FUNC(Hero);
	void flipSpeedY();
	bool isDirectionDown();
	
private:
	Node * actionNode;
	int currentMod = 0;
	float speed_y = 0;
	float moveupPath = 0;
	void addPhysicsHero();
	void loadHeroAnim1();
	void loadHeroAnim2();
	void loadHeroAnim3();
	void loadHeroAnim4();
	void loadHeroAnim5();
	void loadHeroAnim6();
	void loadHeroAnim7();
	void changeHeroSkin(int id);
	void update(float dt);
};  