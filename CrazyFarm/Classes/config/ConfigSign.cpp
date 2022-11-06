#include "config/ConfigSign.h"
#include "utill/dayUtil.h"
#define SIGNURL "http://114.119.39.150:1701/sign/config"
ConfigSign* ConfigSign::_instance = NULL;

ConfigSign::ConfigSign(){
}

ConfigSign* ConfigSign::getInstance(){
	if (_instance == NULL){
		_instance = new ConfigSign();
	}
	return _instance;
}

bool ConfigSign::LoadConfig() {
	HttpClientUtill::getInstance()->onGetHttp(SIGNURL, CC_CALLBACK_2(ConfigSign::onHttpRequestCompleted,this));
	return true;
}


void ConfigSign::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		return;
	}
	if (!response->isSucceed())
	{
		log("error buffer: %s", response->getErrorBuffer());
		bIsGetDataSuccess = false;
		today = SystemTime::getdaytime()->getFormatString();
		return;
	}

	long statusCode = response->getResponseCode();
	char statusString[64] = {};
	// dump data
	std::vector<char> *buffer = response->getResponseData();
	auto temp = std::string(buffer->begin(), buffer->end());
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
 
	today = doc["today"].GetString();
	auto &itemlists = doc["item_lists"];
	for (size_t i = 0; i < itemlists.Size(); i++)
	{
		auto &dayrewards = itemlists[i];
		SignRewardItem item;
		item.probability = dayrewards["probability"].GetInt();
		item.propNum = dayrewards["num"].GetInt();
		item.propID = dayrewards["item_id"].GetInt();
		rewards.push_back(item);
	}
	if (rewards.size() > 0)
	{
		bIsGetDataSuccess = true;
	}	
}


std::vector<SignRewardItem> ConfigSign::getRewards()
{
	return rewards;
}

int ConfigSign::CalculateTheDayToSign()
{
	if (!ConfigSign::getInstance()->isGetDataSuccess())
	{
		return -1;
	}
	auto str = UserDefault::getInstance()->getStringForKey(KEY_LASTSIGNDAY, "-1");
	auto sToday = ConfigSign::getInstance()->getToday();
	if (str == "-1")
	{
		return 1;
	}
	else if (str == sToday)
	{
		return 0;
	}
	SystemTime* lastDay = new SystemTime(str);
	SystemTime* toDay = new SystemTime(sToday);
	bool isContinue = SystemTime::isContinuousByAandB(lastDay, toDay);
	if (isContinue)
	{
		int dayCout = UserDefault::getInstance()->getIntegerForKey(KEY_SEQSIGNDAY, 0);
		return (dayCout + 1) > 7 ? 1 : dayCout + 1;
	}
	else
	{
		return 1;
	}



}