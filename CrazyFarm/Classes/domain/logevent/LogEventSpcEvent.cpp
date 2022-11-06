#include "LogEventSpcEvent.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "server/HttpMannger.h"
LogEventSpcEvent* LogEventSpcEvent::_instance = NULL;

LogEventSpcEvent::LogEventSpcEvent(){
    
}

void LogEventSpcEvent::init(){

}

LogEventSpcEvent* LogEventSpcEvent::getInstance(){
    if(_instance == NULL){
		_instance = new LogEventSpcEvent();
    }
    return _instance;
}



std::string LogEventSpcEvent::getDataForJson()
{

	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value array(rapidjson::kArrayType);

	for (auto var : datas)
	{
		if (var.nums<= 0)
		{
			continue;
		}
		rapidjson::Value object(rapidjson::kObjectType);
		object.AddMember("event_desc", var.event_desc, allocator);
		object.AddMember("event_id", var.event_id, allocator);
		object.AddMember("nums", var.nums, allocator);
		array.PushBack(object, allocator);
	}
	document.AddMember("events", array, allocator);
	document.AddMember("data_type", 7, allocator);

	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	std::string result = buffer.GetString();
	return result;
}

void LogEventSpcEvent::loadLocalData()
{
	datas.clear();
	for (int i = 1; i <= 3; i++)
	{
		SpcEvent item;
		item.event_id = i;
		item.event_desc = 0;
		auto str = String::createWithFormat("%s%d%d", EventSpcEventNum, i,0);
		item.nums = UserDefault::getInstance()->getIntegerForKey(str->getCString(), 0);
		if (item.nums>0)
		{
			datas.push_back(item);
		}
	}
}
void LogEventSpcEvent::sendDataToServer()
{
	loadLocalData();
	HttpMannger::getInstance()->HttpToPostRequestLogEvent(getDataForJson(), 7);
}

void LogEventSpcEvent::addEventItems(int event_id, int event_desc)
{
	auto str = String::createWithFormat("%s%d%d", EventSpcEventNum, event_id, event_desc);
	auto localdata = UserDefault::getInstance();
	localdata->setIntegerForKey(str->getCString(), localdata->getIntegerForKey(str->getCString(), 0) + 1);
}

void LogEventSpcEvent::clearLocalData()
{
	for (int i = 1; i <= 3; i++)
	{
		auto str = String::createWithFormat("%s%d%d", EventSpcEventNum, i, 0);
		 UserDefault::getInstance()->setIntegerForKey(str->getCString(), 0);
	
	}
}