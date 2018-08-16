#include "GameLayer.h"
USING_NS_CC;

bool GameLayer::init() {
	if (!Layer::init()) {
		return false;
	}


	auto black = LayerColor::create(Color4B(200, 200, 200, 204), 1280, 720);
	addChild(black);
    
    superHero = Hero::create();
    superHero->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    superHero->setPosition(640,0);
    addChild(superHero);

    loadControlPad();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
	return true;
}

void GameLayer::loadControlPad(){
    leftRect = Rect(0,0,200,720);
    rightRect = Rect(200,0,200,720);
    slideRect = Rect(880,0,200,720);
    shootRect = Rect(1080,0,200,720);
    auto left = Sprite::create("left.png");
    left->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    left->setPosition(100,0);
    addChild(left);
    auto right = Sprite::create("left.png");
    right->setFlippedX(true);
    right->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    right->setPosition(300,0);
    addChild(right);
}

bool GameLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event){
    if(leftRect.containsPoint(touch->getLocation())){
        //moveleft
        superHero->controlHero(true, Hero::Direction::left);
    }else if(rightRect.containsPoint(touch->getLocation())){
        //moveright
        superHero->controlHero(true, Hero::Direction::right);
    }else if(slideRect.containsPoint(touch->getLocation())){
        //slide
    }else if(shootRect.containsPoint(touch->getLocation())){
        //shoot
        superHero->shoot();
    }
    return true;
}

void GameLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event){
    
}

void GameLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event){
     superHero->controlHero(false, Hero::Direction::null);
}
