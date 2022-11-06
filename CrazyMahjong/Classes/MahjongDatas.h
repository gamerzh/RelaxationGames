/// 麻将数据类

#ifndef __MAHJONG_DATAS_H__
#define __MAHJONG_DATAS_H__

#include <vector>
using namespace std;
enum TYPE{TONG, WAN, NOTYPE};
#include "Card.h"


//1-9   一万-九万
//-1 - -9  九筒-一筒
//此处wan和tong相反。

class MahjongDatas
{
public:
	static MahjongDatas* getInstance()
	{
		if (nullptr == instance)
		{
			instance = new MahjongDatas();
		}

		return instance;
	}
	void initData();
	int getCardNum();
	int goodCardTimes = 3;
	/// 抽取一张牌,
	void initGoodType();
	int popACard();
	int popAGoodCard(vector<Card*> cardInHand);
	int popTong();
	int popWan();
	TYPE goodCard = NOTYPE;

	void reviewAllCards();

	bool isFalseCard = false;
private:
	// ========== Function ============
	MahjongDatas();
	// 初始化牌

	// ========== Member ============
	// 麻将数据单例
	static MahjongDatas* instance;

	// 剩余牌 characters万(1~9)  circles筒(-1~-9)
	vector<int> cardsTong;
	vector<int> cardsWan;
	// 已经打出的牌
	vector<int> playedCards;// 假牌



};

#endif