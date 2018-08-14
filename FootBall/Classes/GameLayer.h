#pragma once
#include "cocos2d.h"
#include "Ball.h"
#include "Rocker.h"
#include "FieldMan.h"
#include "FootballTeam.h"
#include "GlobalProperty.h"
#include "TeamInfoFactory.h"

#define FOOTBALL_LOCAL_ZORDER 10

class GameLayer : public cocos2d::Layer {
public:
    virtual bool init();
    void onEnter();
    void onExit();
    CREATE_FUNC(GameLayer);
private:
    bool canChangeControlMan = true;
    float changeControlManInterval = CAN_CHANGE_FOOTMAN_TIME;
    float special_time = 0;
    float track_time = 1.5;//铲球冷却
    bool can_track = true;
    
    cocos2d::Camera* playerCamera;
    cocos2d::MenuItemImage* trackOrPassBtn;
    Ball* footBall = nullptr;
    Rocker* heroRocker = nullptr;
    FootballTeam* playerTeam;
    FootballTeam* computerTeam;
    FieldMan* controlingFootman;//当前被控制的球员
    
    void updateButtonTexture();
    void passAndTackle();//传球铲球
    void shoot();//射门
    void speedMan();//加速
    void manLootBall();//球员获得球权
    bool checkFootManInShootArea(FieldMan* man);//检查球员是否进入射门区域
    void replacementAll();//重置游戏场景
    void loadGameLayerUI();
    void createFootballFild();
    void createFootBallTeam();
    void addCustomEvent();
    void removeCustomEvent();
    void update(float dt);
};
