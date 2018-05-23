#include "GameLayer.h"
#include "GameOver.h"
#include "GeometryUtils.h"
#include "GameStatus.h"
#include "UserData.h"
#include "Audio.h"
#include "DreamNode.h"
#include "Dream.h"
#include "GuideLayer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"


GameLayer* GameLayer::create(Camera* ca) {
	auto mapLayer = new GameLayer();
	if (mapLayer && mapLayer->init(ca)) {
		mapLayer->autorelease();
		return mapLayer;
	}
	else {
		CC_SAFE_DELETE(mapLayer);
		return NULL;
	}
}

bool GameLayer::init(Camera* ca) {
	if (!Layer::init()) {
		return false;
	}
	auto win = Director::getInstance()->getWinSize();
	_camera = ca;
	initGameMap();
	playerGesture = Gesture::forward;
	player = Player::create();
	player->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	auto playerPos = GeometryUtils::transitionPlayerVec2(mapList.at(0)->getHeroStartPos());
	player->setPosition(playerPos.x, playerPos.y);
	player->setCameraMask(int(CameraFlag::USER1));
	log("Player postion = (%.1f,%.1f)", playerPos.x, playerPos.y);
	addChild(player, MaxZorder);

	scheduleUpdate();
	schedule(schedule_selector(GameLayer::checkMapInScene), 0.1f);
	addTouchListener();
	Audio::getInstance()->playSoundCar();
	if (!UserData::getInstance()->getShowgGuide()) {
		GameStatus::getInstance()->setGameStatus(false);
		auto guide = GuideLayer::create();
		guide->setPosition(win.width/2, 0);
		addChild(guide, MaxZorder);
	}
	else {
		if (!Dream::getInstance()->getGameDreamTimes()) {
			auto kaiju = DreamNode::create(5, Vec2(win.width, win.height / 2));
			addChild(kaiju, MaxZorder);
		}
	}
	return true;
}


void GameLayer::initGameMap() {
	addGameMap();
}

void GameLayer::checkMapInScene(float dt) {
	if (mapList.size() == 0) {
		return;
	}
	auto win = Director::getInstance()->getWinSize();
	vector<MapNode*>::iterator it;
	for (it = mapList.begin(); it != mapList.end(); )
	{
		auto node = *it;
		if (_camera->getPositionY() >= used_map_node*defult_tmx_y_num * default_tmx_height - win.height && !node->getPrepareToRecycle()) {
			node->setPrepareToRecycle(true);
			needAddMap = true;
		}
		if (_camera->getPositionY() > used_map_node*defult_tmx_y_num * default_tmx_height + win.height) {
			it = mapList.erase(it);
			node->removeFromParent();
		}

		else {
			++it;
		}

	}
	if (needAddMap) {
		//log("add new map");
		addGameMap();
		needAddMap = false;
	}
}

void GameLayer::addGameMap() {
	int ran = random(0, 7);
	auto node = MapNode::create(ran);
	if (mapList.size() == 0 && used_map_node == 0) {
		node->setPosition(0, 0);
	}
	else {
		node->setPosition(0, used_map_node*defult_tmx_y_num * default_tmx_height);
	}
	node->setCameraMask(int(CameraFlag::USER1));
	addChild(node);
	mapList.push_back(node);
	++used_map_node;

	//生成金币
	for (auto goldInfo : node->getGoldInfoList()) {
		createGold(goldInfo.pos);
	}

	//在地图上生成树木和屋子
	for (auto treePos : node->getBlockInfoList()) {
		createHouseAndTree(treePos.type, Size(treePos.width, treePos.height), treePos.position);
	}
	////在地图上生成卡车
	for (auto info : node->getEnemyInfoList()) {
		createAutomoblie(_camera, info.type, info.direction, info.speed, info.interval, info.position);
	}
	//生成木板和荷叶
	for (auto woodInfo : node->getWoodInfoList())
	{
		createWood(woodInfo.type, woodInfo.direction, woodInfo.time, woodInfo.position);
	}

	////生成火车
	for (auto lightInfo : node->getLightInfoList()) {
		createTrain(lightInfo.pos);
	}

}

