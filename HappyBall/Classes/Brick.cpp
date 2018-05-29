#include "Brick.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

bool Brick::init()
{
	if (!Node::init()) {
		return false;
	}
	loadBrickFile();
	return true;
}

void Brick::loadBrickFile() {
	auto brick = CSLoader::createNode("brick.csb");
	brick->setPosition(360, 300);
	addChild(brick);
	//auto myBrick = brick->getChildByName("kk_2")->getChildByName("llk_3_0");
	//auto brickCol = myBrick->getColor();
	//auto physicsBody = PhysicsBody::createBox(myBrick->getContentSize(), PhysicsMaterial(1.0f, 1.0f, 0));
	//physicsBody->setDynamic(false);
	//physicsBody->setGravityEnable(false);
	//myBrick->addComponent(physicsBody);
}
