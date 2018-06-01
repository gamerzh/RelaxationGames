#include "Brick.h"
#include "GameLayer.h"
#include "GeometryTools.h"
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




void Brick::setFrameIndex(int current) {
	heroTimeLine->gotoFrameAndPause(current);
}

int Brick::getFrameIndex() {
	return heroTimeLine->getCurrentFrame();
}

Rect Brick::getCollisionRect() {
	if (NULL != getChildByTag(15)) {
		auto node = (Sprite*)(getChildByTag(15)->getChildByName("kk_2")->getChildByName("llk_3_0"));
		return node->getBoundingBox();
	}
	return Rect();
}


std::vector<AngeleRange> Brick::getOutAnglesByFrameIndex(int dex) {
	std::vector<AngeleRange> outList;
	int offset = dex * (360 / BRICK_ANIM_NUM);
	AngeleRange angle;
	angle.startAngle = (270 + offset) % 360;
	angle.endAngle = (270 + 360 / CIRCLE_DIVISION_NUMBER + offset)%360;
	outList.push_back(angle);
	return outList;
}

std::vector<AngeleRange> getDangousAnglesByFrameIndex(int index) {
	std::vector<AngeleRange> outList;
	return outList;
}


AngeleRange Brick::getOutAngle() {
	AngeleRange angle;
	angle.startAngle =  180 - 180 / CIRCLE_DIVISION_NUMBER;
	angle.endAngle = 180 + 180 / CIRCLE_DIVISION_NUMBER;
	return angle;
}

void Brick::update(float dt) {
	//GeometryTools::drawCollisionBox(this, getCollisionRect());
}


