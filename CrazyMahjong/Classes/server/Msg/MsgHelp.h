#pragma once
#include "cocos2d.h"
#include "MSGstdafx.h"
using namespace cocos2d;


class MsgHelp
{
public:
	static Msg_Base*getInfoByMsg(const char* msgId, const char* msgBody);
};