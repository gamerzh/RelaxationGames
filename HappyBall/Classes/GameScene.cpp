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

void GameScene::onEnter() {
	Scene::onEnter();
	addPhysicsToScene();
}

void GameScene::addLayerToScene() {
	//add game layer to scene
	auto gameLayer = GameLayer::create();
	addChild(gameLayer);
}

void GameScene :: addPhysicsToScene(){
	getPhysicsWorld()->setAutoStep(true);
	getPhysicsWorld()->setGravity(Vec2(0,-98*4));
	getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
}