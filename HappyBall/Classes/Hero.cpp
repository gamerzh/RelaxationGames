#include "Hero.h"
USING_NS_CC;

bool Hero::init() {
	if (!Sprite::init()) {
		return false;
	}
	addPhysicsHero();
	return true;
}

void Hero::addPhysicsHero() {
	//auto physicsBody = PhysicsBody::createCircle(HERO_BALL_RADIUS,
	//	PhysicsMaterial(1.0f, 1.0f, 0));
	//physicsBody->setDynamic(true);
	//physicsBody->setGravityEnable(true);
	//physicsBody->setCategoryBitmask(0x02);    // 0010
	//physicsBody->setCollisionBitmask(0x01);   // 0001
	//hero->addComponent(physicsBody);
	auto hero = Sprite::create("HelloWorld.png");
	hero->setScale(0.2f);
	hero->setPosition(360, 640);
	addChild(hero);
}