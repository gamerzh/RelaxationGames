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
	// 发牌回调
	void dealGoodBtnCallBack(Ref* pSender);
	
	// 碰杠的回调
	void pengCallback(Ref* pSender);		// 别人打牌自己碰
	void qiPengCallback(Ref* pSender);

	void gangCallback(Ref* pSender);		// 别人打牌，自己有3张，可碰可杠时的杠
	void qiGangCallback(Ref* pSender);

	void pengGangCallback(Ref* pSender);	// 自己摸牌，续杠时的杠
	void qiPengGangCallback(Ref* pSender);

	void anGangCallback(Ref* pSender);	// 自己摸牌，手中有3张，自己暗杠
	void qiAnGangCallback(Ref* pSender);
	// 胡的回调
	void ziMoCallback(Ref* pSender);			// 自摸胡
	void qiZiMoHuCallback(Ref* pSender);

	void dianPaoCallback(Ref* pSender);	// 点炮胡
	void qiDianPaoCallback(Ref* pSender);

	void qiangGangCallback(Ref* pSender);	// 抢杠胡
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
