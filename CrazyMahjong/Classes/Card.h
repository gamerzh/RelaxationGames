/// �齫��

#ifndef __CARD_H__
#define __CARD_H__
#include "MahjongEvent.h"
#include "cocos2d.h"
USING_NS_CC;

// ����λ�ã������ϻ����Ѿ����ȥ��

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
// �������滹�Ǳ��泯��
enum CARD_SIDE{UP, DOWN};
#define IS_LOGINFO_ONSCREEN  false
class Card : public Node
{
public :
	/// �����齫
	// @pos, side, content �齫λ��, �齫�������齫����
	static Card* createHandCard(PLAYER dir, int type);
	static Card* createTableCard(PLAYER dir, int type);
	static Card* createSideCard(PLAYER dir, CARD_SIDE side, int type);
	static Card* createLieCard(PLAYER dir, CARD_SIDE side, int type);
	static Card* createShowCard();
	static Card* createPengGangCard();

	// �õ���ɫ��ͼƬ��
	static std::string getTypeName(int type);
	// �õ������ͼƬ��
	static std::string getBodyName(CARD_BODY bodyName);

	// @pos, side, content �齫λ��, �齫�������齫����
	void cardFadeIn(float delayTime, float fadeInTime, Vec2 playerPos);
	void cardFadeIn(float fadeInTime, float moveTime, Vec2 playerPos, float scaleTo);

	virtual void removeFromParentAndCleanup(bool cleanup);
	// �����ƵĻ�ɫ
	void changeCard(int type);

	void TurnCard();
	// �õ�������Ϣ
	CC_SYNTHESIZE(int, type, _type);
	// �õ�����λ��
	CC_SYNTHESIZE(PLAYER, eDir, _dir);


	Vec2 getBodySize(){ return bodySpr->getContentSize(); };
	///��ʾ��ͷ
	void showPoint();
	void hidePoint();
private:
	CREATE_FUNC(Card);
	Sprite* typeSpr = nullptr;
	Sprite* bodySpr = nullptr;

	bool init();
	// ��������
	void setHandCard(PLAYER dir, int content, bool canTouch);
	// ��������
	void setTableCard(PLAYER dir, int content);
	// ���ð�����
	void setSideCardAn(PLAYER dir, int type);
	// ����������
	void setSideCardMing(PLAYER dir, int type);
	//������������
	void setLieCardMing(PLAYER dir, int type);
	// �����ƵĻ�ɫ
	Sprite* createType(int type);
	// �����Ƶ�����
	Sprite* createBody();
	// ������¼�
	bool onCardTouchBegan(Touch *touch, Event *event);
	void addType(std::string typeName);
	void addBody(std::string bodyName);

};

#endif // end MahjongScene.h
