/// �����Ϣ
// ������������ң�λ�ã�ͷ�񣩣������б������б�
// ÿ��player��һ��MahJongDrawer����������Լ���Mahjongs��

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
USING_NS_CC;

#include <vector>
using namespace std;

#include "Card.h"
#include "MahjongDrawer.h"
#include "MahjongEvent.h"

enum RESULT{NEUTRAL, ZIMO, HU, DIANPAO, LOSE };
class PlayMenu;

class Player : public Node
{
public:
	CREATE_FUNC(Player);
	// ����
	static Player* createPlayer(PLAYER playerIndex);

	// ����
	Card* operaPick();
	void goOnOperaPick();

	// ����
	void operaPlay();
	void playACard(Card* card);

	// ��
	void operaPeng();
	void peng();
	bool kaiPeng();

	// ��
	void operaGang();
	void gang();
	// ����
	void operaAnGang();
	void anGang();
	// ����
	void operaPengGang();
	void pengGang();
	// ����
	void kaiGang(bool isMingGang);
	
	// ����
	void operaZiMo();
	void ziMo();
	// ����
	void operaDianPao();
	void dianPao();
	// ����
	void operaQiangGang();
	void qiangGang();

	int addNiaoNum();

	bool initLogo();

	void showCards();//�Ƶ���

	void updateName();
	void updateCoin();
	void setTimes();
	// ����һ��ǵ���
	CC_SYNTHESIZE(bool, isZhuang, _isZhuang);
	CC_SYNTHESIZE(bool, isPlayer, _isPlayer);
	// �Ƿ���Բ���
	CC_SYNTHESIZE(bool, CanOpera, _CanOpera);
	CC_SYNTHESIZE(bool, isPickGood, _isPickGood);
	// �����ͷ���
	CC_SYNTHESIZE(int, FanShu, _FanShu);
	CC_SYNTHESIZE(int, Score, _Score);
	// �Ƿ���Ժ�
	CC_SYNTHESIZE(bool, canHu, _canHu);
	// ���Ľ�����䣬Ӯ��
	CC_SYNTHESIZE(RESULT, Result, _Result);
	// Ӯ��֮�������
	CC_SYNTHESIZE(bool, QingYiSe, _QingYiSe);					// ���Ժ�֮����ж���һɫ
	CC_SYNTHESIZE(bool, DaDiaoChe, _DaDiaoChe);			// �����ƺ�
	CC_SYNTHESIZE(bool, PengPengHu, _PengPengHu);		// AABBB
	CC_SYNTHESIZE(bool, GangKai, _GangKai);					// ���������ܺ����ܶ�Ҫ����Ϊture��
	CC_SYNTHESIZE(int, NiaoNum, _NiaoNum);					// ץ�����������
	CC_SYNTHESIZE(int, ZhongNiaoFen, _ZhongNiaoFen);					// ץ�����������
	CC_SYNTHESIZE(int, Multiple, _multiple);					// �еı���
	MahjongDrawer* drawer;	// ����
	static PlayMenu* playMenu;
private:
	bool init();
	// �õ�ĳ���¿����ڵ�ǰ������Ӧ�����ĸ�λ��
	int getNewCardLocation(int type);
	void addHeadPortrait(int dir);

public:
	void turnOnLight();
	void turnOffLight(float dt);
private:
	static Vec2 lightPos;
	Vec2 pos;								// λ��
	string name;						// ����ǳ�
	int coins;								// ��ҽ��
	Sprite* light = nullptr;
};
#endif