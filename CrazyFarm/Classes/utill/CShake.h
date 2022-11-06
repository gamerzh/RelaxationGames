/**
 desc:��ָ���ؼ�����
 һ��CCNodeͬʱִ�ж��CCShake����,����һ��CCShakeû������ִ��һ��CCShake�Ļ��ͻ��������,�����ƫ�Ƶ�����!
 
 �������:
 1).��Ҫͬʱִ�ж��CCShake����.
 2.�Լ��ⲿ��¼���CCNode��λ��,ִ����ɺ��ֶ�setPosition();
 */
#pragma once
#include "cocos2d.h"
using namespace cocos2d;

/**
 * ��ָ��Ƶ�ȷ�Χ�ڶ���[-strength_x,strength_x][-strength_y, strength_y]
 */
class CCShake : public cocos2d::CCActionInterval
{
public:
    CCShake();
    
    // Create the action with a time and a strength (same in x and y)
    static CCShake* create(float d, float strength );
    // Create the action with a time and strengths (different in x and y)
    static CCShake* createWithStrength(float d, float strength_x, float strength_y );
    bool initWithDuration(float d, float strength_x, float strength_y );
    
protected:
    
    virtual void startWithTarget(cocos2d::CCNode *pTarget);
    virtual void update(float time);
    virtual void stop(void);
    
    
    // Initial position of the shaked node
    float m_initial_x, m_initial_y;
    // Strength of the action
    float m_strength_x, m_strength_y;
};


