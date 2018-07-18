#include "Rocker.h"
USING_NS_CC;

Rocker* Rocker::create(Vec2 pos)
{
    Rocker *ret = new Rocker();
    if (ret && ret->init(pos))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool Rocker::init(Vec2 pos)
{
    if (!Node::init()) {
        return false;
    }
    
    Sprite *h_bg = Sprite::create("rocker_bc.png");
    h_bg->setAnchorPoint(Vec2(0.5, 0.5));
    h_bg->setPosition(pos);
    h_bg->setVisible(false);
    addChild(h_bg, 0, ROCKER_NACKGROUMD_TAG);
    
    Sprite *h_rocker = Sprite::create("rocker_bt.png");
    h_rocker->setAnchorPoint(Vec2(0.5, 0.5));
    h_rocker->setPosition(pos);
    h_rocker->setVisible(false);
    addChild(h_rocker, 0, ROCKER_CONTENT_TAG);
    
    rockerAngle = 0;
    rockerRad = h_bg->getContentSize().width *0.3;
    bgCenter = pos;
    return true;
}

void Rocker::openRocker()
{
    Sprite* bg = (Sprite*)getChildByTag(ROCKER_NACKGROUMD_TAG);
    bg->setVisible(true);
    Sprite* rk = (Sprite*)getChildByTag(ROCKER_CONTENT_TAG);
    rk->setVisible(true);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(Rocker::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(Rocker::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(Rocker::onTouchEnded, this);
    listener->setSwallowTouches(true);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void Rocker::closeRocker(bool isVisible)
{
    Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
    if (!isVisible)
    {
        auto bg = (Sprite*)getChildByTag(ROCKER_NACKGROUMD_TAG);
        bg->setVisible(false);
        
        auto rk = (Sprite*)getChildByTag(ROCKER_CONTENT_TAG);
        rk->setVisible(false);
    }
}

bool Rocker::onTouchBegan(Touch* pTouch, Event* pEvent)
{
    Vec2 point = pTouch->getLocation();
    auto rod = (Sprite*)getChildByTag(ROCKER_NACKGROUMD_TAG);
    if (rod->getBoundingBox().containsPoint(point))
    {
        return true;
    }
    return false;
}

void Rocker::onTouchMoved(Touch* touch, Event* event)
{
    Vec2 pos = touch->getLocation();
    auto rocker = (Sprite*)getChildByTag(ROCKER_CONTENT_TAG);
    float angle = calculateAngle(bgCenter, pos);
    int length = sqrt(pow((bgCenter.x - pos.x), 2) + pow((bgCenter.y - pos.y), 2));
    if (length > rockerRad - 20) {
        rocker->setPosition(getPosByAngle(rockerRad - 20, angle) + bgCenter);
    }else{
        rocker->setPosition(pos);
    }
    rockerAngle = angle;
}

void Rocker::onTouchEnded(Touch*, Event*)
{
    rockerAngle = 0;
    auto rocker = (Sprite*)getChildByTag(ROCKER_CONTENT_TAG);
    rocker->runAction(MoveTo::create(0.1f, bgCenter));
}

float Rocker::calculateAngle(Vec2 pos1, Vec2 pos2)
{
    float p1x = pos1.x;
    float p1y = pos1.y;
    float p2x = pos2.x;
    float p2y = pos2.y;
    float incline = sqrt(pow((p1x - p2x), 2) + pow((p1y - p2y), 2));
    float cosValue = (p2x - p1x) / incline;
    float angle = acos(cosValue);
    if (p2y < p1y) {
        angle = -angle;
    }
    return angle;
}

Vec2 Rocker::getPosByAngle(float rad, float angle)
{
    return Vec2(rad*cos(angle), rad*sin(angle));
}

float Rocker::getRockerAngle() {
    return rockerAngle;
}

