#include "GameLayer.h"
#include "ResultScene.h"
#include "Hero.h"

USING_NS_CC;

bool GameLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	auto black = LayerColor::create(Color4B(100, 100, 255, 255), 720, 1280);
	addChild(black);
	createBrick();
	addHeroToGame();
	addTouchListener();
	return true;
}

void GameLayer::addHeroToGame() {
	auto hero = Hero::create();
	addChild(hero);
}

void GameLayer::createBrick() {
	for (int i=0;i<5;i++)
	{
		auto brick = Brick::create();
		brick->setTag(1000 + i);
		brick->setPosition(360, 1280 - BRICK_HEIGHT * i );
		addChild(brick, BRICK_START_ZORDER -i );
		brickVector.push_back(brick);
	}

}


void GameLayer::recycleBrick() {


}


void GameLayer::addTouchListener() {

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool GameLayer::onTouchBegan(Touch *touch, Event  *event) {
	preTouchPosition = touch->getLocation();
	return true;
}

void GameLayer::onTouchMoved(Touch *touch, Event  *event) {
	auto curpos = touch->getLocation();
	int index = (curpos.x - preTouchPosition.x) / win.width * BRICK_ANIM_NUM/2;
	if (NULL != getChildByTag(1002)) {
		auto br = (Brick*)getChildByTag(1002);
		int fin = br->getFrameIndex() - index;
		while (fin<0)
		{
			fin += BRICK_ANIM_NUM;
		}
		br->setFrameIndex(fin % BRICK_ANIM_NUM);
	}
}


void GameLayer::onTouchEnded(Touch *touch, Event  *event) {

}