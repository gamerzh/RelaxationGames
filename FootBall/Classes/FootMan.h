#pragma once
#include "cocos2d.h"
#include "TeamInfoFactory.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"


#define FOOTBALL_MAN_ZORDER 5000
//简单AI的逻辑,进入距离500内开始靠近对方,距离小于100发动铲球，最多只有2名球员去防守
#define DEFEND_RADIUS  200 //球员的防守半径
#define TACKLE_DISTANCE 40//发动铲球的距离
#define SUPPORT_DISTANCE 600//友方支援队员的距离

//foot man state
enum FootManState{
    waiting,
    running,
    shoot,
    tackle
};

class FootMan : public cocos2d::Node {
public:
    bool isGoalkeeper = false;
    std::string footManId = "";
    static FootMan* create(int teamId,FootManProperty property,bool goalkeeper = false,cocos2d::Camera* camera = nullptr);
    virtual bool init(int teamId,FootManProperty property, bool goalkeeper,cocos2d::Camera* camera);
    int getFootManTeamId();
    float getShootSpeed();
    std::string getFileNameByTeamId(int d,bool goalkeeper);
    void setFootManAngle(float angle);
    void doSlideTackle();//滑铲
    void doShoot();//射门
    void moveRight();
    void moveLeft();
    void replacement();
    void setOriginPosition(cocos2d::Vec2 vec);
    void changeFootManState(FootManState state);
    void runToPositon(cocos2d::Vec2 pos);//跑向目标
    void controlSimpleAI(bool p);
    FootManState getFootManState();
private:
    int belongTeamId = 0;
    int foot_man_skill_type = 0;
    float runSpeed = 5;
    bool simpleRobotAI = false;//简单AI关闭
    bool canUpdateStae = true;//想允许切换动画
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
    void supportPosition(cocos2d::Vec2 pos);//向目标提供支援,单纯移动X轴方向
    void showDebugInfo();
    void update(float dt);
    void playFootManRun();
    void playFootManTackle();
    void playFootManShoot();
    void playFootManStand();
};
