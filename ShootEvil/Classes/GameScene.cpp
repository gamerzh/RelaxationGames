#include "GameScene.h"
#include "GameLayer.h"
USING_NS_CC;

bool GameScene::init() {
	if (!Scene::initWithPhysics()) {
		return false;
	}
	addLayerToScene();
	return true;
}

void GameScene::addLayerToScene() {
	//add game layer to scene
	auto gameLayer = GameLayer::create();
	addChild(gameLayer);
}
