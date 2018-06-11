#include "GameLayer.h"
#include "Rocker.h"
#include "Ball.h"
#include "ResultScene.h"
#include "TeamFactory.h"
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
	addChild(playerCamera);//添加到当前场景里

	auto ball = Ball::create(playerCamera);
	ball->setPosition(playerCamera->getPositionX()+visibleSize.width / 2, playerCamera->getPositionY() + visibleSize.height / 2);
	ball->setCameraMask((int)CameraFlag::USER1);
	addChild(ball);

	//auto footMan = FootMan::create();
	//footMan->setPosition(playerCamera->getPositionX() + visibleSize.width / 2, playerCamera->getPositionY() + visibleSize.height / 2);
	//footMan->setCameraMask((int)CameraFlag::USER1);
	//footMan->setTag(1025);
	//addChild(footMan);


	auto showtime = Label::createWithSystemFont(StringUtils::format("%.1f",gameTime),"arial",40);
	showtime->setTag(100);
	showtime->setColor(Color3B::WHITE);
	showtime->setPosition(visibleSize.width/2, visibleSize.height-40);
	addChild(showtime);
	
	//上半场玩家在左边场地
	currentPlayerTeamId = getFootManTeamById(GameStatus::getInstance()->getPlayerTeamId());
	//设置玩家队伍的守门员

	//随机分布玩家队伍的球员

	currentComputerTeamId = getFootManTeamById(GameStatus::getInstance()->getComputerTeamId());

	scheduleUpdate();

	return true;
}

FootManTeam* GameLayer::getFootManTeamById(int id) {
	std::vector<FootManTeam*> team = TeamFactory::getInstance()->getFootManTeamVector();
	for (auto var : team) {
		if (var->getTeamId() == id) {
			return var;
		}
	}
	return nullptr;
}

void GameLayer::update(float dt) {
	//在游戏场景中会有6个球员,玩家可以控制离球最近的那个
	if (nullptr != getChildByTag(1024)) {
		auto angle = ((Rocker*)getChildByTag(1024))->getRockerAngle();
		if (angle != 0) {
			//玩家正在操控球员
			((FootMan*)getChildByTag(1025))->setFootManAngle(angle);
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