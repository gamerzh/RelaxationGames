#ifndef __BASE_DIALOG_H__
#define __BASE_DIALOG_H__
#include "cocos2d.h"
USING_NS_CC;

class BaseDialog :public Layer{
public:
	virtual bool init();
	CREATE_FUNC(BaseDialog);
protected:
	virtual void drawDialog();
	void closeView();
private:
	bool onTouchBegan(Touch *touch, Event  *event);
};
#endif