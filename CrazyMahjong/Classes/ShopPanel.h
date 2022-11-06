#pragma once
#include "cocos2d.h"
#include "ShopCell.h"
USING_NS_CC;



class ShopPanel : public Node
{
public:
	CREATE_FUNC(ShopPanel);

	void showPanel();
	void hidePanel();

private:
	bool init();
	std::vector<PropItem> getPropItems();
	EventListenerTouchOneByOne* listenr1;
	float time = 0.2f;
	bool onTouchBegin(Touch*touch, Event*event);
	std::vector<ShopCell*> cells;
};
