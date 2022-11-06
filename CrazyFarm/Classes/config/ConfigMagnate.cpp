#include "config/ConfigMagnate.h"
#include "utill/JniFunUtill.h"
#include "ConfigDefine.h"
ConfigMagnate* ConfigMagnate::_instance = NULL;

ConfigMagnate::ConfigMagnate(){
}

ConfigMagnate* ConfigMagnate::getInstance(){
	if (_instance == NULL){
		_instance = new ConfigMagnate();
	}
	return _instance;
}

bool ConfigMagnate::LoadConfig() {
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
		filename += "config/config_magnate.json";
		rapidjson::Document doc;
		if (!FileUtils::getInstance()->isFileExist(filename))
		{
			break;
		}

		std::string data = FileUtils::getInstance()->getStringFromFile(filename);
		doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
		if (doc.HasParseError())
		{
			log("ConfigMagnate get json data err!");
			break;
		}
		rapidjson::Value& itemList = doc["item_list"];
		if (!itemList.IsArray())
		{
			log("ConfigMagnate The data is not json");
				break;
		}
		for (unsigned int i = 0; i < itemList.Size(); ++i) {
			const rapidjson::Value &val = itemList[i];

			MagnateItem magnateItem;
			magnateItem.type	= val["type"].GetInt();
            magnateItem.fire_time_from	= val["fire_time_from"].GetInt();
            magnateItem.fire_time_to = val["fire_time_to"].GetInt();
            
            magnateItems[i] = magnateItem;
		}
		
		return true;
	}
    return true;
}


MagnateItem ConfigMagnate::getDiamandMagnate() {
    for(int i=0; i<magnateItems.size();i++) {
        if(magnateItems[i].type == 1) {
            return magnateItems[i];
        }
    }
    MagnateItem item;
    item.type = 1;
    item.fire_time_from = 200;
    item.fire_time_from = 400;
    return item;
}

MagnateItem ConfigMagnate::getItemMagnate() {
    for(int i=0; i<magnateItems.size();i++) {
        if(magnateItems[i].type == 2) {
            return magnateItems[i];
        }
    }
    MagnateItem item;
    item.type = 2;
    item.fire_time_from = 300;
    item.fire_time_from = 700;
    return item;
}


