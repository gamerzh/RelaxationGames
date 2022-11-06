#include "SkillLightButton.h"
#include "domain/bag/BagManager.h"
#include "data/GameData.h"
SkillLightButton* SkillLightButton::createSkillLightButton()
{
	SkillLightButton* skillButton = new SkillLightButton();
	if (skillButton && skillButton->init(5, "skillStencil.png", "item_1007.png", "item_1007.png"))
	{
		skillButton->autorelease();
		return skillButton;
	}
	else
	{
		delete skillButton;
		skillButton = NULL;
	}

	return NULL;
}

/** ���ܰ�ť����ص� */
void SkillLightButton::skillClickCallBack(Ref* obj)
{
	//if (JudgeUseSkill())
	//{
	//	SkillButton::skillClickCallBack(obj);
	//	skillManager::getInstance()->useSkillLight();
	//}
	useSkill();
}

/** ������ȴ��ɻص� */
void SkillLightButton::skillCoolDownCallBack()
{
	SkillButton::skillCoolDownCallBack();

}

