#pragma once
#include "cocos2d.h"
#include "MsgBase.h"
using namespace cocos2d;


class  Msg_LuckDraw :public Msg_Base
{
public:
	virtual void setBody(const char* msgBody);
	int errorCode;
	int itemid;
	int num;
};
