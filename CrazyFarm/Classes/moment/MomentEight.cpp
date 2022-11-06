#include "moment/MomentEight.h"
#include "utill/FunUtil.h"

void MomentEight::init(float FFOneTime)
{
	updata(FFOneTime);
	
	///////////////////////////TODO:时间的问题
	//float fps = Director::getInstance()->getAnimationInterval();
	//for (float k = FFOneTime - 5.0; k < FFOneTime; k += fps)
	//{
	//	/*updata(fps);*/
	//	Director::getInstance()->getScheduler()->update(fps);
	//}
}
void MomentEight::clearFish()
{
	FishManage::getInstance()->cleanVector();///暂时处理先清空所有的鱼
}
void MomentEight::setMomentEightType(int type)
{
	life_time = ConfigMomentEight::getInstance()->getLifeTime(type);
	momentEightItemType = ConfigMomentEight::getInstance()->getMomentEightItemBytype(type);
	for (auto &item : momentEightItemType)
	{
		item.fTempTime = getRandonNumByAtoB(item.interval_time_start, item.interval_time_end);
	}
	
	
	
}

bool MomentEight::updata(float dt)
{
	nNowTime += dt;
	if (nNowTime > life_time)
	{
		return true;
	}
	for (auto &item : momentEightItemType)
	{
		item.fTempTime -= dt;
		if (item.fTempTime <= 0)
		{
			item.fTempTime = getRandonNumByAtoB(item.interval_time_start, item.interval_time_end);
			for (auto &fishitem:item.momentEightItemFishs)
			{
				fishitem.wait_time = getRandonNumByAtoB(fishitem.fish_wait_time_start, fishitem.fish_wait_time_end);
				FishManage::getInstance()->addMomentEightItemFishs(fishitem);
					
			}

		}
	}
	return false;
}
