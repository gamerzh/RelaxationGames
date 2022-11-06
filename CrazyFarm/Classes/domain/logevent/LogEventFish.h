#pragma once
#include "cocos2d.h"
using namespace cocos2d;


struct FishStatInfo
{
	int nFishID;
	int nCreateTimes;
	int nCatchTimes;
	int nHitTimes;
	int nUserCatchTimes;
	int nUserCostCoin;
};
struct FishEventData
{
	int room_id;
	std::vector<FishStatInfo> fishes;

};
class LogEventFish {

public:
	static LogEventFish* getInstance();
	
	
	void clearLocalData();
	void addFishCreateTimes(int fishid);
	void addFishCatchTimes(int fishid);
	void addFishHitTimes(int fishid);
	void addFishUserCatchTimes(int fishid);
	void addFishUserCostCoin(int fishid, int coin);
	void sendDataToServer();

	void sendLocaLData();
	void sendMemoryData();
	
private:
	void loadLocalData();
	LogEventFish();
	std::string getDataForJson(FishEventData data);
	static LogEventFish* _instance;
	std::vector<FishEventData> logEventFishes;
	const char* FISHCREATETIME = "FISHCREATETIME";
	const char* FISHCATCHTIME = "FISHCATCHTIME";
	const char* FISHUSERCATCHTIMES = "FISHUSERCATCHTIMES";
	const char* FISHUSERCOSTCOIN = "FISHUSERCOSTCOIN";
	const char* FISHHITTIMES = "FISHHITTIMES";
};


