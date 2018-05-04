#include "Block.h"

Block * Block::create(int type, Size size)
{
	Block* ret = new Block();
	if (ret && ret->init(type,size)) {
		ret->autorelease();
		return ret;
	}
	else {
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

bool Block::init(int type, Size size)
{
	if (!Sprite::init()) {
		return false;
	}
	this->checkSize = size;
	initWithFile("tree_1.png");
	setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
	return true;
}


Rect Block::getBlockCheckRect() {
	float x = this->getPositionX();
	float y = this->getPositionY();
	return Rect(x,y,checkSize.width,checkSize.height);
}