#pragma once
#include "cocos2d.h"
#include "MsgBase.h"
using namespace cocos2d;


class  Msg_Payresult :public Msg_Base
{
public:
	virtual void setBody(const char* msgBody);
	std::string msg;
};
