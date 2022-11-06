#include "config/ConfigBonuspool.h"
#include "utill/JniFunUtill.h"
#include "ConfigDefine.h"
ConfigBonuspool* ConfigBonuspool::_instance = NULL;

ConfigBonuspool::ConfigBonuspool(){
}

ConfigBonuspool* ConfigBonuspool::getInstance(){
	if (_instance == NULL){
		_instance = new ConfigBonuspool();
	}
	return _instance;
}

bool ConfigBonuspool::LoadConfig() {
    
	bool bRet = false;
	while (!bRet) {

	std::string filename;			
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	if (ISDEBUGCONFIG)
	{
		filename += JniFunUtill::getInstance()->getSDcardpath();
		filename += "/CrazyFarm/";
	}
#endif
		filename += "config/config_bonuspool.json";
		rapidjson::Document doc;
		if (!FileUtils::getInstance()->isFileExist(filename))
		{
			break;
		}

		std::string data = FileUtils::getInstance()->getStringFromFile(filename);
		doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
		if (doc.HasParseError())
		{
			log("ConfigBonuspool get json data err!");
			break;
		}
        
        bonuspool.allow_draw_fish_counts = doc["allow_draw_fish_counts"].GetInt();
		bonuspool.fistRewardItemid = doc["fistLuckyDraw"]["item_id"].GetInt();
		rapidjson::Value& itemList = doc["item_list"];
		if (!itemList.IsArray())
		{
			log("ConfigBonuspool The data is not json");
				break;
		}
        
		for (unsigned int i = 0; i < itemList.Size(); i++) {
            BonuspoolItem bonuspoolItem;
            const rapidjson::Value &bonuspoolItemConfig = itemList[i];
            bonuspoolItem.start_coins = bonuspoolItemConfig["start_coins"].GetInt();
            bonuspoolItem.end_coins = bonuspoolItemConfig["end_coins"].GetInt();
            
            const rapidjson::Value &rewardList = bonuspoolItemConfig["reward_list"];
			
            
            for (unsigned int j = 0; j < rewardList.Size(); j++) {
                const rapidjson::Value &val = rewardList[j];
                BonuspoolRewardItem bonuspoolRewardItem;
                bonuspoolRewardItem.item_id = val["item_id"].GetInt();
                bonuspoolRewardItem.num = val["num"].GetInt();
                bonuspoolRewardItem.per = val["per"].GetDouble();
                
                bonuspoolItem.reward_list.push_back(bonuspoolRewardItem);
            }
            bonuspool.bonuspoolItems.push_back(bonuspoolItem);
            
		}
		
		return true;
	}
    return true;
}

Bonuspool ConfigBonuspool::getBonuspool() {
	return bonuspool;
}

