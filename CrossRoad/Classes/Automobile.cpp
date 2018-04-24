#include "Automobile.h"


Automobile* Automobile::create(AutomobileType type, Point pos) {
	auto automoblie = new Automobile();
	if (automoblie && automoblie->init(type,pos)) {
		automoblie->autorelease();
		return automoblie;
	}
	else {
		CC_SAFE_DELETE(automoblie);
		return NULL;
	}
}

bool Automobile::init(AutomobileType type, Point pos) {
	if (!Sprite::init()) {
		return false;
	}
	initWithFile(getFileNameByType(type));
	setPosition(pos);
	setScale(0.6f);
	return true;
}

string Automobile:: getFileNameByType(AutomobileType type) {
	return "player_1.png";
}

string Automobile:: getSpeedByType(AutomobileType type) {
	return "";
}