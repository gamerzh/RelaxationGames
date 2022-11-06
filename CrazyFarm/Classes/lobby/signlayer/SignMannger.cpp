#include "lobby/signlayer/SignMannger.h"
#include "domain/user/User.h"
#define SIGNURL "http://106.75.135.78:1701/sign/today"
SignMannger* SignMannger::_instance = NULL;

SignMannger::SignMannger(){
}

SignMannger* SignMannger::getInstance(){
	if (_instance == NULL){
		_instance = new SignMannger();
	}
	return _instance;
}


void SignMannger::sendRequest()
{
	HttpToPostRequestSign(); 
}

void SignMannger::HttpToPostRequestSign()
{
	auto session_id = User::getInstance()->getSessionid();
	if (session_id!="")
	{
		auto requstData = String::createWithFormat("session_id=%s", session_id.c_str());
		HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), SIGNURL, CC_CALLBACK_2(SignMannger::onHttpRequestCompletedForSign, this));
	}
}
void SignMannger::onHttpRequestCompletedForSign(HttpClient *sender, HttpResponse *response)
{
	if (!response || !response->isSucceed())
	{
		log("http back  get sign info falied");
		return;
	}
	long statusCode = response->getResponseCode();
	std::vector<char> *buffer = response->getResponseData();
	auto temp = std::string(buffer->begin(), buffer->end());
	log("http back  before pay info: %s", temp.c_str());
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
	if (doc.HasParseError())
	{
		log("get json data err!");;
	}
	int result = doc["errorcode"].GetInt();

	if (result == 0)
	{
		auto &rewards = doc["rewards"];
		unsigned int size = rewards.Size();
		if (size>0)
		{
			for (unsigned int i = 0; i < size;i++)
			{
				SignItem item;
				item.itemId = rewards[i]["item_id"].GetInt();
				item.num = rewards[i]["nums"].GetInt();
				_signItems.push_back(item);
			}
			_layer->showSign(1);
		}
	}
	else
	{

	}
}