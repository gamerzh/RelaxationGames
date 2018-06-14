#include "GameScene.h"
#include "GameLayer.h"
#include "FightLayer.h"
USING_NS_CC;

bool GameScene::init() {
	if (!Scene::init()) {
		return false;
	}
	addLayerToScene();
	return true;
}

void GameScene::addLayerToScene() {
	auto fightLayer = FightLayer::create();
	addChild(fightLayer);
	fightLayer->setMenuCallback([=](Ref* ref) {
		startFootBall();
		fightLayer->removeFromParent();
	});
}


void GameScene::startFootBall() {
	//add game layer to scene
	auto gameLayer = GameLayer::create();
	addChild(gameLayer,2);
}