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
	initWithFile(getFileNameByType(type));
	return true;
}


Rect Block::getBlockCheckRect() {
	float x = this->getPositionX();
	float y = this->getPositionY();
	return Rect(x,y,checkSize.width,checkSize.height);
}


std::string Block::getFileNameByType(int type) {
	switch (type)
	{
	case 1:
		return "tree_1.png";
	case 2:
		return "tree_2.png";
	case 3:
		return "tree_2.png";
	case 4:
		return "tree_2.png";
	case 5:
		return "house_1.png";
	case 6:
		return "house_2.png";
	default:
		return "tree_1.png";
	}

}