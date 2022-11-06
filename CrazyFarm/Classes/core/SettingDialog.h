#pragma once
#include "cocos2d.h"
#include "widget/MyDialog.h"
#include "ui/UISlider.h"
#include "utill/Audio.h"
using namespace ui;
USING_NS_CC;
class SettingDialog : public MyDialog
{
public:
	CREATE_FUNC(SettingDialog);
	virtual bool init();
protected:
	void lingquCallback(Ref*psend);
	void sliderEvent(Ref *pSender, Slider::EventType type);
	void closeButtonCallBack(Ref*psend);
};

