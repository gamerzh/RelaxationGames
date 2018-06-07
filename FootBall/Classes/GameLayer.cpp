#include "GameLayer.h"
#include "ResultScene.h"
#include "Rocker.h"
#include "Ball.h"
#include "FootMan.h"
USING_NS_CC;

bool GameLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto roc = Rocker::create(Vec2(visibleSize.width / 6, visibleSize.height / 5));
	roc->openRocker();
	addChild(roc);

	auto black = Sprite::create("green.jpg");
	black->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	black->setPosition(0, 0);
	black->setCameraMask((int)CameraFlag::USER1);
	addChild(black,-1);

	auto playerCamera = Camera::createOrthographic(visibleSize.width, visibleSize.height, 1024, -1024);
	playerCamera->setCameraFlag(CameraFlag::USER1);
	playerCamera->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	addChild(playerCamera);//添加到当前场景里

	auto ball = Ball::create(playerCamera);
	ball->setPosition(playerCamera->getPositionX()+visibleSize.width / 2, playerCamera->getPositionY() + visibleSize.height / 2);
	ball->setCameraMask((int)CameraFlag::USER1);
	addChild(ball);

	auto footMan = FootMan::create();
	footMan->setPosition(playerCamera->getPositionX() + visibleSize.width / 2, playerCamera->getPositionY() + visibleSize.height / 2);
	footMan->setCameraMask((int)CameraFlag::USER1);
	addChild(footMan);

	auto node = Node::create();
	addChild(node);
	auto action = Sequence::create(DelayTime::create(5), CallFunc::create([=]() {
		//Director::getInstance()->replaceScene(TransitionMoveInT::create(1.0f, ResultScene::create()));
	}), NULL);
	node->runAction(action);

	return true;
}