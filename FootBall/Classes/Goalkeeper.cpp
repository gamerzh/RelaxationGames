#include "Goalkeeper.h"
#include "GameStatus.h"
#include "GlobalProperty.h"
#include "GeometryTools.h"
USING_NS_CC;

Goalkeeper* Goalkeeper :: create(int teamId,cocos2d::Camera* camera) {
    Goalkeeper *ret = new Goalkeeper();
    if (ret && ret->init(teamId,camera))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool Goalkeeper::init(int teamId,cocos2d::Camera* camera) {
    if (!Footballer::init()) {
        return false;
    }
    this->belongTeamId = teamId;
    this->fileName = getFileNameByTeamId(teamId);
    //添加阴影
    shadow = Sprite::create("shadow_man.png");
    shadow->setScale(ANIMATION_SCALE_RATE*2);
    shadow->setPosition(0,0);
    addChild(shadow);
    
    playerCsb = CSLoader::createNode(fileName);
    playerCsb->setScale(ANIMATION_SCALE_RATE);
    playerCsb->setPosition(0, 0);
    this->addChild(playerCsb);
    playFootManStand();
    scheduleUpdate();
    return true;
}

void Goalkeeper::doTumble(){
    playFootManTumble();
}

void Goalkeeper::playFootManStand() {
    playerCsb->stopAllActions();
    auto heroTimeLine = CSLoader::createTimeline(fileName);
    heroTimeLine->play("animation2", true);
    playerCsb->runAction(heroTimeLine);
}

void Goalkeeper::playFootManRun() {
    if(canUpdateState){
        playerCsb->stopAllActions();
        auto heroTimeLine = CSLoader::createTimeline(fileName);
        heroTimeLine->play("animation0", true);
        playerCsb->runAction(heroTimeLine);
        canUpdateState = false;
    }
}


void Goalkeeper::playFootManShoot() {
    canUpdateState = false;
    playerCsb->stopAllActions();
    auto heroTimeLine = CSLoader::createTimeline(fileName);
    heroTimeLine->play("animation1", false);
    playerCsb->runAction(heroTimeLine);
    heroTimeLine->setAnimationEndCallFunc("animation1",[=](){
        //射门动画结束后允许其他动画
        canUpdateState = true;
        playFootManStand();
    });
}

void Goalkeeper::playFootManTumble(){
    canUpdateState = false;
    playerCsb->stopAllActions();
    auto heroTimeLine = CSLoader::createTimeline(fileName);
    heroTimeLine->play("animation6", false);
    playerCsb->runAction(heroTimeLine);
    heroTimeLine->setAnimationEndCallFunc("animation6",[=](){
        canUpdateState = true;
        
    });
}

void Goalkeeper::playFootManSnap(){
    canUpdateState = false;
    playerCsb->stopAllActions();
    shadow->setVisible(false);
    auto heroTimeLine = CSLoader::createTimeline(fileName);
    heroTimeLine->play("animation7", false);
    playerCsb->runAction(heroTimeLine);
    heroTimeLine->setAnimationEndCallFunc("animation7",[=](){
        canUpdateState = true;
        playFootManStand();
        shadow->setVisible(true);
    });
}

float Goalkeeper::getShootSpeed() {
    return 10;
}

void Goalkeeper::moveRight() {
    playerCsb->setScaleX(ANIMATION_SCALE_RATE);
}


void Goalkeeper::moveLeft() {
    playerCsb->setScaleX(ANIMATION_SCALE_RATE*-1);
}

void Goalkeeper::updateFootManZorder() {
    this->setLocalZOrder(FOOTBALL_MAN_ZORDER - (int)this->getPositionY());
}

Vec2 Goalkeeper::getOriginPosition(){
    return this->originVec2;
}

void Goalkeeper::setOriginPosition(cocos2d::Vec2 vec){
    this->originVec2 = vec;
    this->setPosition(vec);
}

void Goalkeeper::replacement(){
    this->setPosition(this->originVec2);
    //HACK通过位置来判断球员朝向
    if(originVec2.x > FLIED_HALF_DISTANCE){
        moveLeft();
    }else{
        moveRight();
    }
}


int Goalkeeper::getFootManTeamId(){
    return this->belongTeamId;
}

bool Goalkeeper::getSimpleAI(){
    return this->simpleRobotAI;
}

float Goalkeeper::getBallDistance(){
    auto pos = GameStatus::getInstance()->getGameBall()->getPosition();
    return GeometryTools::calculateDistance(pos, this->getPosition());
}

//获取资源名称,为了压包删除过部分资源
std::string Goalkeeper::getFileNameByTeamId(int id){
    return StringUtils::format("team_%d_3.csb",id);
}

cocos2d::Vec2 Goalkeeper::getManDefendVec2(){
    //球员回去防守时会跑回默认位置附近
    return originVec2;
}

cocos2d::Vec2 Goalkeeper::getFootballVec2(){
    auto dir = playerCsb->getScaleX();
    if(dir<0){
        return Vec2(this->getPositionX()-45,this->getPositionY());
    }else{
        return Vec2(this->getPositionX()-10,this->getPositionY()+20);
    }
}

void Goalkeeper::moveDefendBall(cocos2d::Vec2 pos){
    this->targetPosition  = pos;
}

void Goalkeeper::update(float dt) {
    if(targetPosition != Vec2(0,0)){
        auto vec = this->getPosition();
        auto dis = GeometryTools::calculateDistance(targetPosition, vec);
        if(dis >10){
            float speedy = 4 *(targetPosition.y-vec.y)/GeometryTools::calculateDistance(targetPosition, vec);
            if(speedy != 0){
                playFootManRun();
            }
            if(this->getPositionY()>500 && this->getPositionY()<900){
                this->setPosition(vec.x,vec.y+speedy);
            }
        }
    }
    updateFootManZorder();
}



