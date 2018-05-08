#include "Wood.h"
#include "MapNode.h"

Wood * Wood::create(int type, int direction, float time)
{
	Wood* woo = new Wood();
	if (woo && woo->init(type,direction, time)) {
		woo->autorelease();
		return woo;
	}
	else {
		CC_SAFE_DELETE(woo);
		return NULL;
	}
}

bool Wood::init(int type, int direction, float time)
{
	if (!Sprite::init()) {
		return false;
	}
	this->woodType = type;
	this->woodDir = direction;
	this->woodTime = time;
	if(woodDir == 2) {
		this->woodSpeed = -1 * this->woodSpeed;
	}
	initWithFile(getFileNameByType(type));
	setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	scheduleUpdate();
	return true;
}

void Wood::update(float dt) {
	if (woodDir == 1) {
		this->setPosition(this->getPositionX() + woodSpeed, this->getPositionY());
	}
	else {
		this->setPosition(this->getPositionX() + woodSpeed, this->getPositionY());
		
	}
}


std::string Wood::getFileNameByType(int type) {
	if (type == 1) {
		return "wood_2.png";
	}
	else {
		return "wood_1.png";
	}
}

float Wood::getSpeedX() {
	return this->woodSpeed;
}