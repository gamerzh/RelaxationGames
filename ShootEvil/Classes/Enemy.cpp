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
    physicsBody->setGravityEnable(true);
    // sprite will use physicsBody
    this->addComponent(physicsBody);
    
    return true;
}

std::string Enemy::getTextureName(){
    return "ball.png";
}

