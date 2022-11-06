#pragma once
#include "cocos2d.h"
#include "MsgBase.h"
using namespace cocos2d;

class  Msg_onAdd :public Msg_Base
{
public:
	virtual void setBody(const char* msgBody);
	std::string username;
	unsigned long coins;
	unsigned long diamonds;
	int turrent_level;
	int vip_level;
	int box_level;
	int roomPos;
	float catch_per;
};

