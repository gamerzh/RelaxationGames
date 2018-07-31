#include "Ball.h"
#include "GlobalProperty.h"
#include "GeometryTools.h"
USING_NS_CC;


Ball* Ball::create(Camera* camera)
{
    Ball *ret = new Ball();
    if (ret && ret->init(camera))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool Ball::init(Camera* camera) {
    if (!Sprite::init()) {
        return false;
    }
    this->myCamera = camera;
    initWithFile("ball.png");
    setScale(ANIMATION_SCALE_RATE);
    scheduleUpdate();
    return true;
}

int Ball::getBallState() {
    return this->ballState;
}

void Ball::setBallState(int state) {
    this->ballState = state;
}


void Ball::setBallShoot(cocos2d::Vec2 vec) {
    setBallState(ball_is_pass);
    this->ballOwner = NULL;
    this->targetPosition = vec;
}

void Ball::setBallPass(cocos2d::Vec2 vec){
    setBallState(ball_is_pass);
    this->ballOwner = NULL;
    if(vec != Vec2(0,0)){
        this->targetPosition = vec;
    }
}

void Ball::setBallFree(){
    this->ballOwner = NULL;
     setBallState(ball_is_free);
}

FootMan* Ball::getOwerMan() {
    return this->ballOwner;
}

void Ball::setOwnerMan(FootMan* owern) {
    setBallState(ball_is_ower);
    this->ballOwner = owern;
}

Point Ball::cameraMoveInRect(Point pos) {
//    log("Ball Ball Ball (%f,%f)",pos.x,pos.y);
    auto size = Director::getInstance()->getVisibleSize();
    pos = Vec2(pos.x - size.width / 2, pos.y - size.height / 2);
    
    if (pos.x < 0) {
        pos.x = 0;
    }
    else if (pos.x > football_field_width - size.width) {
        pos.x = football_field_width - size.width;
    }
    if (pos.y < 0) {
        pos.y = 0;
    }
    else if (pos.y > football_field_height - size.height) {
        pos.y = football_field_height - size.height;
    }
//    log("Camera Camera Camera (%f,%f)",pos.x,pos.y);
    return pos;
}

bool Ball::checkBallInGoal() {
    if (goalLeft.containsPoint(this->getPosition()) ) {
        if(!sendGoalMsg){
            sendGoalMsg = true;
            char* buf = const_cast<char*>("left");
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(foot_ball_in_goal, buf);
        }
        return true;
    }
    else if (goalRight.containsPoint(this->getPosition())) {
        if(!sendGoalMsg){
            sendGoalMsg = true;
            char* buf = const_cast<char*>("right");
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(foot_ball_in_goal, buf);
        }
        return true;
    }
    else {
        return false;
    }
}

BallSpeed Ball::getBallSpeedToTarget(){
    //获得球的运动速度
    Vec2 curPos = this->getPosition();
    BallSpeed speed;
    float fenmu = GeometryTools::calculateDistance(targetPosition, curPos);
    if(fenmu>=1){
        speed.speedx = (targetPosition.x-curPos.x)/fenmu* speed_fly;
        speed.speedy = (targetPosition.y-curPos.y)/fenmu* speed_fly;
    }else{
        speed.speedx = 0;
        speed.speedy = 0;
    }
//    log("curPos=(%f,%f)",curPos.x,curPos.y);
//    log("targetPosition=(%f,%f)",targetPosition.x,targetPosition.y);
//    log("Speed=(%f,%f)",speed.speedx,speed.speedy);
    return speed;
}

bool Ball::droppointInCorrect(cocos2d::Vec2 tar,cocos2d::Vec2 cor){
    //直径50的落点圈
    if(GeometryTools::calculateDistance(tar, cor)<50){
        return  true;
    }else{
        return false;
    }
}

void Ball::replacement(){
    sendGoalMsg = false;
    this->setPosition(1080, 680);
}

void Ball::update(float dt) {
    if (NULL != this->ballOwner && this->ballState == ball_is_ower) {
        this->setPosition(this->ballOwner->getPosition());
    }else if(this->ballState == ball_is_pass){
        if(droppointInCorrect(this->targetPosition,this->getPosition())){
            this->ballState = ball_is_free;
        }
        this->setPosition(this->getPositionX()+getBallSpeedToTarget().speedx,this->getPositionY()+getBallSpeedToTarget().speedy);
    }
   
    this->myCamera->setPosition(cameraMoveInRect(this->getPosition()));
    checkBallInGoal();
}
