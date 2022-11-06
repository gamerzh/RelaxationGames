#include "domain/marquee//MarqueeManager.h"
#include "server/HttpClientUtill.h"
#define SIGNURL "http://114.119.39.150:1701/marquee/config"
MarqueeManager* MarqueeManager::_instance = NULL;

MarqueeManager::MarqueeManager(){

}


void MarqueeManager::init(){
	HttpClientUtill::getInstance()->onGetHttp(SIGNURL, CC_CALLBACK_2(MarqueeManager::onHttpRequestCompleted, this));
}

MarqueeManager* MarqueeManager::getInstance(){
    if(_instance == NULL){
		_instance = new MarqueeManager();
    }
    return _instance;
}


void MarqueeManager::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		return;
	}
	if (!response->isSucceed())
	{
		log("error buffer: %s", response->getErrorBuffer());
		bIsGetDataSuccess = false;
		return;
	}

	long statusCode = response->getResponseCode();
	char statusString[64] = {};
	// dump data
	std::vector<char> *buffer = response->getResponseData();
	auto temp = std::string(buffer->begin(), buffer->end());
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());

	play_interval = doc["play_interval"].GetDouble();
	req_interval = doc["req_interval"].GetDouble();
	auto &itemlists = doc["item_list"];
	for (size_t i = 0; i < itemlists.Size(); i++)
	{
		contents.push_back(itemlists[i]["msg"].GetString());
	}
	if (contents.size()>0)
	{
		bIsGetDataSuccess = true;
	}
}

std::string MarqueeManager::getContent()
{
	auto str = contents[curIndex];
    if (++curIndex>contents.size())
    {
		curIndex == 0;
    }
	return str;
};