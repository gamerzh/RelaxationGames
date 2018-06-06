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

void Ball::update(float dt) {
	if (nullptr != this->myCamera) {
		this->myCamera->setPosition(this->myCamera->getPositionX() + 5, this->myCamera->getPositionY());
	}
	this->setPosition(this->getPositionX()+5,this->getPositionY());
}