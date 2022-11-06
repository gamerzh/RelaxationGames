#include "PayPointConfig.h"

PayPointConfig* PayPointConfig::_instance = NULL;

PayPointConfig::PayPointConfig(){
}

PayPointConfig* PayPointConfig::getInstance(){
	if (_instance == NULL){
		_instance = new PayPointConfig();
	}
	return _instance;
}

bool PayPointConfig::LoadConfig() {
	bool bRet = false;
	while (!bRet) {
		std::string filename;
		filename += "config/pay/paypoint.json";
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
		rapidjson::Value& itemList = doc["paypoint"];
		if (!itemList.IsArray())
		{
			log("ConfigSkill The data is not json");
			break;
		}
		for (unsigned int i = 0; i < itemList.Size(); ++i) {
			const rapidjson::Value &val = itemList[i];

			PayPointInfo info;
			info.paypoint_id = val["id"].GetInt();
			info.price = val["price"].GetInt();
			info.pay_point_desc = val["desc"].GetString();
			auto &payitems = val["describe"];
			for (unsigned int i = 0; i < payitems.Size();++i)
			{
				PayItem item;
				item.ItemID = payitems[i]["propid"].GetInt();
				item.ItemNum = payitems[i]["propnum"].GetInt();
				info.items.push_back(item);
			}
			payPointInfos.push_back(info);
		}
		payversion = doc["pay_version"].GetInt();
		return true;
	}
	return true;
}

PayPointInfo PayPointConfig::getPayPointInfoById(int id) {
	for (int i = 0; i < payPointInfos.size(); i++) {
		if (payPointInfos[i].paypoint_id == id) {
			return payPointInfos[i];
		}
	}
	return PayPointInfo();
}



