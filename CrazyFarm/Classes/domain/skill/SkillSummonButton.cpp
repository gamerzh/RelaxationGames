#include "SkillSummonButton.h"
#include "domain/bag/BagManager.h"
#include "data/GameData.h"
#include "domain/game/GameManage.h"
SkillSummonButton* SkillSummonButton::createSkillSummonButton()
{

	SkillSummonButton* skillButton = new SkillSummonButton();
	if (skillButton && skillButton->init(3, "skillStencil.png", "item_1005.png", "item_1005.png"))
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
void SkillSummonButton::skillClickCallBack(Ref* obj)
{
	//if (JudgeUseSkill())
	//{
	//	SkillButton::skillClickCallBack(obj);
	//	skillManager::getInstance()->useSkillSummon(GameManage::getInstance()->getGameLayer()->GetMyTurret());
	//}
	useSkill();
}

/** 技能冷却完成回调 */
void SkillSummonButton::skillCoolDownCallBack()
{
	SkillButton::skillCoolDownCallBack();

}

