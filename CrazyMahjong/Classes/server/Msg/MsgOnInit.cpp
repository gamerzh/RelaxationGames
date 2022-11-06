#include "MsgOnInit.h"
#include "domain/user/User.h"
#include "domain/bag/BagManager.h"
void Msg_onInit::setBody(const char* msgBody)
{
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(msgBody);
	if (doc.HasParseError())
	{
		return;
	}
	
	rapidjson::Value& users = doc["users"];
	if (!users.IsArray())
	{
		log("ConfigExp The data is not json");
		return;
	}
	auto &my_info = doc["my_info"];
	//用户信息
	User::getInstance()->setUserName(my_info["nick_name"].GetString());
	User::getInstance()->setCoins(my_info["coins"].GetInt64());
	User::getInstance()->setDiamonds(my_info["diamonds"].GetInt64());
	User::getInstance()->setExp(my_info["exps"].GetInt());
	User::getInstance()->setMaxTurrentLevel(my_info["turrent_level"].GetInt());
	User::getInstance()->setUserBoxLevel(my_info["chest_level"].GetInt());
	User::getInstance()->setChargeMoney(my_info["mo"].GetInt()/100);
	User::getInstance()->setcatchPer(my_info["catch_per"].GetDouble());
	roomPos = my_info["r_pos"].GetInt()-1;
	auto &item_lists = my_info["item_lists"];
	for (unsigned int i = 0; i < item_lists.Size();i++)
	{
		BagManager::getInstance()->setItemNum(item_lists[i]["item_id"].GetInt(), item_lists[i]["nums"].GetInt());
	}




	//玩家信息
	for (unsigned int i = 0; i < users.Size();i++)
	{
		auto &user = users[i];
		RoomPlayer* player = new RoomPlayer();
		player->setCoins(user["coins"].GetInt());
		player->setDiamonds(user["diamonds"].GetInt());
		player->setMaxTurretLevel(user["turrent_level"].GetInt());
		player->setLevel(user["vip_level"].GetInt());
		player->setChestLv(user["chest_level"].GetInt());
		player->setUserName(user["nick_name"].GetString());
		player->setRoomPosition(user["r_pos"].GetInt()-1);
		player->setVipLevel(/*user["vip_level"].GetInt()*/rand() % 10);
		player->setchestper(user["catch_per"].GetDouble()*2);
		roomplayers.push_back(player);
	}
	//鱼群
	rapidjson::Value& fishes = doc["fishes"];
	for (unsigned int i = 0; i < fishes.Size();i++)
	{
		auto &info = fishes[i];
		MsgFishesInfo fishInfo;
		fishInfo.seq_id = info["seq_id"].GetInt();
		fishInfo.seq_interval = info["seq_interval"].GetInt();
		fishInfo.seq_create_time = info["seq_create_time"].GetDouble();
		fishInfo.randomSTC = info["seq_create_time"].GetDouble();
		{
			auto &fishgroupinfo = info["fish_group_info"];
			MsgFishGourpInfo groupInfo;
			
			groupInfo.group_type = fishgroupinfo["group_type"].GetInt();
			groupInfo.sub_type = fishgroupinfo["sub_type"].GetInt();
			groupInfo.seq = fishgroupinfo["seq"].GetInt();
			groupInfo.seq_time = fishgroupinfo["seq_time"].GetInt();
			if (groupInfo.group_type == 0)
			{
				auto &fishitems = fishgroupinfo["fishes"];
				for (unsigned int k = 0; k < fishitems.Size(); k++)
				{
					MsgFishInfo fishitem;
					fishitem.fish_ids = fishitems[k]["fish_ids"].GetInt();
					fishitem.time = fishitems[k]["time"].GetDouble();
					fishitem.fish_route = fishitems[k]["fish_route"].GetInt();


					//
					fishitem.time -= groupInfo.seq_time*(groupInfo.seq - 1);
					//
					groupInfo.fishItems.push_back(fishitem);
				}
			}
			else
			{

			}
			fishInfo.fishGroupsItem = groupInfo;
		}
		_FishesInfos.push_back(fishInfo);
	}

	//初始时间戳
	initCreateTime = doc["create_time"].GetDouble();
	//子弹相关
	bullet_speed = doc["bullet_speed"].GetDouble();
	bullet_interval = doc["bullet_interval"].GetDouble();

	std::sort(roomplayers.begin(), roomplayers.end(), Msg_onInit::sortFun);
}

bool Msg_onInit::sortFun(const RoomPlayer * m1, const RoomPlayer * m2) {
	return m1->getRoomPosition()>m2->getRoomPosition();
}