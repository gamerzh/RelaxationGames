#include "MsgOnMarquee.h"

void Msg_OnMarquee::setBody(const char* msgBody)
{
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(msgBody);
	if (doc.HasParseError())
	{
		return;
	}
	msg = doc["msg"].GetString();

}