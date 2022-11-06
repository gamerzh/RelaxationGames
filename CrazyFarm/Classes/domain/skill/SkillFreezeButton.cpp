#include "SkillFreezeButton.h"
#include "domain/bag/BagManager.h"
#include "data/GameData.h"
#include "turret/PlayerTurret.h"
#include "domain/game/GameManage.h"
SkillFreezeButton* SkillFreezeButton::createSkillFreezeButton()
{
	SkillConfigInfo info = ConfigSkill::getInstance()->getskillConfigInfoBySkillId(1);
	SkillFreezeButton* skillButton = new SkillFreezeButton();
	if (skillButton && skillButton->init(1, "skillStencil.png", "item_1003.png", "item_1003.png"))
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
void SkillFreezeButton::skillClickCallBack(Ref* obj)
{
	//if (JudgeUseSkill())
	//{
	//	SkillButton::skillClickCallBack(obj);
	//	skillManager::getInstance()->useSkillFreeze(GameManage::getInstance()->getGameLayer()->GetMyTurret());
	//}
	useSkill();
}

/** ������ȴ��ɻص� */
void SkillFreezeButton::skillCoolDownCallBack()
{
	SkillButton::skillCoolDownCallBack();
	
}

