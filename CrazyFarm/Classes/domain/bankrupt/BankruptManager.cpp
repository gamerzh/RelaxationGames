#include "domain/bankrupt/BankruptManager.h"
#include "domain/user/User.h"
#include "domain/game/GameManage.h"
BankruptManager* BankruptManager::_instance = NULL;

BankruptManager::BankruptManager(){
    this->init();
}


void BankruptManager::init(){
	setgetRewardNode(nullptr);
}

BankruptManager* BankruptManager::getInstance(){
    if(_instance == NULL){
        _instance = new BankruptManager();
    }
    return _instance;
}

Bankrupt BankruptManager::getBankrupt() {
    if( getTodayRequestTimes() < ConfigBankrupt::getInstance()->getBankrupts().size() ) {
        return ConfigBankrupt::getInstance()->getBankrupts().at( getTodayRequestTimes() );
    }else {
        Bankrupt bankrupt;
        bankrupt.coins = 0;
        bankrupt.wait_time = 0;
		return bankrupt;
    }
}
Bankrupt BankruptManager::getRobotBankrupt() {

		Bankrupt bankrupt;
		bankrupt.coins = rand()%20000;
		bankrupt.wait_time = rand()%60;
		return bankrupt;
}

int BankruptManager::getTodayRequestTimes() {

	return getDayCnt(BankruptData);
}

void BankruptManager::addTodayRequestTime()
{
	addDayCnt(BankruptData);
}


int  BankruptManager::XygGetToday()
{
	int day = 1900;
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	day += timeinfo->tm_year;
	day = day * 100 + timeinfo->tm_mon + 1;
	day = day * 100 + timeinfo->tm_mday;

	return day;
}


int BankruptManager::getDayCnt(const char* key)
{
	//保存格式为2015031202 20150312为年月日，02为使用次数
	int val = UserDefault::sharedUserDefault()->getIntegerForKey(key, 0);
	if (val <= 0)
	{
		return 0;
	}

	int day = XygGetToday();
	//不是今天
	if (val / 100 != day)
	{
		return 0;
	}
	else
	{
		return val % 100;
	}
}

void BankruptManager::addDayCnt(const char* key)
{
	int val = getDayCnt(key);
	CCUserDefault::sharedUserDefault()->setIntegerForKey(key, XygGetToday() * 100 + val + 1);
	CCUserDefault::sharedUserDefault()->flush();
}




///服务器
void BankruptManager::RequestServerToBroke(PlayerTurret* turret)
{
	auto sessionid = User::getInstance()->getSessionid();
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_BROKE);
	auto requstData = String::createWithFormat("session_id=%s&room_id=%d", sessionid.c_str(),GameData::getInstance()->getRoomID());
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(BankruptManager::onHttpRequestCompletedForBroke, this),turret);
}
void BankruptManager::onHttpRequestCompletedForBroke(HttpClient *sender, HttpResponse *response)
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
	std::vector<char> *buffer = response->getResponseData();
	auto temp = std::string(buffer->begin(), buffer->end());
	log("http back broke info  info: %s", temp.c_str());
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
	if (doc.HasParseError())
	{
		log("get json data err!");;
	}
	int code = doc["errorcode"].GetInt();
	if (code == 0)
	{
		PlayerTurret* turret = (PlayerTurret*)(response->getHttpRequest()->getUserData());
		GameManage::getInstance()->onBrokeBySomeTurret(turret, doc["left_times"].GetInt(), 0/*doc["wait_time"].GetInt()*/);
	}
}

void BankruptManager::RequestServerToRebirth()
{
	auto sessionid = User::getInstance()->getSessionid();
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_REBRITH);
	auto requstData = String::createWithFormat("session_id=%s&room_id=%d", sessionid.c_str(),GameData::getInstance()->getRoomID());
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(BankruptManager::onHttpRequestCompletedForRebirth, this));

}
void BankruptManager::onHttpRequestCompletedForRebirth(HttpClient *sender, HttpResponse *response)
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
	std::vector<char> *buffer = response->getResponseData();
	auto temp = std::string(buffer->begin(), buffer->end());
	log("http back broke info  info: %s", temp.c_str());
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
	if (doc.HasParseError())
	{
		log("get json data err!");;
	}
	int code = doc["errorcode"].GetInt();
	if (code == 0)
	{
		GameManage::getInstance()->onRebirthBySomeTurret(doc["reward_coins"].GetInt());
	}
	else
	{
		GameManage::getInstance()->onRebirthBySomeTurret(1000);
	}
}