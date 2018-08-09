#include "Ball.h"
#include "GeometryTools.h"
#include "Audio.h"
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
    footballCsb = CSLoader::createNode("football.csb");
    footballCsb->setScale(ANIMATION_SCALE_RATE);
    footballCsb->setPosition(0, 0);
    addChild(footballCsb);
    ballEffect = Sprite::create("effects/team_1_1.png");
    ballEffect->setCameraMask((int)CameraFlag::USER1);
    addChild(ballEffect);
    ballEffect->setVisible(false);
    scheduleUpdate();
    return true;
}

void Ball::setFootballRotate(bool ro){
    if(ro){
        ballRotate = true;
        footballCsb->stopAllActions();
        auto timeLine = CSLoader::createTimeline("football.csb");
        timeLine->play("animation0", true);
        footballCsb->runAction(timeLine);
    }else{
        ballRotate = false;
        footballCsb->stopAllActions();
    }
}

int Ball::getBallState() {
    return this->ballState;
}


void Ball::setBallShoot(cocos2d::Vec2 vec) {
    this->speed_fly = FOOT_BALL_START_SPEED;
    this->ballState = ball_is_fly;
    this->ballOwner = NULL;
    this->targetPosition = vec;
}

void Ball::setBallPass(cocos2d::Vec2 vec){
    this->speed_fly = FOOT_BALL_START_SPEED;
    this->ballState = ball_is_fly;
    this->ballOwner = NULL;
    if(vec != Vec2(0,0)){
        this->targetPosition = vec;
    }
}

void Ball::setBallFree(){
    this->ballOwner = NULL;
    this->ballState = ball_is_free;
}

int Ball::getKeeperId(){
    return this->keeperId;
}

void Ball::setBallKeep(int teamid){
    //球被守门员持有
    this->keeperId = teamid;
    this->ballOwner = nullptr;
    this->ballState = ball_is_snap;
}

FieldMan* Ball::getOwerMan() {
    return this->ballOwner;
}

void Ball::setOwnerMan(FieldMan* owern) {
    this->ballState = ball_is_ower;
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
        Audio::getInstance()->playEffect(GOAL_BALL);
        return true;
    }
    else if (goalRight.containsPoint(this->getPosition())) {
        if(!sendGoalMsg){
            sendGoalMsg = true;
            char* buf = const_cast<char*>("right");
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(foot_ball_in_goal, buf);
        }
        Audio::getInstance()->playEffect(GOAL_BALL);
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

void Ball::showBallEffect(int id,bool left){
    ballEffect->setVisible(true);
    if(left){
        ballEffect->setPosition(100,10);
        ballEffect->setFlippedX(false);
    }else{
        ballEffect->setPosition(-50,10);
        ballEffect->setFlippedX(true);
    }
}

void Ball::hideBallEffect(){
    ballEffect->setVisible(false);
}

bool Ball::ballInSafeRect(Point pos) {
    if (pos.y < football_field_offset_bottom) {
        return false;
    }
    else if (pos.y > football_field_height- football_field_offset_top) {
        return false;
    }
    
    if (pos.x < GeometryTools::getPositionXByYLeft(pos.y)) {
        return false;
    }
    else if (pos.x > GeometryTools::getPositionXByYRight(pos.y)) {
        return false;
    }
    return true;
}

void Ball::update(float dt) {
    auto speedCamera =0;
    auto preLocation = this->getPosition();
    auto curLocation = preLocation;
    if (NULL != this->ballOwner && this->ballState == ball_is_ower) {
        curLocation = this->ballOwner->getFootballVec2();
        this->setPosition(curLocation);
        speedCamera = 2;
    }else if(this->ballState == ball_is_fly){
        if(droppointInCorrect(this->targetPosition,this->getPosition())){
            this->ballState = ball_is_free;
            this->hideBallEffect();
        }
        curLocation =Vec2(this->getPositionX()+getBallSpeedToTarget().speedx,this->getPositionY()+getBallSpeedToTarget().speedy);
        this->setPosition(curLocation);
        speedCamera = 7;
    }else if(this->ballState == ball_is_free){
        preLocation = curLocation;
    }
    if(preLocation != curLocation){
        if(!ballRotate){
            setFootballRotate(true);
        }
    }else{
        setFootballRotate(false);
    }
    auto cameraCurrentVec2 = this->myCamera->getPosition();
    auto cameraTargetVec2 = cameraMoveInRect(curLocation);
    float mu = GeometryTools::calculateDistance(cameraCurrentVec2, cameraTargetVec2);
    if(mu > camera_follow_dis){
        auto speedx =speedCamera*(cameraTargetVec2.x-cameraCurrentVec2.x)/mu;
        auto speedy =speedCamera*(cameraTargetVec2.y-cameraCurrentVec2.y)/mu;
//        log("(%f,%f)",speedx,speedy);
        this->myCamera->setPosition(cameraCurrentVec2.x+speedx,cameraCurrentVec2.y+speedy);
    }
    checkBallInGoal();
}
