//
//  GameFeedDialog.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/7/6.
//
//

#ifndef GameFeedDialog_hpp
#define GameFeedDialog_hpp
#include "cocos2d.h"
USING_NS_CC;
#include "ui/CocosGUI.h"
using namespace ui;
class GameFeedDialog : public Layer , public ui::EditBoxDelegate{
public:
    virtual bool init();
    void onEnter() override;
    void onExit() override;
    CREATE_FUNC(GameFeedDialog);
private:
    EventListenerCustom* feedListener;
    void closeView();
    void clickComfirm();
	virtual void editBoxEditingDidBegin(ui::EditBox* editBox);
	virtual void editBoxEditingDidEnd(ui::EditBox* editBox);
	virtual void editBoxTextChanged(ui::EditBox* editBox, const std::string& text);
	virtual void editBoxReturn(ui::EditBox* editBox);

};

#endif /* GameFeedDialog_hpp */
