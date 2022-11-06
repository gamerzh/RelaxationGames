#include "MsgOnBossDead.h"

void Msg_OnBossDead::setBody(const char* msgBody)
{
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(msgBody);
	if (doc.HasParseError())
	{
		return;
	}
	auto &reward_lists = doc["reward_lists"];
	for (unsigned int i = 0; i < reward_lists.Size();i++)
	{
		_items.push_back(RewardValue(reward_lists[i]["item_id"].GetInt(), reward_lists[i]["nums"].GetInt()));
	}

}