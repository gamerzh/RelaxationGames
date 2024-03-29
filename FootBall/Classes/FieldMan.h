#pragma once
#include "cocos2d.h"
#include "Footballer.h"


class FieldMan : public Footballer {
public:
    //foot man state
    enum FootManState{
        space,
        waiting,
        running,
        shoot,
        tackle,
        tumble
    };
    static FieldMan* create(int teamId,FootManProperty property,cocos2d::Camera* camera = nullptr);
    virtual bool init(int teamId,FootManProperty property,cocos2d::Camera* camera);
    bool getCanObtainBall();
    bool getSimpleAI();
    int getFootManTeamId();
    float getShootSpeed();
    std::string getFileNameByTeamId(int d);
    cocos2d::Vec2 getManDefendVec2();//获取球员的防守位置
    cocos2d::Vec2 getFootballVec2();//获取足球的坐标
    cocos2d::Vec2 getOriginPosition();
    FootManState getFootManState();
    void setFootManAngle(float angle);
    void doSlideTackle();//滑铲
    void doTumble();//摔倒
    void doDefend(cocos2d::Vec2 vec);//防守
    void moveRight();
    void moveLeft();
    void replacement();
    void speedUp();//加速
    void setOriginPosition(cocos2d::Vec2 vec);
    void changeFootManState(FootManState state);
    void manRunToTarget(cocos2d::Vec2 pos,float rad,cocos2d::CallFunc* callback = NULL);//跑向目标
    void manRunToTargetX(cocos2d::Vec2 pos,cocos2d::CallFunc* callback = NULL);//向目标提供支援,单纯移动X轴方向

    void showControlCircle(bool show);
private:
    int belongTeamId = 0;
    int foot_man_skill_type = 0;
    float runSpeed = 3.5f;
    
    float animUpdateInterval =0;
    
    bool simpleRobotAI = true;//简单AI关闭
    
    bool canFootmanTackle = true;//是否允许铲球
    float tackleInterval = 3;//球员铲球间隔
    float tacklePercentage = 0.25;//球员的铲球成功率
    
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
    FootManState manState;
    cocos2d::Point moveInSafeRect(cocos2d::Point pos);

    float getBallDistance();//获取和球的距离
    void updateFootManZorder();
    void showDebugInfo();
    void update(float dt);
    void playFootManRun();
    void playFootManTackle();
    void playFootManTumble();
    void playFootManShoot();//射门动画
    void playFootManStand();
};
