//
//  Enemy.cpp
//  ShootEvil
//
//
USING_NS_CC;

#include "Enemy.h"

bool Enemy::init(){
    if(!Sprite::init()){
        return false;
    }
    // init  sprite
    this->initWithFile(getTextureName()); 
    // create a static PhysicsBody
    auto size = this->getContentSize();
    auto physicsBody = PhysicsBody::createBox(size, PhysicsMaterial(0.1f, 1.0f, 0.0f));
    physicsBody->setCategoryBitmask(0x02);//0010
    physicsBody->setCollisionBitmask(0x07);//0111
    physicsBody->setDynamic(true);
    physicsBody->setGravityEnable(false);
    // sprite will use physicsBody
    this->addComponent(physicsBody);
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(Enemy::onContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    return true;
}

bool Enemy::onContactBegin(PhysicsContact& contact)
{
//    auto bodyA = contact.getShapeA()->getBody();
//    auto bodyB = contact.getShapeB()->getBody();
//    log("bodyA->name = %s",bodyA->getName().c_str());
//    log("bodyB->name = %s",bodyB->getName().c_str());
    return true;
}

std::string Enemy::getTextureName(){
    return "ball.png";
}

