#include "config/ConfigNewbieFishCatch.h"
#include "ConfigDefine.h"
#include "utill/JniFunUtill.h"
using namespace cocos2d;

ConfigNewbieFishCatch* ConfigNewbieFishCatch::_instance = NULL;

ConfigNewbieFishCatch::ConfigNewbieFishCatch(){
}

ConfigNewbieFishCatch* ConfigNewbieFishCatch::getInstance(){
    if(_instance == NULL){
		_instance = new ConfigNewbieFishCatch();
    }
    return _instance;
}

bool ConfigNewbieFishCatch::LoadConfig() {
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
		filename += "config/config_newbieFishCatch.json";
		
        rapidjson::Document doc;
        if (!FileUtils::getInstance()->isFileExist(filename))
		{
			log("kkkkkkkkkkkkkkkkkkkkkkkk%s", filename.c_str());
            break;
        }
        
        std::string data = FileUtils::getInstance()->getStringFromFile(filename);
        doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
        if (doc.HasParseError())
        {
            log("ConfigExp get json data err!");
            break;
        }
        rapidjson::Value& itemList = doc["item_list"];
        if (!itemList.IsArray())
        {
            log("ConfigExp The data is not json");
            break;
        }
        for (unsigned int i = 0; i < itemList.Size(); ++i) {
            
			const rapidjson::Value &val = itemList[i];
			const rapidjson::Value  &catchpers = val["catch_pers"];
			std::vector<NewbieFishCatch> vec;
			for (unsigned int j = 0; j < catchpers.Size(); j++)
			{
				const rapidjson::Value &var = catchpers[j];
				NewbieFishCatch nb;
				nb.fishid = var["fish_id"].GetInt();
				nb.per = var["catch_per"].GetDouble();
				vec.push_back(nb);

			}
			levelToNewbieFishCatchs[val["level_id"].GetInt()] = vec;
        }
        
        return true;
    }
    return true;
}


float ConfigNewbieFishCatch::getperByLevelAndFishID(int level, int fishid)
{
	if (level>levelToNewbieFishCatchs.size())
	{
		return -1;
	}
	auto vec = levelToNewbieFishCatchs[level];
	for (auto var : vec)
	{
		if (var.fishid == fishid)
		{
			return  var.per;
		}
	}
	return -1;	
}