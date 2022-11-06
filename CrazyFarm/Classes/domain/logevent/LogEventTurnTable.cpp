#include "LogEventTurnTable.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "server/HttpMannger.h"

LogEventTurnTable* LogEventTurnTable::_instance = NULL;

LogEventTurnTable::LogEventTurnTable(){

}


LogEventTurnTable* LogEventTurnTable::getInstance(){
	if (_instance == NULL){
		_instance = new LogEventTurnTable();
	}
	return _instance;
}



std::string LogEventTurnTable::getDataForJson(int tType, int pType)
{
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value array(rapidjson::kArrayType);

	rapidjson::Value object(rapidjson::kObjectType);
	object.AddMember("t_type", tType, allocator);
	for (int i = 1; i <= 6;i++)
	{
		auto key = String::createWithFormat("p_type_%d", i);
		int value = pType == i ? 1 : 0;
		object.AddMember(key->getCString(), value, allocator);
	}
	array.PushBack(object, allocator);
	
	document.AddMember("lists", array, allocator);
	document.AddMember("data_type", 9, allocator);
	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	std::string result = buffer.GetString();
	return result;
}

void LogEventTurnTable::sendDataToServer(int tType, int pType)
{
	HttpMannger::getInstance()->HttpToPostRequestLogEvent(getDataForJson(tType,pType), 9);
}