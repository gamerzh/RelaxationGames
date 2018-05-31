#include "Hero.h"
USING_NS_CC;

bool Hero::init() {
	if (!Sprite::init()) {
		return false;
	}
	this->speed_y = SPEED_Y;
	initWithFile("HelloWorld.png");
	setScale(0.2f);
	scheduleUpdate();
	return true;
}

void Hero::addPhysicsHero() {
	auto hero = Sprite::create("HelloWorld.png");
	hero->setScale(0.2f);
	hero->setPosition(360, 640);
	addChild(hero);
}

void Hero::flipSpeedY(){
	speed_y = speed_y * -1;
}

void Hero::update(float dt) {
	float py = getPositionY();
	this->setPositionY(py-speed_y);
}