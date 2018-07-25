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
    playerCsb = CSLoader::createNode(getFileNameByTeamId(teamId,goalkeeper));
    playerCsb->setScale(ANIMATION_SCALE_RATE);
    playerCsb->setPosition(0, 0);
    this->addChild(playerCsb);
    playFootManStand();
    scheduleUpdate();
    //    showDebugInfo();
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
    playFootManShoot();
}

void FootMan::playFootManRun() {
    if(canUpdateStae){
        canUpdateStae = false;
        this->manState = FootManState::running;
        playerCsb->stopAllActions();
        auto heroTimeLine = CSLoader::createTimeline("rw1.csb");
        heroTimeLine->play("animation0", true);
        playerCsb->runAction(heroTimeLine);
    }
}

void FootMan::playFootManTackle() {
    this->manState = FootManState::tackle;
    playerCsb->stopAllActions();
    auto heroTimeLine = CSLoader::createTimeline("rw1.csb");
    heroTimeLine->play("animation4", false);
    playerCsb->runAction(heroTimeLine);
    heroTimeLine->setAnimationEndCallFunc("animation4",[=](){
        //TODO 射门动画结束后允许其他动画
        canUpdateStae = true;
    });
}


void FootMan::playFootManShoot() {
    this->manState = FootManState::shoot;
    playerCsb->stopAllActions();
    auto heroTimeLine = CSLoader::createTimeline("rw1.csb");
    heroTimeLine->play("animation1", false);
    playerCsb->runAction(heroTimeLine);
    heroTimeLine->setAnimationEndCallFunc("animation1",[=](){
        //TODO 射门动画结束后允许其他动画
        canUpdateStae = true;
    });
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

void FootMan::setRobotAI(bool f){
    this->robotAI = f;
}

float FootMan::getBallDistance(){
    auto pos = GameStatus::getInstance()->getGameBall()->getPosition();
    return GeometryTools::calculateDistance(pos, this->getPosition());
}

void FootMan::runToPositon(Vec2 pos){
    //跑向球
    auto vec = this->getPosition();
    float speedx = runSpeed*(pos.x-vec.x)/GeometryTools::calculateDistance(pos, vec);
    float speedy = runSpeed*(pos.y-vec.y)/GeometryTools::calculateDistance(pos, vec);
    if(speedx>0){
        moveRight();
    }else{
        moveLeft();
    }
    this->setPosition(vec.x+speedx,vec.y+speedy);
    playFootManRun();
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
    if(d == 1){
        if(goalkeeper){
            return "team_1_3.csb";
        }else{
            return StringUtils::format("team_1_%d.csb",random(1,2));
        }
    }
    return "rw1.csb";
}

void FootMan::update(float dt) {
    //判断持球的是否是己方球员或者没有人持球
    auto ball = GameStatus::getInstance()->getGameBall();
    if(robotAI){
        auto man = ball->getOwerMan();
        if(NULL != man){
            if(this->belongTeamId != man->getFootManTeamId()){
                //地方队员,防守
                if(getBallDistance()<DEFEND_RADIUS){
                    if(manState == FootManState::waiting){
                        playFootManRun();
                    }
                    if(getBallDistance()<TACKLE_DISTANCE){
                        if(manState != FootManState::tackle){
                            playFootManTackle();
                        }
                    }else{
                        runToPositon(GameStatus::getInstance()->getGameBall()->getPosition());
                    }
                }else{
                    if(manState != FootManState::waiting){
                        playFootManStand();
                    }else{
                        manState = FootManState::waiting;
                    }
                }
            }else{
                //己方队友,去支援
                if(GeometryTools::calculateDistance(this->getPosition(), man->getPosition())>SUPPORT_DISTANCE && !this->isGoalkeeper){
                    supportPosition(man->getPosition());
                }
            }
        }else{
            //TODO 无人持球,通知最近的队员去抢球
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


