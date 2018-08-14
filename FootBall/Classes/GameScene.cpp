#include "GameScene.h"
#include "GameLayer.h"
USING_NS_CC;

bool GameScene::init() {
	if (!Scene::init()) {
		return false;
	}
	startFootBall();
	return true;
}

void GameScene::startFootBall() {
	//add game layer to scene
	auto gameLayer = GameLayer::create();
	addChild(gameLayer,2);
}