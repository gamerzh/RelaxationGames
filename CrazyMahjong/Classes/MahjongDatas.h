/// �齫������

#ifndef __MAHJONG_DATAS_H__
#define __MAHJONG_DATAS_H__

#include <vector>
using namespace std;
enum TYPE{TONG, WAN, NOTYPE};
#include "Card.h"


//1-9   һ��-����
//-1 - -9  ��Ͳ-һͲ
//�˴�wan��tong�෴��

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
	/// ��ȡһ����,
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
	// ��ʼ����

	// ========== Member ============
	// �齫���ݵ���
	static MahjongDatas* instance;

	// ʣ���� characters��(1~9)  circlesͲ(-1~-9)
	vector<int> cardsTong;
	vector<int> cardsWan;
	// �Ѿ��������
	vector<int> playedCards;// ����



};

#endif