#include "SkillLockButton.h"
#include "domain/bag/BagManager.h"
#include "data/GameData.h"
#include "domain/game/GameManage.h"
SkillLockButton* SkillLockButton::createSkillLockButton()
{
	SkillLockButton* skillButton = new SkillLockButton();
	if (skillButton && skillButton->init(2,"skillStencil.png", "item_1004.png", "item_1004.png"))
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
void SkillLockButton::skillClickCallBack(Ref* obj)
{
	useSkill();	
	auto nd = getChildByName("tipnode");
	if (nd)
	{
		setZOrder(0);
		GameManage::getInstance()->getGuiLayer()->setLayerAlpha(0);
		nd->removeFromParentAndCleanup(1);
		GameManage::getInstance()->getGameLayer()->GetMyTurret()->setLockFish(FishManage::getInstance()->getHignSoreInVec());
	}
}

/** 技能冷却完成回调 */
void SkillLockButton::skillCoolDownCallBack()
{
	SkillButton::skillCoolDownCallBack();

}

