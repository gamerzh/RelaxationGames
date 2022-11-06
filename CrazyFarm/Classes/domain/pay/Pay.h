#ifndef _PAY_H_
#define _PAY_H_
#include "cocos2d.h"
#include "PayPointConfig.h"
using namespace cocos2d;

struct payRequest
{
	std::string sessionid;
	int pay_and_Event_version;
	int pay_event_id;
	int pay_point_id;
	std::string channel_id;
	std::string orderID;
	int third_payType =1; //0:斯凯支付1:支付宝 2:微信
	//微信参数
	std::string wx_nonceStr;//随机字符串
	std::string wx_prepayid;//微信订单号
	std::string wx_sign;//微信签名
	std::string wx_timestamp;//微信时间戳
};

struct prepayidAndReqNum
{
	std::string prepayid;
	int reqnum;
};

enum PayState
{
	UnDoing,//未在进行
	OrderBooking,//下单中
	WxPaying,//在微信APP支付中
	DemandEntrying//查询订单中
};


class Pay:public Node {

public:
    static Pay* getInstance();


	void Overbooking(int paypoint, int eventPoint,Node*paynode);
	
	void setPayState(PayState state){ m_state = state; };
	
	void jniCallBack(int code, const char*msg, const char* prepayid);
	

	void pay(payRequest*data);//起支付插件
	void payCallBack(int code, const char* msg, std::string prepayid);
	void update(float dt);
	void DemandEntry(int reqNum,std::string prePayid);//最多请求两次



	void CancelTheOrder();

	std::string getOrderIdByprepayid(std::string prepayid);
	std::string getPrepayIdByOrderid(std::string orderid);


	bool getIsPaying(){ return m_state!=UnDoing; };
private:
	
	void OverbookingActual(int paypoint, int eventPoint);//下单
	PayPointInfo getInfoByPaypoint(int paypoint);
    Pay();
    bool init();
    static Pay* _instance;
	std::map<std::string, payRequest*>  prepayidToPayRequest;

	std::string nowPayOrderId;


	PayState m_state = UnDoing;
	int payResult = -1;   //初始值-1,成功1，3,查单，失败2
	
	std::string wx_cb_prepayid;
	
};

#endif
