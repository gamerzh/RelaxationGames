#pragma once
#include "cocos2d.h"
USING_NS_CC;
class CircleMoveTo :
	public ActionInterval
{
	public:
		bool initWithDuration(float duration, const cocos2d::CCPoint& center, float scaleDiff, float angle, bool isClockwise);
		virtual void startWithTarget(cocos2d::CCNode *pTarget);
		virtual void update(float time);
	public:
		static CircleMoveTo* create(float duration, const cocos2d::CCPoint& center, float scale, float angle, bool isClockwise);

	protected:

		float m_duration;
		Point m_center;
		float m_scaleDiff;
		float m_currScale;
		float m_angle;
		float m_anglePreFrame;
		int m_frameCnts;
		float m_nTime = 0;
		Point m_initPos;
		bool m_isClockwise;
};

