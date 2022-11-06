#ifndef __MAHJONG_EVENT_H__
#define __MAHJONG_EVENT_H__

#include "cocos2d.h"
USING_NS_CC;
enum PLAYER{ PLAYER_0 = 0, PLAYER_1 = 1, PLAYER_2 = 2, PLAYER_3 = 3, PLAYER_NULL = 4 };

enum FLOW_NAME
{
	DEALCARDS,			// 发牌
	
	OPERA_PICK_END,	// 摸牌结束
	OPERA_PLAY_END,	// 打牌结束
	OPERA_PENGGANG_END,  // 碰杠结束
	QI_RETURN_BEFORE,			// 继续
	QI_QIANGGANG_BEFORE,	// 放弃抢杠，之前碰杠的玩家继续摸牌。
	DELETE_TABLE_BEFORE,

	OPERA_ZIMO_END,					// 自摸
	OPERA_DIANPAO_END,			// 点炮
	OPERA_DIAMPAO_ENDALL,		// 点炮结束
	OPERA_QIANGGANG_END,		// 抢杠
	OPERA_QIANGGANG_ENDALL,// 抢杠结束
	GAME_OVER,							// 游戏结束

	Refresh_Coin,         //刷新金币
	WAIT,
};
void addMahjongListener(FLOW_NAME flowName, const std::function<void(EventCustom*)>& callback);
void dispatchMahjongEvent(FLOW_NAME flowName, void *optionalUserData);
void removeMahjongListener(FLOW_NAME flowName);

bool addToTextureCache(std::string path, std::string name, int num);
bool addToTextureCache(std::string path, std::string name);
Texture2D* getTexFromeCache(std::string key);
Animate* createAnimateFromTextureCache(std::string name, int num, float totalTime);

Sprite* addAnimWithAnimate(Node & nodeParent, Animate* & animate, std::string path, std::string name, int num, float time);
Sprite* addAnimNoAnimte(Node & nodeParent, std::string path, std::string name);

PLAYER playerPlusPlus(PLAYER & player);

enum PLAY_MENU
{
	
};

enum PICK_RESULT
{
	PICK_ZIMO,
	PICK_ANGANG,
	PICK_PENGGANG,
	PICK_NEXT,
	PICK_LIUJU,
};

enum PLAY_RESULT
{
	PLAY_PENG,
	PLAY_GANG,
	PLAY_DIANPAO,
	PLAY_NEXT,
	PLAY_PENG_AND_GANG,
	PLAY_PENG_AND_DIANPAO
};



#endif
