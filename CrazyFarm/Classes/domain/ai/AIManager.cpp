#include "domain/ai/AIManager.h"
#include "data/GameData.h"
#include "domain/game/GameManage.h"
#include "utill/FunUtil.h"
#include "AIJun.h"
AIManager* AIManager::_instance = NULL;

AIManager::AIManager(){
    this->init();
}

void AIManager::init(){
	setNowCreateGoldFish(1);
}

AIManager* AIManager::getInstance(){
    if(_instance == NULL){
        _instance = new AIManager();
    }
    return _instance;
}

AI* AIManager::getAI( int maxTurrentLevel) {
	
	
    int who = rand()%100;
    if(who < 20) {
		AI* molo = new AIMolo();
        if(maxTurrentLevel > 0) {
            molo->setMaxTurrentLevel(maxTurrentLevel);
        }else {
            molo->setMaxTurrentLevel(1);
        }
        
        molo->setReqSteps(0.2f);
        return molo;
    }
	else if (who<60)
	{
		AI*hu = new AIHu();
		hu->setMaxTurrentLevel(maxTurrentLevel);
		hu->setReqSteps(0.2f);
		return hu;
	}
	else
    {
		AI*jun = new AIJun();
		jun->setMaxTurrentLevel(maxTurrentLevel);
		jun->setReqSteps(0.2f);
		return jun;
    }
}

bool AIManager::allowAiFire() {
    return aiFire;
}

void AIManager::setAiFire(bool allow) {
     aiFire = allow;
}

void  AIManager::MainUpdata(float dt)
{
	
}

void AIManager::addCreateGoldFish()
{
	auto turrets = GameManage::getInstance()->getGameLayer()->GetOtherTurret();
	auto turret = getRandValueInVector(turrets);
	nNowCreateGoldFish++;
	auto roomid = GameData::getInstance()->getRoomID();
	switch (roomid)
	{
	case 1:
		if (nNowCreateGoldFish % 10 ==0)
		{
			///some one use lock
		}
		break;
	case 2:
	case 3:
	case 4:
		if (nNowCreateGoldFish % 18 == 0)
		{
			skillManager::getInstance()->robotUseSkillFreeze(turret);
			break;
		}
		if (nNowCreateGoldFish % 6 == 0)
		{
			///some one use lock
			break;
		}
		if (nNowCreateGoldFish % 60 == 0)
		{
			skillManager::getInstance()->useSkillSummon(turret);
			break;
		}
		break;
	default:
		break;
	}
}