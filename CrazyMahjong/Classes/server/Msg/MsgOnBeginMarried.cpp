#include "MsgOnBeginMarried.h"

void Msg_OnBeginMarried::setBody(const char* msgBody)
{
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(msgBody);
	if (doc.HasParseError())
	{
		return;
	}
	_taskID = doc["task_id"].GetInt();
	_lefttime = doc["left_times"].GetInt();
	auto &itemlist = doc["fish_ids"];
	for (unsigned int i = 0; i < itemlist.Size();i++)
	{
		MarriedTaskFishItem item;
		item.fishid = itemlist[i]["fish_id"].GetInt();
		item.nums = itemlist[i]["nums"].GetInt();
		_items.push_back(item);
	}

}