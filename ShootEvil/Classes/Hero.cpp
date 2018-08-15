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
    // init  sprite
    this->initWithFile("hero.png");
    // create a static PhysicsBody
    auto size = this->getContentSize();
    auto physicsBody = PhysicsBody::createBox(size, PhysicsMaterial(0.1f, 1.0f, 0.0f));
    physicsBody->setDynamic(true);
    // sprite will use physicsBody
    this->addComponent(physicsBody);
    //add contact event listener
    //    auto contactListener = EventListenerPhysicsContact::create();
    //    contactListener->onContactBegin = CC_CALLBACK_1(Hero::onContactBegin, this);
    //    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    return true;
}

//bool Hero::onContactBegin(PhysicsContact& contact){
//    return true;
//}
