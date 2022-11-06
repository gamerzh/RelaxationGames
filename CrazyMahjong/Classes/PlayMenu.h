#ifndef __PLAY_MENU_H__
#define __PLAY_MENU_H__

#include "cocos2d.h"
USING_NS_CC;

#include "MahjongEvent.h"
#include "Player.h"

class GameFlow;

class MahjongControler;

class PlayMenu : public Node
{
public:
	CREATE_FUNC(PlayMenu);
	void getPlayer(Player* const player);

	void ShowPengButton();
	void ShowAnGangButton();
	void ShowPengGangButton();
	void ShowPengAndGang();
	void ShowQiangGangButton();

	void ShowZiMoButton();
	void ShowDianPaoButton();
	void ShowDianPaoAndPengButton();
	void getInfo(int newCoins, int newTimes);
	void dealBtnCallBack(Ref* pSender);

	void hideBack(){ roomInfoNode->runAction(MoveBy::create(0.5f, Vec2(-55, 0))); };
private:
	bool init();

	void hide();
	// ���ƻص�
	void dealGoodBtnCallBack(Ref* pSender);
	
	// ���ܵĻص�
	void pengCallback(Ref* pSender);		// ���˴����Լ���
	void qiPengCallback(Ref* pSender);

	void gangCallback(Ref* pSender);		// ���˴��ƣ��Լ���3�ţ������ɸ�ʱ�ĸ�
	void qiGangCallback(Ref* pSender);

	void pengGangCallback(Ref* pSender);	// �Լ����ƣ�����ʱ�ĸ�
	void qiPengGangCallback(Ref* pSender);

	void anGangCallback(Ref* pSender);	// �Լ����ƣ�������3�ţ��Լ�����
	void qiAnGangCallback(Ref* pSender);
	// ���Ļص�
	void ziMoCallback(Ref* pSender);			// ������
	void qiZiMoHuCallback(Ref* pSender);

	void dianPaoCallback(Ref* pSender);	// ���ں�
	void qiDianPaoCallback(Ref* pSender);

	void qiangGangCallback(Ref* pSender);	// ���ܺ�
	void qiQiangGangCallback(Ref* pSender);

	Player* player;
	MenuItemImage* peng;
	MenuItemImage* gang;
	MenuItemImage* hu;
	MenuItemImage* qi;

	LabelAtlas* label = nullptr;
	LabelAtlas* labelTimes = nullptr;
	Node* roomInfoNode = nullptr;

};

#endif // !__PLAY_MENU_H__
