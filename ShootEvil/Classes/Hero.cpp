//
//  Hero.cpp
//  ShootEvil
//

#include "Hero.h"
USING_NS_CC;

bool Hero::init(){
    if(!Sprite::init()){
        return false;
    }
    this->moveDir = Direction::null;
    this->isMoveing = false;
    // init  sprite
    this->initWithFile("hero.png");
    // create a static PhysicsBody
    auto size = this->getContentSize();
    auto physicsBody = PhysicsBody::createBox(size, PhysicsMaterial(0.1f, 1.0f, 0.0f));
    physicsBody->setDynamic(true);
    physicsBody->setCategoryBitmask(0x01);
    physicsBody->setCollisionBitmask(0x02);
    // sprite will use physicsBody
    this->addComponent(physicsBody);
    scheduleUpdate();
    return true;
}


void Hero::shoot(){
    auto bul = Bullet::create();
    bul->setPosition(31,0);
    addChild(bul,-1);
}

void Hero::controlHero(bool move,Direction dir){
    this->isMoveing = move;
    this->moveDir = dir;
}

void Hero::update(float dt){
    if(isMoveing){
        auto pre = this->getPosition();
        if(this->moveDir == Direction::left){
            this->setPosition(pre.x-2,pre.y);
        }else if(this->moveDir == Direction::right){
            this->setPosition(pre.x+2,pre.y);
        }
    }
}





