#ifndef __MAHJONG_EVENT_H__
#define __MAHJONG_EVENT_H__

#include "cocos2d.h"
USING_NS_CC;
enum PLAYER{ PLAYER_0 = 0, PLAYER_1 = 1, PLAYER_2 = 2, PLAYER_3 = 3, PLAYER_NULL = 4 };

enum FLOW_NAME
{
	DEALCARDS,			// ����
	
	OPERA_PICK_END,	// ���ƽ���
	OPERA_PLAY_END,	// ���ƽ���
	OPERA_PENGGANG_END,  // ���ܽ���
	QI_RETURN_BEFORE,			// ����
	QI_QIANGGANG_BEFORE,	// �������ܣ�֮ǰ���ܵ���Ҽ������ơ�
	DELETE_TABLE_BEFORE,

	OPERA_ZIMO_END,					// ����
	OPERA_DIANPAO_END,			// ����
	OPERA_DIAMPAO_ENDALL,		// ���ڽ���
	OPERA_QIANGGANG_END,		// ����
	OPERA_QIANGGANG_ENDALL,// ���ܽ���
	GAME_OVER,							// ��Ϸ����

	Refresh_Coin,         //ˢ�½��
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
