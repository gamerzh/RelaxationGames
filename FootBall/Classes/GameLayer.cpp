#include "GameLayer.h"
#include "GameStatus.h"
#include "math.h"
#include "Setting.h"
#include "FootballTeam.h"
#include "GlobalProperty.h"
#include "GeometryTools.h"
USING_NS_CC;

bool GameLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	GameStatus::getInstance()->setPlayerTeamId(1);

	createFootballFild();//绘制场地

	createFootBallTeam();//添加球员

	heroRocker = Rocker::create(Vec2(visibleSize.width / 8, visibleSize.height / 5));
	addChild(heroRocker);
	heroRocker->openRocker();

	playerCamera = Camera::createOrthographic(visibleSize.width, visibleSize.height, 1024, -1024);
	playerCamera->setCameraFlag(CameraFlag::USER1);
	playerCamera->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	addChild(playerCamera);//添加到当前场景里

	footBall = Ball::create(playerCamera);
	footBall->setPosition(1280, 800);
	footBall->setCameraMask((int)CameraFlag::USER1);
	addChild(footBall, FOOTBALL_LOCAL_ZORDER);

	loadGameLayerUI();

	scheduleUpdate();
	return true;
}




void GameLayer::createFootballFild() {
	auto black = Sprite::create("green.jpg");
	black->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	black->setPosition(0, 0);
	black->setCameraMask((int)CameraFlag::USER1);
	addChild(black, FOOTBALL_LOCAL_ZORDER-1);

	auto leftGoal = Sprite::create("door_left.png");
	leftGoal->setPosition(145,750);
	leftGoal->setCameraMask((int)CameraFlag::USER1);
	addChild(leftGoal, FOOTBALL_LOCAL_ZORDER+1);

	auto rightGoal = Sprite::create("door_right.png");
	rightGoal->setCameraMask((int)CameraFlag::USER1);
	rightGoal->setPosition(1990, 750);
	addChild(rightGoal, FOOTBALL_LOCAL_ZORDER + 1);
}

void GameLayer::createFootBallTeam() {
	//创建玩家的队伍
	playerTeam = FootballTeam::create(1);
	currentPlayerTeam = playerTeam->getFootManVector();
	//添加球员到场地上
	for (auto var: currentPlayerTeam)
	{
		addChild(var);
	}

	//创建AI的队伍
	//computerTeam = FootballTeam::create(1);
	//currentComputerTeam = computerTeam->getFootManVector();
	//添加球员到场地上
}


void GameLayer::loadGameLayerUI() {
	auto btn1 = MenuItemImage::create("pass_ball_1.png","pass_ball_2.png",CC_CALLBACK_0(GameLayer::passAndTackle,this));
	auto btn2 = MenuItemImage::create("shoot_ball_1.png", "shoot_ball_2.png", CC_CALLBACK_0(GameLayer::shoot, this));
	auto btn3 = MenuItemImage::create("speed_ball_1.png", "speed_ball_2.png", CC_CALLBACK_0(GameLayer::speedMan, this));
	auto menu = Menu::create(btn1, btn2, btn3, NULL);
	btn1->setPosition(1070, 80);
	btn2->setPosition(1160, 190);
	btn3->setPosition(1190, 320);
	menu->setPosition(0,0);
	addChild(menu);
	auto set = Setting::create();
	addChild(set, 100);
}


void GameLayer::passAndTackle() {
	//传球逻辑
	//if(footBall->getOwerMan() == )
	//抢断逻辑
	//if (NULL != currentFootMan) {
	//	currentFootMan->doSlideTackle();
	//}
}

void GameLayer::shoot() {
	//射门逻辑
	//if (currentControlFootMan == currentFootMan) {
	//	footBall->setBallShoot(currentFootMan->getShootSpeed());
	//	currentFootMan->doShoot();
	//	//Point pos = currentFootMan->getTargetPosition();
	//}
	//射门逻辑
}

void GameLayer::speedMan() {

}

void GameLayer::manLootBall() {
	//遍历所有球员,当球员和球达到要求距离后,球被球员拥有，其他球员无法获得球权]
	//std::vector<FootMan*> alternativeMan;
	//for (auto var1 : currentPlayerTeam) {
	//	float dis = calculateDistance(var1->getPosition(),footBall->getPosition());
	//	if (dis < owner_ball_max_dis) {
	//		alternativeMan.push_back(var1);
	//	}
	//}
	//for (auto var2 : currentComputerTeam) {
	//	float dis = calculateDistance(var2->getPosition(), footBall->getPosition());
	//	if (dis < owner_ball_max_dis) {
	//		alternativeMan.push_back(var2);
	//	}
	//}
	////随机选择一个球员获取球权
	//if (alternativeMan.size() == 0) {
	//	return;
	//}
	//int area = alternativeMan.size();
	//auto man = alternativeMan.at(random(0, area - 1));
	//footBall->setOwnerMan(man);
	//currentControlFootMan = man;
	//alternativeMan.at(random(0, area - 1))->setFootManLootBall(footBall);
}

float GameLayer::calculateDistance(Vec2 p1, Vec2 p2) {  
	return sqrt(pow((p1.x - p2.x),2) + pow((p1.y - p2.y),2));
}

void GameLayer::update(float dt) {
	if (footBall->getBallState() == ball_is_free) {
		manLootBall();
	}
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
	//currentFootMan = controlMan;
	if (nullptr != controlMan && nullptr != heroRocker) {
		auto angle = heroRocker->getRockerAngle();                                 
		if (angle != 0) {
			//玩家正在操控球员
			controlMan->setFootManAngle(angle);
		}
	}

}

void GameLayer::onEnter() {
	Layer::onEnter();
	addCustomEvent();
}


void GameLayer::onExit() {
	Layer::onExit();

}

void GameLayer::addCustomEvent() {
	auto footballInGoal = EventListenerCustom::create(foot_ball_in_goal, [=](EventCustom* event) {
		//log("AAAAAAAAAAAAAAAAAAAAAA");
	});
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(footballInGoal, 1);
}

void GameLayer::removeCustomEvent() {
	Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(foot_ball_in_goal);
}