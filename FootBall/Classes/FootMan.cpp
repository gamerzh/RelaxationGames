#include "FootMan.h"
USING_NS_CC;

FootMan* FootMan :: create(cocos2d::Camera* camera) {
	FootMan *ret = new FootMan();
	if (ret && ret->init(camera))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool FootMan::init(cocos2d::Camera* camera) {
	if (!Node::init()) {
		return false;
	}
	auto people = Sprite::create("timg.jpg");
	people->setAnchorPoint(Point::ANCHOR_MIDDLE);
	people->setPosition(0, 0);
	addChild(people);
	return true;
}

void FootMan::setFootManAngle(float angle) {
	//玩家操控摇杆,人物才会移动
	if (angle != 0) {
		//log("setFootManAngle %f,%f,%f", angle, cos(angle), sin(angle));
		Vec2 curPos = this->getPosition();
		this->setPosition(curPos.x+cos(angle)*5,curPos.y+sin(angle)*5);
	}
}

void FootMan::setSlideTackle() {

}


void FootMan::setShoot() {

}