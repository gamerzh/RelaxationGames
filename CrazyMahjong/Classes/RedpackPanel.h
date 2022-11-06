#pragma once
#include "cocos2d.h"
USING_NS_CC;

#include "ui/CocosGUI.h"
using namespace ui;

class RedpackPanel : public Node
{
public:
	static RedpackPanel*create(int index,int price);
private:
	bool init(int index,int price);
	void close(Ref*psend);
	void update(float delta);
	float totaltime = 0;
};
