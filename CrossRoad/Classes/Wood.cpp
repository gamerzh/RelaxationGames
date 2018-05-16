#include "Wood.h"
#include "MapNode.h"
#include "GeometryUtils.h"

Wood * Wood::create(Camera* ca, int type, int direction, float time)
{
	Wood* woo = new Wood();
	if (woo && woo->init(ca,type,direction, time)) {
		woo->autorelease();
		return woo;
	}
	else {
		CC_SAFE_DELETE(woo);
		return NULL;
	}
}

bool Wood::init(Camera* ca, int type, int direction, float time)
{
	if (!Sprite::init()) {
		return false;
	}
	this->woodType = type;
	this->woodDir = direction;
	this->woodTime = time;
	this->myCamera = ca;
	initWithFile(getFileNameByType(type));
	setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	scheduleUpdate();
	return true;
}


//  1�����ģ�� 2����ľ�� 3������ 4�������ʾ�� 5�����Ҷ
std::string Wood::getFileNameByType(int type) {
	//log("HHHHHHHHH %d", type);
	if (type == ObjectType::wood_long) {
		return "wood_2.png";
	}
	else if(type == ObjectType::leaf){
		return "leaf.png";
	}
	else {
		return "wood_1.png";
	}
}


float Wood::getSpeedX() {
	if (woodType != ObjectType::leaf) {
		if (woodDir == DirectionType::move_left) {
			this->woodSpeed = -GeometryUtils::randomFloat(1,2);
		}
		else {
			this->woodSpeed = GeometryUtils::randomFloat(1,2);
		}
	}
	else {
		this->woodSpeed = 0;//��Ҷ���߱��ƶ�������
	}
	return this->woodSpeed;
}

void Wood::update(float dt) {
	this->setPosition(this->getPositionX() + getSpeedX(), this->getPositionY());
		if (woodDir == DirectionType::move_left) {
			if (this->getPositionX() + this->getContentSize().width < myCamera->getPositionX()) {
			
				this->setPosition(myCamera->getPositionX() + win.width + this->getContentSize().width, this->getPositionY());
			}
		}
		else {
			if (this->getPositionX()  > myCamera->getPositionX() + win.width+ this->getContentSize().width) {
				this->setPosition(myCamera->getPositionX() - this->getContentSize().width, this->getPositionY());
			}
		}
}
