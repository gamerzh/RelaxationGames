#include "MsgOnUpdateTurrent.h"

void Msg_OnUpdateTurrent::setBody(const char* msgBody)
{
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(msgBody);
	if (doc.HasParseError())
	{
		return;
	}
	errorcode = doc["errorcode"].GetInt();
	if (errorcode==0)
	{
		_info.requireDiamonds = doc["diamonds"].GetInt();
		_info.rewards = doc["coins"].GetInt();
		_info.turrent_level = doc["turrent_level"].GetInt();
	}
	else
	{

	}
}
