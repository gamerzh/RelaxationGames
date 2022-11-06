#pragma once
#include "cocos2d.h"
#include "RoleShow.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocos2d::ui;

class ReadpackNode :
	public Button
{
public:
	CREATE_FUNC(ReadpackNode);
private:
	virtual bool init();
	void updateBySecond(float delta);
	void showResult(int index);
};

