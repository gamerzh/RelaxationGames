#include "GameLayer.h"
#include "GameOver.h"
#include "GeometryUtils.h"
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
	auto playerPos = GeometryUtils::transitionPlayerVec2(mapList.at(0)->getHeroStartPos(), used_map_node);
	player->setPosition(playerPos.x, playerPos.y);
	player->setCameraMask(int(CameraFlag::USER1));
	//log("Player postion = (%.1f,%.1f)", playerPos.x, playerPos.y);
	addChild(player, MaxZorder);
	scheduleUpdate();
	schedule(schedule_selector(GameLayer::checkMapInScene), 0.1f);
	addTouchListener();
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
		if (_camera->getPositionY() >used_map_node*defult_tmx_y_num * default_tmx_height + win.height) {
			it = mapList.erase(it);
			node->removeFromParent();
		}
		
		else {
			++it;
		}

	}
	if (needAddMap) {
		log("add new map");
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
	//在地图上生成卡车
	for (auto info : node->getEnemyInfoList()) {
		createAutomoblie(_camera, info.type, info.direction, info.speed, info.interval, info.position);
	}
	//生成木板和荷叶
	for (auto woodInfo : node->getWoodInfoList())
	{
		createWood(woodInfo.type, woodInfo.direction, woodInfo.time, woodInfo.position);
	}

	//生成火车
	for (auto lightInfo : node->getLightInfoList()) {
		createTrain(lightInfo.pos);
	}

}

void GameLayer::createHouseAndTree(int type, Size size, Point pos) {
	int line = floor(pos.y / default_tmx_height);
	auto tree = Block::create(type, pos, size);
	tree->setCameraMask(int(CameraFlag::USER1));
	tree->setPosition(GeometryUtils::transitionObjectVec2(pos, used_map_node).x, GeometryUtils::transitionObjectVec2(pos, used_map_node).y + default_tmx_height / 5);
	addChild(tree, MaxZorder - line);
	treeList.push_back(tree);
}

void GameLayer::createAutomoblie(Camera* camera, int type, int direction, int speed, int interval, Point pos) {
	//需要更具MapNode的情况来产生汽车
	auto automoblie = Automobile::create(camera, type, direction, speed, interval, pos);
	automoblie->setCameraMask(int(CameraFlag::USER1));
	addChild(automoblie, MaxZorder - floor(pos.y / default_tmx_height));
	autoList.push_back(automoblie);
	//log("Automobile Zorder %d", automoblie->getZOrder());
}

void GameLayer::createWood(int type, int dir, int time, Point pos) {
	auto wood = Wood::create(type, dir, time);
	wood->setPosition(GeometryUtils::transitionObjectVec2(pos, used_map_node));
	wood->setCameraMask(int(CameraFlag::USER1));
	addChild(wood, MaxZorder - round(pos.y / default_tmx_height));
	woodList.push_back(wood);
	//log("Wood position %.1f,%.1f", wood->getPositionX(),wood->getPositionY());
	//log("Wood Zorder = %d", wood->getZOrder());
}

void GameLayer::createGold(Point position) {
	auto goldIcon = GoldIcon::create();
	goldIcon->setPosition(GeometryUtils::transitionObjectVec2(position, used_map_node));
	goldIcon->setCameraMask(int(CameraFlag::USER1));
	addChild(goldIcon, MaxZorder - round(position.y / default_tmx_height));
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
	return true;
}


void GameLayer::onTouchMoved(Touch* touch, Event* event) {
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
	//对于操作指法的判定,向左滑动,向右滑动,双击
	if (NULL != player) {
		if (playerGesture == Gesture::left) {

			if (player->getPositionX() > default_tmx_width) {
				if (player->playerJumpLeft(treeList,used_map_node)) {
					cameraMoveLeft += default_tmx_width;
					cameraMoveRight = 0;
				}
			}
		}
		else if (playerGesture == Gesture::right) {
			if (player->getPositionX() < default_tmx_width * 17) {
				if (player->playerJumpRight(treeList, used_map_node)) {
					cameraMoveRight += default_tmx_width;
					cameraMoveLeft = 0;
				}
			}

		}
		else if (playerGesture == Gesture::backwards) {
			if (player->getPositionY() >= _camera->getPositionY() + default_tmx_height) {
				player->playerJumpBackwards(treeList, used_map_node);
			}
		}
		else {
			cameraMoveY += default_tmx_height / 4;
			cameraMoveRight += PLAYER_JUMP_OFFSET;
			player->playerJumpForward(treeList, used_map_node);

		}
		player->setZOrder(MaxZorder - floor(player->getPositionY() / default_tmx_height));
		log("Player Zorder %d", player->getZOrder());
		//检查玩家是否碰到了金币
		vector<GoldIcon*>::iterator it;
		for (it = goldList.begin(); it != goldList.end(); ++it) {
			GoldIcon* myGold = *it;
			if (GeometryUtils::intersectsRect(myGold->getBoundingBox(), player->getPlayerCheckRect())) {
				it = goldList.erase(it);
				myGold->removeFromParent();
			}
		}
	}

}

