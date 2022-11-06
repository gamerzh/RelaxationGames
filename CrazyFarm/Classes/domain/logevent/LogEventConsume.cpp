#include "LogEventConsume.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "server/HttpMannger.h"
LogEventConsume* LogEventConsume::_instance = NULL;

LogEventConsume::LogEventConsume(){
    
}

void LogEventConsume::init(){
	
}

LogEventConsume* LogEventConsume::getInstance(){
    if(_instance == NULL){
		_instance = new LogEventConsume();
    }
    return _instance;
}



std::string LogEventConsume::getDataForJson()
{

	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value array(rapidjson::kArrayType);

	rapidjson::Value object(rapidjson::kObjectType);
	object.AddMember("coin_get", UserDefault::getInstance()->getIntegerForKey(EventGetCoin,0), allocator);
	object.AddMember("coin_use", UserDefault::getInstance()->getIntegerForKey(EventCostCoin, 0), allocator);
	object.AddMember("diamond_get", UserDefault::getInstance()->getIntegerForKey(EventGetDiamond, 0), allocator);
	object.AddMember("diamond_use", UserDefault::getInstance()->getIntegerForKey(EventCostDiamond, 0), allocator);
	array.PushBack(object, allocator);

	document.AddMember("lists", array, allocator);
	document.AddMember("data_type", 10, allocator);

	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	std::string result = buffer.GetString();
	return result;
}

void LogEventConsume::sendDataToServer()
{
	auto jsonstr = getDataForJson();
	if (jsonstr.size()>0)
	{
		HttpMannger::getInstance()->HttpToPostRequestLogEvent(jsonstr, 10);
	}
	
}

void LogEventConsume::clearLocalData()
{
	UserDefault::getInstance()->setIntegerForKey(EventGetCoin, 0);
	UserDefault::getInstance()->setIntegerForKey(EventCostCoin, 0);
	UserDefault::getInstance()->setIntegerForKey(EventGetDiamond, 0);
	UserDefault::getInstance()->setIntegerForKey(EventCostDiamond, 0);
}


void LogEventConsume::addEventCoin(int coin)
{
	if (coin>0)
	{
		auto nowcoin = UserDefault::getInstance()->getIntegerForKey(EventGetCoin, 0);
		UserDefault::getInstance()->setIntegerForKey(EventGetCoin, nowcoin + coin);
	}
	else
	{
		auto nowcoin = UserDefault::getInstance()->getIntegerForKey(EventCostCoin, 0);
		UserDefault::getInstance()->setIntegerForKey(EventCostCoin, nowcoin - coin);
	}
	
}
void LogEventConsume::addEventDiamond(int diamond)
{
	if (diamond > 0)
	{
		auto nowcoin = UserDefault::getInstance()->getIntegerForKey(EventGetDiamond, 0);
		UserDefault::getInstance()->setIntegerForKey(EventGetDiamond, nowcoin + diamond);
	}
	else
	{
		auto nowcoin = UserDefault::getInstance()->getIntegerForKey(EventCostDiamond, 0);
		UserDefault::getInstance()->setIntegerForKey(EventCostDiamond, nowcoin -diamond);
	}
}
