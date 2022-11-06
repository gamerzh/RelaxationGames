#include "MsgOnMarriedSuccess.h"

void Msg_OnMarriedSuccess::setBody(const char* msgBody)
{
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(msgBody);
	if (doc.HasParseError())
	{
		return;
	}
	coins = doc["reward_coins"].GetUint();

}