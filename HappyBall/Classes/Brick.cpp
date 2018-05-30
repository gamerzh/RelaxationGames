#include "Brick.h"
USING_NS_CC;

bool Brick::init()
{
	if (!Sprite::init()) {
		return false;
	}
	loadBrickFile();
	scheduleUpdate();
	return true;
}

void Brick::loadBrickFile() {
	//auto myBrick = brick->getChildByName("kk_2")->getChildByName("llk_3_0");
	//auto brickCol = myBrick->getColor();
	//auto physicsBody = PhysicsBody::createBox(myBrick->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0));
	//physicsBody->setDynamic(false);
	//physicsBody->setGravityEnable(false);
	//myBrick->addComponent(physicsBody);
	auto brick = CSLoader::createNode("Node.csb");
	brick->setPosition(360, 300);
	this->addChild(brick);
	heroTimeLine = CSLoader::createTimeline("Node.csb");
	heroTimeLine->play("rotate", false);
	brick->runAction(heroTimeLine);
	setFrameIndex(0);
}


void Brick::update(float dt){
	//log("AAAAAAAAAAAAAAA %d", heroTimeLine->getCurrentFrame());
}


void Brick::setFrameIndex(int current) {
	heroTimeLine->gotoFrameAndPause(current);
}

int Brick::getFrameIndex() {
	return heroTimeLine->getCurrentFrame();
}
