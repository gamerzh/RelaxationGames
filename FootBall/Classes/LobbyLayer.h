#pragma once
#include "cocos2d.h"
#include "StartLayer.h"

class LobbyLayer :public cocos2d::Layer {
public:
	virtual bool init();
	CREATE_FUNC(LobbyLayer);
private:
    StartLayer* startLayer;
    int selectLayerIndex = 0;//选择的页面编号
	cocos2d::Layer * worldLayer;
	cocos2d::Layer * masterLayer;
	cocos2d::Layer * teamLayer;
	cocos2d::MenuItemToggle* worldItemToggle;
	cocos2d::MenuItemToggle* masterItemToggle;
	cocos2d::MenuItemToggle* teamItemToggle;
	void loadButtonView();
	void loadWorldCupView();
	void loadMasterVupView();
	void loadTeamView();
    void loadWorldPipeView(cocos2d::Node* node,int index);
	void loadMasterPipeView(cocos2d::Node* node,int index);
	void worldMenuCallBack(cocos2d::Ref* ref);
	void masterMenuCallBack(cocos2d::Ref* ref);
	void teamMenuCallBack(cocos2d::Ref* ref);
	void selectCupLevel(cocos2d::Ref* ref);
	void controlSound(cocos2d::Ref* ref);
	void startGame(cocos2d::Ref* ref);
};
