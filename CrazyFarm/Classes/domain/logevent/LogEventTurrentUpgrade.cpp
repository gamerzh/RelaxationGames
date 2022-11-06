#include "LogEventTurrentUpgrade.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "server/HttpMannger.h"
LogEventTurrentUpgrade* LogEventTurrentUpgrade::_instance = NULL;

LogEventTurrentUpgrade::LogEventTurrentUpgrade(){
    
}

void LogEventTurrentUpgrade::init(){

}

LogEventTurrentUpgrade* LogEventTurrentUpgrade::getInstance(){
    if(_instance == NULL){
		_instance = new LogEventTurrentUpgrade();
    }
    return _instance;
}



std::string LogEventTurrentUpgrade::getDataForJson(int turrent_level, float updata_times)
{
	int intTime = (int)updata_times;
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	
	document.AddMember("turrent_level", turrent_level, allocator);
	document.AddMember("update_times", intTime, allocator);
	document.AddMember("data_type", 8, allocator);
	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	std::string result = buffer.GetString();
	return result;
}

void LogEventTurrentUpgrade::sendDataToServer(int turrent_level, float updata_times)
{
	HttpMannger::getInstance()->HttpToPostRequestLogEvent(getDataForJson(turrent_level,updata_times),8);
}