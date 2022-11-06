#pragma once
#include "cocos2d.h"
#include "utill/define.h"
#include "config/ConfigBankrupt.h"
#include "server/HttpMannger.h"
using namespace cocos2d;
class PlayerTurret;
class BankruptManager {

public:
    static BankruptManager* getInstance();
    
    ///向服务器请求生成破产宝箱
	void RequestServerToBroke(PlayerTurret* turret);
	void onHttpRequestCompletedForBroke(HttpClient *sender, HttpResponse *response);
	///向服务器请求领取破产宝箱
	void RequestServerToRebirth();
	void onHttpRequestCompletedForRebirth(HttpClient *sender, HttpResponse *response);
	

    Bankrupt getBankrupt();
	Bankrupt getRobotBankrupt();
    void addTodayRequestTime();
private:
    BankruptManager();
    void init();
    static BankruptManager* _instance;
    
	CC_SYNTHESIZE(Node*, m_getRewardNode, getRewardNode);
    int getTodayRequestTimes(); //已经领过几次
	const char* BankruptData = "BankruptData";
	CC_SYNTHESIZELOCALINT(BankruptData, BankruptData, 0);
	//DAY 
	int getDayCnt(const char* key);
	void addDayCnt(const char* key);
	int  XygGetToday();

};

