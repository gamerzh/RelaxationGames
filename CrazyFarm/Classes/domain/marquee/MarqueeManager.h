#pragma once

#include "cocos2d.h"
#include "config/ConfigMagnate.h"
#include "server/HttpClientUtill.h"
using namespace cocos2d;


class MarqueeManager {

public:
	static MarqueeManager* getInstance();
     void init();

	void onHttpRequestCompleted(HttpClient *sender, HttpResponse *response);
   
	float getPlayTime(){ return play_interval; };
	float getReqInterval(){ return req_interval; };
	std::string getContent();
	std::vector<std::string> getContents(){ return contents; };
private:
	MarqueeManager();
   
	static MarqueeManager* _instance;
	bool bIsGetDataSuccess = false;
	int curIndex = 0;
	std::vector<std::string> contents;
	float play_interval;
	float req_interval;
    
};

