#pragma once
#include <cocos2d.h>
#include "utill/SkillButton.h"
#include "config/ConfigSkill.h"
#include "skillManager.h"
USING_NS_CC;
class SkillBombButton : public SkillButton
{
public:
	static SkillBombButton* createSkillBombButton();
protected:
    /** ���ܰ�ť����ص� */
    virtual void    skillClickCallBack(Ref* obj);

    /** ������ȴ��ϻص�*/
   virtual void    skillCoolDownCallBack();

};

