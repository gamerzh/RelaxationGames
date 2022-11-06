#include "config/ConfigFishCollisionOBB.h"
#include "utill/JniFunUtill.h"
#include "ConfigDefine.h"
ConfigFishCollisionOBB* ConfigFishCollisionOBB::_instance = NULL;

ConfigFishCollisionOBB::ConfigFishCollisionOBB(){

}

ConfigFishCollisionOBB* ConfigFishCollisionOBB::getInstance(){
	if (_instance == NULL){
		_instance = new ConfigFishCollisionOBB();
	}
	return _instance;
}

bool ConfigFishCollisionOBB::LoadConfig() {
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
		filename += "config/config_fishCollisionOBB.json";

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
			auto &figures = val["figures"];
			std::vector<ObbData> vec;
			for (unsigned int i = 0; i < figures.Size();i++)
			{
				auto &figure = figures[i];
				ObbData var;
				var.leftBottom = Vec2(figure["leftBottom"]["x"].GetDouble(), figure["leftBottom"]["y"].GetDouble());
				var.rightBottom = Vec2(figure["rightBottom"]["x"].GetDouble(), figure["rightBottom"]["y"].GetDouble());
				var.rightTop = Vec2(figure["rightTop"]["x"].GetDouble(), figure["rightTop"]["y"].GetDouble());
				var.leftTop = Vec2(figure["leftBottom"]["x"].GetDouble(), figure["leftTop"]["y"].GetDouble());
				vec.push_back(var);
			}
			uiidToOBBdatas[val["fish_UiId"].GetInt()] = vec;
		}
		
		return true;
	}
    return true;
}


std::vector<ObbData> ConfigFishCollisionOBB::getFishFOBBPoints(int uiId)
{
	return uiidToOBBdatas[uiId];
}
