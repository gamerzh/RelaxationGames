#ifndef __MAHJONG_ANIM_H__
#define __MAHJONG_ANIM_H__

#include "cocos2d.h"
USING_NS_CC;
#include "SimpleAudioEngine.h" 

using namespace std;

enum SOUND{
	BGM,
	ADDCOIN,
	BUTTONDOWN,
	FAIL,
	PENGGANG,
	PLAYCARD,
	SHAIZI,
	PICKCARD
};
class  GameFlow;

class MahjongAnim : public Node
{
public:
	CREATE_FUNC(MahjongAnim);
	
	void playSound(SOUND sound);

	static MahjongAnim* getInstance();
	static void updateInstance();


	void playDealShaiZi();
	void playDealCard();

	void playPlayAnim(int type, Vec2 pos);	// 牌动画
	void playPengAnim(int type, Vec2 pos);
	void playGangAnim(int type, Vec2 pos);

	void playWordGangAnim(Vec2 pos);		// 文字动画
	void playWordPengAnim(Vec2 pos);
	void hideWordAnim();


	///TODO:缺失自摸和杠开动画
	void playAccountZiMoAnim();
	void playAccountHuAnim(GameFlow & gameFlow);	// 胡＆＆点炮
	void playAccountGangKaiAnim();//　杠开 || 抢杠

	void playWordHuAnim(Vec2 pos);

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	Color3B colorCurrent = Color3B(.0f, 255.0f, 100.0f);
	Color3B colorBefore = Color3B::WHITE;
	Label* screenLogLabel;
	int numError = 4;
	void addRemever(int type);
	void logScreen(string strLog, int index);

	Label* wanLabels[10];
	int wanNum[10];
	bool isCurrentWan = false;
	int currentIndex = 0;
	Label* tongLabels[10];
	int tongNum[10];
	//////////////////////////////////////////////////////////////////////////////////////////////////////


	void playWinBanner();
	void hideWinBanner();

private:
	bool init();

	bool initDealAnim();
	bool initDealCards();
	bool initWordPengGangAnim();

	bool initAccountHuAnim();	// 胡＆＆点炮

	bool initAccountPanel();

	bool initPlayPengGangFrames();

	// 碰杠的文字动画，d=
	Sprite* animPengGangNode = nullptr;		// 下面的菱形
	Animate* animPengGang = nullptr;
	float animPengGangInter = 0.3f;
	float animPengGangTime = .0f;
	float timeShanLight = .3f;						// 闪光的时间
	float timeWordShowWord = 0.4f;			// 从开始闪光到显示文字的事件
	float timeWordScale = 0.3f;						// 文字放大的时间。

	Sprite* framePlay = nullptr;				// 打出牌的框
	Sprite* framePengGang = nullptr;	// 碰杠牌的框
	static MahjongAnim* instance;

	//胡动画【杠开】
    Node*	nodeAccountGangKai;

	//胡动画【胡】
	Node* nodeAccountHu = nullptr;

	Sprite* huFlash = nullptr;
	Sprite* huLightPoints = nullptr;
	Sprite* huLightYellow = nullptr;
	Sprite* huCirclePurple = nullptr;
	Sprite* huLightPink = nullptr;
	Sprite* huRing = nullptr;
	Sprite* huShadowCircle = nullptr;
	Animate* animHuLightYellow = nullptr;
	Animate* animHuFlash = nullptr;
	Animate* animHuLightPoints = nullptr;

	//胡动画【自摸】

	// 赢动画
	Node* nodeWinBanner = nullptr;

	Sprite* winBanner = nullptr;
	Sprite* winManyCoins = nullptr;

	Animate* animBanner = nullptr;
	Animate* animManyCoins = nullptr;

	// 发筛子
	Node* nodeDeal = nullptr;
	Sprite* dealShaiZi = nullptr;
	Sprite* dealShaiZiL = nullptr;
	Sprite* dealShaiZiR = nullptr;

	Animate* animShaiZi = nullptr;
	float timeShaiZi = 1.0f;
	float timeShow2ShaiZi = 0.8f;
};

#endif