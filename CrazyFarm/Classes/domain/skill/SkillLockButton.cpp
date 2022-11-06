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

/** ���ܰ�ť����ص� */
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

/** ������ȴ��ɻص� */
void SkillLockButton::skillCoolDownCallBack()
{
	SkillButton::skillCoolDownCallBack();

}

