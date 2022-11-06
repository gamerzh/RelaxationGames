#ifndef __ACCOUNT_PANEL_H__
#define _ACCOUNT_PANEL_H__

#include "cocos2d.h"
USING_NS_CC;

#include "Player.h"

class AccountPanel : public Node
{
public:
	CREATE_FUNC(AccountPanel);
	void getInfoFromPlayer(Player & player);

	void getAccountInfo();

	void showAccountInfo(int niaoNum,int beishu);
	void showBigAccountInfo(Player & player);

	bool showWord(bool isShow, Node & node, Vec2 pos);


	void showPayPoint(bool isUsePickGood,  bool isWin);
	Node* wordBig = nullptr;
private:

	// ÄÚÁªÀà
	class Head : public Node
	{
	public:
		void setInfo(RESULT result, std::string scoreStr, string name, int photoID,int times,int zhongniaofen);

		CREATE_FUNC(Head);
		int id;
	private:
		LabelAtlas* label;
		bool init();
	};
	// end class

	Head* heads[4];
	Node* panel = nullptr;

	Node* wordNode = nullptr;
	Sprite* wordGangKai = nullptr;
	Sprite* wordPengPengHu = nullptr;
	Sprite* wordQingYiSe = nullptr;
	Sprite* wordDaDiaoChe = nullptr;
	Sprite* wordMenQing = nullptr;

	//Sprite* wordKuoHaoL = nullptr;
	//Sprite* wordKuoHaoR = nullptr;
	Sprite* wordZhongNiaoFen = nullptr;
	Sprite* wordNiaoShu = nullptr;

	Sprite*wordBeishu = nullptr;

	Sprite* wordDiFen = nullptr;
	Player* player = nullptr;

	Sprite* wordBigPengPengHu = nullptr;
	Sprite* wordBigQingYiSe = nullptr;
	Sprite* wordBigDaDiaoChe = nullptr;
	Sprite* wordBigFrame = nullptr;
	Sprite* wordBigMenQing = nullptr;

	bool GangKai = false;
	bool DaDiaoChe = false;
	bool PengPengHu = false;
	bool QingYiSe = false;
	bool MenQing = false;

	bool init();

	void backCallBack(Ref* pSender);

	void againCallBack(Ref* pSender);

	static Vec2 typePos[4];
};
#endif