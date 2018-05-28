#include "GameLayer.h"
#include "ResultScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

bool GameLayer::init() {
	if (!Layer::init()) {
		return false;
	}


	auto black = LayerColor::create(Color4B(100, 100, 255, 255), 720, 1280);
	addChild(black);

	//auto hero = CSLoader::createNode("Node.csb");
	//hero->setPosition(360, 300);
	//hero->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	//addChild(hero);
	////auto a1 = hero->getChildByName("Node");
	//auto a2 = hero->getChildByName("kk_2")->getChildByName("llk_3_0");
	//auto c = a2->getColor();
	//a2->setPosition(360, 840);

	auto physicsBody = PhysicsBody::createBox(Size(100, 100),
		PhysicsMaterial(1.0f, 1.0f, 0));
	physicsBody->setDynamic(true);
	physicsBody->setGravityEnable(true);
	physicsBody->setCategoryBitmask(0x02);    // 0010
	//physicsBody->setCollisionBitmask(0x01);   // 0001
	//create a sprite
	auto sprite = Sprite::create("HelloWorld.png");
	sprite->setScale(0.2f);
	sprite->setPosition(360,640);
	addChild(sprite);
	//apply physicsBody to the sprite
	sprite->addComponent(physicsBody);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameLayer::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);

	return true;
}


bool GameLayer::onContactBegin(PhysicsContact& contact){

	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();
	log("AAAAAAAAAAAAA");
	if (nodeA && nodeB)
	{
		log("AAAAAAAAAAAAA");
	}

	//bodies can collide
	return true;
}