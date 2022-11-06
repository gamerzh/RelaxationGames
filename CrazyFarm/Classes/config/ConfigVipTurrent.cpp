#include "config/ConfigVipTurrent.h"
#include "domain/user/User.h"
#include "ConfigDefine.h"
#include "utill/JniFunUtill.h"
ConfigVipTurrent* ConfigVipTurrent::_instance = NULL;

ConfigVipTurrent::ConfigVipTurrent(){
}

ConfigVipTurrent* ConfigVipTurrent::getInstance(){
	if (_instance == NULL){
		_instance = new ConfigVipTurrent();
	}
	return _instance;
}

bool ConfigVipTurrent::LoadConfig() {
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
		filename += "config/config_vip_turrent.json";
		rapidjson::Document doc;
		if (!FileUtils::getInstance()->isFileExist(filename))
		{
			break;
		}

		std::string data = FileUtils::getInstance()->getStringFromFile(filename);
		doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
		if (doc.HasParseError())
		{
			log("ConfigVipTurrent get json data err!");
			break;
		}
		rapidjson::Value& itemList = doc["item_list"];
		if (!itemList.IsArray())
		{
			log("ConfigVipTurrent The data is not json");
				break;
		}
		for (unsigned int i = 0; i < itemList.Size(); ++i) {

			const rapidjson::Value &val = itemList[i];
			VipTurrent vipTurrent;
			vipTurrent.vip_turrent_id	= val["vip_turrent_id"].GetInt();
            vipTurrent.turrent_ui_id	= val["turrent_ui_id"].GetInt();
            vipTurrent.net_per = val["net_per"].GetDouble();
            vipTurrent.catch_per = val["catch_per"].GetDouble();
            vipTurrent.ui_type = val["ui_type"].GetInt();
            vipTurrent.net_type = val["net_type"].GetInt();
            

			vipTurrents[vipTurrent.vip_turrent_id] = vipTurrent;
		}
		
		return true;
	}
    return true;
}

std::map<int, VipTurrent> ConfigVipTurrent::getVipTurrents() {
    return vipTurrents;
}

VipTurrent ConfigVipTurrent::getVipTurrent(int level) {
    VipTurrent vipTurrent;
    if(level <= 0) {
        return vipTurrent;
    }
    if(level >= vipTurrents.size()) {
        return vipTurrent;
    }
    return vipTurrents[level];
}



std::vector<VipTurrent>  ConfigVipTurrent::getUnUpgradeTurrents()
{
	std::vector<VipTurrent> vec;
	auto vipLv =User::getInstance()->getVipLevel();
	for (int i = 1; i <= 9; i++)
	{
		if (i>vipLv)
		{
			vec.push_back(vipTurrents[i]);
		}
	}
	return vec;
}