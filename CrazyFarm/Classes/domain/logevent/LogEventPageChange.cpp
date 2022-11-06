#include "LogEventPageChange.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "server/HttpMannger.h"
LogEventPageChange* LogEventPageChange::_instance = NULL;

LogEventPageChange::LogEventPageChange(){
    
}

void LogEventPageChange::init(){
	items.clear();
}

LogEventPageChange* LogEventPageChange::getInstance(){
    if(_instance == NULL){
		_instance = new LogEventPageChange();
    }
    return _instance;
}



std::string LogEventPageChange::getDataForJson()
{

	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value array(rapidjson::kArrayType);

	for (auto var : items)
	{
		if (var.num<= 0)
		{
			continue;
		}
		rapidjson::Value object(rapidjson::kObjectType);
		object.AddMember("from_page", var.from_page, allocator);
		object.AddMember("to_page", var.to_page, allocator);
		object.AddMember("channel", var.channel, allocator);
		object.AddMember("nums", var.num, allocator);
		array.PushBack(object, allocator);
	}
	document.AddMember("pagechanges", array, allocator);
	document.AddMember("data_type", 6, allocator);

	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	std::string result = buffer.GetString();
	return result;
}

void LogEventPageChange::sendDataToServer()
{
	auto jsonstr = getDataForJson();
	if (jsonstr.size()>0)
	{
		HttpMannger::getInstance()->HttpToPostRequestLogEvent(jsonstr, 6);
	}
	
	items.clear();
}

void LogEventPageChange::addEventItems(int from_page, int to_page, int channel)
{

	for (auto &var:items)
	{
		if (var.from_page == from_page&&var.channel==channel&&var.to_page==to_page)
		{
			var.num++;
		}
	}
	EventPageChange info;
	info.from_page = from_page;
	info.to_page = to_page;
	info.channel = channel;
	info.num = 1;
	items.push_back(info);
	sendDataToServer();
	/*
	auto str = String::createWithFormat("%s%d%d%d", EventPageChangeNum, from_page, to_page, channel);
	auto localdata = UserDefault::getInstance();
	localdata->setIntegerForKey(str->getCString(), localdata->getIntegerForKey(str->getCString(), 0) + 1);
	CCLOG("add loevetPageChange: from_page = %d,to_page = %d,channel=%d", from_page, to_page, channel);*/
}

void LogEventPageChange::loadLocalData()
{
	items.clear();
	//i:from_page, j: to_page, k: channel
	/*for (int i = 1; i <= 13; i++)
	{
		for (int j = 1; j <= 13; j++)
		{
			for (int k = 0; k <= 6;k++)
			{
				EventPageChange item;
				item.from_page = i;
				item.to_page = j;
				item.channel = k;
				auto str = String::createWithFormat("%s%d%d%d", EventPageChangeNum, item.from_page, item.to_page, item.channel);
				item.num = UserDefault::getInstance()->getIntegerForKey(str->getCString(), 0);
				if (item.num > 0)
				{
					items.push_back(item);
				}
			}
			
		}

	}*/
}

void LogEventPageChange::clearLocalData()
{
	items.clear();
	//i:from_page, j: to_page, k: channel
	/*for (int i = 1; i <= 13; i++)
	{
		for (int j = 1; j <= 13; j++)
		{
			for (int k = 0; k <= 6; k++)
			{
				EventPageChange item;
				item.from_page = i;
				item.to_page = j;
				item.channel = k;
				auto str = String::createWithFormat("%s%d%d%d", EventPageChangeNum, item.from_page, item.to_page, item.channel);
				UserDefault::getInstance()->setIntegerForKey(str->getCString(), 0);

			}

		}

	}*/
}