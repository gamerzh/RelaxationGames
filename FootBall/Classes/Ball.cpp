#include "Ball.h"
#include "GlobalProperty.h"
#include "GeometryTools.h"
USING_NS_CC;


Ball* Ball::create(Camera* camera)
{
	Ball *ret = new Ball();
	if (ret && ret->init(camera))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool Ball::init(Camera* camera) {
	if (!Sprite::init()) {
		return false;
	}
	this->myCamera = camera;
	initWithFile("ball.png");
	setScale(0.4);
	scheduleUpdate();
	return true;
}

int Ball::getBallState() {
	return this->ballState;
}

void Ball::setBallState(int state) {
	this->ballState = state;
}


void Ball::setBallShoot(int  speed) {
	setBallState(ball_is_free);
	this->ballOwner = NULL;
}

FootMan* Ball::getOwerMan() {
	return this->ballOwner;
}

void Ball::setOwnerMan(FootMan* owern) {
	setBallState(ball_is_ower);
	this->ballOwner = owern;
}

Point Ball::cameraMoveInRect(Point pos) {
	auto size = Director::getInstance()->getVisibleSize();
	pos = Vec2(pos.x - size.width / 2, pos.y - size.height / 2);//球的坐标转化为摄像机的坐标

	if (pos.x < 0) {
		pos.x = 0;
	}
	else if (pos.x > football_field_width - size.width) {
		pos.x = football_field_width - size.width;
	}
	if (pos.y < 0) {
		pos.y = 0;
	}
	else if (pos.y > football_field_height - size.height) {
		pos.y = football_field_height - size.height;
	}

	return pos;
}

bool Ball::checkBallInGoal() {
	if (goalLeft.containsPoint(this->getPosition()) ) {
		char* buf = const_cast<char*>("left");
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("foot_ball_in_goal", buf);
		return true;
	}
	else if (goalRight.containsPoint(this->getPosition())) {
		char* buf = const_cast<char*>("right");
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("foot_ball_in_goal", buf);
		return true;
	}
	else {
		return false;
	}
}

void Ball::update(float dt) {
	if (NULL != this->ballOwner) {
		this->setPosition(this->ballOwner->getPosition());
	}
	this->myCamera->setPosition(cameraMoveInRect(this->getPosition()));
	if (checkBallInGoal()) {
		this->setPosition(100, 700);
	}
}
