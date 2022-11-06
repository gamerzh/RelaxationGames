#pragma once
#include "cocos2d.h"
USING_NS_CC;

#include "ui/CocosGUI.h"
using namespace ui;

class RanklistPanel : public Sprite
{
public:
	CREATE_FUNC(RanklistPanel);
private:
	bool init();
	void selectedItemEvent(Ref *pSender, ListView::EventType type);

};
