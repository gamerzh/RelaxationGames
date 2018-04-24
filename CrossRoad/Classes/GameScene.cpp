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

	addTouchListener();

    //auto rootNode = CSLoader::createNode("MainScene.csb");
    //addChild(rootNode);

	player = Player::create();
	player->setPosition(300, 300);
	player->setCameraMask(2);
	addChild(player);

	auto map1 = MapNode::create(Point(320,200));
	map1->setCameraMask(1);
	addChild(map1);

	//正交相机的使用
	//auto win = Director::getInstance()->getWinSize();
	//auto camera = Camera::createOrthographic(win.width * 1.0, win.height * 1.0, -1024, 1024);
	//camera->setCameraFlag(CameraFlag::USER1);
	//addChild(camera, 1);//添加到当前场景里
	//camera->runAction(MoveTo::create(10, Vec2(camera->getPositionX(), camera->getPositionY() - win.height)));

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