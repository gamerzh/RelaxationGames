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
	playerCamera->setPosition(win.width/2,0);
	addChild(playerCamera, 1);//添加到当前场景里

	mapLayer = GameLayer::create(playerCamera);
	mapLayer->setCameraMask(2);
	addChild(mapLayer);

	scheduleUpdate();

    return true;
}




void GameScene::update(float dt) {
	//playerCamera->setPosition(playerCamera->getPositionX(),playerCamera->getPositionY()+0.25f);
}