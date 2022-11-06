#pragma once
#include "cocos2d.h"
#include "MsgBase.h"
#include "domain/room/RoomManager.h"
using namespace cocos2d;




class  Msg_OnFishes :public Msg_Base
{
public:
	virtual void setBody(const char* msgBody);

	std::vector<std::string> eventstrs;
	
	MsgFishesInfo _info;
};

