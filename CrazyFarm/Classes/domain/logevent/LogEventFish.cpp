#include "LogEventFish.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#include "server/HttpMannger.h"
#include "data/GameData.h"
LogEventFish* LogEventFish::_instance = NULL;

LogEventFish::LogEventFish(){
	for (int i = 1; i <= 4;i++)
    {
		FishEventData data;
		data.room_id = i;
		logEventFishes.push_back(data);
    }
}

LogEventFish* LogEventFish::getInstance(){
    if(_instance == NULL){
		_instance = new LogEventFish();
    }
    return _instance;
}


void LogEventFish::addFishCreateTimes(int fishid)
{
	bool isHava = false;
	for (auto &var : logEventFishes)
	{
		if (var.room_id == GameData::getInstance()->getRoomID())
		{
			for (auto &var2:var.fishes)
			{
				if (var2.nFishID == fishid)
				{
					var2.nCreateTimes++;
					isHava = true;
					break;
				}
			}
			if (isHava == false)
			{
				FishStatInfo info;
				info.nFishID = fishid;
				info.nCatchTimes = 0;
				info.nCreateTimes = 1;
				info.nHitTimes = 0;
				info.nUserCatchTimes = 0;
				info.nUserCostCoin = 0;
				var.fishes.push_back(info);
			}
			
		}
	}
	/*int roomid = GameData::getInstance()->getRoomID();
	auto str = String::createWithFormat("%d%d%s", roomid,fishid, FISHCREATETIME);
	CCLOG("%s", str->getCString());
	auto localdata = UserDefault::getInstance();
	localdata->setIntegerForKey(str->getCString(), localdata->getIntegerForKey(str->getCString(), 0) + 1);*/
}
void LogEventFish::addFishCatchTimes(int fishid)
{
	bool isHava = false;
	for (auto &var : logEventFishes)
	{
		if (var.room_id == GameData::getInstance()->getRoomID())
		{
			for (auto &var2 : var.fishes)
			{
				if (var2.nFishID == fishid)
				{
					var2.nCatchTimes++;
					isHava = true;
					break;
				}
			}
			if (isHava == false)
			{
				FishStatInfo info;
				info.nFishID = fishid;
				info.nCatchTimes = 1;
				info.nCreateTimes = 0;
				info.nHitTimes = 0;
				info.nUserCatchTimes = 0;
				info.nUserCostCoin = 0;
				var.fishes.push_back(info);
			}

		}
	}/*
	int roomid = GameData::getInstance()->getRoomID();
	auto str = String::createWithFormat("%d%d%s", roomid,fishid, FISHCATCHTIME);
	CCLOG("%s", str->getCString());
	auto localdata = UserDefault::getInstance();
	localdata->setIntegerForKey(str->getCString(), localdata->getIntegerForKey(str->getCString(), 0) + 1);*/
}
void LogEventFish::addFishHitTimes(int fishid)
{
	bool isHava = false;
	for (auto& var : logEventFishes)
	{
		if (var.room_id == GameData::getInstance()->getRoomID())
		{
			for (auto &var2 : var.fishes)
			{
				if (var2.nFishID == fishid)
				{
					var2.nHitTimes++;
					isHava = true;
					break;
				}
			}
			if (isHava == false)
			{
				FishStatInfo info;
				info.nFishID = fishid;
				info.nCatchTimes = 0;
				info.nCreateTimes = 0;
				info.nHitTimes = 1;
				info.nUserCatchTimes = 0;
				info.nUserCostCoin = 0;
				var.fishes.push_back(info);
			}

		}
	}/*
	int roomid = GameData::getInstance()->getRoomID();
	auto str = String::createWithFormat("%d%d%s", roomid,fishid, FISHHITTIMES);
	CCLOG("%s", str->getCString());
	auto localdata = UserDefault::getInstance();
	localdata->setIntegerForKey(str->getCString(), localdata->getIntegerForKey(str->getCString(), 0) + 1);*/
}
void LogEventFish::addFishUserCatchTimes(int fishid)
{
	bool isHava = false;
	for (auto &var : logEventFishes)
	{
		if (var.room_id == GameData::getInstance()->getRoomID())
		{
			for (auto &var2 : var.fishes)
			{
				if (var2.nFishID == fishid)
				{
					var2.nUserCatchTimes++;
					isHava = true;
					break;
				}
			}
			if (isHava == false)
			{
				FishStatInfo info;
				info.nFishID = fishid;
				info.nCatchTimes = 0;
				info.nCreateTimes = 0;
				info.nHitTimes = 0;
				info.nUserCatchTimes = 1;
				info.nUserCostCoin = 0;
				var.fishes.push_back(info);
			}

		}
	}/*
	int roomid = GameData::getInstance()->getRoomID();
	auto str = String::createWithFormat("%d%d%s", roomid,fishid, FISHUSERCATCHTIMES);
	CCLOG("%s", str->getCString());
	CCLOG("%f", GetCurrentTime());
	auto localdata = UserDefault::getInstance();
	localdata->setIntegerForKey(str->getCString(), localdata->getIntegerForKey(str->getCString(), 0) + 1);
	CCLOG("%f", GetCurrentTime());*/
}

