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
	getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//定义世界的边界;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(body);
	addChild(edgeNode);

}