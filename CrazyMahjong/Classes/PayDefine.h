#pragma once
#pragma execution_character_set("utf-8")
#include "cocos2d.h"

enum PAYPOINT
{
	FIRSTPAYGFIT = 1,
	VIPGIFT,
	COINGIFT,
	COIN_18,
	COIN_28,
	COIN_58,
	COIN_88,
	INVALID = -1
};

struct PayItem
{
	PAYPOINT PPoint;
	int PPrice;
	int PPropNum;
	int PPpropType; //1:VIP  2:COIN
	PayItem(PAYPOINT point, int price, int propnum, int proptype) :PPoint(point), PPrice(price), PPropNum(propnum), PPpropType(proptype){};
};

enum PayResult
{
	Pay_Cancel,
	Pay_Success,
	Pay_Failed
};
#define MSG_PAYBASE "msg_paybase"


