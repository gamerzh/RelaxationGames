#include "FishArrange.h"
#include "config/ConfigFishCollisionOBB.h"
void FishArrange::initFish(int fishID){
	auto fishdata = ConfigFish::getInstance()->getFish(fishID);
	fishGold = getintRandonNumByAtoB(fishdata.baseRewardStart, fishdata.baseRewardEnd);
	this->grabProbability = fishdata.probability;
	this->fishID = fishID;
	this->speed = getRandValueInVec(fishdata.move_speeds);
	this->experience = getFishExperienceByID(fishID);
	this->BonusPoorGold = fishdata.bonus_pool_reward;
	setFishType(getFishTypeByID(fishID));
	setuiId(fishdata.uiId);
	initFishAnim(fishdata.uiId);
	rewards = fishdata.rewards;
	LogEventFish::getInstance()->addFishCreateTimes(fishID);
}
void FishArrange::addShader()
{

}
void FishArrange::onDead()
{
	onFreezeResume();
	stopAllActions();
	runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create(CC_CALLBACK_0(Fish::removeself, this)), nullptr));
}

void FishArrange::pushBackFigureVec(int uiid, Point pos)
{
	auto data = ConfigFishCollisionOBB::getInstance()->getFishFOBBPoints(uiid);
	for (auto var:data)
	{
		ObbData val;
		val.leftBottom = var.leftBottom + pos;
		val.rightBottom = var.rightBottom + pos;
		val.leftTop = var.leftTop + pos;
		val.rightTop = var.rightTop + pos;
		obbdatas.push_back(val);
	}
}

void FishArrange::onHeart()
{
	for (auto child : fishes)
	{
		auto ac = child->getActionByTag(50);
		if (ac)
		{
			child->stopAllActionsByTag(50);
		}
		auto action = Sequence::create(
			CallFunc::create([=]{child->setColor(Color3B(135,105,80)); }),
			DelayTime::create(0.3f),
			CallFunc::create([=]{child->setColor(Color3B::WHITE); }),
			nullptr);
		action->setTag(50);
		child->runAction(action);
	}
}


void FishArrange::onFreeze()
{
	for (auto child : fishes)
	{
		child->pause();
	}
}
void FishArrange::onFreezeResume()
{
	for (auto child : fishes)
	{
		child->resume();
	}
}
std::vector<Rect>  FishArrange::getAABBBoxs()
{
	std::vector<Rect> vec;
	for (auto child:fishes)
	{
		auto box = child->getBoundingBox();
		auto orgin = convertToWorldSpace(box.origin);
		box.setRect(orgin.x, orgin.y, box.size.width, box.size.height);
			vec.push_back(box);
	}
	return vec;
}