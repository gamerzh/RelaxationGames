//
//  Bullet.cpp
//  ShootEvil
//
//  Created by gamerzh on 2018/8/16.
//

#include "Bullet.h"
USING_NS_CC;

bool Bullet::init(){
    if(!Sprite::init()){
        return false;
    }
    initWithFile("bullet1.png");
    // create a static PhysicsBody
    auto size = this->getContentSize();
    auto physicsBody = PhysicsBody::createBox(size, PhysicsMaterial(0.1f, 1.0f, 0.0f));
    physicsBody->setDynamic(true);
    physicsBody->setCategoryBitmask(0x04);//0100
    physicsBody->setCollisionBitmask(0x02);//0010
    physicsBody->setGravityEnable(false);
    // sprite will use physicsBody
    this->addComponent(physicsBody);
    scheduleUpdate();
    return true;
}


void Bullet::update(float dt){
    auto pre = this->getPosition();
    this->setPosition(pre.x,pre.y+4);
}
