#include "MsgOnLeave.h"

void Msg_onLeave::setBody(const char* msgBody)
{
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(msgBody);
	if (doc.HasParseError())
	{
		return;
	}
	roomPos = doc["r_pos"].GetInt()-1;

}