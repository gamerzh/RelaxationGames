#pragma once
#include "cocos2d.h"
#include "FootMan.h"
#include "GlobalProperty.h"

struct BallSpeed{
    float speedx;
    float speedy;
};

class Ball : public cocos2d::Sprite
{
public:
    static Ball* create(cocos2d::Camera* camera);
    virtual bool init(cocos2d::Camera* camera);
    int getBallState();
    void setBallShoot(cocos2d::Vec2 vec);
    void setBallPass(cocos2d::Vec2 vec);
    void setBallFree();
    void setOwnerMan(FootMan* owern);
    void replacement();//重置足球的位置
    void setFootballRotate(bool ro);
    BallSpeed getBallSpeedToTarget();
    FootMan* getOwerMan();
    bool droppointInCorrect(cocos2d::Vec2 tar,cocos2d::Vec2 cor);
private:
    const  cocos2d::Rect goalLeft = cocos2d::Rect(115, 520, 100, 330);
    const  cocos2d::Rect goalRight = cocos2d::Rect(1920, 520, 100, 330);
    bool ballRotate = false;
    bool sendGoalMsg = false;//是否发送过进球信息
    cocos2d::Vec2 targetPosition;
    cocos2d::Node* footballCsb;
    cocos2d::Camera* myCamera = nullptr;
    FootMan* ballOwner = nullptr;
    float speed_fly;
    float speed_calm = 3;
    void ballMoveDirect();
    void setBallState(int state);
    int ballState = ball_is_free;
    bool checkBallInGoal();
    cocos2d::Point cameraMoveInRect(cocos2d::Point pos);
    void update(float dt);
};
