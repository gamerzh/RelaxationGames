#include "MsgOnBankruptRebirth.h"

void Msg_OnBankruptRebirth::setBody(const char* msgBody)
{
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(msgBody);
	if (doc.HasParseError())
	{
		return;
	}

	errorcode = doc["errorcode"].GetInt();
	if (errorcode == 0)
	{
		getCoin = doc["reward_coins"].GetInt();
	}
	
}
