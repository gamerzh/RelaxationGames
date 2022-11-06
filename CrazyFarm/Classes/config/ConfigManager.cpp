#include "config/ConfigManager.h"

#include "config/ConfigItem.h"
#include "config/ConfigVipLevel.h"
#include "config/ConfigTurrent.h"
#include "config/ConfigFish.h"
#include "config/ConfigRoom.h"
#include "config/ConfigExp.h"
#include "config/ConfigVipTurrent.h"
#include "config/ConfigNormalTurrent.h"
#include "config/ConfigSkill.h"
#include "config/ConfigBankrupt.h"
#include "config/ConfigChest.h"
#include "config/ConfigMagnate.h"
#include "config/ConfigBonuspool.h"
#include "config/ConfigMomentEight.h"
#include "data/GameData.h"
#include "fish/FishGroupData.h"
#include "fish/FishRouteData.h"
#include "domain/mermaid/MermaidTask.h"
#include "moment/MonmetEightRoute.h"
#include "domain/gameConfig/gameConfig.h"
#include "config/ConfigBox.h"
#include "config/ConfigNewbieFishCatch.h"
#include "domain/pay/PayPointConfig.h"
#include "domain/pay/PayEventPointConfig.h"
#include "config/ConfigFishCollisionOBB.h"
ConfigManager* ConfigManager::_instance = NULL;

ConfigManager::ConfigManager(){
}

ConfigManager* ConfigManager::getInstance(){
	if (_instance == NULL){
		_instance = new ConfigManager();
	}
	return _instance;
}

void ConfigManager::LoadConfig() {
    //load json
	(ConfigExp::getInstance()->LoadConfig());

	PayEventPointConfig::getInstance()->LoadConfig();
    
    ConfigItem::getInstance()->LoadConfig();
    ConfigVipLevel::getInstance()->LoadConfig();
    ConfigTurrent::getInstance()->LoadConfig();
    ConfigFish::getInstance()->LoadConfig();
	PayPointConfig::getInstance()->LoadConfig();
    ConfigRoom::getInstance()->LoadConfig();
    ConfigVipTurrent::getInstance()->LoadConfig();
    ConfigNormalTurrent::getInstance()->LoadConfig();
    ConfigSkill::getInstance()->LoadConfig();
    ConfigBankrupt::getInstance()->LoadConfig();
    
    ConfigChest::getInstance()->LoadConfig();
    
	ConfigFishCollisionOBB::getInstance()->LoadConfig();
    ConfigMagnate::getInstance()->LoadConfig();
    
    ConfigBonuspool::getInstance()->LoadConfig();
    ConfigMomentEight::getInstance()->LoadConfig();
 
	GameData::getInstance()->setmermaidTask(MermaidTask::getNewMermaidTask());
	GameConfig::getInstance()->loadConfig();
	FishRouteData::getInstance()->loadConfig();
	FishGroupData::getInstance()->loadConfig();
	MonmetEightRoutedata::getInstance()->loadConfig();
	ConfigBox::getInstance()->LoadConfig();

	ConfigNewbieFishCatch::getInstance()->LoadConfig();
}


