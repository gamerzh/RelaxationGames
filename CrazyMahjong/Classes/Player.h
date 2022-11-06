/// 玩家信息
// 包括姓名，金币，位置（头像），手牌列表，出牌列表
// 每个player有一个MahJongDrawer，负责绘制自己的Mahjongs。

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
	// 创建
	static Player* createPlayer(PLAYER playerIndex);

	// 摸牌
	Card* operaPick();
	void goOnOperaPick();

	// 打牌
	void operaPlay();
	void playACard(Card* card);

	// 碰
	void operaPeng();
	void peng();
	bool kaiPeng();

	// 杠
	void operaGang();
	void gang();
	// 暗杠
	void operaAnGang();
	void anGang();
	// 碰杠
	void operaPengGang();
	void pengGang();
	// 开杠
	void kaiGang(bool isMingGang);
	
	// 自摸
	void operaZiMo();
	void ziMo();
	// 点炮
	void operaDianPao();
	void dianPao();
	// 抢杠
	void operaQiangGang();
	void qiangGang();

	int addNiaoNum();

	bool initLogo();

	void showCards();//推倒牌

	void updateName();
	void updateCoin();
	void setTimes();
	// 是玩家还是电脑
	CC_SYNTHESIZE(bool, isZhuang, _isZhuang);
	CC_SYNTHESIZE(bool, isPlayer, _isPlayer);
	// 是否可以操作
	CC_SYNTHESIZE(bool, CanOpera, _CanOpera);
	CC_SYNTHESIZE(bool, isPickGood, _isPickGood);
	// 番数和分数
	CC_SYNTHESIZE(int, FanShu, _FanShu);
	CC_SYNTHESIZE(int, Score, _Score);
	// 是否可以胡
	CC_SYNTHESIZE(bool, canHu, _canHu);
	// 最后的结果，输，赢，
	CC_SYNTHESIZE(RESULT, Result, _Result);
	// 赢了之后的牌型
	CC_SYNTHESIZE(bool, QingYiSe, _QingYiSe);					// 可以胡之后才判断清一色
	CC_SYNTHESIZE(bool, DaDiaoChe, _DaDiaoChe);			// 两张牌胡
	CC_SYNTHESIZE(bool, PengPengHu, _PengPengHu);		// AABBB
	CC_SYNTHESIZE(bool, GangKai, _GangKai);					// 杠在自摸杠和碰杠都要设置为ture。
	CC_SYNTHESIZE(int, NiaoNum, _NiaoNum);					// 抓到的鸟的数量
	CC_SYNTHESIZE(int, ZhongNiaoFen, _ZhongNiaoFen);					// 抓到的鸟的数量
	CC_SYNTHESIZE(int, Multiple, _multiple);					// 叫的倍数
	MahjongDrawer* drawer;	// 绘制
	static PlayMenu* playMenu;
private:
	bool init();
	// 得到某个新卡牌在当前手牌中应该是哪个位置
	int getNewCardLocation(int type);
	void addHeadPortrait(int dir);

public:
	void turnOnLight();
	void turnOffLight(float dt);
private:
	static Vec2 lightPos;
	Vec2 pos;								// 位置
	string name;						// 玩家昵称
	int coins;								// 玩家金币
	Sprite* light = nullptr;
};
#endif