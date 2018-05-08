#pragma once
#include "cocos2d.h"
USING_NS_CC;

class  Block : public Sprite
{
public:
	static Block* create(int type,Size size);
	virtual bool init(int type, Size size);
	Rect getBlockCheckRect();
private:
	Size checkSize;
	std::string getFileNameByType(int type);
};