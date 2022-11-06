#include "MsgOnCatchMarriedFish.h"

void Msg_OnCatchMarriedFish::setBody(const char* msgBody)
{
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(msgBody);
	if (doc.HasParseError())
	{
		return;
	}

	auto &itemlist = doc["catchfish_ids"];
	for (unsigned int i = 0; i < itemlist.Size();i++)
	{
	
		fishids.push_back(itemlist[i].GetInt());
	}

}