void GameLayer::createHouseAndTree(int type, Size size, Point pos) {
	int line = floor(pos.y / default_tmx_height) + (used_map_node - 1)*defult_tmx_y_num;
	auto tree = Block::create(type, pos, size);
	tree->setMapIndex(used_map_node);
	tree->setCameraMask(int(CameraFlag::USER1));
	tree->setPosition(GeometryUtils::transitionObjectVec2(pos, used_map_node).x, GeometryUtils::transitionObjectVec2(pos, used_map_node).y + default_tmx_height / 5);
	addChild(tree, MaxZorder - line);
	treeList.push_back(tree);
}

void GameLayer::createAutomoblie(Camera* camera, int type, int direction, int speed, int interval, Point pos) {
	//需要更具MapNode的情况来产生汽车
	auto line = floor(pos.y / default_tmx_height) + (used_map_node - 1)*defult_tmx_y_num;
	auto automoblie = Automobile::create(camera, type, direction, speed, interval, pos);
	automoblie->setCameraMask(int(CameraFlag::USER1));
	automoblie->setMapIndex(used_map_node);
	addChild(automoblie, MaxZorder - line);
	autoList.push_back(automoblie);
	//log("Automobile Zorder %d", automoblie->getZOrder());
}

void GameLayer::createWood(int type, int dir, int time, Point pos) {
	auto line = round(pos.y / default_tmx_height) + (used_map_node - 1)*defult_tmx_y_num;
	auto wood = Wood::create(_camera, type, dir, time, pos);
	wood->setCameraMask(int(CameraFlag::USER1));
	wood->setMapIndex(used_map_node);
	addChild(wood, MaxZorder - line);
	woodList.push_back(wood);
	//log("Wood position %.1f,%.1f", wood->getPositionX(),wood->getPositionY());
	//log("Wood Zorder = %d", wood->getZOrder());
}

void GameLayer::createGold(Point position) {
	auto zorder = round(position.y / default_tmx_height) + (used_map_node - 1)*defult_tmx_y_num;
	auto goldIcon = GoldIcon::create();
	goldIcon->setPosition(GeometryUtils::transitionObjectVec2(position, used_map_node));
	goldIcon->setCameraMask(int(CameraFlag::USER1));
	addChild(goldIcon, MaxZorder - zorder);
	goldList.push_back(goldIcon);
}


void GameLayer::createTrain(Point position) {

	//log("random dir %d", dir);
	auto train = Train::create(_camera, position);
	train->setPosition(GeometryUtils::transitionObjectVec2(position, used_map_node));
	train->setCameraMask(int(CameraFlag::USER1));
	addChild(train, MaxZorder - round(position.y / default_tmx_height));
	trainList.push_back(train);
}

void GameLayer::addTouchListener() {
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}


bool GameLayer::onTouchBegan(Touch *touch, Event *event) {
	if (isShowGameOver) {
		return true;
	}
	if (!allowJump) {
		return true;
	}
	preTouchPoint = touch->getLocation();
	if (playerGesture == Gesture::left) {
		player->playPlayerJiYaLeft();
	}
	else if (playerGesture == Gesture::right) {
		player->playPlayerJiYaRight();
	}
	else if (playerGesture == Gesture::forward) {
		player->playPlayerJiYa();
	}
	else if (playerGesture == Gesture::backwards) {
		player->playPlayerJiYaBack();
	}
	playerGesture = Gesture::forward;
	return true;
}


void GameLayer::onTouchMoved(Touch* touch, Event* event) {
	if (isShowGameOver) {
		return;
	}
	if (!allowJump) {
		return;
	}
	if (touch->getLocation().x > preTouchPoint.x && touch->getLocation().x - preTouchPoint.x > 10
		&& abs(touch->getLocation().y - preTouchPoint.y) / abs(touch->getLocation().x - preTouchPoint.x) < 1) {
		playerGesture = Gesture::right;
	}
	else if (touch->getLocation().x < preTouchPoint.x &&  preTouchPoint.x - touch->getLocation().x >10
		&& abs(touch->getLocation().y - preTouchPoint.y) / abs(preTouchPoint.x - touch->getLocation().x) < 1) {
		playerGesture = Gesture::left;
	}
	else if (touch->getLocation().y < preTouchPoint.y &&  abs(preTouchPoint.y - touch->getLocation().y) >10
		&& abs(preTouchPoint.y - touch->getLocation().y) / abs(preTouchPoint.x - touch->getLocation().x) > 1) {
		playerGesture = Gesture::backwards;
	}
	else {
		playerGesture = Gesture::forward;
	}

}


