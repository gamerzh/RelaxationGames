#pragma once
#include "cocos2d.h"
#include "server/HttpClientUtill.h"
#include "HttpMsgDefine.h"

using namespace cocos2d;
//ÄÚÍø
//#define URL_HEAD_FIX "http://172.23.1.54:1701" 
//#define URL_HEAD "http://172.23.1.54:1701" 
//#define TCPIDURL "172.23.1.54" 
//ÕýÊ½
#define TCPIDURL HttpMannger::getInstance()->getGameUrl().c_str()
#define URL_HEAD_FIX "http://106.75.141.82:1701"
#define URL_HEAD  HttpMannger::getInstance()->getCurUrl().c_str()




#define URL_BASECONFIG  "/config/get/base"
#define URL_REGISTER  "/user/hello"
#define URL_LOGIN  "/user/login"
#define URL_PAY  "/mo/order/booking"
#define URL_CANCELORDER "/mo/order/cancel"
#define URL_SYNCINFO  "/player/info/sync/fortuneInfo"
#define URL_SETNAME  "/user/nickname"
#define URL_FEEDBACK "/help/feedback"
#define URL_LOGEVENTFISH "/statistics/data"
#define URL_DEMANDENTRY "/mr/order/result"
#define URL_BROKE "/bankrupt/broke"
#define URL_REBRITH "/bankrupt/rebirth"
#define URL_PLAYERINFO "/player/info/get"
#define URL_ITEMINFO "/player/info/bag/get"
#define URL_BUYITEM "/player/info/bag/buy"
#define URL_BIND "/user/nickname/bind/"
#define URL_BYNICKNAME "/user/nickname/login"
#define URL_REGISTERFORWARDLY "/user/register"
#define URL_CDKEY "/cdkey/get"
#define URL_OPENBOX "/bag/chest/get"
#define URL_GETMISSIONLIST "/gametask/everyday"
#define URL_GETMISSIONREWARD "/gametask/everyday/getreward"
#define URL_GETACHIEVELIST "/gametask/achievement"
#define URL_GETACHIEVEREWARD "/gametask/achievement/getreward"
#define URL_GETNACTIVEINFO "/activity/config"
#define URL_GETNOBILITYINFO "/nobility/surplus"
#define URL_GETNOBILITYREWARD "/nobility/today/reward"
#define URL_MARQUEE  "/marquee/config"
#define URL_GETROOMINFO  "/room/roominfo"
#define URL_GETVIPCOINS  "/vip/getrewards"
#define URL_CHANGEGFIT  "/change/getrewards"
#define URL_GETRECORDGFIT "/change/getrecord"
#define URL_GETEMAILLIST "/mailbox/info/list/get"
#define URL_GETEMAILREWARDSINGLE "/mailbox/info/reward/get"
#define URL_GETEMAILREWARDALL "/mailbox/info/reward/get/all"
#define URL_GETEMAILREWARDPLURAL "/mailbox/info/list/get"
#define URL_GETSENDPRESENT "/present/give"
#define URL_GETREDBAGKEY "/hongbao/get"
#define URL_GETWXSHAREDINFO "/hongbao/shareinfo/get"

struct setNameRequest
{
	const char* nickname;
	int gender;
};
enum HTTP_TYPE
{
	Req_Register,
	Req_Login,
	Req_LoginByName,
	Req_BeforePay,
	Req_AfterPay,
	Req_SyncInfo,
	Req_SetName,
	Req_BindName,
	Req_FeedBack,
	Req_DemandEntry,
	Req_CancelOrder,
	Req_GetUserInfo,
	Req_GetItemInfo,
	Req_BuyItem

};
class HttpMannger {

public:
	static HttpMannger* getInstance();
	
private:

	HttpMannger();
    void init();
	static HttpMannger* _instance;
};


