#include "LogEventMagnate.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "server/HttpMannger.h"
LogEventMagnate* LogEventMagnate::_instance = NULL;

LogEventMagnate::LogEventMagnate(){
    
}

void LogEventMagnate::init(){

	
}

LogEventMagnate* LogEventMagnate::getInstance(){
    if(_instance == NULL){
		_instance = new LogEventMagnate();
    }
    return _instance;
}


std::string LogEventMagnate::getDataForJson()
{

	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value array(rapidjson::kArrayType);
	
	for (auto var : items)
	{
		if (var.itemNum<=0)
		{
			continue;
		}
		rapidjson::Value object(rapidjson::kObjectType);
		object.AddMember("prop_id", var.itemID, allocator);
		object.AddMember("nums", var.itemNum, allocator);
		array.PushBack(object, allocator);
	}	
	document.AddMember("presenteds", array, allocator);
	document.AddMember("data_type", 3, allocator);
	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	std::string result = buffer.GetString();
	
	return result;
}
void LogEventMagnate::loadLocalData()
{
	items.clear();
	for (int i = 1002; i <= 1005;i++)
	{
		Magnatecell item;
		item.itemID = i;
		auto str = String::createWithFormat("%s%d", EventMagnateItemNum,i);
		item.itemNum = UserDefault::getInstance()->getIntegerForKey(str->getCString(), 0);
		if (item.itemNum>0)
		{
			items.push_back(item);
		}
	}
}
void LogEventMagnate::sendDataToServer()
{
	loadLocalData();
	HttpMannger::getInstance()->HttpToPostRequestLogEvent(getDataForJson(),3);
}

void LogEventMagnate::addMagnateNum(int itemid, int num)
{
	auto str = String::createWithFormat("%s%d", EventMagnateItemNum, itemid);
	auto localdata = UserDefault::getInstance();
	localdata->setIntegerForKey(str->getCString(), localdata->getIntegerForKey(str->getCString(), 0) + 1);
}

void LogEventMagnate::clearLocalData()
{
	for (int i = 1002; i <= 1005; i++)
	{
		auto str = String::createWithFormat("%s%d", EventMagnateItemNum, i);
		UserDefault::getInstance()->setIntegerForKey(str->getCString(), 0);

	}
}