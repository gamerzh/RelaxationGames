#include "MsgOnMagnate.h"

void Msg_OnMagnate::setBody(const char* msgBody)
{
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(msgBody);
	if (doc.HasParseError())
	{
		return;
	}
	int dimond = doc["diamonds"].GetInt();
	if (dimond>0)
	{
		MagnateData item;
		item.itemid = 1002;
		item.num = dimond;
		items.push_back(item);
	}
	auto &itemlist = doc["item_ids"];
	for (unsigned int i = 0; i < itemlist.Size();i++)
	{
		MagnateData item;
		item.itemid = itemlist[i].GetInt();
		item.num = 1;
		items.push_back(item);
	}
	
}
