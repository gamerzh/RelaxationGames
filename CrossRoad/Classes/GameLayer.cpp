#include "GameLayer.h"
#include "GameOver.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GeometryUtils.h"

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
	player->setPosition(mapList.at(0)->getHeroStartPos());
	player->setCameraMask(int(CameraFlag::USER1));
	addChild(player, PlayerZorder);
	scheduleUpdate();
	schedule(schedule_selector(GameLayer::checkMapInScene), 0.1f);
	addTouchListener();
	return true;
}

void GameLayer::initGameMap() {
	//for (int i = 0; i < 4; i++) {
		addGameMap();
	//}
}

void GameLayer::checkMapInScene(float dt) {
	if (mapList.size() == 0) {
		return;
	}
	vector<MapNode*>::iterator it;
	for (it = mapList.begin(); it != mapList.end(); it++)
	{
		auto node = *it;
		if (_camera->getPositionY() > node->getPositionY() + node->getContentSize().height) {
			it = mapList.erase(it);
			node->removeFromParent();
			needAddMap = true;
		}
		if (needAddMap) {
			//addGameMap();
			needAddMap = false;
		}

	}
}

void GameLayer::addGameMap() {
	int ran = random(0,3);
	auto node = MapNode::create(MapNodeType(ran));
	if (mapList.size() == 0) {
		node->setPosition(0, 0);
	}
	else {
		node->setPosition(0, mapList.at(mapList.size() - 1)->getPositionY() + mapList.at(mapList.size() - 1)->getContentSize().height);
	}
	node->setCameraMask(int(CameraFlag::USER1));
	addChild(node);
	mapList.push_back(node);

	//在地图上生成树木和屋子
	for (auto treePos : node->getBlockInfoList()) {
		createHouseAndTree(treePos.type,Size(treePos.width,treePos.height),treePos.position);
	}
	//在地图上生成卡车
	for (auto info : node->getEnemyInfoList()) {
		createAutomoblie(_camera,info.type,info.direction,info.speed,info.interval,info.position);
	}

	for (auto woodInfo : node->getWoodInfoList())
	{
		createWood(woodInfo.type, woodInfo.direction,woodInfo.speed,woodInfo.position);
	}
}

void GameLayer::createHouseAndTree(int type,Size size, Point pos) {
	int line = floor(pos.y / default_tmx_height);
	auto tree = Block::create(type, size);
	tree->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	tree->setPosition(floor(pos.x / default_tmx_width)*default_tmx_width + (PLAYER_JUMP_OFFSET*line)%default_tmx_width,
		line*default_tmx_height + default_tmx_height/6);
	addChild(tree, MaxZorder - line);
	treeList.push_back(tree);
}

void GameLayer::createAutomoblie(Camera* camera,int type, int direction, int speed, int interval, Point pos) {
	//需要更具MapNode的情况来产生汽车
	auto automoblie = Automobile::create(camera,type, direction, speed, interval, pos);
	automoblie->setCameraMask(int(CameraFlag::USER1));
	addChild(automoblie, MaxZorder - floor(pos.y / default_tmx_height));
	autoList.push_back(automoblie);
}

void GameLayer::createWood(int type,int dir,int speed, Point pos) {
	auto wood = Wood::create(type, dir, speed);
	wood->setPosition(pos.x, floor(pos.y / default_tmx_height)*default_tmx_height+ default_tmx_height/6);
	addChild(wood, MaxZorder - floor(pos.y / default_tmx_height));
	woodList.push_back(wood);
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
				if (player->playerJumpLeft(treeList)) {
					cameraMoveLeft += default_tmx_width;
					cameraMoveRight = 0;
				}
			}
			

		}
		else if (playerGesture == Gesture::right) {
			if (player->getPositionX() < default_tmx_width*17){
				if (player->playerJumpRight(treeList) ){
					cameraMoveRight += default_tmx_width;
					cameraMoveLeft = 0;
				}
			}

		}
		else if (playerGesture == Gesture::backwards) {
			if (player->getPositionY() >= _camera->getPositionY() + default_tmx_height) {
				player->playerJumpBackwards(treeList);
			}
		}
		else {
			cameraMoveY += default_tmx_height/4;
			cameraMoveRight += PLAYER_JUMP_OFFSET;
			player->playerJumpForward(treeList);
		}
		player->setZOrder(MaxZorder - floor(player->getPositionY() / default_tmx_height));
	}

}

void GameLayer::updateTreeZorder() {
	//TODO
}


void GameLayer::changeCameraMoveStep() {
	//更具玩家和摄像机的距离调整步幅
	if (cameraMoveRight > 0) {
		if (player->getPositionX() - _camera->getPositionX() < 3* default_tmx_width) {
			cameraMoveStep = 1.2;
			return;
		}
		else if (player->getPositionX() - _camera->getPositionX() < 6 * default_tmx_width) {
			cameraMoveStep = 1.6;
			return;
		} else{
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
	},1.0f/60, SCHEDULE_CAMERA_X);
}

void GameLayer::cancelMoveCameraX() {
	player->setSpeedX(0);
	unschedule(SCHEDULE_CAMERA_X);
}

void GameLayer::update(float dt) {
	if (mapList.size() == 0) {
		return;
	}
	for (auto var : autoList) {
		for (auto car : var->getCarList()) {
			Rect newRect = Rect(car->getBoundingBox().getMinX(), 
				car->getBoundingBox().getMinY(), 
				car->getBoundingBox().getMaxX()- car->getBoundingBox().getMinX(),
				default_tmx_height);
			if (GeometryUtils::intersectsRect(newRect, player->getPlayerCheckRect())) {
				if (NULL == getChildByTag(100)) {
					auto over = GameOver::create();
					over->setTag(100);
					addChild(over);
				}
			}
		}
	}

	for (auto mymap:mapList)
	{
		auto water = mymap->getTMXWater();
		//玩家在水面上
		if (water->getTileGIDAt(Vec2(defult_tmx_x_num-1-floor(player->getPositionX()/default_tmx_width), defult_tmx_y_num-1-floor(player->getPositionY()/default_tmx_height)))) {

			bool canLive = false;
			for (auto wo : woodList)
			{
				if(GeometryUtils::intersectsRect(wo->getBoundingBox(), player->getPlayerCheckRect())) {
					canLive = true;
					player->setSpeedX(wo->getSpeedX());
					moveCameraX();
					playerStandOnWood = true;
				}
			}
			if (!canLive) {
				if (NULL == getChildByTag(100)) {
					auto over = GameOver::create();
					over->setTag(100);
					addChild(over);
					//log("aaaaaaaaaaaaaaaa %f %f", player->getPositionY(), floor(player->getPositionX() / default_tmx_width));
					//log("bbbbbbbbbbbbbbbb %f %f", player->getPositionY(),floor(player->getPositionY() / default_tmx_height));
					
				}
			}
		}
		else {
			if (playerStandOnWood) {
				cancelMoveCameraX();
				playerStandOnWood = false;
			}
		}
	}
	
	changeCameraMoveStep();
	if (cameraMoveY > 0) {
		cameraMoveY -= 1;
		if (_camera->getPositionX() > 0) {
			_camera->setPosition(_camera->getPositionX(), _camera->getPositionY() +1);
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