/// 绘制麻将

#ifndef __MAHJONG_DRAWER_H__
#define __MAHJONG_DRAWER_H__

#include "cocos2d.h"
#include "MahjongEvent.h"
USING_NS_CC;

#include <vector>
using namespace std;

#include "Card.h"

class MahjongDrawer : public Node
{
public:
	CREATE_FUNC(MahjongDrawer);
	bool init();
	void setDrawer(PLAYER dir);
	
	Card* drawHandCard(int id);
	Card* drawTableCard(Card* card);
	Card* drawTableCardAI(Card* card);
	Card* drawTableCardPlayer(Card* card);

	void drawSideCard(int type, int sideNum, CARD_SIDE side);

	void drawPengCard(int type,int pickDir);

	void remove4CardInHand();
	void remove3CardInHand();
	void remove2CardInHand(int pengType);
	void remove1CardInHand();
	void remove1CardInTable();

	Node* sideNode;
	Node* handNode;
	Node* tableNode;

	vector<Card*> cardInSide;		// 碰杠的牌
	vector<Card*> cardInHand;	// 手牌
	vector<Card*> cardInTable;	// 打出的牌
	void logHand();

	void sortData();
	void sortCard(bool isAfterPick = false);

	int operator [] (int index) {
		if (index > 4){ index %= 5; }
		return cardInHand.at(index)->get_type();
	}
	CC_SYNTHESIZE(PLAYER, dir, _dir);

	static float timePickCard;
	static float timePlayCard;
	static float timePlayingCard;
	static float timeKaiGang;
	static Vec2 cardPickDis[4];

	Vec2 cardHandPos[5];				// 手牌

	void showCards();
private:
	/// 四个方向初始位置
	static Vec2 cardSidePos[4];
	static Vec2 cardTablePos[4];
	static Vec2 cardOutHandDis[4];


	Card* nowPickCard;
	Vec2 cardBigCard[4];

	int tableRow = 7;


};

#endif // end MahjongScene.h


