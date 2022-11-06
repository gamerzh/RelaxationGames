/// 麻将类

#ifndef __CARD_H__
#define __CARD_H__
#include "MahjongEvent.h"
#include "cocos2d.h"
USING_NS_CC;

// 卡牌位置（在手上还是已经打出去）

enum CARD_BODY
{
	UP_L_STAND		= 0, 
	UP_L_DAO			= 1, 
	UP_S_HENG			= 2, 
	UP_S_SHU			= 3, 
	BACK_L_DAO		= 4, 
	BACK_M_STAND	= 5, 
	BACK_S_HENG	= 6, 
	BACK_S_SHU		= 7, 
	SIDE = 8,
	LIE						= 9,
};
// 卡牌正面还是背面朝上
enum CARD_SIDE{UP, DOWN};
#define IS_LOGINFO_ONSCREEN  false
class Card : public Node
{
public :
	/// 创建麻将
	// @pos, side, content 麻将位置, 麻将正反，麻将牌面
	static Card* createHandCard(PLAYER dir, int type);
	static Card* createTableCard(PLAYER dir, int type);
	static Card* createSideCard(PLAYER dir, CARD_SIDE side, int type);
	static Card* createLieCard(PLAYER dir, CARD_SIDE side, int type);
	static Card* createShowCard();
	static Card* createPengGangCard();

	// 得到花色的图片名
	static std::string getTypeName(int type);
	// 得到牌体的图片名
	static std::string getBodyName(CARD_BODY bodyName);

	// @pos, side, content 麻将位置, 麻将正反，麻将牌面
	void cardFadeIn(float delayTime, float fadeInTime, Vec2 playerPos);
	void cardFadeIn(float fadeInTime, float moveTime, Vec2 playerPos, float scaleTo);

	virtual void removeFromParentAndCleanup(bool cleanup);
	// 更改牌的花色
	void changeCard(int type);

	void TurnCard();
	// 得到牌面信息
	CC_SYNTHESIZE(int, type, _type);
	// 得到归属位置
	CC_SYNTHESIZE(PLAYER, eDir, _dir);


	Vec2 getBodySize(){ return bodySpr->getContentSize(); };
	///显示箭头
	void showPoint();
	void hidePoint();
private:
	CREATE_FUNC(Card);
	Sprite* typeSpr = nullptr;
	Sprite* bodySpr = nullptr;

	bool init();
	// 设置手牌
	void setHandCard(PLAYER dir, int content, bool canTouch);
	// 设置桌牌
	void setTableCard(PLAYER dir, int content);
	// 设置暗杠牌
	void setSideCardAn(PLAYER dir, int type);
	// 设置明杠牌
	void setSideCardMing(PLAYER dir, int type);
	//设置躺着碰牌
	void setLieCardMing(PLAYER dir, int type);
	// 创建牌的花色
	Sprite* createType(int type);
	// 创建牌的牌体
	Sprite* createBody();
	// 点击牌事件
	bool onCardTouchBegan(Touch *touch, Event *event);
	void addType(std::string typeName);
	void addBody(std::string bodyName);

};

#endif // end MahjongScene.h
