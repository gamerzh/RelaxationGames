//
//  GameRuleDialog.cpp
//  Mahjong
//
//  Created by qiuzhong on 16/7/6.
//
//

#include "GameRuleDialog.hpp"

bool GameRuleDialog::init(){
    if(!Layer::init()){
        return false;
    }
    
    MenuItem* item = MenuItem::create();
    item->setContentSize(Size(1280, 720));
    Menu* bg = Menu::create(item, NULL);
    this->addChild(bg,-1);
    
    auto  dialogBg = Sprite::create("common/dialog_bg_mid.png");
    dialogBg->setPosition(640, 360);
    this->addChild(dialogBg);
    
    auto closeImage = MenuItemImage::create("common/close_btn_1.png", "common/close_btn_1.png", CC_CALLBACK_0(GameRuleDialog::closeView, this));
    auto closeMenu = Menu::create(closeImage, NULL);
    closeMenu->setPosition(980, 650);
    addChild(closeMenu);
    
    auto paodai = Sprite::create("common/piaodai_zi.png");
    paodai->setPosition(640, 660);
    this->addChild(paodai);
    auto icon = Sprite::create("setting/rule_info.png");
    icon->setPosition(640, 680);
    addChild(icon);
    
    auto input_bg = ui::Scale9Sprite::create("common/input_box_bg.png");
    input_bg->setContentSize(Size(700,560));
    input_bg->setPosition(640, 340);
    addChild(input_bg);
    
    listView = ListView::create();
    listView->setDirection(ui::ScrollView::Direction::VERTICAL);//设置ListView布局方向
    listView->setTouchEnabled(true);//可触摸
    listView->setContentSize(Size(720,480));//设置ListView大小
    listView->ignoreContentAdaptWithSize(false);//开启锚点设置，false可更改锚点，true不可更改，Layer默认为point(0,0),其他Node为Point(0.5,0.5)
    listView->setAnchorPoint(Vec2(0.5, 0.5));//设置锚点，即锚点放在节点setPosition的位置，0，0：表示节点左下角；1，1：表示节点右上角；0.5，0.5表示节点中点
    listView->setPosition(Point(640,350));
    addChild(listView);
    
    for(auto var: getGameRules()){
        Layout *customItem = Layout::create();
        customItem->setLayoutType(Layout::Type::ABSOLUTE);
        customItem->setContentSize(Size(720,40));
        listView->pushBackCustomItem(customItem);
        
        auto text = Label::createWithSystemFont(var,"arial",26);
        text->setColor(Color3B(255,255,255));
        text->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        text->setPosition(40,30);
        customItem->addChild(text);
    }
    
    return true;
}


void GameRuleDialog::closeView(){
    removeFromParent();
}

std::vector<std::string> GameRuleDialog::getGameRules(){
	std::vector<std::string> rules;
	rules.push_back("游戏规则:");
	rules.push_back("玩法:上海麻将敲麻");
	rules.push_back("番数算法:");
	rules.push_back("底分:不同房间不同底分");
	/*rules.push_back("花分:不同房间不同花分");*/
	/*rules.push_back("勒子封顶值:按照1分底1分花算,勒子峰顶值20分");*/
	rules.push_back("底分+花分=输赢分数");
	rules.push_back("翻数算法:");
	rules.push_back("大吊车*2");
	rules.push_back("门清*2");
	rules.push_back("杠开*2");
	rules.push_back("碰碰胡*2");
	rules.push_back("混一色*2");
	rules.push_back("混碰勒子");
	rules.push_back("以上翻数最多翻到勒子,勒子是20,那最大值就是20");
	rules.push_back("清碰2个勒子，勒子20,最大值就是40");
	rules.push_back("开宝*2");
	return rules;
}