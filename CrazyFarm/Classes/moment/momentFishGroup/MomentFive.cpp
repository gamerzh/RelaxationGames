#include "MomentFive.h"
#include "fish/FishGroupData.h"
#include "domain/game/GameManage.h"
void MomentFive::init(float FFOneTime)
{
	datas.push_back(MomentFiveData(8, 1,Vec2(-270,342)));
	datas.push_back(MomentFiveData(9, 5, Vec2(-270, 200)));
	datas.push_back(MomentFiveData(7, 9, Vec2(-270, 342)));
	datas.push_back(MomentFiveData(6, 13, Vec2(-270, 200)));
	datas.push_back(MomentFiveData(4, 17, Vec2(-270, 342)));
	
}

bool MomentFive::updata(float dt)
{
	nNowTime += dt;
	if (datas.size()<=0&&nNowTime>(50))
	{
		GameManage::getInstance()->getGameLayer()->onClearFishFinish();
		return true;
	}
	for (auto iter = datas.begin(); iter != datas.end();)
	{
		if (iter->startTime<nNowTime)
		{
			FishManage::getInstance()->createCycleFish(20, 165, iter->fishID, iter->pos, Vec2(1500, 0), 25);
			iter = datas.erase(iter);

		}
		else
		{
			return false;
		}
	}
	return false;

}