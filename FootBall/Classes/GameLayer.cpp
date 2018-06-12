#include "GameLayer.h"
#include "Rocker.h"
#include "Ball.h"
#include "ResultScene.h"
#include "GameStatus.h"
USING_NS_CC;

bool GameLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto roc = Rocker::create(Vec2(visibleSize.width / 6, visibleSize.height / 5));
	roc->setTag(1024);
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
	addChild(playerCamera);//��ӵ���ǰ������

	auto ball = Ball::create(playerCamera);
	ball->setPosition(1280, 720);
	ball->setCameraMask((int)CameraFlag::USER1);
	addChild(ball);

	auto showtime = Label::createWithSystemFont(StringUtils::format("%.1f",gameTime),"arial",40);
	showtime->setTag(100);
	showtime->setColor(Color3B::WHITE);
	showtime->setPosition(visibleSize.width/2, visibleSize.height-40);
	addChild(showtime);
	
	//�ϰ볡�������߳���
	currentPlayerTeamProperty = TeamInfoFactory::getInstance()->getTeamPropertyById(GameStatus::getInstance()->getPlayerTeamId());
	for (auto var1 : currentPlayerTeamProperty.footManVec) {
		auto foot1 = FootMan::create(var1);
		foot1->setCameraMask((int)CameraFlag::USER1);
		addChild(foot1);
		if (var1.goalkeeper) {
			foot1->setPosition(100, 720);
		}
		else {
			foot1->setPosition(1280, 720);
		}
		currentPlayerTeam.push_back(foot1);
	}

	currentComputerTeamProperty = TeamInfoFactory::getInstance()->getTeamPropertyById(GameStatus::getInstance()->getComputerTeamId());
	for (auto var2 : currentPlayerTeamProperty.footManVec) {
		auto foot2 = FootMan::create(var2);
		foot2->setCameraMask((int)CameraFlag::USER1);
		addChild(foot2);
		currentPlayerTeam.push_back(foot2);
	}

	scheduleUpdate();

	return true;
}

void GameLayer::update(float dt) {
	//����Ϸ�����л���6����Ա,��ҿ��Կ�������������Ǹ�
	if (nullptr != getChildByTag(1024)) {
		auto angle = ((Rocker*)getChildByTag(1024))->getRockerAngle();
		if (angle != 0) {
			//������ڲٿ���Ա
			//((FootMan*)getChildByTag(1025))->setFootManAngle(angle);
		}
	}
	passTime += dt;
	if (passTime > timestep) {
		gameTime -= timestep;
		passTime -= timestep;
		if (gameTime > 0) {
			if (NULL != getChildByTag(100)) {
				((Label*)getChildByTag(100))->setString(StringUtils::format("%.1f", gameTime));
			}
		}
		else {
			this->pause();
			Director::getInstance()->replaceScene(TransitionMoveInT::create(1.0f, ResultScene::create()));
		}
	}
}