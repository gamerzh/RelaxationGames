#include "MsgOnGetBounsPool.h"

void Msg_OnGetBounsPool::setBody(const char* msgBody)
{
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(msgBody);
	if (doc.HasParseError())
	{
		return;
	}

	fish_nums = doc["fish_nums"].GetInt();
	fish_coins = doc["fish_coins"].GetUint64();
}