void GameLayer::onTouchEnded(Touch* touch, Event* event) {
	if (isShowGameOver) {
		return;
	}
	if (!allowJump) {
		return;
	}

	//对于操作指法的判定,向左滑动,向右滑动,双击
	if (NULL != player) {
		if (playerGesture == Gesture::left) {
			if (player->getPositionX() > default_tmx_width) {
				auto jmpResult = player->playerJumpLeft(treeList, CallFunc::create([=]() {
					goldPickCheck();
					//cameraMoveX -= default_tmx_width;
				}));
			}
		}
		else if (playerGesture == Gesture::right) {
			if (player->getPositionX() < default_tmx_width * 17) {
				auto jmpResult = player->playerJumpRight(treeList, CallFunc::create([=]() {
					goldPickCheck();
					//cameraMoveX += default_tmx_width;
				}));
			}

		}
		else if (playerGesture == Gesture::backwards) {
			if (player->getPositionY() >= _camera->getPositionY() + default_tmx_height) {
				auto jmpResult = player->playerJumpBackwards(treeList, CallFunc::create([=]() {
					goldPickCheck();
				}));
				if (jmpResult) {
					GameStatus::getInstance()->minusStepNum();
				}
			}
		}
		else {
			auto jmpResult = player->playerJumpForward(treeList, CallFunc::create([=]() {
				goldPickCheck();
				//cameraMoveY += default_tmx_height*0.72;
				//cameraMoveX += PLAYER_JUMP_OFFSET;
			}));
			if (jmpResult) {
				GameStatus::getInstance()->plusStepNum();
				playerStayTime = 0;
			}
		}
		allowJump = false;
	}

}




void GameLayer::hawkKillPlayer() {
	auto hawk = Sprite::create("hawk.png");
	hawk->setCameraMask(int(CameraFlag::USER1));
	hawk->setPosition(Vec2(player->getPositionX(), player->getPositionY() + win.height));
	addChild(hawk, MaxZorder);
	//setp1 hawk 飞向玩家
	auto step_1 = MoveTo::create(1, player->getPosition());
	//玩家和老鹰一起飞走
	auto step_2 = MoveTo::create(0.5f, Vec2(player->getPositionX(), -win.height / 2));
	hawk->runAction(Sequence::create(step_1, CallFunc::create([=]() {
		player->runAction(step_2->clone());
	}), step_2, NULL));
}

void GameLayer::showGameOver(int type) {
	if (GameStatus::getInstance()->getInvincible() && type == 0) {
		return;
	}
	if (!isShowGameOver) {
		GameStatus::getInstance()->setDoubleScore(false);
		isShowGameOver = true;
		float delay = 0;
		if (type == 1) {
			delay = 1.0;
			Audio::getInstance()->playSoundWater();
			player->playerGoWater();
		}
		else if (type == 2) {
			delay = 3;
			Audio::getInstance()->playSoundHawk();
			hawkKillPlayer();
		}
		else {
			Audio::getInstance()->playSoundHit();
			player->playerGoDie();
			player->setLocalZOrder(player->getLocalZOrder() - PlayerZorder);//死亡后图层下降
		}
		if (NULL == getChildByTag(99)) {
			this->runAction(Sequence::create(DelayTime::create(delay), CallFunc::create([=]() {
				auto dreamAlive = DreamNode::create(7, Vec2(_camera->getPositionX() + win.width / 2, _camera->getPositionY() + win.height / 2));
				dreamAlive->setCameraMask((int)CameraFlag::USER1);
				dreamAlive->setTag(99);
				addChild(dreamAlive, MaxZorder);
			}), NULL));
		}

	}
}


void GameLayer::goldPickCheck() {
	//检查玩家是否碰到了金币
	vector<GoldIcon*>::iterator it;
	if (goldList.size() != 0) {
		for (it = goldList.begin(); it != goldList.end(); ++it) {
			GoldIcon* myGold = *it;
			if (GeometryUtils::intersectsRect(myGold->getBoundingBox(), player->getPlayerCheckRect())) {
				it = goldList.erase(it);
				myGold->removeFromParent();
				UserData::getInstance()->setPlayerGoldNum(UserData::getInstance()->getPlayerGoldNum() + 10);
				Audio::getInstance()->playSoundGold();
				return;
			}
		}
	}
}

