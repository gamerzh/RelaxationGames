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
//    showDebugInfo();
    return true;
}

void Goalkeeper::doTumble(){
    
}

void Goalkeeper::changeFootManState(GoalkeeperState state){
    if(state == GoalkeeperState::waiting){
        playFootManStand();
    }else if(state == GoalkeeperState::running){
        playFootManRun();
    }else if(state == GoalkeeperState::shoot){
        playFootManShoot();
    }else if(state == GoalkeeperState::snap){
        playFootManShoot();
    }
}

void Goalkeeper::playFootManStand() {
    if(animUpdateInterval == 0 &&  this->manState !=  GoalkeeperState::waiting){
        animUpdateInterval = 20/60;
        this->manState = GoalkeeperState::waiting;
        playerCsb->stopAllActions();
        auto heroTimeLine = CSLoader::createTimeline(fileName);
        heroTimeLine->play("animation2", true);
        playerCsb->runAction(heroTimeLine);
    }
}

void Goalkeeper::playFootManRun() {
    if(animUpdateInterval == 0 &&  this->manState !=  GoalkeeperState::running){
        animUpdateInterval = 117/60;
        this->manState = GoalkeeperState::running;
        playerCsb->stopAllActions();
        auto heroTimeLine = CSLoader::createTimeline(fileName);
        heroTimeLine->play("animation0", true);
        playerCsb->runAction(heroTimeLine);
    }
}

void Goalkeeper::playFootManShoot() {
    if(animUpdateInterval == 0){
        animUpdateInterval = 32/60;
        this->manState = GoalkeeperState::shoot;
        playerCsb->stopAllActions();
        auto heroTimeLine = CSLoader::createTimeline(fileName);
        heroTimeLine->play("animation1", false);
        playerCsb->runAction(heroTimeLine);
    }
}
void Goalkeeper::playFootManSnap(){
    if(animUpdateInterval == 0){
        animUpdateInterval = 73/60;
        playerCsb->stopAllActions();
        shadow->setVisible(false);
        auto heroTimeLine = CSLoader::createTimeline(fileName);
        heroTimeLine->play("animation7", false);
        playerCsb->runAction(heroTimeLine);
    }
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
    playFootManStand();
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
//    log("AAAAAAAAAAAAA");
    auto vec = this->getPosition();
    auto dis = GeometryTools::calculateDistanceY(pos, vec);
    if(dis<DEFEND_BACK_OFFSET/2){
        changeFootManState(Goalkeeper::GoalkeeperState::waiting);
        return;
    }
     auto speedy = 5 * (pos.y-vec.y>0?1:-1);
    if(this->getPositionY()<=500){
        if(speedy>0){
            this->setPosition(vec.x,500+speedy);
        }else{
            this->setPosition(vec.x,500);
            changeFootManState(Goalkeeper::GoalkeeperState::waiting);
        }
    }else if(this->getPositionY()>500 && this->getPositionY()<900){
        changeFootManState(Goalkeeper::GoalkeeperState::running);
        this->setPosition(vec.x,vec.y+speedy);
    }else if(this->getPositionY()>=900){
        if(speedy<0){
            this->setPosition(vec.x,900+speedy);
        }else{
            this->setPosition(vec.x,900);
            changeFootManState(Goalkeeper::GoalkeeperState::waiting);
        }
        
    }
    
}

void Goalkeeper::update(float dt) {
    //动作切换的间隔
    if(animUpdateInterval>0){
        animUpdateInterval -= dt;
        if(animUpdateInterval<=0){
            animUpdateInterval = 0;
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

