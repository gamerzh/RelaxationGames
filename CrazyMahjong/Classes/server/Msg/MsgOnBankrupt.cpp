#include "MsgOnBankrupt.h"

void Msg_OnBankrupt::setBody(const char* msgBody)
{
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(msgBody);
	if (doc.HasParseError())
	{
		return;
	}
	wait_time = doc["wait_time"].GetInt();
	left_times = doc["left_times"].GetInt();
	if (left_times>0)
	{
		coins = doc["coins"].GetInt();
	}
	
}
