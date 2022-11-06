#include "config/ConfigFish.h"
#include "utill/JniFunUtill.h"
#include "ConfigDefine.h"
ConfigFish* ConfigFish::_instance = NULL;

ConfigFish::ConfigFish(){
	initFishDropCoinData();
}

ConfigFish* ConfigFish::getInstance(){
	if (_instance == NULL){
		_instance = new ConfigFish();
	}
	return _instance;
}

bool ConfigFish::LoadConfig() {
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
		filename += "config/config_fish.json";
		rapidjson::Document doc;
		if (!FileUtils::getInstance()->isFileExist(filename))
		{
			break;
		}

		std::string data = FileUtils::getInstance()->getStringFromFile(filename);
		doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
		if (doc.HasParseError())
		{
			log("ConfigFish get json data err!");
			break;
		}
		rapidjson::Value& itemList = doc["item_list"];
		if (!itemList.IsArray())
		{
			log("ConfigFish The data is not json");
				break;
		}
		for (unsigned int i = 0; i < itemList.Size(); ++i) {

			const rapidjson::Value &val = itemList[i];
            
			FishData fish;
			fish.fishId	= val["fish_id"].GetInt();
            fish.fishID = val["fish_type"].GetInt();
			for (unsigned int j = 0; j < val["move_speed"].Size();j++)
			{
				fish.move_speeds.push_back(val["move_speed"][j].GetInt()) ;
			}
            
            fish.probability = (val["probability"].GetDouble());

            fish.baseRewardStart = val["baseReward"]["start"].GetInt();
			fish.baseRewardEnd = val["baseReward"]["end"].GetInt();
	

            fish.maxHitTime = val["maxHitTime"].GetInt();
            fish.protectedTime = val["protectedTime"].GetInt();
            fish.uiId = val["ui_id"].GetInt();
            fish.catch_ui_type = val["catch_ui_type"].GetInt();


            fish.exp = val["exp"].GetInt();
            fish.bonus_pool_reward = val["bonus_pool_reward"].GetInt();
            fish.be_hit_logic = val["be_hit_logic"].GetInt();
			
			auto &rewardVal = val["reward_list"];
			if (rewardVal.IsArray())
			{
				for (unsigned int k = 0; k < rewardVal.Size();k++)
				{
					FishReward data;
					data.item_id = rewardVal[k]["item_id"].GetInt();
					data.num = rewardVal[k]["num"].GetInt();
					fish.rewards.push_back(data);
				}
			}
			fishes[fish.fishId] = fish;


		}
		
		return true;
	}
    return true;
}


std::map<int, FishData> ConfigFish::getFishes() {
    return fishes;
}

FishData ConfigFish::getFish(int fishId) {
    return fishes[fishId];
}



void ConfigFish::initFishDropCoinData()
{
	FishDropCoinDatas[1] = FishDropCoin("aniSilver", 1);
	FishDropCoinDatas[2] = FishDropCoin("aniSilver", 2);
	FishDropCoinDatas[3] = FishDropCoin("aniSilver", 3);
	FishDropCoinDatas[4] = FishDropCoin("aniSilver", 4);
	FishDropCoinDatas[5] = FishDropCoin("aniSilver", 5);
	FishDropCoinDatas[6] = FishDropCoin("aniSilver", 6);
	FishDropCoinDatas[7] = FishDropCoin("aniSilver", 8);
	FishDropCoinDatas[8] = FishDropCoin("aniGold", 10);
	FishDropCoinDatas[9] = FishDropCoin("aniGold", 1);
	FishDropCoinDatas[10] = FishDropCoin("aniGold", 2);
	FishDropCoinDatas[30] = FishDropCoin("aniGold",3);
	FishDropCoinDatas[31] = FishDropCoin("aniGold", 4);
	FishDropCoinDatas[32] = FishDropCoin("aniGold", 5);
	FishDropCoinDatas[33] = FishDropCoin("aniGold", 6);
	FishDropCoinDatas[34] = FishDropCoin("aniGold", 8);
	FishDropCoinDatas[35] = FishDropCoin("aniGold", 10);
	FishDropCoinDatas[36] = FishDropCoin("aniGold", 12);
	FishDropCoinDatas[37] = FishDropCoin("aniGold", 14);
	FishDropCoinDatas[40] = FishDropCoin("aniGold", 16);
	FishDropCoinDatas[41] = FishDropCoin("aniGold", 18);
	FishDropCoinDatas[42] = FishDropCoin("aniGold", 20);
	FishDropCoinDatas[43] = FishDropCoin("aniGold", 20);
	FishDropCoinDatas[44] = FishDropCoin("aniGold", 20);
	FishDropCoinDatas[50] = FishDropCoin("aniGold", 20);
	FishDropCoinDatas[51] = FishDropCoin("aniGold", 20);
	FishDropCoinDatas[52] = FishDropCoin("aniGold", 20);

	FishDropCoinDatas[101] = FishDropCoin("aniGold", 10);
	FishDropCoinDatas[102] = FishDropCoin("aniGold", 10);
	FishDropCoinDatas[103] = FishDropCoin("aniGold", 10);
	FishDropCoinDatas[104] = FishDropCoin("aniGold", 10);
	FishDropCoinDatas[60] = FishDropCoin("aniGold", 10);

}

FishDropCoin ConfigFish::getFishDropCoinData(int uiid)
{
	return FishDropCoinDatas[uiid];
}
