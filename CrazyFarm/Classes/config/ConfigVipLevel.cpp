#include "config/ConfigVipLevel.h"
#include "utill/JniFunUtill.h"
ConfigVipLevel* ConfigVipLevel::_instance = NULL;

ConfigVipLevel::ConfigVipLevel(){
}

ConfigVipLevel* ConfigVipLevel::getInstance(){
	if (_instance == NULL){
		_instance = new ConfigVipLevel();
	}
	return _instance;
}

bool ConfigVipLevel::LoadConfig() {
	bool bRet = false;
	while (!bRet) {
std::string filename;	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID&&ISDEBUGCONFIG) 
filename += JniFunUtill::getInstance()->getSDcardpath();
		filename += "/CrazyFarm/";
	#endif
		filename += "config/config_user_viplevel.json";

		rapidjson::Document doc;
		if (!FileUtils::getInstance()->isFileExist(filename))
		{
			break;
		}

		std::string data = FileUtils::getInstance()->getStringFromFile(filename);
		doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
		if (doc.HasParseError())
		{
			log("ConfigVipLevel get json data err!");
			break;
		}
		rapidjson::Value& itemList = doc["item_list"];
		if (!itemList.IsArray())
		{
			log("ConfigVipLevel The data is not json");
				break;
		}
		for (unsigned int i = 0; i < itemList.Size(); ++i) {

			const rapidjson::Value &val = itemList[i];
			VipLevel viplevel;
			viplevel.vip_level	= val["vip_level"].GetInt();
            viplevel.charge_money = val["charge_money"].GetInt();
            viplevel.title = val["title"].GetString();
            viplevel.desc_title = val["desc_title"].GetString();
            viplevel.desc_content = val["desc_content"].GetString();
            viplevel.vip_turrent_id = val["vip_turrent_id"].GetDouble();   // VIP鐐甀D
            viplevel.double_login_reward = val["double_login_reward"].GetDouble();  // 鐧婚檰濂栧姳缈诲�嶇郴鎿�
            viplevel.pay_reward = val["pay_reward"].GetDouble();          // 鍏呭�煎鍔辩櫨鍒嗘瘮
            viplevel.kill_per_add = val["kill_per_add"].GetDouble();           // 鍑绘潃姒傜巼绯绘暟
            viplevel.send_coins_over = val["send_coins_over"].GetInt();         // 閲戝竵琛ヨ冻閲戦
            viplevel.send_coins_over_day_time = val["send_coins_over_day_time"].GetInt(); // 姣忔棩閲戝竵琛ヨ冻娆℃暟

			vipLevels[i] = viplevel;
		}
		
		return true;
	}
    return true;
}

std::map<int, VipLevel> ConfigVipLevel::getVipLevels() {
    return vipLevels;
}

VipLevel ConfigVipLevel::getVipLevel(int level) {
	if (level>9)
	{
		level = 9;
	}
    return vipLevels[level];
}

int ConfigVipLevel::getLevel(int chargeMoney) {
    if(chargeMoney <= 0) {
        return 0;
    }
    for( auto item = vipLevels.rbegin(); item != vipLevels.rend(); item++ ) {
        if(chargeMoney >= item->second.charge_money) {
            return item->second.vip_level;
        }
    }
}
