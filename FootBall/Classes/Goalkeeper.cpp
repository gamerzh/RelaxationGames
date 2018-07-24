//
//  Goalkeeper.cpp
//  FootBall
//

#include "Goalkeeper.h"
USING_NS_CC;


Goalkeeper* Goalkeeper::create(int teamId,cocos2d::Camera* camera){
    Goalkeeper *ret = new Goalkeeper();
    if (ret && ret->init(teamId,camera))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool Goalkeeper::init(int teamId, cocos2d::Camera* camera){
    if(!Node::init()){
        return false;
    }
    return true;
}
