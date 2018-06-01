#include "GameLayer.h"
#include "ResultScene.h"
#include "GeometryTools.h"

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
	scheduleUpdate();
	return true;
}

void GameLayer::addHeroToGame() {
	hero = Hero::create();
	hero->setPosition(360, 1280);
	addChild(hero, BRICK_START_ZORDER);
}

void GameLayer::createBrick() {
	for (int i=0;i<5;i++)
	{
		//random(0, BRICK_ANIM_NUM)
		auto brick = Brick::create(0+20*i);
		brick->setPosition(360, 720 - BRICK_HEIGHT * i );
		addChild(brick, BRICK_START_ZORDER -i );
		brickVector.push_back(brick);
		auto node = GeometryTools::drawCollisionCircle(Vec2(360,760),96);
		addChild(node, BRICK_START_ZORDER);
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
	//auto prepos = touch->getPreviousLocation();
	int index = round((curpos.x - preTouchPosition.x) / win.width * BRICK_ANIM_NUM);
	for (auto var : brickVector) {
		int fin = var->getFrameIndex() - index;
		while (fin < 0)
		{
			fin += BRICK_ANIM_NUM;
		}
		var->setFrameIndex(fin % BRICK_ANIM_NUM);
	}
	preTouchPosition = touch->getLocation();
}


void GameLayer::onTouchEnded(Touch *touch, Event  *event) {

}




void GameLayer::update(float dt) {
	//Åö×²¼ì²â
	if (nullptr == hero) {
		return;
	}
	bool moveup = false;
	auto first_brick = brickVector.front();
	for (auto ang : first_brick->getOutAnglesByFrameIndex(first_brick->getFrameIndex())) {
			//log("brick frame = %d", brick->getFrameIndex());
		if (GeometryTools::angleCollision(first_brick->getOutAngle(), ang)) {
				//log("ang = (%d,%d)", ang.startAngle,ang.endAngle);
				//Öù×ÓÍøÉÏÉý¸ß
			if (hero->getPositionY() < 720) {
				moveup = true;
				std::vector<Brick*>::iterator it;
				it = brickVector.begin();
				(*it)->removeFromParent();
				brickVector.erase(it);
				hero->flipSpeedY();
			}
		}
		else {
			if (hero->getPositionY() < 720 && hero->getPositionY() > 700) {
					hero->flipSpeedY();
			}
		}
	}
	if (moveup) {
		for (auto brick : brickVector) {
			brick->setPositionY(brick->getPositionY()+ BRICK_HEIGHT);
		}
		moveup = false;
	}
}