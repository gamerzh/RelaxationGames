#include "Brick.h"
USING_NS_CC;


Brick* Brick::create(int frame) {
	auto brick = new Brick();
	if (brick && brick->init(frame)) {
		brick->autorelease();
		return brick;
	}
	else {
		CC_SAFE_DELETE(brick);
		return nullptr;
	}
}

bool Brick::init(int frame)
{
	if (!Sprite::init()) {
		return false;
	}
	loadBrickFile();
	setFrameIndex(frame);
	scheduleUpdate();
	return true;
}

void Brick::loadBrickFile() {
	auto brick = CSLoader::createNode("Node.csb");
	brick->setPosition(0, 0);
	brick->setTag(15);
	this->addChild(brick);
	heroTimeLine = CSLoader::createTimeline("Node.csb");
	heroTimeLine->play("rotate", false);
	brick->runAction(heroTimeLine);
}


void Brick::update(float dt){
	
}


void Brick::setFrameIndex(int current) {
	heroTimeLine->gotoFrameAndPause(current);
}

int Brick::getFrameIndex() {
	return heroTimeLine->getCurrentFrame();
}

Rect Brick::getCollisionRect() {
	if (NULL != getChildByTag(15)) {
		auto node = getChildByTag(15)->getChildByName("kk_2")->getChildByName("llk_3_0");
		return node->getBoundingBox();
	}
	return Rect();
}
