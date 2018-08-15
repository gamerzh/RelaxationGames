#include "GameLayer.h"
#include "Hero.h"
USING_NS_CC;

bool GameLayer::init() {
	if (!Layer::init()) {
		return false;
	}


	auto black = LayerColor::create(Color4B(200, 200, 200, 204), 1280, 720);
	addChild(black);
    
    auto hero = Hero::create();
    hero->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
    hero->setPosition(640,0);
    addChild(hero);

    loadControlPad();
    
	return true;
}

void GameLayer::loadControlPad(){
//
}