void GameLayer::updateTreeZorder() {
	//TODO
}


void GameLayer::changeCameraMoveStep() {
	//更具玩家和摄像机的距离调整步幅
	if (cameraMoveRight > 0) {
		if (player->getPositionX() - _camera->getPositionX() < 3 * default_tmx_width) {
			cameraMoveStep = 1.2;
			return;
		}
		else if (player->getPositionX() - _camera->getPositionX() < 6 * default_tmx_width) {
			cameraMoveStep = 1.6;
			return;
		}
		else {
			cameraMoveStep = 2.0;
			return;
		}
	}

	if (cameraMoveLeft > 0) {
		if (player->getPositionX() - _camera->getPositionX() < 3 * default_tmx_width) {
			cameraMoveStep = 2.0;
			return;
		}
		else if (player->getPositionX() - _camera->getPositionX() < 6 * default_tmx_width) {
			cameraMoveStep = 1.6;
			return;
		}
		else {
			cameraMoveStep = 1.2;
			return;
		}
	}
}

void GameLayer::moveCameraX() {
	schedule([=](float dt) {
		if (_camera->getPositionX() >= 0 && _camera->getPositionX() <= 10 * default_tmx_width) {
			_camera->setPosition(_camera->getPositionX() + player->getSpeedX(), _camera->getPositionY());
		}
	}, 1.0f / 60, SCHEDULE_CAMERA_X);
}

void GameLayer::cancelMoveCameraX() {
	player->setSpeedX(0);
	unschedule(SCHEDULE_CAMERA_X);
}

void GameLayer::showGameOver() {
	player->playerGoDie();
	player->setZOrder(player->getZOrder() - PlayerZorder);//死亡后图层下降
	if (NULL == getChildByTag(100)) {
		auto over = GameOver::create();
		over->setTag(100);
		addChild(over);
	}
}

void GameLayer::update(float dt) {
	if (mapList.size() == 0) {
		return;
	}
	for (auto var : autoList) {
		for (auto car : var->getCarList()) {
			Rect newRect = Rect(car->getBoundingBox().getMinX(),
				car->getBoundingBox().getMinY(),
				car->getBoundingBox().getMaxX() - car->getBoundingBox().getMinX(),
				default_tmx_height);
			if (GeometryUtils::intersectsRect(newRect, player->getPlayerCheckRect())) {
				showGameOver();
			}
		}
	}

	for (auto tra : trainList)
	{

		if (GeometryUtils::intersectsRect(tra->getTrainObjectBox(), player->getPlayerCheckRect())) {
			showGameOver();
		}
		//auto train = tra->getTrainObject();
		//if (train != nullptr) {
			/*log("Train Rect(%.1f,%.1f,%.1f,%.1f)",
				train->getBoundingBox().getMinX(),
				train->getBoundingBox().getMinY(),
				train->getBoundingBox().getMaxX() - train->getBoundingBox().getMinX(),
				train->getBoundingBox().getMaxY() - train->getBoundingBox().getMinY());*/

				//}
	}

	auto playerLine = floor(player->getPositionY() / default_tmx_height);
	for (auto mymap : mapList)
	{
		auto water = mymap->getWaterLineNumber();
		for (auto line : water)
		{
			//玩家在水面上
			if (playerLine == line) {

				bool canLive = false;
				for (auto wo : woodList)
				{
					if (GeometryUtils::intersectsRect(wo->getBoundingBox(), player->getPlayerCheckRect())) {
						canLive = true;
						player->setSpeedX(wo->getSpeedX());
						moveCameraX();
						playerStandOnWood = true;
					}
				}
				if (!canLive) {
					showGameOver();
				}
			}
			else {
				if (playerStandOnWood) {
					cancelMoveCameraX();
					playerStandOnWood = false;
				}
			}
		}
	}

	changeCameraMoveStep();
	if (cameraMoveY > 0) {
		cameraMoveY -= 1;
		if (_camera->getPositionX() > 0) {
			_camera->setPosition(_camera->getPositionX(), _camera->getPositionY() + 1);
		}
		else {
			cameraMoveY = 0;
		}
	}
	else {
		cameraMoveY = 0;
	}
	if (cameraMoveLeft > 0) {
		cameraMoveLeft -= cameraMoveStep;
		if (_camera->getPositionX() > 0) {
			_camera->setPosition(_camera->getPositionX() - cameraMoveStep, _camera->getPositionY());
		}
		else {
			cameraMoveLeft = 0;
		}
	}
	else {
		cameraMoveLeft = 0;
	}
	if (cameraMoveRight > 0) {
		cameraMoveRight -= cameraMoveStep;
		if (_camera->getPositionX() < default_tmx_width * 10) {
			_camera->setPosition(_camera->getPositionX() + cameraMoveStep, _camera->getPositionY());
		}
		else {
			cameraMoveRight = 0;
		}
	}
	else {
		cameraMoveRight = 0;
	}
}