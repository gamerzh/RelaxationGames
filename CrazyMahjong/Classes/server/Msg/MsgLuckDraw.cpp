#include "MsgLuckDraw.h"

void Msg_LuckDraw::setBody(const char* msgBody)
{
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(msgBody);
	if (doc.HasParseError())
	{
		return;
	}
	errorCode = doc["errorcode"].GetInt();
	auto &itemList = doc["reward_lists"];
	itemid = itemList[(unsigned int)0]["item_id"].GetInt();
	num = itemList[(unsigned int)0]["nums"].GetInt();

}