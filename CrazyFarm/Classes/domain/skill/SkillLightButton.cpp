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

/** 技能按钮点击回调 */
void SkillLightButton::skillClickCallBack(Ref* obj)
{
	//if (JudgeUseSkill())
	//{
	//	SkillButton::skillClickCallBack(obj);
	//	skillManager::getInstance()->useSkillLight();
	//}
	useSkill();
}

/** 技能冷却完成回调 */
void SkillLightButton::skillCoolDownCallBack()
{
	SkillButton::skillCoolDownCallBack();

}

