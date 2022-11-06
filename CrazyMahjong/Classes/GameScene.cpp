#include "GameScene.h"
#include "NameMannger.h"
#include "GameFlow.h"
#include "SystemUI.h"
#include "Jniutill.h"
#include "User.h"
Scene* GameScene::createScene()
{
	GameScene* mahjongScene = GameScene::create();
	return mahjongScene;
}

bool GameScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 centerPoint = Vec2(visibleSize.width/2, visibleSize.height/2);

	// 桌面背景
	Sprite* bkg = Sprite::create("GameBkg.jpg");
	bkg->setPosition(centerPoint);
	this->addChild(bkg);

	auto playerframe = Sprite::create("ori_bg.png");
	playerframe->setPosition(centerPoint + Vec2(0, 50));
	addChild(playerframe);

	Sprite* phoneNumberSpr = Sprite::create("phoneNumber.png");

	phoneNumberSpr->setPosition(700.0f, 20.0f);
	this->addChild(phoneNumberSpr);
	// 游戏
	GameFlow* gameFlow = GameFlow::create();
	this->addChild(gameFlow,0,"gameflow");


	return true;
}

void GameScene::GameOver()
{
	
}

