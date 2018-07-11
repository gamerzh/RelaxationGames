#include "GameLayer.h"
#include "GameStatus.h"
#include "math.h"
#include "Setting.h"
#include "GeometryTools.h"
USING_NS_CC;

bool GameLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	GameStatus::getInstance()->setPlayerTeamId(1);

	createFootballFild();//���Ƴ���

	createFootBallTeam();//�����Ա

	heroRocker = Rocker::create(Vec2(visibleSize.width / 8, visibleSize.height / 5));
	addChild(heroRocker);
	heroRocker->openRocker();

	playerCamera = Camera::createOrthographic(visibleSize.width, visibleSize.height, 1024, -1024);
	playerCamera->setCameraFlag(CameraFlag::USER1);
	playerCamera->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
	addChild(playerCamera);//��ӵ���ǰ������

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
	//�ϰ볡�������߳���
	currentPlayerTeamProperty = TeamInfoFactory::getInstance()->getTeamPropertyById(GameStatus::getInstance()->getPlayerTeamId());
	for (int i = 0; i < currentPlayerTeamProperty.footManVec.size(); i++) {
		auto var1 = currentPlayerTeamProperty.footManVec.at(i);
		auto foot1 = FootMan::create(var1);
		foot1->setCameraMask((int)CameraFlag::USER1);
		addChild(foot1, FOOTBALL_MAN_ZORDER);
		if (var1.goalkeeper) {
			foot1->setPosition(300, 720);
		}
		else {
			foot1->setPosition(1280 - i * 200, 720);
		}
		foot1->setTargetPosition(Vec2(150, 720));
		currentPlayerTeam.push_back(foot1);
	}

	currentComputerTeamProperty = TeamInfoFactory::getInstance()->getTeamPropertyById(GameStatus::getInstance()->getComputerTeamId());
	for (auto var2 : currentPlayerTeamProperty.footManVec) {
		auto foot2 = FootMan::create(var2);
		foot2->setCameraMask((int)CameraFlag::USER1);
		addChild(foot2, FOOTBALL_MAN_ZORDER);
		currentPlayerTeam.push_back(foot2);
	}
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
	//�����߼�
	//if(footBall->getOwerMan() == )
	//�����߼�
	if (NULL != currentFootMan) {
		currentFootMan->doSlideTackle();
	}
}

void GameLayer::shoot() {
	//�����߼�
	if (NULL != currentFootMan) {
		currentFootMan->doShoot();
		Point pos = currentFootMan->getTargetPosition();
		log("shoot target pos = (%f,%f)",pos.x,pos.y);
		//footBall->setPosition(pos);
		footBall->runAction(MoveTo::create(5, pos));
		//Scheduler
	}
	//�����߼�
}

void GameLayer::speedMan() {

}

void GameLayer::manLootBall() {
	//����������Ա,����Ա����ﵽҪ������,����Աӵ�У�������Ա�޷������Ȩ]
	std::vector<FootMan*> alternativeMan;
	for (auto var1 : currentPlayerTeam) {
		float dis = calculateDistance(var1->getPosition(),footBall->getPosition());
		if (dis < owner_ball_max_dis) {
			alternativeMan.push_back(var1);
		}
	}
	for (auto var2 : currentComputerTeam) {
		float dis = calculateDistance(var2->getPosition(), footBall->getPosition());
		if (dis < owner_ball_max_dis) {
			alternativeMan.push_back(var2);
		}
	}
	//���ѡ��һ����Ա��ȡ��Ȩ
	if (alternativeMan.size() == 0) {
		return;
	}
	int area = alternativeMan.size();
	footBall->setOwnerMan(alternativeMan.at(random(0,area-1)));
	//alternativeMan.at(random(0, area - 1))->setFootManLootBall(footBall);
}

float GameLayer::calculateDistance(Vec2 p1, Vec2 p2) {  
	return sqrt(pow((p1.x - p2.x),2) + pow((p1.y - p2.y),2));
}

void GameLayer::update(float dt) {
	if (footBall->getBallState() == ball_is_free) {
		manLootBall();
	}
	//����Ϸ�����л���6����Ա,��ҿ��Կ��Ƽ�������������Ǹ�
	FootMan* controlMan = nullptr;
	int min = INT_FAST32_MAX;
	for (auto mine : currentPlayerTeam) {
		auto dis = calculateDistance(footBall->getPosition(), mine->getPosition());
		if (dis < min) {
			controlMan = mine;
			min = dis;
		}
	}
	currentFootMan = controlMan;
	if (nullptr != controlMan && nullptr != heroRocker) {
		auto angle = heroRocker->getRockerAngle();                                 
		if (angle != 0) {
			//������ڲٿ���Ա
			controlMan->setFootManAngle(angle);
		}
	}

}