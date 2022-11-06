#pragma once
#include <cocos2d.h>
#include "utill/SkillButton.h"
#include "config/ConfigSkill.h"
#include "skillManager.h"
USING_NS_CC;
class SkillLightButton : public SkillButton
{
public:
	static SkillLightButton* createSkillLightButton();
protected:
    /** ���ܰ�ť����ص� */
    virtual void    skillClickCallBack(Ref* obj);

    /** ������ȴ��ϻص�*/
   virtual void    skillCoolDownCallBack();

};

