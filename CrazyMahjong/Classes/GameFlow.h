#ifndef  __GAME_FLOW_H__
#define __GAME_FLOW_H__
#include "cocos2d.h"
USING_NS_CC;
#include "Player.h"
#include "PlayMenu.h"
#include "MahjongEvent.h"
#include "AccountPanel.h"

// ��Ϸ����
class Rules;

class GameFlow : public Node
{
	// ����...
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

	void onDealCardsBegin(EventCustom* event);		// ���¼������Է���
	void onDealGoodCardsBegin(EventCustom* event);

	void onOperaPickEnd(EventCustom* event);			// ���¼�����������
	void onOperaPlayEnd(EventCustom* event);		// ���¼������˴���
	void onOperaPengGangEnd(EventCustom* event);
	void deleteTableBefore(EventCustom* event);

	void onOperaZiMoEnd(EventCustom* event);
	void onOperaDianPaoEnd(EventCustom* event);			// ���¼��������пɵ��ڵ��˶�ѡ������Ƿ���ں�
	void onOperaQiangGangEnd(EventCustom* event);

	void onGameOver(EventCustom* event);	// ���¼�����Ϸ����׼��ץ��
	void onPeng(EventCustom* event);						// ���¼����������ƣ�
	void onKaiGang(EventCustom* event);					// ���¼������Կ��ܣ�����
	void returnBefore(EventCustom* event);			// ����/���ܺ󣬷�����һ�����.
	void returnPengGang(EventCustom* event);
	void turnToNext();

	// �����ƺ�Ĳ���
	void OperaWhenCanZiMoHu();
	void OperaWhenCanKaiGang();
	
	// �����ƺ�Ĳ���
	void OperaWhenCanDianPaoHu();
	void OperaWhenCanQiangGang();

	void OperaWhenCanPeng();
	void OperaWhenCanGang();
	void OperaWhenCanHu(Player* player);
	void OperaWhenCanPengGang();

	void showAccount(bool isLiuJu);


	void showReadPack();

	void sortCardForAll();

	PLAYER currentPlayer;		// ��ǰ���в��������
	PLAYER beforePlayer;		// ֮ǰ���в��������

	Player* players[4];		// �ĸ����
	CC_SYNTHESIZE(bool, isGameOver, _isGameOver);


	int tmepIndex = 0;
};

#endif
