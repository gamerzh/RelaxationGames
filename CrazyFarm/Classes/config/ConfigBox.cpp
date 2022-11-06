#include "config/ConfigBox.h"
#include "utill/JniFunUtill.h"
#include "ConfigDefine.h"
ConfigBox* ConfigBox::_instance = NULL;

ConfigBox::ConfigBox(){
}

ConfigBox* ConfigBox::getInstance(){
	if (_instance == NULL){
		_instance = new ConfigBox();
	}
	return _instance;
}

bool ConfigBox::LoadConfig() {
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
		filename += "config/config_box.json";
		rapidjson::Document doc;
		if (!FileUtils::getInstance()->isFileExist(filename))
		{
			break;
		}

		std::string data = FileUtils::getInstance()->getStringFromFile(filename);
		doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
		if (doc.HasParseError())
		{
			log("ConfigSkill get json data err!");
			break;
		}
		rapidjson::Value& itemList = doc["item_list"];
		if (!itemList.IsArray())
		{
			log("ConfigSkill The data is not json");
				break;
		}
		for (unsigned int i = 0; i < itemList.Size(); ++i) {
			const rapidjson::Value &val = itemList[i];
            
			BoxConfigInfo var;
			var.item_id = val["item_id"].GetInt();
			var.catch_fish_per = val["catch_fish_per"].GetDouble();
			var.money = val["money"].GetInt();
            
			m_BoxConfigInfos.push_back(var);
		}
		
		return true;
	}
    return true;
}

BoxConfigInfo ConfigBox::getBoxConfigInfoByItemId(int itemId) {
   for (auto var:m_BoxConfigInfos)
   {
	   if (var.item_id == itemId)
	   {
		   return var;
	   }
   }
   //lack±£»¤
   return BoxConfigInfo();
}



