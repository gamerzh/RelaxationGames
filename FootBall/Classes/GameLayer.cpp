#include "GameLayer.h"
#include "ResultScene.h"
#include "GameStatus.h"
#include "math.h"
USING_NS_CC;

bool GameLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	heroRocker = Rocker::create(Vec2(visibleSize.width / 6, visibleSize.height / 5));
	heroRocker->openRocker();
	addChild(heroRocker);

	auto black = Sprite::create("green.jpg");
	black->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	black->setPosition(0, 0);
	black->setCameraMask((int)CameraFlag::USER1);
	addChild(black,-1);

	auto playerCamera = Camera::createOrthographic(visibleSize.width, visibleSize.height, 1024, -1024);
	playerCamera->setCameraFlag(CameraFlag::USER1);
	playerCamera->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	addChild(playerCamera);//添加到当前场景里

	footBall = Ball::create(playerCamera);
	footBall->setPosition(1280, 800);
	footBall->setCameraMask((int)CameraFlag::USER1);
	addChild(footBall);

	auto showtime = Label::createWithSystemFont(StringUtils::format("%.1f",gameTime),"arial",40);
	showtime->setTag(100);
	showtime->setColor(Color3B::WHITE);
	showtime->setPosition(visibleSize.width/2, visibleSize.height-40);
	addChild(showtime);
	
	//上半场玩家在左边场地
	currentPlayerTeamProperty = TeamInfoFactory::getInstance()->getTeamPropertyById(GameStatus::getInstance()->getPlayerTeamId());
	for (int i = 0; i < currentPlayerTeamProperty.footManVec.size();i++) {
		auto var1 = currentPlayerTeamProperty.footManVec.at(i);
		auto foot1 = FootMan::create(var1);
		foot1->setCameraMask((int)CameraFlag::USER1);
		addChild(foot1);
		if (var1.goalkeeper) {
			foot1->setPosition(100, 720);
		}
		else {
			foot1->setPosition(1280-i*200, 720);
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

float GameLayer::calculateDistance(Vec2 p1, Vec2 p2) {
	return sqrt(pow((p1.x - p2.x),2) + pow((p1.y - p2.y),2));
}

void GameLayer::update(float dt) {
	//在游戏场景中会有6个球员,玩家可以控制己方离球最近的那个
	FootMan* controlMan = nullptr;
	int min = INT_FAST32_MAX;
	for (auto mine : currentPlayerTeam) {
		auto dis = calculateDistance(footBall->getPosition(), mine->getPosition());
		if (dis < min) {
			controlMan = mine;
			min = dis;
		}
	}
	if (nullptr != controlMan && nullptr != heroRocker) {
		auto angle = heroRocker->getRockerAngle();
		if (angle != 0) {
			//玩家正在操控球员
			controlMan->setFootManAngle(angle);
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