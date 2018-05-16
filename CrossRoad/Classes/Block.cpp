#include "Block.h"
#include "MapNode.h"
#include "GeometryUtils.h"

Block * Block::create(int type,Point pos, Size size)
{
	Block* ret = new Block();
	if (ret && ret->init(type,pos,size)) {
		ret->autorelease();
		return ret;
	}
	else {
		CC_SAFE_DELETE(ret);
		return nullptr;
	}
}

bool Block::init(int type, Point pos, Size size)
{
	if (!Sprite::init()) {
		return false;
	}
	this->pos = pos;
	this->checkSize = size;
	initWithFile(getFileNameByType(type));
	setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	setContentSize(size);
	return true;
}


Rect Block::getBlockCheckRect() {
	auto position = GeometryUtils::transitionObjectVec2(pos, getMapIndex());
	auto size = GeometryUtils::transitionObjectSize(checkSize);
	//log("Tree Rect = %.1f,%.1f,%.1f,%.1f", position.x, position.y, size.width,size.height);
	return Rect(position.x, position.y, size.width, size.height);
}

void Block::setMapIndex(int index) {
	this->mapIndex = index;
}

int Block::getMapIndex() {
	return this->mapIndex;
}

std::string Block::getFileNameByType(int type) {
	switch (type)
	{
	case TreeType::tree_1:
		return "tree_1.png";
	case TreeType::tree_2:
		return "tree_2.png";
	case TreeType::tree_3:
		return "tree_3.png";
	case TreeType::tree_4:
		return "tree_4.png";
	case TreeType::house_1:
		return "house_1.png";
	case TreeType::house_2:
		return "house_2.png";
	case TreeType::stone:
		return "stone.png";
	default:
		return "tree_1.png";
	}
}