#include "GameScene.h"
#include "GameLayer.h"
#include "MainLayer.h"
USING_NS_CC;

bool GameScene::init() {
	if (!Scene::init()) {
		return false;
	}
	
	addLayerToScene();
	return true;
}

void GameScene::onEnter() {
	Scene::onEnter();
}

void GameScene::addLayerToScene() {
	//add game layer to scene
	auto gameLayer = GameLayer::create();
	addChild(gameLayer);

	auto mainLayer = MainLayer::create();
	addChild(mainLayer);
}

void GameScene :: addPhysicsToScene(){
	//getPhysicsWorld()->setAutoStep(true);
	//getPhysicsWorld()->setGravity(Vec2(0,-98*4));
	//getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
}