void LogEventFish::addFishUserCostCoin(int fishid, int coin)
{
	bool isHava = false;
	for (auto& var : logEventFishes)
	{
		if (var.room_id == GameData::getInstance()->getRoomID())
		{
			for (auto &var2 : var.fishes)
			{
				if (var2.nFishID == fishid)
				{
					var2.nUserCostCoin++;
					isHava = true;
					break;
				}
			}
			if (isHava == false)
			{
				FishStatInfo info;
				info.nFishID = fishid;
				info.nCatchTimes = 0;
				info.nCreateTimes = 0;
				info.nHitTimes = 0;
				info.nUserCatchTimes = 0;
				info.nUserCostCoin = 1;
				var.fishes.push_back(info);
			}

		}
	}
	}/*
	int roomid = GameData::getInstance()->getRoomID();
	auto str = String::createWithFormat("%d%d%s", roomid,fishid, FISHUSERCOSTCOIN);
	CCLOG("%s", str->getCString());
	auto localdata = UserDefault::getInstance();
	localdata->setIntegerForKey(str->getCString(), localdata->getIntegerForKey(str->getCString(), 0) + 1);
	}*/


void LogEventFish::loadLocalData()
{
	
}
std::string LogEventFish::getDataForJson(FishEventData data)
{
	auto fishes = data.fishes;
	auto m_roomid = data.room_id;
	rapidjson::Document document;
	document.SetObject();
	rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
	rapidjson::Value array(rapidjson::kArrayType);
	
	for (auto var : fishes)
	{
		if (var.nCreateTimes<=0)
		{
			continue;
		}
		rapidjson::Value object(rapidjson::kObjectType);
		object.AddMember("fish_id", var.nFishID, allocator);
		object.AddMember("create_times", var.nCreateTimes, allocator);
		object.AddMember("hit_times", var.nHitTimes, allocator);
		object.AddMember("catch_times", var.nCatchTimes, allocator);
		object.AddMember("catch_times_user", var.nUserCatchTimes, allocator);
		object.AddMember("hit_moneys", var.nUserCostCoin, allocator);
		array.PushBack(object, allocator);
	}	
	document.AddMember("fishes", array, allocator);
	document.AddMember("room_id",m_roomid, allocator);
	document.AddMember("data_type", 1, allocator);
	rapidjson::StringBuffer  buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	document.Accept(writer);
	std::string result = buffer.GetString();
	return result;
}

void LogEventFish::sendDataToServer()
{
	sendMemoryData(); //目前不保存本地

	
}
void LogEventFish::sendMemoryData()
{
	for (auto var : logEventFishes)
	{
		if (var.fishes.size()>0)
		{
			auto jsonStr = getDataForJson(var);
			if (jsonStr.size()>0)
			{
				HttpMannger::getInstance()->HttpToPostRequestLogEvent(getDataForJson(var), 1);
			}
			
		}	
	}
	
}
void LogEventFish::sendLocaLData()
{
	for (int i = 1; i <= 4;i++)
	{
		auto filename = String::createWithFormat("logeventfish_roomid_%d.json");
		filename = String::createWithFormat("%s%s", FileUtils::getInstance()->getWritablePath().c_str(), filename->getCString());
		if (FileUtils::getInstance()->isFileExist(filename->getCString()))
		{
			std::string data = FileUtils::getInstance()->getStringFromFile(filename->getCString());
			HttpMannger::getInstance()->HttpToPostRequestLogEvent(data, 1);
			CCLOG("Remove file %s", FileUtils::getInstance()->removeFile(filename->getCString()) ? "true": "false");
		}
	}
	

}

