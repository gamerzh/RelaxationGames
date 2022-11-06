#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
USING_NS_CC;





class SetNameLayer : public cocos2d::Layer,public cocos2d::ui::EditBoxDelegate
{
public:

    virtual bool init();

	CREATE_FUNC(SetNameLayer);

private:
	void quedingcallback(Ref*);
	//edit box
	ui::EditBox *_editNickname;
	virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);
	virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);
	virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);
	virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);
	bool checkTheName(const char* name);

};
