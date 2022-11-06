#pragma once
#include "cocos2d.h"
#include "MsgBase.h"
using namespace cocos2d;


struct MsgUpdateTurrentInfo
{
	int requireDiamonds;
	int rewards;
	int turrent_level;

};



///todo: 303 vip等级不够，304， 炮台等级不够
class  Msg_OnUpdateTurrent :public Msg_Base
{
public:
	virtual void setBody(const char* msgBody);	
	MsgUpdateTurrentInfo _info;
	int errorcode;
};

