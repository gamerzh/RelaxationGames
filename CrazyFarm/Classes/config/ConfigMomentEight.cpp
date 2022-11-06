#include "config/ConfigMomentEight.h"
#include "utill/JniFunUtill.h"
#include "ConfigDefine.h"
ConfigMomentEight* ConfigMomentEight::_instance = NULL;

ConfigMomentEight::ConfigMomentEight(){
}

ConfigMomentEight* ConfigMomentEight::getInstance(){
	if (_instance == NULL){
		_instance = new ConfigMomentEight();
	}
	return _instance;
}

bool ConfigMomentEight::LoadConfig() {
	int type = 1;
	do 
	{
		if (!LoadConfigByType(type))
		{
			CCLOG(" load %d MommentEightConfigs", type - 1);
			break;
		}
		else
		{
			type++;
		}
	} while (1);
	return true;
}

bool ConfigMomentEight::LoadConfigByType(int type)
{
		std::string filename;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		if (ISDEBUGCONFIG)
		{
			filename += JniFunUtill::getInstance()->getSDcardpath();
			filename += "/CrazyFarm/";
		}
#endif
		auto strFileName = String::createWithFormat("config/config_eight_type%d.json", type);
		filename += strFileName->getCString();
		rapidjson::Document doc;
		if (!FileUtils::getInstance()->isFileExist(filename))
		{
			return false;
		}

		std::string data = FileUtils::getInstance()->getStringFromFile(filename);
		doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
		if (doc.HasParseError())
		{
			log("ConfigMomentEight get json data err!");
			return false;
		}
		std::vector<MomentEightItem> items;
		lifeTimeForType[type] = doc["life_time"].GetDouble();
		auto &launching_points = doc["launching_points"];
		for (unsigned int i = 0; i < launching_points.Size(); i++)
		{
			MomentEightItem item;
			item.interval_time_start = launching_points[i]["interval_time_start"].GetDouble();
			item.interval_time_end = launching_points[i]["interval_time_end"].GetDouble();
			rapidjson::Value& itemList = launching_points[i]["item_list"];
			if (!itemList.IsArray())
			{
				log("ConfigMomentEight The data is not json");
				return false;
			}
			for (unsigned int i = 0; i < itemList.Size(); ++i) {
				const rapidjson::Value &val = itemList[i];

				MomentEightItemFishs itemfishes;
				itemfishes.fish_startcount = val["count_start"].GetInt();
				itemfishes.fish_endcount = val["count_end"].GetInt();
				itemfishes.fish_wait_time_start = val["wait_time_start"].GetDouble();
				itemfishes.fish_wait_time_end = val["wait_time_end"].GetDouble();
				if (val["fishRoute"].IsArray())
				{
					auto &fishroutes = val["fishRoute"];
					for (unsigned int j = 0; j < fishroutes.Size(); j++)
					{
						itemfishes.fishRoutes.push_back(fishroutes[j].GetInt());
					}

				}
				auto &fishids = val["fish_id"];
				for (unsigned int j = 0; j < fishids.Size();j++)
				{
					itemfishes.fish_ids.push_back(fishids[j].GetInt());
				}
				
				item.momentEightItemFishs.push_back(itemfishes);
			}
			items.push_back(item);
		}
		momentEightItemTypes[type] = items;
		return true;
}


std::map<int, std::vector<MomentEightItem>> ConfigMomentEight::getMomentEightItemTypes() {
	return momentEightItemTypes;
}