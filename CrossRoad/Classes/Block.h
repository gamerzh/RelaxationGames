#pragma once
#include "cocos2d.h"
USING_NS_CC;

class  Block : public Sprite
{
public:
	static Block* create(int type ,Point pos, Size size);
	virtual bool init(int type,Point pos,Size size);
	Rect getBlockCheckRect();
	void setMapIndex(int index);
	int getMapIndex();
private:
	Point pos;
	Size checkSize;
	int mapIndex = 0;
	std::string getFileNameByType(int type);
};