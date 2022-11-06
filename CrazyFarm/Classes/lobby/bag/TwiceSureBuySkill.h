#pragma once
#include "cocos2d.h"
USING_NS_CC;


class TwiceSureBuySkill : public Layer
{
public:
    virtual bool init(int itemid);
	static TwiceSureBuySkill* createTwiceBuySkillTip(int itemid);
private:

	void sureButtonCallBack(Ref*psend);
	void closeButtonCallBack(Ref*psend);
	int m_itemid;
};
