#include "GameLayer.h"
#include "ResultScene.h"
#include "Hero.h"
#include "Brick.h"
USING_NS_CC;

bool GameLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	auto black = LayerColor::create(Color4B(100, 100, 255, 255), 720, 1280);
	addChild(black);
	addEdgeToGame();
	addBrickToGame();
	addHeroToGame();
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
	return true;
}

void GameLayer::addEdgeToGame() {
	//定义世界的边界;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto body = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(1.0f, 1.0f, 0));
	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(body);
	addChild(edgeNode);
}

void GameLayer::addHeroToGame() {
	auto hero = Hero::create();
	addChild(hero);
}

void GameLayer::addBrickToGame() {
	auto brick = Brick::create();
	addChild(brick);
}


bool GameLayer::onContactBegin(PhysicsContact& contact){
	log("AAAAAAAAAAAAA");
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB)
	{
		log("AAAAAAAAAAAAA");
	}

	//bodies can collide
	return true;
}