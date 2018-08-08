#pragma once
#include "cocos2d.h"
#include "Footballer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

class Goalkeeper : public Footballer {
public:
    static Goalkeeper* create(int teamId,cocos2d::Camera* camera = nullptr);
    virtual bool init(int teamId,cocos2d::Camera* camera);
    bool getCanObtainBall();
    bool getSimpleAI();
    int getFootManTeamId();
    float getShootSpeed();

    cocos2d::Vec2 getManDefendVec2();//获取球员的防守位置
    cocos2d::Vec2 getFootballVec2();//获取足球的坐标
    void doTumble();//摔倒
    void doDefend(cocos2d::Vec2 vec);//防守
    void moveRight();
    void moveLeft();
    void replacement();
    void setOriginPosition(cocos2d::Vec2 vec);
    void playFootManShoot();//射门动画
    void playFootManSnap();//守门员扑救
    void showControlCircle(bool show);
private:
    int belongTeamId = 0;
    int foot_man_skill_type = 0;
    
    bool simpleRobotAI = true;//简单AI关闭
    bool canUpdateState = true;//想允许切换动画
    
    bool canObtainBall = true;//是否可以获取球
    float obtainInterval = 1.4f;//获取球权间隔
    
    std::string fileName = "";
    std::string foot_man_img;
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Point targetPosition;
    cocos2d::Node* playerCsb;
    cocos2d::Camera* ball_camera = nullptr;
    cocos2d::Vec2 runTargetPos;
    cocos2d::Vec2 originVec2;//球员的默认位置    
    std::string getFileNameByTeamId(int d);
    cocos2d::Point moveInSafeRect(cocos2d::Point pos);
    
    float getBallDistance();//获取和球的距离
    void playFootManRun();
    void playFootManStand();
    void playFootManTumble();
    void updateFootManZorder();
    void showDebugInfo();
    void update(float dt);
};
