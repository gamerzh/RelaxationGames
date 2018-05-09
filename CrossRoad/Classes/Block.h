#pragma once
#include "cocos2d.h"
USING_NS_CC;

class  Block : public Sprite
{
public:
	static Block* create(int type ,Point pos, Size size);
	virtual bool init(int type,Point pos,Size size);
	Rect getBlockCheckRect();
private:
	Point pos;
	Size checkSize;
	std::string getFileNameByType(int type);
};