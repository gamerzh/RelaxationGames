#include "domain/gameConfig/gameConfig.h"
#include "utill/JniFunUtill.h"

#include "config/ConfigDefine.h"



GameConfig* GameConfig::_instance = NULL;

GameConfig::GameConfig(){
 ;
}

bool GameConfig::loadConfig(){
	bool bRet = false;
	while (!bRet) {
		std::string filename;
		filename = FileUtils::getInstance()->getWritablePath() + "config_game.json";
		if (!FileUtils::getInstance()->isFileExist(filename))
		{
			filename = "config/config_game.json";
			if (!FileUtils::getInstance()->isFileExist(filename))
			{
				break;
			}
		}
		rapidjson::Document doc;
		if (!FileUtils::getInstance()->isFileExist(filename))
		{
			break;
		}

		std::string data = FileUtils::getInstance()->getStringFromFile(filename);
		doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
		if (doc.HasParseError())
		{
			log("ConfigRoom get json data err!");
			break;
		}
		rapidjson::Value& itemList = doc["shootList"];
		shootData.shootInterval = itemList["shootInterval"].GetDouble();
		shootData.shootSpeed = itemList["bulletSpeed"].GetInt();
		configVersion = doc["version"].GetInt();
		bRet = true;
	}
	loadConfigFromServer();
	return bRet;

}

void GameConfig::loadConfigFromServer()
{
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_BASECONFIG);
	auto requstData = String::createWithFormat("config_version=%d", configVersion);
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(GameConfig::onHttpRequestCompletedForLoadConfig, this));
}


GameConfig* GameConfig::getInstance(){
    if(_instance == NULL){
		_instance = new GameConfig();
    }
    return _instance;
}


void GameConfig::onHttpRequestCompletedForLoadConfig(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		return;
	}
	if (!response->isSucceed())
	{
		return;
	}
	long statusCode = response->getResponseCode();
	// dump data
	std::vector<char> *buffer = response->getResponseData();
	auto temp = std::string(buffer->begin(), buffer->end());
	log("http back register info  info: %s", temp.c_str());
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
	if (doc.HasParseError())
	{
		log("get json data err!");;
	}
	int code = doc["errorcode"].GetInt();
	if (code == 0)
	{
		shootData.shootInterval = doc["bullet_interval"].GetDouble();
		shootData.shootSpeed = doc["bullet_speed"].GetDouble();
		catch_fish_per_coef = doc["catch_per"].GetDouble();
		configVersion = doc["config_version"].GetInt();
		WriteConfigToLocal();
	}
}


void GameConfig::WriteConfigToLocal()
{
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	document.AddMember("version", configVersion, allocator);
	document.AddMember("catch_fish_per_coef", catch_fish_per_coef, allocator);
	rapidjson::Value object(rapidjson::kObjectType);
	object.AddMember("shootInterval", shootData.shootInterval, allocator);
	object.AddMember("bulletSpeed", shootData.shootSpeed, allocator);
	document.AddMember("shootList", object, allocator);
	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	std::string result = buffer.GetString();


	auto path = FileUtils::getInstance()->getWritablePath();
	path.append("config_game.json");
	FILE* file = fopen(path.c_str(), "wb");
	if (file)
	{
		fputs(buffer.GetString(), file);
		fclose(file);
	}
	CCLOG("%s", buffer.GetString());
}