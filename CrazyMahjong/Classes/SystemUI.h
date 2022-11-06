#ifndef __SYSTEM_UI_H__
#define __SYSTEM_UI_H__

#include "cocos2d.h"
USING_NS_CC;

#include "SetPanel.h"
#include "ui/setting/UserSetting.h"
class SystemUI : public Node
{
public:
	CREATE_FUNC(SystemUI);

	void hideAddCoin();
	//TIP
	void showFirstPlayTip();
private:
	MenuItem* backBtn;
	MenuItem* inforBtn;
	MenuItem* gameBtn;
	MenuItem* setBtn;
	MenuItem*addCoinBtn;
	bool init();
	void onBackBtnCallBack(Ref* pSender);

	void onInforBtnCallBack(Ref* pSender);
	void onGameBtnCallBack(Ref* pSender);
	void onSetBtnCallBack(Ref* pSender);
	void onAddCoinBtnCallBack(Ref* pSender);



	//TASK
	bool IsEnableToTask();
	void ResetTask();
	int XygGetToday();
	void OnActive();
	void showdiog(float dt);

	UserSetting* setPanel = nullptr;
};
#endif