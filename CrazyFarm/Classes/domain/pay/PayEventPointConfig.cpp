#include "PayEventPointConfig.h"

PayEventPointConfig* PayEventPointConfig::_instance = NULL;

PayEventPointConfig::PayEventPointConfig(){
}

PayEventPointConfig* PayEventPointConfig::getInstance(){
	if (_instance == NULL){
		_instance = new PayEventPointConfig();
	}
	return _instance;
}

bool PayEventPointConfig::LoadConfig() {
	bool bRet = false;
	while (!bRet) {
		std::string filename;
		filename += "config/pay/eventPoint.json";
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
		version = doc["event_version"].GetInt();
		return true;
	}
	return true;
}




