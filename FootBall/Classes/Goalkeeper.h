#pragma once
#include "cocos2d.h"
#include "Footballer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

class Goalkeeper : public Footballer {
public:
    static Goalkeeper* create(int teamId,cocos2d::Camera* camera = nullptr);
    virtual bool init(int teamId,cocos2d::Camera* camera);
    
    bool getSimpleAI();
    int getFootManTeamId();
    float getShootSpeed();

    cocos2d::Vec2 getManDefendVec2();//获取球员的防守位置
    cocos2d::Vec2 getFootballVec2();//获取足球的坐标
    cocos2d::Vec2 getOriginPosition();
    void doTumble();//摔倒
    void moveRight();
    void moveLeft();
    void replacement();
    void setOriginPosition(cocos2d::Vec2 vec);
    void playFootManShoot();//射门动画
    void playFootManSnap();//守门员扑救
    void moveDefendBall(cocos2d::Vec2 pos);//更具球的位置移动
private:
    int belongTeamId = 0;
    int foot_man_skill_type = 0;
    
    bool simpleRobotAI = true;//简单AI关闭
    bool canUpdateState = true;//想允许切换动画
    
    std::string fileName = "";
    std::string foot_man_img;
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Point targetPosition = cocos2d::Vec2(0,0);
    cocos2d::Node* playerCsb;
    cocos2d::Camera* ball_camera = nullptr;
    cocos2d::Vec2 originVec2;//球员的默认位置
    cocos2d::Sprite* shadow;
    std::string getFileNameByTeamId(int d);
    
    float getBallDistance();//获取和球的距离
    void playFootManRun();
    void playFootManStand();
    void playFootManTumble();
    void updateFootManZorder();
    void update(float dt);
};
