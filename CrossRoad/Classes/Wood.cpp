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
	initWithFile(getFileNameByType(type));
	setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	scheduleUpdate();
	return true;
}


//  1�����ģ�� 2����ľ�� 3������ 4�������ʾ�� 5�����Ҷ
std::string Wood::getFileNameByType(int type) {
	if (type == WoodType::wood_long) {
		return "wood_2.png";
	}
	else if(type == WoodType::leaf){
	   
		return "leaf.png";
	}
	else {
		return "wood_1.png";
	}
}


float Wood::getSpeedX() {
	if (woodType != WoodType::leaf) {
		if (woodDir == DirectionType::move_left) {
			this->woodSpeed = -1;
		}
		else {
			this->woodSpeed = 1;
		}
	}
	else {
		this->woodSpeed = 0;//��Ҷ���߱��ƶ�������
	}
	return this->woodSpeed;
}

void Wood::update(float dt) {
	this->setPosition(this->getPositionX() + getSpeedX(), this->getPositionY());
}
