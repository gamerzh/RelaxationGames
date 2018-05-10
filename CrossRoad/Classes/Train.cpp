#include "Train.h"


Train* Train::create(Camera* _camera,Point pos) {
	auto tra = new Train();
	if (tra && tra->init(_camera,pos)) {
		tra->autorelease();
		return tra;
	}
	else {
		CC_SAFE_DELETE(tra);
		return nullptr;
	}
}


bool Train::init(Camera* _camera,Point pos) {
	if (!Sprite::init()) {
		return false;
	}
	this->_camera = _camera;
	int time = random(0, 5);
	this->trainInterval = time;
	initWithFile("light_1.png");
	setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	dir = random(0, 1);
	myTrain = Sprite::create();
	myTrain->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	myTrain->setCameraMask(int(CameraFlag::USER1));
	if (dir == 0) {
		myTrain->initWithFile("train_left.png");
	}
	else {
		myTrain->initWithFile("train_right.png");
		speed = speed * -1;
	}
	if (dir == 0) {
		myTrain->setPosition(-myTrain->getContentSize().width, myTrain->getContentSize().height / 2);
	}
	else {
		myTrain->setPosition(myTrain->getContentSize().width, myTrain->getContentSize().height / 2);
	}
	addChild(myTrain,-1);
	scheduleUpdate();
	return true;
}

Rect Train::getTrainObjectBox(){
	return Rect(myTrain->getBoundingBox().getMinX() + getPositionX(),
		myTrain->getBoundingBox().getMinY()+getPositionY(), 
		myTrain->getBoundingBox().getMaxX()- myTrain->getBoundingBox().getMinX(),
		myTrain->getBoundingBox().getMaxY()- myTrain->getBoundingBox().getMinY());
}

void Train::moveTrain(CallFunc* call) {
	auto win = Director::getInstance()->getWinSize();
	if (dir == 0) {
		auto move = MoveTo::create(3, Vec2(win.width  + myTrain->getContentSize().width, myTrain->getPositionY()));
		myTrain->runAction(Sequence::create(move->clone(), call, NULL));
	}
	else {
		auto move = MoveTo::create(3, Vec2(- myTrain->getContentSize().width, myTrain->getPositionY()));
		myTrain->runAction(Sequence::create(move->clone(), call, NULL));
	}
}

void Train::trainLightAnim(CallFunc* call) {
	auto animation = Animation::create();
	for (int i = 1; i <= 4; i++)
	{

		std::string imageName = StringUtils::format("light_%d.png", i);
		animation->addSpriteFrameWithFile(imageName);
	}
	// should last 1 seconds. And there are 24 frames.
	animation->setDelayPerUnit(4.0f / 36.0f);
	animation->setRestoreOriginalFrame(false);
	auto action = Animate::create(animation);
	this->runAction(Sequence::create(action,call,NULL));
}


void Train::update(float dt){
	passTime += dt;
	if (passTime > trainInterval) {
		passTime = 0;
		trainLightAnim(CallFunc::create([=]() {
			moveTrain(CallFunc::create([=](){
				setTexture("light_1.png");
				if (dir == 0) {
					myTrain->setPosition(-myTrain->getContentSize().width, myTrain->getContentSize().height / 2);
				}
				else {
					myTrain->setPosition(myTrain->getContentSize().width, myTrain->getContentSize().height / 2);
				}
			}));
		}));
	}
}