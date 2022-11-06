//
//  MsgObserver.h
//  LearnCppCode
//
//  Created by molo on 16/3/8.
//  Copyright © 2016年 molo. All rights reserved.
//

#ifndef MsgObserver_h
#define MsgObserver_h
#include "cocos2d.h"
enum EnumRequestID
{
	MJ_Request_TEST,
};

class MsgObserver
{
public:
	virtual void handle_event(EnumRequestID request, const char* msgBody) = 0;
};

#endif /* MsgObserver_h */
