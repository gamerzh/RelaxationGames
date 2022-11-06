#ifndef __USER_SETTING_H__
#define __USER_SETTING_H__
#include "cocos2d.h"
#include "ui/base/BaseDialog.h"
USING_NS_CC;
#include "ui/CocosGUI.h"
using namespace ui;


class UserSetting :public BaseDialog{
public:
	virtual bool init();
	CREATE_FUNC(UserSetting);
private:
	void slderEvent(Ref* pSender, SliderEventType type);
    void showGameHelp();
    void feedBack();
	void drawDialog() override;

};
#endif
