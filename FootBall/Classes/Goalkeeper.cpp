#include "Goalkeeper.h"
#include "GameStatus.h"
#include "GlobalProperty.h"
#include "GeometryTools.h"
USING_NS_CC;

Goalkeeper* Goalkeeper :: create(int teamId,FootManProperty property,cocos2d::Camera* camera) {
    Goalkeeper *ret = new Goalkeeper();
    if (ret && ret->init(teamId,property,camera))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool Goalkeeper::init(int teamId,FootManProperty property,cocos2d::Camera* camera) {
    if (!Node::init()) {
        return false;
    }
    this->belongTeamId = teamId;
    this->manState = FootManState::waiting;
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

void Goalkeeper::setFootManAngle(float angle) {
    if (angle != 0 && canObtainBall) {
        Vec2 curPos = this->getPosition();
        if (cos(angle) < 0) {
            moveLeft();
        }
        else {
            moveRight();
        }
        auto vec = Vec2(curPos.x + cos(angle) * runSpeed, curPos.y + sin(angle) * runSpeed);
        this->setPosition(moveInSafeRect(vec));
    }
}

void Goalkeeper::doSlideTackle() {
    playFootManTackle();
    //判断本次铲球结果,判断求是否在铲球范围内
    if(GeometryTools::calculateDistance(this->getPosition(),GameStatus::getInstance()->getGameBall()->getPosition())<TACKLE_DISTANCE
       &&random(1,100)<=tacklePercentage*100){
        //success 发出通知,持球队员摔倒,球恢复为自由态
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(foot_man_trackle_success);
    }
}

void Goalkeeper::doTumble(){
    playFootManTumble();
    canObtainBall = false;
}

void Goalkeeper::doDefend(cocos2d::Vec2 vec){
    //球员去追对方持球队员
    if(GeometryTools::calculateDistance(this->getPosition(),vec)>TACKLE_DISTANCE){
        manRunToTarget(vec,TACKLE_DISTANCE,CallFunc::create([=](){
            if(manState != FootManState::tackle && canFootmanTackle){
                doSlideTackle();
                canFootmanTackle = false;
            }
        }));
    }
}

void Goalkeeper::playFootManStand() {
    this->manState = FootManState::waiting;
    playerCsb->stopAllActions();
    auto heroTimeLine = CSLoader::createTimeline(fileName);
    heroTimeLine->play("animation2", true);
    playerCsb->runAction(heroTimeLine);
}

void Goalkeeper::playFootManRun() {
    if(canUpdateState){
        this->manState = FootManState::running;
        playerCsb->stopAllActions();
        auto heroTimeLine = CSLoader::createTimeline(fileName);
        heroTimeLine->play("animation0", true);
        playerCsb->runAction(heroTimeLine);
        canUpdateState = false;
    }
}

void Goalkeeper::playFootManTackle() {
    canUpdateState = false;
    this->manState = FootManState::tackle;
    playerCsb->stopAllActions();
    auto heroTimeLine = CSLoader::createTimeline(fileName);
    heroTimeLine->play("animation4", false);
    playerCsb->runAction(heroTimeLine);
    heroTimeLine->setAnimationEndCallFunc("animation4",[=](){
        //铲球动画结束后允许其他动画
        this->manState = running;
        canUpdateState = true;
    });
}


void Goalkeeper::playFootManShoot() {
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

void Goalkeeper::playFootManTumble(){
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

void Goalkeeper::playFootManSnap(){
    canUpdateState = false;
    this->manState = FootManState::tumble;
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

Goalkeeper::FootManState Goalkeeper::getFootManState(){
    return this->manState;
}

void Goalkeeper::changeFootManState(FootManState state){
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

void Goalkeeper::setOriginPosition(cocos2d::Vec2 vec){
    this->originVec2 = vec;
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

void Goalkeeper::manRunToTarget(Vec2 pos,float rad,CallFunc* callback){
    //跑向球
    if(this->simpleRobotAI){
        auto vec = this->getPosition();
        if(GeometryTools::calculateDistance(pos, vec) < rad/2){
            return;
        }
        float speedx = runSpeed*(pos.x-vec.x)/GeometryTools::calculateDistance(pos, vec);
        float speedy = runSpeed*(pos.y-vec.y)/GeometryTools::calculateDistance(pos, vec);
        if(speedx>0){
            moveRight();
        }else if(speedx<0){
            moveLeft();
        }
        if(manState != FootManState::tackle || manState != FootManState::tumble){
            this->setPosition(vec.x+speedx,vec.y+speedy);
        }
        playFootManRun();
        if(GeometryTools::calculateDistance(this->getPosition(),pos) <= rad && nullptr != callback){
            //到达目标
            this->runAction(callback);
        }
    }
}

void Goalkeeper::manRunToTargetX(cocos2d::Vec2 pos){
    if(simpleRobotAI){
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
        if(manState != FootManState::tackle || manState != FootManState::tumble){
            this->setPosition(vec.x+speedx,vec.y);
        }
    }
}

void Goalkeeper::manRunToTargetY(cocos2d::Vec2 pos){
    if(simpleRobotAI){
        auto vec = this->getPosition();
        float speedy = runSpeed*(pos.y-vec.y)/GeometryTools::calculateDistance(pos, vec);
        if(speedy != 0){
            playFootManRun();
        }
        if(manState != FootManState::tackle || manState != FootManState::tumble){
            this->setPosition(vec.x,vec.y+speedy);
        }
    }
}

//获取资源名称,为了压包删除过部分资源
std::string Goalkeeper::getFileNameByTeamId(int id){
    if(id == PLAYER_TEAM_ID){
        return StringUtils::format("team_%d_%d.csb",id,random(1,2));
    }else{
        return StringUtils::format("team_%d_1.csb",id);
    }
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

void Goalkeeper::speedUp(){
    this->runSpeed = 6;
}

void Goalkeeper::update(float dt) {
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
    //速度衰减
    if(runSpeed>3.5){
        runSpeed -= dt/4;
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


