#include "moment/momentFishGroup/MomentIntervalCreate.h"
#include "fish/FishManage.h"
#include "domain/game/GameManage.h"
bool MomentIntervalCreate::updata(float dt)
{
	nNowTime += dt;
	auto fishcount = FishManage::getInstance()->getAllFishInPoolCount();
	if (fishcount < fishMinSize&&nNowTime>50)//50 == �㳲ʱ�� todo:��������
	{
		
		GameManage::getInstance()->getGameLayer()->onClearFishFinish();
		return true;
	}

	return false;
}

void MomentIntervalCreate::init(float FFOneTime)
{
	initData();
	Audio::getInstance()->playBGM(FISHFLOCKBGM);
	FishManage::getInstance()->createFishGroup(m_groupTag);
}

void MomentIntervalCreate::initData()
{
	nNowTime = 0;
}