#pragma once
#include "cocos2d.h"
#include "MsgBase.h"
#include "config/ConfigExp.h"
using namespace cocos2d;



class  Msg_OnExpUpdate :public Msg_Base
{
public:
	virtual void setBody(const char* msgBody);	
	int errorcode;

	std::vector<std::vector<LevelRewardItem>> _infos;

};

