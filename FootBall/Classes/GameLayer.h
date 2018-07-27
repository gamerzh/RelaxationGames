#pragma once
#include "cocos2d.h"
#include "Ball.h"
#include "Rocker.h"
#include "FootMan.h"
#include "TeamInfoFactory.h"
#include "FootballTeam.h"

#define FOOTBALL_LOCAL_ZORDER 10

class GameLayer : public cocos2d::Layer {
public:
    virtual bool init();
    CREATE_FUNC(GameLayer);
private:
    bool canChangeControlMan = true;
    float changeControlManInterval = 1.5f;
    Ball* footBall = nullptr;
    Rocker* heroRocker = nullptr;
    cocos2d::Camera* playerCamera;
    FootballTeam* playerTeam;
    FootballTeam* computerTeam;
    FootMan* controlingFootman;//当前被控制的球员
    void onEnter();
    void onExit();
    void passAndTackle();
    void shoot();
    void manLootBall();
    void speedMan();
    void loadGameLayerUI();
    void addCustomEvent();
    void removeCustomEvent();
    bool checkFootManInShootArea(FootMan* man);//检查球员是否进入射门区域
    void createFootballFild();
    void createFootBallTeam();
    void replacementAll();
    void update(float dt);
};
