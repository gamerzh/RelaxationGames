#include "CircleMoveTo.h"



CircleMoveTo* CircleMoveTo::create(float duration, const CCPoint& center, float scale, float angle,bool isClockwise)
{
	CircleMoveTo *pRet = new CircleMoveTo();
	pRet->initWithDuration(duration, center, scale, angle, isClockwise);
	pRet->autorelease();

	return pRet;
}

bool CircleMoveTo::initWithDuration(float duration, const CCPoint& center, float scaleDiff, float angle, bool isClockwise)
{
	if (CCActionInterval::initWithDuration(duration))
	{
		this->m_duration = duration;
		this->m_center = center;
		this->m_scaleDiff = scaleDiff;
		this->m_currScale = 1.0f;
		this->m_angle = angle;
		this->m_isClockwise = isClockwise;
		/************************************************************************/
		/* 计算每次update调用时需要转动的弧度                                   */
		/************************************************************************/
		auto fps = Director::sharedDirector()->getAnimationInterval();
		//this->m_anglePreFrame = angle / duration/* * fps*/ / (180 / M_PI);

		this->m_anglePreFrame = CC_DEGREES_TO_RADIANS(angle/* / duration*/);
		this->m_frameCnts = 0;
		return true;
	}
	return false;
}

void CircleMoveTo::startWithTarget(CCNode *pTarget)
{
	CCActionInterval::startWithTarget(pTarget);
	m_initPos = pTarget->getPosition();
}
void CircleMoveTo::update(float time)
{
	int nIsClockWise = m_isClockwise ? -1 : 1;
	m_currScale += m_scaleDiff;

	CCPoint newPos = ccpRotateByAngle(m_initPos, m_center,  time* m_anglePreFrame*nIsClockWise);
	CCPoint diff = ccpSub(newPos, m_center);
	newPos = diff * m_currScale + m_center;

	getTarget()->setPosition(newPos);
	getTarget()->setRotation(time* m_anglePreFrame);
	


}