#pragma once
#include "cocos2d.h"
using namespace cocos2d;


class SignManager {

public:
	static SignManager* getInstance();
private:
	SignManager();
	static SignManager*_instance;
public:
	
	int  getCurrentSignDay();
	void sign(int seqDay);
};

