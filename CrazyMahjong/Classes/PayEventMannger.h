#pragma once
#include "cocos2d.h"
using namespace cocos2d;
#define CC_SYNTHESIZELOCALINT(KeyName, funName,initValue)\
public: int get##funName(void) const { return UserDefault::getInstance()->getIntegerForKey(KeyName,initValue); }\
public: void set##funName(int var){ UserDefault::getInstance()->setIntegerForKey(KeyName,var); }



#define CC_SYNTHESIZELOCALFLOAT(KeyName, funName,initValue)\
public: float get##funName(void) const { return UserDefault::getInstance()->getFloatForKey(KeyName,initValue); }\
public: void set##funName(float var){ UserDefault::getInstance()->setFloatForKey(KeyName,var); }

enum EventToPoint
{
	Event_1 = 1,
	Event_2,
	Event_3,
	Event_4,
	Event_5,
	Event_6,
	Event_7,
	Event_8,
	Event_9,
	Event_10,
	Event_11,
	Event_12,
	Event_13,
	Event_14,
	Event_15
};
//具体条件描述参照
//	json/event2pay.json
class PayEventMannger{
public:
	static PayEventMannger* getInstance();
private:
	PayEventMannger();
	static PayEventMannger* _instance;
	void init();
public:
	void RecordInfoOnGamestart();
	void RecordInfoOnGameend(bool IsDelevel, bool IsGainAlms, bool isWin, bool isCouldUpdateRoom);
	bool isSatisfied_Event_5(bool isPickGood);//一局结束，如果玩家用了发好牌且刚好用完，弹出提示
	bool isSatisfied_Event_8(bool isPickGood);//使用免费发好牌后胜利，弹出
	bool isSatisfied_Event_9();//首次进入弹出
	bool isSatisfied_Event_10(int roomCoin);//银币低于房间进入所需最低值时弹出
	bool isSatisfied_Event_7();//第一局结束弹出
	bool isSatisfied_Event_11();//每玩12盘，若用户从未付费成功过，弹出
	bool isSatisfied_Event_12();//玩家上一局是房间降级+上一局结束领过救济金+玩家当前赢+玩家当前的金币数还不能升级房间，之前已经2次满足这4个条件，弹出，送送买
	bool isSatisfied_Event_13();//玩家点击开始游戏按钮，银币不足1000弹出，这个优先级低于其他事件点
	bool isSatisfied_Event_14();//玩家上一局是房间降级+上一局结束领过救济金+玩家当前赢+玩家当前的金币数还不能升级房间，每第一、二次满足这4个条件，弹出，送送买
	bool isSatisfied_Event_15();//购买过银币礼包+发好牌次数用完+游戏输，符合该要求的每3盘，弹出
public://统计信息
	CC_SYNTHESIZELOCALINT("_Gamecount", Gamecount, 0); //游戏局数
	CC_SYNTHESIZELOCALINT("_IsPay", IsPay, 0); //是否支付过
	CC_SYNTHESIZELOCALINT("_IsPay_Coin", IsPay_Coin, 0); //是否支付过银币礼包
	CC_SYNTHESIZELOCALINT("_IsPay_PickGood", IsPay_PickGood, 0); //是否支付过发好牌
	CC_SYNTHESIZELOCALINT("isSatisfied_Event_15_count", isSatisfied_Event_15_count, 0); //是否满足事件点15的次数
	CC_SYNTHESIZELOCALINT("isSatisfied_Event_12or14_count", isSatisfied_Event_12or14_count, 0); //满足事件点12或14的次数

	CC_SYNTHESIZE(bool, isLastGameDelevel, _isLastGameDelevel);//上一句是否降级
	CC_SYNTHESIZE(bool, isLastGainAlms, _isLastGainAlms);//上一句是否领取过救济金

	CC_SYNTHESIZE(bool, isSatisfied_Event12, _isSatisfied_Event12);//是否满足计费点12
	CC_SYNTHESIZE(bool, isSatisfied_Event14, _isSatisfied_Event14);//是否满足计费点14
	CC_SYNTHESIZE(bool, isSatisfied_Event15, _isSatisfied_Event15);//是否满足计费点15

};

	