#include "MsgOnExpUpdate.h"


void Msg_OnExpUpdate::setBody(const char* msgBody)
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
		auto &levels = doc["user_level_up_infos"];
		for (unsigned int i = 0; i < levels.Size();i++)
		{
			std::vector<LevelRewardItem> items;
			auto &level = levels[i];
			auto &rewards = level["rewards"];
			for (unsigned int i = 0; i < rewards.Size(); i++)
			{
				LevelRewardItem item;
				item.item_id = rewards[i]["item_id"].GetInt();
				item.num = rewards[i]["num"].GetInt();
				items.push_back(item);
			}
			LevelRewardItem levelRewardItem;
			levelRewardItem.item_id = 1012;
			levelRewardItem.num = level["level"].GetInt(); +1;
			items.push_back(levelRewardItem);
			_infos.push_back(items);
		}
	
	}

}
