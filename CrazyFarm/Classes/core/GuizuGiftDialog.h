#pragma once
#include "cocos2d.h"
#include "widget/MyDialog.h"
USING_NS_CC;
class GuizuGiftDialog : public MyDialog
{
public:
	CREATE_FUNC(GuizuGiftDialog);
	virtual bool init();
protected:
	void lingquCallback(Ref*psend);
};

