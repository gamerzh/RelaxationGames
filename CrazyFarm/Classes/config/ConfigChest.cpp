#include "config/ConfigChest.h"
#include "utill/JniFunUtill.h"
#include "ConfigDefine.h"
ConfigChest* ConfigChest::_instance = NULL;

ConfigChest::ConfigChest(){
}

ConfigChest* ConfigChest::getInstance(){
	if (_instance == NULL){
		_instance = new ConfigChest();
	}
	return _instance;
}

bool ConfigChest::LoadConfig() {
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
		filename += "config/config_chest.json";
		rapidjson::Document doc;
		if (!FileUtils::getInstance()->isFileExist(filename))
		{
			break;
		}

		std::string data = FileUtils::getInstance()->getStringFromFile(filename);
		doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
		if (doc.HasParseError())
		{
			log("ConfigChest get json data err!");
			break;
		}
		rapidjson::Value& itemList = doc["item_list"];
		if (!itemList.IsArray())
		{
			log("ConfigChest The data is not json");
				break;
		}
		for (unsigned int i = 0; i < itemList.Size(); ++i) {
			const rapidjson::Value &val = itemList[i];
            
			Chest chest;
			chest.chest_level	= val["chest_level"].GetInt();
            chest.chest_name	= val["chest_name"].GetString();
            chest.item_id = val["item_id"].GetInt();
            chest.allow_presented = val["allow_presented"].GetBool();
            chest.catch_per = val["catch_per"].GetDouble();
            chest.have_get_reward = val["have_get_reward"].GetInt();
            chests[i] = chest;
		}
		
		return true;
	}
    return true;
}


Chest ConfigChest::getChestByItemId(int itemId) {
    for(int i=0; i< chests.size();i++) {
        if(chests[i].item_id == itemId) {
            return chests[i];
        }
    }
    Chest chest;
    chest.chest_level = 0;
    chest.catch_per = 1;
    return chest;
}

Chest ConfigChest::getChestByLevel(int chestLevel) {
    for(int i=0; i< chests.size();i++) {
        if(chests[i].chest_level == chestLevel) {
            return chests[i];
        }
    }
    Chest chest;
    chest.chest_level = 0;
    chest.catch_per = 1;
    return chest;
}


