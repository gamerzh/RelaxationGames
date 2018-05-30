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
	//addEdgeToGame();
	addBrickToGame();
	addHeroToGame();
	addTouchListener();
	//auto contactListener = EventListenerPhysicsContact::create();
	//contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, this);
	//Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
	return true;
}

void GameLayer::addHeroToGame() {
	auto hero = Hero::create();
	addChild(hero);
}

void GameLayer::addBrickToGame() {
	auto brick = Brick::create();
	brick->setTag(1024);
	addChild(brick);
}


void GameLayer::addTouchListener() {

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool GameLayer::onTouchBegan(Touch *touch, Event  *event) {
	if (NULL != getChildByTag(1024)) {
		auto br = ((Brick*)getChildByTag(1024));
		br->setFrameIndex((br->getFrameIndex()+2)%41);
	}

	return true;
}

void GameLayer::onTouchMoved(Touch *touch, Event  *event) {

}


void GameLayer::onTouchEnded(Touch *touch, Event  *event) {


}

//bool GameLayer::onContactBegin(PhysicsContact& contact){
//	log("AAAAAAAAAAAAA");
//	auto nodeA = contact.getShapeA()->getBody()->getNode();
//	auto nodeB = contact.getShapeB()->getBody()->getNode();
//
//	if (nodeA && nodeB)
//	{
//		log("AAAAAAAAAAAAA");
//	}
//
//	//bodies can collide
//	return true;
//}

//void GameLayer::addEdgeToGame() {
//	//定义世界的边界;
//	auto visibleSize = Director::getInstance()->getVisibleSize();
//	auto body = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(1.0f, 1.0f, 0));
//	auto edgeNode = Node::create();
//	edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
//	edgeNode->setPhysicsBody(body);
//	addChild(edgeNode);
//}