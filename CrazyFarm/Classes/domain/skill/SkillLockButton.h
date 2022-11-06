#pragma once
#include <cocos2d.h>
#include "utill/SkillButton.h"
#include "config/ConfigSkill.h"
#include "skillManager.h"
USING_NS_CC;
class SkillLockButton : public SkillButton
{
public:
	static SkillLockButton* createSkillLockButton();
protected:
    /** ���ܰ�ť����ص� */
    virtual void    skillClickCallBack(Ref* obj);

    /** ������ȴ��ϻص�*/
   virtual void    skillCoolDownCallBack();

};