void LogEventFish::clearLocalData() //TODO::改写成json存储
{
	logEventFishes.clear();
	for (int i = 1; i <= 4; i++)
	{
		FishEventData data;
		data.room_id = i;
		logEventFishes.push_back(data);
	}
	/*auto localdata = UserDefault::getInstance();
	for (int j = 1; j <= 4; j++)
	{
	for (int i = 1; i <= 20; i++)
	{


	auto str = String::createWithFormat("%d%d%s", j, i, FISHCATCHTIME);
	localdata->setIntegerForKey(str->getCString(), 0);

	str = String::createWithFormat("%d%d%s", j, i, FISHCREATETIME);
	localdata->setIntegerForKey(str->getCString(), 0);

	str = String::createWithFormat("%d%d%s", j, i, FISHHITTIMES);
	localdata->setIntegerForKey(str->getCString(), 0);

	str = String::createWithFormat("%d%d%s", j, i, FISHUSERCATCHTIMES);
	localdata->setIntegerForKey(str->getCString(), 0);

	str = String::createWithFormat("%d%d%s", j, i, FISHUSERCOSTCOIN);
	localdata->setIntegerForKey(str->getCString(), 0);

	}
	for (int i = 30; i <= 37; i++)
	{

	auto str = String::createWithFormat("%d%d%s", j, i, FISHCATCHTIME);
	localdata->setIntegerForKey(str->getCString(), 0);

	str = String::createWithFormat("%d%d%s", j, i, FISHCREATETIME);
	localdata->setIntegerForKey(str->getCString(), 0);

	str = String::createWithFormat("%d%d%s", j, i, FISHHITTIMES);
	localdata->setIntegerForKey(str->getCString(), 0);

	str = String::createWithFormat("%d%d%s", j, i, FISHUSERCATCHTIMES);
	localdata->setIntegerForKey(str->getCString(), 0);

	str = String::createWithFormat("%d%d%s", j, i, FISHUSERCOSTCOIN);
	localdata->setIntegerForKey(str->getCString(), 0);
	}
	for (int i = 40; i <= 44; i++)
	{
	auto str = String::createWithFormat("%d%d%s", j, i, FISHCATCHTIME);
	localdata->setIntegerForKey(str->getCString(), 0);

	str = String::createWithFormat("%d%d%s", j, i, FISHCREATETIME);
	localdata->setIntegerForKey(str->getCString(), 0);

	str = String::createWithFormat("%d%d%s", j, i, FISHHITTIMES);
	localdata->setIntegerForKey(str->getCString(), 0);

	str = String::createWithFormat("%d%d%s", j, i, FISHUSERCATCHTIMES);
	localdata->setIntegerForKey(str->getCString(), 0);

	str = String::createWithFormat("%d%d%s", j, i, FISHUSERCOSTCOIN);
	localdata->setIntegerForKey(str->getCString(), 0);
	}
	for (int i = 50; i <= 52; i++)
	{
	auto str = String::createWithFormat("%d%d%s", j, i, FISHCATCHTIME);
	localdata->setIntegerForKey(str->getCString(), 0);

	str = String::createWithFormat("%d%d%s", j, i, FISHCREATETIME);
	localdata->setIntegerForKey(str->getCString(), 0);

	str = String::createWithFormat("%d%d%s", j, i, FISHHITTIMES);
	localdata->setIntegerForKey(str->getCString(), 0);

	str = String::createWithFormat("%d%d%s", j, i, FISHUSERCATCHTIMES);
	localdata->setIntegerForKey(str->getCString(), 0);

	str = String::createWithFormat("%d%d%s", j, i, FISHUSERCOSTCOIN);
	localdata->setIntegerForKey(str->getCString(), 0);

	}
	for (int i = 101; i <= 104; i++)
	{
	auto str = String::createWithFormat("%d%d%s", j, i, FISHCATCHTIME);
	localdata->setIntegerForKey(str->getCString(), 0);

	str = String::createWithFormat("%d%d%s", j, i, FISHCREATETIME);
	localdata->setIntegerForKey(str->getCString(), 0);

	str = String::createWithFormat("%d%d%s", j, i, FISHHITTIMES);
	localdata->setIntegerForKey(str->getCString(), 0);

	str = String::createWithFormat("%d%d%s", j, i, FISHUSERCATCHTIMES);
	localdata->setIntegerForKey(str->getCString(), 0);

	str = String::createWithFormat("%d%d%s", j, i, FISHUSERCOSTCOIN);
	localdata->setIntegerForKey(str->getCString(), 0);

	}
	for (int i = 201; i <= 201; i++)
	{

	auto str = String::createWithFormat("%d%d%s", j, i, FISHCATCHTIME);
	localdata->setIntegerForKey(str->getCString(), 0);

	str = String::createWithFormat("%d%d%s", j, i, FISHCREATETIME);
	localdata->setIntegerForKey(str->getCString(), 0);

	str = String::createWithFormat("%d%d%s", j, i, FISHHITTIMES);
	localdata->setIntegerForKey(str->getCString(), 0);

	str = String::createWithFormat("%d%d%s", j, i, FISHUSERCATCHTIMES);
	localdata->setIntegerForKey(str->getCString(), 0);

	str = String::createWithFormat("%d%d%s", j, i, FISHUSERCOSTCOIN);
	localdata->setIntegerForKey(str->getCString(), 0);

	}
	}*/
}