void GameLayer::recycleResource() {
	//回收树木
	vector<Block*>::iterator tree;
	for (tree = treeList.begin(); tree != treeList.end(); ) {
		auto tre = *tree;
		if (tre->getPositionY() < _camera->getPositionY() - default_tmx_height * 3) {
			tree = treeList.erase(tree);
			tre->removeFromParent();
		}
		else {
			++tree;
		}
	}

	//回收金币
	vector<GoldIcon*>::iterator goldIt;
	for (goldIt = goldList.begin(); goldIt != goldList.end(); ) {
		auto god = *goldIt;
		if (god->getPositionY() < _camera->getPositionY() - default_tmx_height * 3) {
			goldIt = goldList.erase(goldIt);
			god->removeFromParent();
		}
		else {
			++goldIt;
		}
	}

	//回收卡车
	vector<Automobile*>::iterator carIt;
	for (carIt = autoList.begin(); carIt != autoList.end(); ) {
		Automobile* car = *carIt;
		if (car->getCarList().size()>0 && car->getCarList().at(0)->getPositionY() < _camera->getPositionY() - default_tmx_height * 3) {
			carIt = autoList.erase(carIt);
			car->removeFromParent();
		}
		else {
			++carIt;
		}
	}
	//回收木板和荷叶
	vector<Wood*>::iterator woodIt;
	for (woodIt = woodList.begin(); woodIt != woodList.end(); ) {
		Wood* woo = *woodIt;
		if (woo->getBoardList().size()>0 &&  woo->getBoardList().at(0)->getPositionY() < _camera->getPositionY() - default_tmx_height * 3) {
			woodIt = woodList.erase(woodIt);
			woo->removeFromParent();
		}
		else {
			++woodIt;
		}
	}
	//回收火车
	vector<Train*>::iterator trainIt;
	for (trainIt = trainList.begin(); trainIt != trainList.end(); ) {
		auto tra = *trainIt;
		if (tra->getPositionY() < _camera->getPositionY() - default_tmx_height * 3) {
			trainIt = trainList.erase(trainIt);
			tra->removeFromParent();
		}
		else {
			++trainIt;
		}
	}
}

void GameLayer::cameraMoveCheck() {
	cruentPlayerOffsetX = player->getPositionX() - _camera->getPositionX();
	cruentPlayerOffsetY = player->getPositionY() - _camera->getPositionY();
	cameraMoveX = cruentPlayerOffsetX - originalPlayerOffsetX;
	cameraMoveY = cruentPlayerOffsetY - originalPlayerOffsetY;
	log("YYYYYYYY = %.1f,%.1f", cameraMoveX, cameraMoveY);
}

void GameLayer::changeCameraMoveStep() {
	//更具玩家和摄像机的距离调整步幅
	if (cameraMoveY > 2 * default_tmx_height) {
		cameraMoveStepY = 4;
	}
	else if (cameraMoveY > 4 * default_tmx_height) {
		cameraMoveStepY = 8;
	}
	else {
		cameraMoveStepY = 2;
	}

	if (abs(cameraMoveX) > 0) {
		if (player->getPositionX() - _camera->getPositionX() > 3 * default_tmx_width) {
			cameraMoveStepX = 4;
		}
		else if (player->getPositionX() - _camera->getPositionX() > 6 * default_tmx_width) {
			cameraMoveStepX = 8;
		}
		else {
			cameraMoveStepX = 2;
		}
	}
}

void GameLayer::moveCameraX() {
	//schedule([=](float dt) {
	//	if (_camera->getPositionX() >= 0 && _camera->getPositionX() < 9 * default_tmx_width) {
	//		_camera->setPosition(_camera->getPositionX() + player->getSpeedX(), _camera->getPositionY());
	//	}
	//}, 1.0f / 60, SCHEDULE_CAMERA_X);
}

void GameLayer::cancelMoveCameraX() {
	player->setSpeedX(0);
	player->setPlayerOnWood(false);
	//unschedule(SCHEDULE_CAMERA_X);
}


