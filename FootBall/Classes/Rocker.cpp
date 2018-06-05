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
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite *h_bg = Sprite::create("rocker_bc.png");
	h_bg->setAnchorPoint(Vec2(0.5, 0.5));
	h_bg->setPosition(pos);
	h_bg->setVisible(false);
	h_bg->setScale(visibleSize.width / 960 + 0.1);
	addChild(h_bg, 0, ROCKER_NACKGROUMD_TAG);

	Sprite *h_rocker = Sprite::create("rocker_bt.png");
	h_rocker->setAnchorPoint(Vec2(0.5, 0.5));
	h_rocker->setPosition(pos);
	h_rocker->setVisible(false);
	h_rocker->setScale(visibleSize.width / 960 + 0.1);
	addChild(h_rocker, 0, ROCKER_CONTENT_TAG);

	//中间
	rockerAngle = 4.f;
	//移动半径
	rockerRad = h_bg->getContentSize().width / 2;
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
		Sprite* bg = (Sprite*)getChildByTag(ROCKER_NACKGROUMD_TAG);
		bg->setVisible(false);

		Sprite* rk = (Sprite*)getChildByTag(ROCKER_CONTENT_TAG);
		rk->setVisible(false);
	}
}

bool Rocker::onTouchBegan(Touch* pTouch, Event* pEvent)
{
	//判断触点是否在摇杆上，如果在的话则进行控制摇杆
	Vec2 point = pTouch->getLocation();
	Sprite* rod = (Sprite*)getChildByTag(ROCKER_NACKGROUMD_TAG);
	if (rod->getBoundingBox().containsPoint(point))
	{
		//log("U get it , pos is ( %d,  %d)", point.x, point.y);
		return true;
	}
	return false;
}

void Rocker::onTouchMoved(Touch* touch, Event* event)
{
	Vec2 pos = touch->getLocation();
	Sprite* rocker = (Sprite*)getChildByTag(ROCKER_CONTENT_TAG);

	float angle = getAngle(bgCenter, pos);
	int length = sqrt(pow((bgCenter.x - pos.x), 2) + pow((bgCenter.y - pos.y), 2));
	if (length > rockerRad - 20)
		rocker->setPosition(getAnglePos(rockerRad - 20, angle) + bgCenter);
	else
		rocker->setPosition(pos);
	rockerAngle = angle;
}

void Rocker::onTouchEnded(Touch*, Event*)
{
	rockerAngle = 4.0f;		//做一个标记值
	Sprite* rocker = (Sprite*)getChildByTag(ROCKER_CONTENT_TAG);
	rocker->runAction(MoveTo::create(0.1f, bgCenter));
}

float Rocker::getAngle(Vec2 pos1, Vec2 pos2)
{
	float p1x = pos1.x;
	float p1y = pos1.y;
	float p2x = pos2.x;
	float p2y = pos2.y;
	//斜边
	float incline = sqrt(pow((p1x - p2x), 2) + pow((p1y - p2y), 2));
	//余弦值
	float cosValue = (p2x - p1x) / incline;
	//通过余弦获得角度
	float angle = acos(cosValue);
	//当触摸点在第三四象限的时候，要取反
	if (p2y < p1y)
		angle = -angle;
	return angle;
}

Vec2 Rocker::getAnglePos(float rad, float angle)
{
	return Vec2(rad*cos(angle), rad*sin(angle));
}


