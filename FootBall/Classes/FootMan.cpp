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
	playerCsb = CSLoader::createNode("rw1.csb");
	playerCsb->setScale(ANIMATION_SCALE_RATE);
	playerCsb->setPosition(0, 0);
	this->addChild(playerCsb);
	playFootManRun();
	scheduleUpdate();
	return true;
}



void FootMan::setFootManAngle(float angle) {
	//玩家操控摇杆,人物才会移动
	if (angle != 0) {
		//log("setFootManAngle %f,%f,%f", angle, cos(angle), sin(angle));
		Vec2 curPos = this->getPosition();
		if (cos(angle) < 0) {
			moveLeft();
		}
		else {
			moveRight();
		}
		this->setPosition(curPos.x+cos(angle)*5,curPos.y+sin(angle)*5);
	}
}

void FootMan::doSlideTackle() {
	playFootManTackle();
}


void FootMan::doShoot() {
	this->footBall = nullptr;
	playFootManShoot();
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


void FootMan::playFootManRun() {
	playerCsb->stopAllActions();
	auto heroTimeLine = CSLoader::createTimeline("rw1.csb");
	heroTimeLine->play("animation0", true);
	playerCsb->runAction(heroTimeLine);
}

void FootMan::playFootManTackle() {
	playerCsb->stopAllActions();
	auto heroTimeLine = CSLoader::createTimeline("rw1.csb");
	heroTimeLine->play("animation4", false);
	playerCsb->runAction(heroTimeLine);
}


void FootMan::playFootManShoot() {
	playerCsb->stopAllActions();
	auto heroTimeLine = CSLoader::createTimeline("rw1.csb");
	heroTimeLine->play("animation1", false);
	playerCsb->runAction(heroTimeLine);
}

void FootMan::setTargetPosition(Vec2 pos) {
	this->targetPosition = pos;
}


Point FootMan::getTargetPosition() {
	return this->targetPosition;
}

void FootMan::moveRight() {
	playerCsb->setScaleX(ANIMATION_SCALE_RATE);
}


void FootMan::moveLeft() {
	playerCsb->setScaleX(ANIMATION_SCALE_RATE*-1);
}

void FootMan::update(float dt) {
	if (nullptr != this->footBall) {
		footBall->setPosition(this->getPosition());
		//log("XXXXXXXXXX = (%f,%f)",this->getPositionX(),this->getPositionY());
	}
}