void GameLayer::update(float dt) {
	if (!allowJump) {
		jumpInterval += dt;
		if (jumpInterval >= 0.30) {
			jumpInterval = 0;
			allowJump = true;
		}
	}
	//玩家复活
	if (GameStatus::getInstance()->getResurgence()) {
		isShowGameOver = false;
		player->playerResurgence();
		if (player->getPositionY() < _camera->getPositionY()-default_tmx_height) {
			player->setPosition(GeometryUtils::transitionPlayerVec2(Vec2(_camera->getPositionX()+default_tmx_width*4, 
				_camera->getPositionY() + default_tmx_height*3)));
		}
		if (playerInWaterRect) {
			player->setResurgence(true);
			auto leaf = Sprite::create("leaf.png");
			leaf->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
			auto vec = Vec2(player->getPosition().x,player->getPosition().y);
			leaf->setPosition(vec.x, vec.y+ default_tmx_height / 10);
			leaf->setCameraMask((int)CameraFlag::USER1);
			addChild(leaf);
		}
		GameStatus::getInstance()->setResurgence(false);
	}


	if (mapList.size() == 0) {
		return;
	}
	playerStayTime += dt;
	if (playerStayTime > 10) {
		showGameOver(2);
		playerStayTime = 0;
	}
	if (player->getPositionY() < _camera->getPositionY()-default_tmx_height) {
		showGameOver(2);
	}
	for (auto var : autoList) {
		for (auto car : var->getCarList()) {

			Rect newRect = Rect(car->getBoundingBox().getMinX(),
				car->getBoundingBox().getMinY(),
				car->getBoundingBox().getMaxX() - car->getBoundingBox().getMinX(),
				default_tmx_height);
			if (GeometryUtils::intersectsRect(newRect, player->getPlayerCheckRect())) {
				showGameOver(0);
			}
		}
	}

	for (auto tra : trainList)
	{
		if (GeometryUtils::intersectsRect(tra->getTrainObjectBox(), player->getPlayerCheckRect())) {
			showGameOver(0);
		}
	}

	auto playerLine = round(player->getPositionY() / default_tmx_height);
	playerInWaterRect = false;
	for (auto mymap : mapList)
	{
		auto water = mymap->getWaterLineNumber();
		for (auto line : water)
		{
			//玩家在水面上
			if (playerLine == line) {
				playerInWaterRect = true;
			}
		}
		if (playerInWaterRect) {
			bool canLive = false;
			for (auto wo : woodList)
			{
				for (auto board : wo->getBoardList()) {
					if (GeometryUtils::intersectsRect(board->getBoundingBox(), player->getPlayerCheckRect())) {
						canLive = true;
						//log("wood speed = %f", wo->getSpeedX());
						//Audio::getInstance()->playSoundBoard();
						player->setSpeedX(wo->getSpeedX());
						player->setPlayerOnWood(true);
						moveCameraX();
					}
				}
			}
			if (!canLive && !player->getResurgence()) {
				showGameOver(1);
			}
		}
		if (!playerInWaterRect) {
			cancelMoveCameraX();
		}
	}


	randomPassTime += dt;
	if (randomPassTime > randomPrideTime) {
		randomPassTime = 0;
		if (NULL == getChildByTag(521)) {
			auto pride = DreamNode::create(6, Vec2(win.width / 2, win.height / 2));
			pride->setTag(521);
			addChild(pride);
		}
	}
	cameraMoveCheck();
	changeCameraMoveStep();
	if (cameraMoveY > 0) {
		cameraMoveY -= cameraMoveStepY;
		if (_camera->getPositionX() > 0) {
			_camera->setPosition(_camera->getPositionX(), _camera->getPositionY() + cameraMoveStepY);
		}
		else {
			cameraMoveY = 0;
		}
	}
	else {
		cameraMoveY = 0;
	}
	if (cameraMoveX < 0) {
		cameraMoveX += cameraMoveStepX;
		if (_camera->getPositionX() > 0 && cameraMoveX < -8) {
			_camera->setPosition(_camera->getPositionX() - cameraMoveStepX, _camera->getPositionY());
		}
	}
	else {
		cameraMoveX -= cameraMoveStepX;
		if (_camera->getPositionX() < default_tmx_width * 9 && cameraMoveX > 8) {
			_camera->setPosition(_camera->getPositionX() + cameraMoveStepX, _camera->getPositionY());
		}
	}

	if (GameStatus::getInstance()->getInvincible()) {
		invincibleTime -= dt;
		if (invincibleTime < 0) {
			GameStatus::getInstance()->setInvincible(false);
			invincibleTime = 10;
		}
	}
	recycleResource();
}