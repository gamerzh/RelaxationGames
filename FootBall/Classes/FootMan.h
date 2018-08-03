#pragma once
#include "cocos2d.h"
#include "TeamInfoFactory.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

class FootMan : public cocos2d::Node {
public:
    //foot man state
    enum FootManState{
        waiting,
        running,
        shoot,
        tackle,
        tumble
    };
    bool isGoalkeeper = false;
    std::string footManId = "";
    static FootMan* create(int teamId,FootManProperty property,bool goalkeeper = false,cocos2d::Camera* camera = nullptr);
    virtual bool init(int teamId,FootManProperty property, bool goalkeeper,cocos2d::Camera* camera);
    bool getCanObtainBall();
    bool getSimpleAI();
    int getFootManTeamId();
    float getShootSpeed();
    std::string getFileNameByTeamId(int d,bool goalkeeper);
    cocos2d::Vec2 getManDefendVec2();//获取球员的防守位置
    cocos2d::Vec2 getFootballVec2();//获取足球的坐标
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
    void manRunToTargetX(cocos2d::Vec2 pos);//向目标提供支援,单纯移动X轴方向
    void manRunToTargetY(cocos2d::Vec2 pos);//向目标提供支援,单纯移动Y轴方向
    void playFootManShoot();//射门动画
    void playFootManSnap();//守门员扑救
    void showControlCircle(bool show);
private:
    int belongTeamId = 0;
    int foot_man_skill_type = 0;
    float runSpeed = 3.5f;
    
    bool simpleRobotAI = true;//简单AI关闭
    bool canUpdateState = true;//想允许切换动画
    
    bool canFootmanTackle = true;//是否允许铲球
    float tackleInterval = 3;//球员铲球间隔
    float tacklePercentage = 0.3;//球员的铲球成功率
    
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
    
    float getPositionXByYLeft(float y);
    float getPositionXByYRight(float y);
    float getBallDistance();//获取和球的距离
    void updateFootManZorder();
    void showDebugInfo();
    void update(float dt);
    void playFootManRun();
    void playFootManTackle();
    void playFootManStand();
    void playFootManTumble();
};
