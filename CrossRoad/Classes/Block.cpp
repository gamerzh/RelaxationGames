#include "Block.h"
#include "GeometryUtils.h"

Block * Block::create(Point pos, Size size)
{
	Block* ret = new Block();
	if (ret && ret->init(pos,size)) {
		ret->autorelease();
		return ret;
	}
	else {
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

bool Block::init(Point pos, Size size)
{
	if (!Sprite::init()) {
		return false;
	}
	this->pos = pos;
	this->checkSize = size;
	setContentSize(size);
	return true;
}


Rect Block::getBlockCheckRect() {
	auto position = GeometryUtils::transitionObjectVec2(pos);
	auto size = GeometryUtils::transitionObjectSize(checkSize);
	//log("Tree Rect = %.1f,%.1f,%.1f,%.1f", position.x, position.y, size.width,size.height);
	return Rect(position.x, position.y, size.width, size.height);
}