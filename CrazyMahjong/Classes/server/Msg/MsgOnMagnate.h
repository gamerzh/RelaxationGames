#pragma once
#include "cocos2d.h"
#include "MsgBase.h"
using namespace cocos2d;
struct MagnateData
{
	int itemid;
	int num;
};

class  Msg_OnMagnate :public Msg_Base
{
public:
	virtual void setBody(const char* msgBody);	
	std::vector<MagnateData> items;
};

