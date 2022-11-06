#pragma once
#include "cocos2d.h"
#include "MsgBase.h"
#include "server/HttpMsgDefine.h"
using namespace cocos2d;

class  Msg_OnBossDead :public Msg_Base
{
public:
	virtual void setBody(const char* msgBody);
	std::vector<RewardValue> _items;
private:
	
};

