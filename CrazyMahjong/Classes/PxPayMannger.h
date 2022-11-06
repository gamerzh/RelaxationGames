#pragma once
#include "cocos2d.h"
#include "BasePayLayer.h"
#include "Jniutill.h"
#include "PayDefine.h"


enum PayState
{
	UnDoing,//δ�ڽ���
	OrderBooking,//�µ���
	SdkPaying,//��΢��APP֧����
	DemandEntrying//��ѯ������
};

using namespace cocos2d;
class PxPayMannger{
public:
	static PxPayMannger* getInstance();
	void LaughPayLayer(PAYPOINT paypoint, Node* parents, std::function<void(EventCustom*)> callback = [](EventCustom*event){; });
	void LaughCoinPayLayer(Node* parents);

	static PayItem getItemByPaypoint(PAYPOINT point);
	void doWxPay(PAYPOINT paypoint,  std::function<void(EventCustom*)>  payCallBack = nullptr);

	bool getIsOnpaying(){ return isOnPaying; };
	void setIsOnPaying(bool isOnpaying){ isOnPaying = isOnpaying; };
private:
	PxPayMannger();
	static PxPayMannger* _instance;
private:
	bool isOnPaying = false;
};

	