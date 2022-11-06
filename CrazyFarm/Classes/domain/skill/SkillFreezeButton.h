#pragma once
#include <cocos2d.h>
#include "utill/SkillButton.h"
#include "config/ConfigSkill.h"
#include "skillManager.h"
USING_NS_CC;
class SkillFreezeButton : public SkillButton
{
public:
	static SkillFreezeButton* createSkillFreezeButton();
protected:
    /** ���ܰ�ť����ص� */
    virtual void    skillClickCallBack(Ref* obj);

    /** ������ȴ��ϻص�*/
   virtual void    skillCoolDownCallBack();

};

