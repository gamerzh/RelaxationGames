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
    auto shadow = Sprite::create("shadow_man.png");
    shadow->setScale(ANIMATION_SCALE_RATE*2);
    shadow->setPosition(0,0);
    addChild(shadow);
    
    //光圈
    auto circle = Sprite::create("footman_selected.png");
    circle->setScale(ANIMATION_SCALE_RATE*3);
    circle->setPosition(0,0);
    circle->setTag(3000);
    circle->setVisible(false);
    addChild(circle);
    
    playerCsb = CSLoader::createNode(fileName);
    playerCsb->setScale(ANIMATION_SCALE_RATE);
    playerCsb->setPosition(0, 0);
    this->addChild(playerCsb);
    playFootManStand();
    
    scheduleUpdate();
    //showDebugInfo();
    return true;
}

void Goalkeeper::showControlCircle(bool show){
    if(NULL != getChildByTag(3000)){
        getChildByTag(3000)->setVisible(show);
    }
    this->simpleRobotAI = !show;
}




Point Goalkeeper::moveInSafeRect(Point pos) {
    if (pos.y < football_field_offset_bottom) {
        pos.y = football_field_offset_bottom;
    }
    else if (pos.y > football_field_height- football_field_offset_top) {
        pos.y = football_field_height- football_field_offset_top;
    }
    
    if (pos.x < GeometryTools::getPositionXByYLeft(pos.y)) {
        pos.x = GeometryTools::getPositionXByYLeft(pos.y);
    }
    else if (pos.x > GeometryTools::getPositionXByYRight(pos.y)) {
        pos.x = GeometryTools::getPositionXByYRight(pos.y);
    }
    return pos;
}

void Goalkeeper::doTumble(){
    playFootManTumble();
    canObtainBall = false;
}

void Goalkeeper::doDefend(cocos2d::Vec2 vec){
    //球员去追对方持球队员
    if(GeometryTools::calculateDistance(this->getPosition(),vec)>TACKLE_DISTANCE){
       //TODO:
    }
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
    auto heroTimeLine = CSLoader::createTimeline(fileName);
    heroTimeLine->play("animation7", false);
    playerCsb->runAction(heroTimeLine);
    heroTimeLine->setAnimationEndCallFunc("animation7",[=](){
        canUpdateState = true;
    });
}

float Goalkeeper::getShootSpeed() {
    return 10;
}

bool Goalkeeper::getCanObtainBall(){
    return canObtainBall;
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
        return Vec2(this->getPositionX()-65,this->getPositionY());
    }else{
        return this->getPosition();
    }
}

void Goalkeeper::update(float dt) {
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

void Goalkeeper::showDebugInfo() {
    auto lable = Label::createWithSystemFont(StringUtils::format("(%.1f,%.1f)",this->getPositionX(),this->getPositionY()), "arial", 30);
    lable->setTag(1000);
    lable->setPosition(0,0);
    addChild(lable);
}


