#include "FootMan.h"
#include "GameStatus.h"
#include "GlobalProperty.h"
#include "GeometryTools.h"
USING_NS_CC;

FootMan* FootMan :: create(int teamId,FootManProperty property, bool goalkeeper,cocos2d::Camera* camera) {
    FootMan *ret = new FootMan();
    if (ret && ret->init(teamId,property,goalkeeper,camera))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool FootMan::init(int teamId,FootManProperty property,bool goalkeeper, cocos2d::Camera* camera) {
    if (!Node::init()) {
        return false;
    }
    this->isGoalkeeper = goalkeeper;
    this->belongTeamId = teamId;
    this->manState = FootManState::waiting;
    this->fileName = getFileNameByTeamId(teamId,goalkeeper);
    playerCsb = CSLoader::createNode(fileName);
    playerCsb->setScale(ANIMATION_SCALE_RATE);
    playerCsb->setPosition(0, 0);
    this->addChild(playerCsb);
    playFootManStand();
    scheduleUpdate();
    //showDebugInfo();
    return true;
}



float FootMan::getPositionXByYLeft(float y) {
    Vec2 p1 = Vec2(175,90);
    Vec2 p2 = Vec2(245, 1215);
    float k = (p2.y - p1.y) / (p2.x - p1.x);
    return y / k + p1.x+25;
}

float FootMan::getPositionXByYRight(float y) {
    Vec2 p1 = Vec2(1975, 90);
    Vec2 p2 = Vec2(1875, 1210);
    float k = (p2.y - p1.y) / (p2.x - p1.x);
    return y / k + p1.x - 30;
}

Point FootMan::moveInSafeRect(Point pos) {
    if (pos.y < football_field_offset_bottom) {
        pos.y = football_field_offset_bottom;
    }
    else if (pos.y > football_field_height- football_field_offset_top) {
        pos.y = football_field_height- football_field_offset_top;
    }
    
    if (pos.x < getPositionXByYLeft(pos.y)) {
        pos.x = getPositionXByYLeft(pos.y);
    }
    else if (pos.x > getPositionXByYRight(pos.y)) {
        pos.x = getPositionXByYRight(pos.y);
    }
    return pos;
}

void FootMan::setFootManAngle(float angle) {
    if (angle != 0 && canObtainBall) {
        Vec2 curPos = this->getPosition();
        if (cos(angle) < 0) {
            moveLeft();
        }
        else {
            moveRight();
        }
        auto vec = Vec2(curPos.x + cos(angle) * 5, curPos.y + sin(angle) * 5);
        this->setPosition(moveInSafeRect(vec));
    }
}

void FootMan::doSlideTackle() {
    playFootManTackle();
    //判断本次铲球结果
    if(random(1,100)<=tacklePercentage*100){
        //success 发出通知,持球队员摔倒,球恢复为自由态
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(foot_man_trackle_success);
    }
}


void FootMan::doShoot() {
    playFootManShoot();
}

void FootMan::doTumble(){
    playFootManTumble();
    canObtainBall = false;
}

void FootMan::doDefend(cocos2d::Vec2 vec){
    //球员去追对方持球队员
    if(GeometryTools::calculateDistance(this->getPosition(),vec)>TACKLE_DISTANCE){
        footmanRunToTarget(vec,TACKLE_DISTANCE,CallFunc::create([=](){
            if(manState != FootManState::tackle && canFootmanTackle){
                doSlideTackle();
                canFootmanTackle = false;
            }
        }));
    }
}

void FootMan::playFootManStand() {
    this->manState = FootManState::waiting;
    playerCsb->stopAllActions();
    auto heroTimeLine = CSLoader::createTimeline(fileName);
    heroTimeLine->play("animation2", true);
    playerCsb->runAction(heroTimeLine);
}

void FootMan::playFootManRun() {
    if(canUpdateState){
        this->manState = FootManState::running;
        playerCsb->stopAllActions();
        auto heroTimeLine = CSLoader::createTimeline(fileName);
        heroTimeLine->play("animation0", true);
        playerCsb->runAction(heroTimeLine);
        canUpdateState = false;
    }
}

void FootMan::playFootManTackle() {
    canUpdateState = false;
    this->manState = FootManState::tackle;
    playerCsb->stopAllActions();
    auto heroTimeLine = CSLoader::createTimeline(fileName);
    heroTimeLine->play("animation4", false);
    playerCsb->runAction(heroTimeLine);
    heroTimeLine->setAnimationEndCallFunc("animation4",[=](){
        //铲球动画结束后允许其他动画
        canUpdateState = true;
    });
}


void FootMan::playFootManShoot() {
    canUpdateState = false;
    this->manState = FootManState::shoot;
    playerCsb->stopAllActions();
    auto heroTimeLine = CSLoader::createTimeline(fileName);
    heroTimeLine->play("animation1", false);
    playerCsb->runAction(heroTimeLine);
    heroTimeLine->setAnimationEndCallFunc("animation1",[=](){
        //射门动画结束后允许其他动画
        canUpdateState = true;
    });
}

void FootMan::playFootManTumble(){
    canUpdateState = false;
    this->manState = FootManState::tumble;
    playerCsb->stopAllActions();
    auto heroTimeLine = CSLoader::createTimeline(fileName);
    heroTimeLine->play("animation6", false);
    playerCsb->runAction(heroTimeLine);
    heroTimeLine->setAnimationEndCallFunc("animation6",[=](){
        canUpdateState = true;
    });
}

float FootMan::getShootSpeed() {
    return 10;
}

bool FootMan::getCanObtainBall(){
    return canObtainBall;
}

void FootMan::moveRight() {
    playerCsb->setScaleX(ANIMATION_SCALE_RATE);
}


void FootMan::moveLeft() {
    playerCsb->setScaleX(ANIMATION_SCALE_RATE*-1);
}

void FootMan::updateFootManZorder() {
    this->setLocalZOrder(FOOTBALL_MAN_ZORDER - (int)this->getPositionY());
}

FootMan::FootManState FootMan::getFootManState(){
    return this->manState;
}

void FootMan::changeFootManState(FootManState state){
    if(state == FootManState::waiting){
        playFootManStand();
    }else if(state == FootManState::running){
        playFootManRun();
    }else if(state == FootManState::tackle){
        playFootManTackle();
    }else if(state == FootManState::tumble){
        playFootManTumble();
    }
}

void FootMan::setOriginPosition(cocos2d::Vec2 vec){
    this->originVec2 = vec;
}

void FootMan::replacement(){
    this->setPosition(this->originVec2);
    if(originVec2.x>1200){
        moveLeft();
    }
}


int FootMan::getFootManTeamId(){
    return this->belongTeamId;
}

bool FootMan::getSimpleAI(){
    return this->simpleRobotAI;
}

void FootMan::openSimpleAI(bool p){
    this->simpleRobotAI = p;
}

float FootMan::getBallDistance(){
    auto pos = GameStatus::getInstance()->getGameBall()->getPosition();
    return GeometryTools::calculateDistance(pos, this->getPosition());
}

void FootMan::footmanRunToTarget(Vec2 pos,float rad,CallFunc* callback){
    //跑向球
    auto vec = this->getPosition();
    float speedx = runSpeed*(pos.x-vec.x)/GeometryTools::calculateDistance(pos, vec);
    float speedy = runSpeed*(pos.y-vec.y)/GeometryTools::calculateDistance(pos, vec);
    if(speedx>0){
        moveRight();
    }else if(speedx<0){
        moveLeft();
    }
    this->setPosition(vec.x+speedx,vec.y+speedy);
//    log("HHHHHHHH %f,%f",this->getPositionX(),this->getPositionY());
    playFootManRun();
    if(GeometryTools::calculateDistance(this->getPosition(),pos) <= rad){
        //到达目标
        this->runAction(callback);
    }
}

void FootMan::supportPosition(cocos2d::Vec2 pos){
    auto vec = this->getPosition();
    float speedx = runSpeed*(pos.x-vec.x)/GeometryTools::calculateDistance(pos, vec);
    if(speedx>0){
        moveRight();
    }else{
        moveLeft();
    }
    if(speedx != 0){
        playFootManRun();
    }
    this->setPosition(vec.x+speedx,vec.y);
}

std::string FootMan::getFileNameByTeamId(int d,bool goalkeeper){
    if(goalkeeper){
        return StringUtils::format("team_%d_3.csb",d);
    }else{
        return StringUtils::format("team_%d_%d.csb",d,random(1,2));
    }
}

void FootMan::update(float dt) {
    //铲球技能的冷却
    if(!canFootmanTackle){
        tackleInterval -= dt;
        if(tackleInterval<0){
            tackleInterval = 3;
            canFootmanTackle = true;
        }
    }
    //球权获得能力恢复
    if(!canObtainBall){
        obtainInterval -= dt;
        if(obtainInterval<0){
            obtainInterval = 2;
            canObtainBall = true;
        }
    }
    updateFootManZorder();
    if (NULL != getChildByTag(1000)) {
        ((Label*)getChildByTag(1000))->setString(StringUtils::format("(%.1f,%.1f)", this->getPositionX(), this->getPositionY()));
    }
}



void FootMan::showDebugInfo() {
    auto lable = Label::createWithSystemFont(StringUtils::format("(%.1f,%.1f)",this->getPositionX(),this->getPositionY()), "arial", 30);
    lable->setTag(1000);
    lable->setPosition(0,0);
    addChild(lable);
}


