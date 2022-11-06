#pragma once

#include "cocos2d.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "server/HttpClientUtill.h"
USING_NS_CC;



struct SignRewardItem 
{
	int propID;
	int propNum;
	int probability;
};


class ConfigSign {
    
public:
	ConfigSign();
	static ConfigSign* getInstance();
   	bool LoadConfig();
	std::string getToday(){ return today; };
	std::vector<SignRewardItem> getRewards();
	void onHttpRequestCompleted(HttpClient *sender, HttpResponse *response);
	bool isGetDataSuccess(){ return bIsGetDataSuccess; };
	//Ç©µ½Âß¼­
	const char* KEY_LASTSIGNDAY = "KEY_LASTSIGNDAY";
	const char* KEY_SEQSIGNDAY = "KEY_SEQSIGNDAY";
	int CalculateTheDayToSign();
private:
	static ConfigSign* _instance;
	bool bIsGetDataSuccess = false;
	std::string today;
	std::vector<SignRewardItem> rewards;
	std::map<int, std::vector<SignRewardItem>> dayToRewards;
};

