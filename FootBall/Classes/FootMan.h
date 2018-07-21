#pragma once
#include "cocos2d.h"
#include "TeamInfoFactory.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#define ANIMATION_SCALE_RATE 0.4
#define FOOTBALL_MAN_ZORDER 5000
//简单AI的逻辑,进入距离500内开始靠近对方,距离小于100发动铲球，最多只有2名球员去防守
#define DEFEND_RADIUS  500 //球员的防守半径
#define TACKLE_DISTANCE 100//发动铲球的距离

//foot man state
enum FootManState{
    waiting,
    running,
    shoot,
    tackle
};

class FootMan : public cocos2d::Node {
public:
    static FootMan* create(FootManProperty property,cocos2d::Camera* camera = nullptr);
    virtual bool init(FootManProperty property, cocos2d::Camera* camera);
    int getFootManTeamId();
    void setFootManTeamId(int id);
    void setFootManAngle(float angle);
    void doSlideTackle();//滑铲
    void doShoot();//射门
    //    bool isGoalkeeper();
    float getShootSpeed();
    void moveRight();
    void moveLeft();
    void runToTargetPosition(cocos2d::Vec2 vec);
    FootManState getFootManState();
    void changeFootManState(FootManState state);
    void setRobotAI(bool f);
private:
    int belongTeamId = 0;
    int foot_man_skill_type = 0;
    float runSpeed = 0;
    bool robotAI;
    std::string foot_man_img;
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Point targetPosition;
    cocos2d::Node* playerCsb;
    cocos2d::Camera* ball_camera = nullptr;
    cocos2d::Vec2 runTargetPos;
    FootManState manState;
    cocos2d::Point moveInSafeRect(cocos2d::Point pos);
    float getPositionXByYLeft(float y);
    float getPositionXByYRight(float y);
    void updateFootManZorder();
    void showDebugInfo();
    void update(float dt);
    void playFootManRun();
    void playFootManTackle();
    void playFootManShoot();
    void playFootManStand();
};
