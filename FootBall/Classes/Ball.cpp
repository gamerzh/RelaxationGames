#include "Ball.h"
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
	scheduleUpdate();
	return true;
}

int Ball::getBallState() {
	return this->ballState;
}

void Ball::setBallState(int state) {
	this->ballState = state;
}


void Ball::setOwnerMan(FootMan* owern) {
	setBallState(ball_is_ower);
	this->ballOwner = owern;
}

void Ball::update(float dt) {
	//足球被球员带着运动
	if (getBallState() == ball_is_ower) {
		this->setPosition(ballOwner->getPosition());
	}
}