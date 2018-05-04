#include "Wood.h"

Wood * Wood::create(int type)
{
	Wood* woo = new Wood();
	if (woo && woo->init()) {
		woo->autorelease();
		return woo;
	}
	else {
		CC_SAFE_DELETE(woo);
		return NULL;
	}
}

bool Wood::init()
{
	if (!Sprite::init()) {
		return false;
	}
	initWithFile("wood.png");
	scheduleUpdate();
	return true;
}

void Wood::update(float dt) {
	this->setPosition(this->getPositionX()+1,this->getPositionY());
}

float Wood::getSpeedX() {
	return 1;
}