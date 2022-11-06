#pragma once
#include "cocos2d.h"
using namespace cocos2d;
struct playerInfo
{
	int  nId;
	int  nLevel;
	int  nCoin;
	int	 nDiamond;
	bool nIsVip = false;

	
};

enum 
{
	kTagCoinFrame0 = 0,
	kTagCoinFrame1 = 1,
	kTagCoinFrame2 = 2,
	kTagCoinFrame3 = 3,
};

enum
{
	kZorderMenu = 20,
	kZorderDialog = 30,
	kZorderNet = 11,
	kZorderBullet = 12,
	kZorderTurrent = 13
};
enum FishZorder
{
	kZorderFishS = 5,
	kZorderFishM = 6,
	kZorderFishL = 7,
	kZorderFishXL = 8
};



#define CC_SYNTHESIZELOCALINT(KeyName, funName,initValue)\
public: int get##funName(void) const { return UserDefault::getInstance()->getIntegerForKey(KeyName,initValue); }\
public: void set##funName(int var){ UserDefault::getInstance()->setIntegerForKey(KeyName,var); }



#define CC_SYNTHESIZELOCALFLOAT(KeyName, funName,initValue)\
public: float get##funName(void) const { return UserDefault::getInstance()->getFloatForKey(KeyName,initValue); }\
public: void set##funName(float var){ UserDefault::getInstance()->setFloatForKey(KeyName,var); }