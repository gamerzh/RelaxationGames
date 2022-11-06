#include "SkillBombButton.h"
#include "domain/bag/BagManager.h"
#include "data/GameData.h"
SkillBombButton* SkillBombButton::createSkillBombButton()
{
	SkillConfigInfo info = ConfigSkill::getInstance()->getskillConfigInfoBySkillId(4);
	SkillBombButton* skillButton = new SkillBombButton();
	if (skillButton && skillButton->init(4, "skillStencil.png", "item_1006.png", "item_1006.png"))
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
void SkillBombButton::skillClickCallBack(Ref* obj)
{
	if (skillManager::getInstance()->isUseSkillNow(4))
	{
		return;
	}
	useSkill();
}

/** ������ȴ��ɻص� */
void SkillBombButton::skillCoolDownCallBack()
{
	SkillButton::skillCoolDownCallBack();
	setEnable(true);

}

