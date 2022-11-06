//
//  GameRuleDialog.hpp
//  Mahjong
//
//  Created by qiuzhong on 16/7/6.
//
//

#ifndef GameRuleDialog_hpp
#define GameRuleDialog_hpp
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/UIListView.h"
#include "ui/UIImageView.h"
#include "ui/UIRichText.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;

class GameRuleDialog : public Layer{
public:
    virtual bool init();
    CREATE_FUNC(GameRuleDialog);
private:
    ListView* listView;
    void closeView();
    std::vector<std::string> getGameRules();
};
#endif /* GameRuleDialog_hpp */
