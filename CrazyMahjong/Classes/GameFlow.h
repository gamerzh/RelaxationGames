#ifndef  __GAME_FLOW_H__
#define __GAME_FLOW_H__
#include "cocos2d.h"
USING_NS_CC;
#include "Player.h"
#include "PlayMenu.h"
#include "MahjongEvent.h"
#include "AccountPanel.h"

// 游戏流程
class Rules;

class GameFlow : public Node
{
	// 神奇...
	friend class Rules;		
	friend class MahjongAnim;

public:
	CREATE_FUNC(GameFlow);

	void ZiMo(PLAYER playerHu);
	void dianPao(PLAYER playerHu);

	Rules* pRules;
private:
	void onEnter() override;
	void onExit() override;
	bool init();
	void initPlayers();
	AccountPanel* panel = nullptr;
	PlayMenu* initMenu();
	void addGameFlowEvent();

	void dealACard(float dt);
	void startGame(float dt);

	void onDealCardsBegin(EventCustom* event);		// 【事件】可以发牌
	void onDealGoodCardsBegin(EventCustom* event);

	void onOperaPickEnd(EventCustom* event);			// 【事件】有人摸牌
	void onOperaPlayEnd(EventCustom* event);		// 【事件】有人打牌
	void onOperaPengGangEnd(EventCustom* event);
	void deleteTableBefore(EventCustom* event);

	void onOperaZiMoEnd(EventCustom* event);
	void onOperaDianPaoEnd(EventCustom* event);			// 【事件】当所有可点炮的人都选择完毕是否点炮后
	void onOperaQiangGangEnd(EventCustom* event);

	void onGameOver(EventCustom* event);	// 【事件】游戏结束准备抓鸟
	void onPeng(EventCustom* event);						// 【事件】可以碰牌，
	void onKaiGang(EventCustom* event);					// 【事件】可以开杠，暗杠
	void returnBefore(EventCustom* event);			// 弃碰/弃杠后，返回上一个玩家.
	void returnPengGang(EventCustom* event);
	void turnToNext();

	// 摸完牌后的操作
	void OperaWhenCanZiMoHu();
	void OperaWhenCanKaiGang();
	
	// 打完牌后的操作
	void OperaWhenCanDianPaoHu();
	void OperaWhenCanQiangGang();

	void OperaWhenCanPeng();
	void OperaWhenCanGang();
	void OperaWhenCanHu(Player* player);
	void OperaWhenCanPengGang();

	void showAccount(bool isLiuJu);


	void showReadPack();

	void sortCardForAll();

	PLAYER currentPlayer;		// 当前进行操作的玩家
	PLAYER beforePlayer;		// 之前进行操作的玩家

	Player* players[4];		// 四个玩家
	CC_SYNTHESIZE(bool, isGameOver, _isGameOver);


	int tmepIndex = 0;
};

#endif
