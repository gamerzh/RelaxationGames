#include "MsgOnFishes.h"

void Msg_OnFishes::setBody(const char* msgBody)
{
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(msgBody);
	if (doc.HasParseError())
	{
		return;
	}
	auto &events = doc["events"];
	for (unsigned int i = 0; i < events.Size(); i++)
	{
		eventstrs.push_back(events[i].GetString());
	}



	//鱼群
	rapidjson::Value& info = doc["msg"];
	_info.seq_id = info["seq_id"].GetInt();
	_info.seq_interval = info["seq_interval"].GetInt();
	_info.seq_create_time = info["seq_create_time"].GetDouble();
	_info.randomSTC = info["seq_create_time"].GetDouble();
	{
		auto &fishgroupinfo = info["fish_group_info"];
		MsgFishGourpInfo groupInfo;
		groupInfo.group_type = fishgroupinfo["group_type"].GetInt();
		groupInfo.sub_type = fishgroupinfo["sub_type"].GetInt();
		groupInfo.seq = fishgroupinfo["seq"].GetInt();
		groupInfo.seq_time = fishgroupinfo["seq_time"].GetInt();
		auto &fishitems = fishgroupinfo["fishes"];
		if (groupInfo.group_type == 0)
		{	
			for (unsigned int k = 0; k < fishitems.Size(); k++)
			{
			MsgFishInfo fishitem;
			fishitem.fish_ids = fishitems[k]["fish_ids"].GetInt();
			fishitem.time = fishitems[k]["time"].GetDouble();
			fishitem.fish_route = fishitems[k]["fish_route"].GetInt();


			//转换时间  110to 10  88to 8   
			fishitem.time -= groupInfo.seq_time*(groupInfo.seq - 1);
			//
			groupInfo.fishItems.push_back(fishitem);
			}
		}
		
		_info.fishGroupsItem = groupInfo;
	}
}