#pragma once
#include "cocos2d.h"
#include "MsgBase.h"
using namespace cocos2d;

class  Msg_UseSkill :public Msg_Base
{
public:
	virtual void setBody(const char* msgBody);
	int use_type; //0:µÀ¾ß 1£º×êÊ¯
	int price;
	int num;
	int itemid;
	int errorcode;
	std::string errormsg;
};

