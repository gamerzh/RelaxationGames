//
//  Goal.cpp
//  FootBall
//
//
#include "Goal.h"
#include "Ball.h"
USING_NS_CC;

bool Goal::init(){
    if(!Node::init()){
        return false;
    }
    return true;
}

cocos2d::Rect getGoalRect(cocos2d::Vec2 dir){
    return Rect(0,0,0,0);
}
