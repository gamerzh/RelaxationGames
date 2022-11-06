#include "LogEventUseSkill.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "server/HttpMannger.h"
#include "domain/skill/skillManager.h"
LogEventUseSkill* LogEventUseSkill::_instance = NULL;

LogEventUseSkill::LogEventUseSkill(){
    
}

void LogEventUseSkill::init(){
	items.clear();
}

LogEventUseSkill* LogEventUseSkill::getInstance(){
    if(_instance == NULL){
		_instance = new LogEventUseSkill();
    }
    return _instance;
}



std::string LogEventUseSkill::getDataForJson()
{
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value array(rapidjson::kArrayType);

	for (auto var : items)
	{
		if (var.nums <= 0)
		{
			continue;
		}
		rapidjson::Value object(rapidjson::kObjectType);
		object.AddMember("skill_id", var.skillID, allocator);
		object.AddMember("type", var.type, allocator);
		object.AddMember("price", var.prices, allocator);
		object.AddMember("nums", var.nums, allocator);
		array.PushBack(object, allocator);
	}
	document.AddMember("skills", array, allocator);
	document.AddMember("data_type", 5, allocator);
	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	std::string result = buffer.GetString();
	return result;
}

void LogEventUseSkill::sendDataToServer()
{
	loadLocalData();
	HttpMannger::getInstance()->HttpToPostRequestLogEvent(getDataForJson(),5);
}
void LogEventUseSkill::addUseSkillData(int skillID, int type, int prices)
{

	auto str = String::createWithFormat("%s%d%d%d", EventUseSkill,skillID,type,prices);
	auto localdata = UserDefault::getInstance();
	localdata->setIntegerForKey(str->getCString(), localdata->getIntegerForKey(EventUseSkill, 0) + 1);

}


void LogEventUseSkill::loadLocalData()
{
	items.clear();
	for (int i = 1; i <= 5; i++)
	{
		for (int j = 0; j <= 2;j++)
		{
			EventSkillCell item;
			item.skillID = i;
			item.type = j;
			if (item.type==1)
			{
				item.prices = skillManager::getInstance()->getSkillPriceById(i);
			}
			else
			{
				item.prices = 0;
			}
			auto str = String::createWithFormat("%s%d%d%d", EventUseSkill, item.skillID, item.type, item.prices);
			item.nums = UserDefault::getInstance()->getIntegerForKey(str->getCString(), 0);
			if (item.nums > 0)
			{
				items.push_back(item);
			}
		}
		
	}
}

void LogEventUseSkill::clearLocalData()
{
	for (int i = 1; i <= 5; i++)
	{
		for (int j = 0; j <= 2; j++)
		{
			EventSkillCell item;
			item.skillID = i;
			item.type = j;
			if (item.type == 1)
			{
				item.prices = skillManager::getInstance()->getSkillPriceById(i);
			}
			else
			{
				item.prices = 0;
			}
			auto str = String::createWithFormat("%s%d%d%d", EventUseSkill, item.skillID, item.type, item.prices);
			UserDefault::getInstance()->setIntegerForKey(str->getCString(), 0);
	
		}

	}
}