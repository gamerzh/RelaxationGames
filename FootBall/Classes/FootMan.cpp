#include "FootMan.h"
#include "GlobalProperty.h"
USING_NS_CC;

FootMan* FootMan :: create(FootManProperty property, cocos2d::Camera* camera) {
    FootMan *ret = new FootMan();
    if (ret && ret->init(property,camera))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool FootMan::init(FootManProperty property, cocos2d::Camera* camera) {
    if (!Node::init()) {
        return false;
    }
    this->manState = FootManState::waiting;
    this->goalkeeper = property.goalkeeper;
    playerCsb = CSLoader::createNode("rw1.csb");
    playerCsb->setScale(ANIMATION_SCALE_RATE);
    playerCsb->setPosition(0, 0);
    this->addChild(playerCsb);
    playFootManStand();
    scheduleUpdate();
    showDebugInfo();
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
    if (angle != 0) {
        //log("setFootManAngle %f,%f,%f", angle, cos(angle), sin(angle));
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
}


void FootMan::doShoot() {
    //this->footBall = nullptr;
    playFootManShoot();
}

bool FootMan::isGoalkeeper() {
    return goalkeeper;
}


void FootMan::playFootManRun() {
    this->manState = FootManState::running;
    playerCsb->stopAllActions();
    auto heroTimeLine = CSLoader::createTimeline("rw1.csb");
    heroTimeLine->play("animation0", true);
    playerCsb->runAction(heroTimeLine);
}

void FootMan::playFootManTackle() {
    this->manState = FootManState::tackle;
    playerCsb->stopAllActions();
    auto heroTimeLine = CSLoader::createTimeline("rw1.csb");
    heroTimeLine->play("animation4", false);
    playerCsb->runAction(heroTimeLine);
}


void FootMan::playFootManShoot() {
    this->manState = FootManState::shoot;
    playerCsb->stopAllActions();
    auto heroTimeLine = CSLoader::createTimeline("rw1.csb");
    heroTimeLine->play("animation1", false);
    playerCsb->runAction(heroTimeLine);
}

void FootMan::playFootManStand() {
    this->manState = FootManState::waiting;
    playerCsb->stopAllActions();
    auto heroTimeLine = CSLoader::createTimeline("rw1.csb");
    heroTimeLine->play("animation2", true);
    playerCsb->runAction(heroTimeLine);
}

float FootMan::getShootSpeed() {
    return 10;
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

FootManState FootMan::getFootManState(){
    return this->manState;
}

void FootMan::changeFootManState(FootManState state){
    this->manState = state;
    if(state == FootManState::waiting){
        playFootManStand();
    }else if(state == FootManState::running){
        playFootManRun();
    }
}

void FootMan::setFootManTeamId(int id){
    this->belongTeamId = id;
}

int FootMan::getFootManTeamId(){
    return this->belongTeamId;
}

void FootMan::runToTargetPosition(cocos2d::Vec2 vec){
    this->runTargetPos = vec;
    // 跑动到目标位置去接应
}

void FootMan::update(float dt) {
    /*if (nullptr != this->footBall) {
     auto set = football_offset_x;
     if (playerCsb->getScaleX() < 0) {                         
     set = set * -1;
     }
     footBall->setPosition(this->getPositionX() + set,this->getPositionY()+ football_offset_y);
     } */
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
