#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"



using namespace cocostudio::timeline;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }


	auto win = Director::getInstance()->getWinSize();
	//正交相机的使用
	playerCamera = Camera::createOrthographic(win.width * 1.0, win.height * 1.0, -1024, 1024);
	playerCamera->setCameraFlag(CameraFlag::USER1);
	playerCamera->setPosition(0,0);
	addChild(playerCamera, 1);//添加到当前场景里

	addTouchListener();

	player = Player::create();
	player->setPosition(300, 220);
	player->setCameraMask(2);
	addChild(player, 1);

	mapLayer = MapLayer::create(playerCamera);
	mapLayer->setCameraMask(2);
	addChild(mapLayer);

	scheduleUpdate();

    return true;
}


void GameScene::addTouchListener() {
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}


bool GameScene::onTouchBegan(Touch *touch, Event *event) {
	preTouchPoint = touch->getLocation();
	playerGesture = Gesture::straight;
	return true;
}


void GameScene::onTouchMoved(Touch* touch, Event* event) {
	if (touch->getLocation().x > preTouchPoint.x && touch->getLocation().x - preTouchPoint.x >10 
		&& (touch->getLocation().y-preTouchPoint.y)/(touch->getLocation().x-preTouchPoint.x)<1) {
		playerGesture = Gesture::right;
	}
	else if(touch->getLocation().x < preTouchPoint.x &&  preTouchPoint.x - touch->getLocation().x >10
		&& (touch->getLocation().y - preTouchPoint.y) / (preTouchPoint.x-touch->getLocation().x)<1){
		playerGesture = Gesture::left;
	}
	else {
		playerGesture = Gesture::straight;
	}
}


void GameScene::onTouchEnded(Touch* touch, Event* event) {
	//对于操作指法的判定,向左滑动,向右滑动,双击
	if (NULL != player) {
		if (playerGesture == Gesture::left) {
			player->playerJumpLeft();
		}
		else if (playerGesture == Gesture::right) {
			player->playerJumpRight();
		}
		else {
			player->playerJumpStraight();
		}
	}

}


void GameScene::update(float dt) {
	playerCamera->setPosition(playerCamera->getPositionX(),playerCamera->getPositionY()+0.25f);

	for (auto var : mapLayer->getMapNodes()) {
		if (var->getBoundingBox().intersectsRect(player->getBoundingBox())) {
			if (var->getMapNodeType() != MapNodeType::type3) {
				//玩家站在可靠的区域

				//for (auto dan : var->getDangerObject()) {
				//	log("Rect 1 = %f,%f,%f,%f", dan->getBoundingBox().getMinX(), dan->getBoundingBox().getMinY(),
				//		dan->getBoundingBox().getMaxX(), dan->getBoundingBox().getMaxY());
				//	/*log("Rect 2 = %f,%f,%f,%f", player->getBoundingBox().getMinX(), player->getBoundingBox().getMinY(),
				//		player->getBoundingBox().getMaxX(), player->getBoundingBox().getMaxY());*/
				//	if (dan->getBoundingBox().intersectsRect(player->getBoundingBox())) {
				//	
				//	}
				//}
			}
		}
	}
}