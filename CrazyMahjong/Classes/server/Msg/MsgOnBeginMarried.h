#pragma once
#include "cocos2d.h"
#include "MsgBase.h"
using namespace cocos2d;



class  Msg_OnBeginMarried :public Msg_Base
{
public:
	virtual void setBody(const char* msgBody);
	int _taskID;
	int _lefttime;//√Î
	std::vector<MarriedTaskFishItem> _items;

	
};

