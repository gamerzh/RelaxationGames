#include "FootMan.h"
USING_NS_CC;

FootMan* FootMan :: create(FootManProperty property, cocos2d::Camera* camera) {
	FootMan *ret = new FootMan();
	if (ret && ret->init(property,camera))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool FootMan::init(FootManProperty property, cocos2d::Camera* camera) {
	if (!Node::init()) {
		return false;
	}
	this->goalkeeper = property.goalkeeper;
	auto people = Sprite::create("timg.jpg");
	people->setAnchorPoint(Point::ANCHOR_MIDDLE);
	people->setPosition(0, 0);
	addChild(people);
	scheduleUpdate();
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

void FootMan::doSlideTackle() {

}


void FootMan::doShoot() {

}

bool FootMan::isGoalkeeper() {
	return goalkeeper;
}

bool FootMan::isLootBall() {
	if (nullptr == footBall) {
		return false;
	}
	else {
		return true;
	}
}

void FootMan::setFootManLootBall(Ball* ball) {
	this->footBall = ball;
}

void FootMan::update(float dt) {
	if (nullptr != this->footBall) {
		footBall->setPosition(this->getPosition());
	}
}