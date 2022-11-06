#pragma once
#include "cocos2d.h"
#include "MsgBase.h"
using namespace cocos2d;


class  Msg_OnBankrupt :public Msg_Base
{
public:
	virtual void setBody(const char* msgBody);	
	int wait_time; 
	int left_times;
	int coins;
};

