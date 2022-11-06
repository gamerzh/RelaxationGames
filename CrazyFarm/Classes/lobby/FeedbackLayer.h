#pragma once
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "utill/Chinese.h"
USING_NS_CC_EXT;
USING_NS_CC;





class FeedbackLayer : public cocos2d::Layer, public cocos2d::ui::EditBoxDelegate
{
public:

    virtual bool init();

	CREATE_FUNC(FeedbackLayer);

private:
	bool onTouchBegan(Touch *touch, Event *unused_event);
	void quedingcallback(Ref*);
	int sex;
	ui::EditBox *_editName;
	void closeButtonCallBack(Ref*psend);
	virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);
	virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);
	bool checkTheName(const char* name);
};
