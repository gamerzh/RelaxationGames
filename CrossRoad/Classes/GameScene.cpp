#include "GameScene.h"
#include "PauseLayer.h"
#include "GameStatus.h"
#include "UserData.h"
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

	initView();

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

void GameScene::initView() {
	auto men = MenuItemImage::create("pause.png", "pause.png", CC_CALLBACK_0(GameScene::pauseMove, this));
	auto menu = Menu::create(men, NULL);
	menu->setPosition(men->getContentSize().width*0.7,
		win.height - men->getContentSize().height*0.7);
	addChild(menu);

	auto stepNum = LabelAtlas::create(String::createWithFormat("%d", GameStatus::getInstance()->getScore())->_string, "step_num.png", 56, 55, '0');
	stepNum->setAnchorPoint(Point::ANCHOR_MIDDLE);
	stepNum->setTag(1024);
	stepNum->setPosition(win.width/2 - stepNum->getContentSize().width/2,
		win.height - stepNum->getContentSize().height/2*1.4);
	addChild(stepNum);


	auto goldNum = LabelAtlas::create(String::createWithFormat("%d", UserData::getInstance()->getPlayerGoldNum())->_string, "c_num.png", 51, 55, '0');
	goldNum->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	goldNum->setPosition(win.width - 10, 
		win.height - goldNum->getContentSize().height/2*1.4);
	goldNum->setTag(1025);
	addChild(goldNum);
	auto icon = Sprite::create("icon_c.png");
	icon->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	icon->setPosition(win.width- goldNum->getContentSize().width,
		win.height - icon->getContentSize().height*1.35);
	addChild(icon);

}

void GameScene::pauseMove() {
	GameStatus::getInstance()->setGameStatus(false);
	PauseLayer* laye = PauseLayer::create();
	addChild(laye);
}


void GameScene::update(float dt) {
	if (GameStatus::getInstance()->getGameStatus()) {
		//playerCamera->setPosition(playerCamera->getPositionX(), playerCamera->getPositionY() + 0.5f);
		if (NULL != getChildByTag(1024)) {
			((LabelAtlas*)getChildByTag(1024))->setString(String::createWithFormat("%d", GameStatus::getInstance()->getScore())->_string);
		}
		if (NULL != getChildByTag(1025)) {
			((LabelAtlas*)getChildByTag(1025))->setString(String::createWithFormat("%d", UserData::getInstance()->getPlayerGoldNum())->_string);
		}
	}
}

