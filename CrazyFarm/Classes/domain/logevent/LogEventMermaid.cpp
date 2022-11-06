#include "LogEventMermaid.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "server/HttpMannger.h"
LogEventMermaid* LogEventMermaid::_instance = NULL;

LogEventMermaid::LogEventMermaid(){
    
}

void LogEventMermaid::init(){
	m_roomid = 0;
	m_result = 0;
	m_reward = 0;
}

LogEventMermaid* LogEventMermaid::getInstance(){
    if(_instance == NULL){
		_instance = new LogEventMermaid();
    }
    return _instance;
}

void LogEventMermaid::addDataToSend(int roomid, int result, int reward)
{
	m_roomid = roomid;
	m_result = result;
	m_reward = reward;
	sendDataToServer();
}

std::string LogEventMermaid::getDataForJson()
{

	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	document.AddMember("result", m_result, allocator);
	document.AddMember("room_id",m_roomid, allocator);
	document.AddMember("rewards", m_reward, allocator);
	document.AddMember("data_type", 2, allocator);
	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	std::string result = buffer.GetString();
	return result;
}

void LogEventMermaid::sendDataToServer()
{
	HttpMannger::getInstance()->HttpToPostRequestLogEvent(getDataForJson(),2);
}