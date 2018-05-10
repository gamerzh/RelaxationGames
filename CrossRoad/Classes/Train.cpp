#include "Train.h"


Train* Train::create(int dir, Point pos) {
	auto tra = new Train();
	if (tra && tra->init(dir, pos)) {
		tra->autorelease();
		return tra;
	}
	else {
		CC_SAFE_DELETE(tra);
		return nullptr;
	}
}


bool Train::init(int dir, Point pos) {
	if (!Sprite::init()) {
		return false;
	}
	if (dir == 0) {
		initWithFile("train_left.png");
	}
	else {
		initWithFile("train_right.png");
		speed = speed * -1;
	}
	setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	scheduleUpdate();
	return true;
}


void Train::update(float dt) {
	setPosition(getPositionX() + speed, getPositionY());
}

