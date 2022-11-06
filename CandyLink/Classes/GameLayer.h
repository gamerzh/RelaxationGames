#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__
#include "cocos2d.h"
#include "Matrix.h"

USING_NS_CC;

class GameLayer : public cocos2d::Layer{
public:
	virtual bool init();
	CREATE_FUNC(GameLayer);
	int  MARGIN_BOTTOM;
	const static int   ELEMENT_WIDTH=76;
	int  MARGIN_LEFT;
	virtual bool onTouchBegan(Touch*touch, Event*event);
private:
	int removeCount = 0;//��¼��������
	int doubleHitCount = 0;
	int clickitem[2];//�����б���Ԫ��
	vector<int> tipPos;
	Vector<Sprite*> allElements;//��������Ԫ����Ϣ
	Vector<Sprite*> allBgElements;
	Vector<Sprite*> lights;//�������ε���Ĺ�Ȧ����
	Vector<Sprite*> items;//�������ε����Ԫ��
	Vector<Node*> clean;//���������Ķ���
	void update(float dt);
	void showTipPos();
	Vec2 getPosByPostion(int postion);//���������ϵ�λ�û����ʾ������
	void onTouchEnded(Touch*touch, Event*event);
	vector<int> screentoIndex(float x, float y);
	void showMatrix(float dt);
	void CleanVector(Vector<Node*> &clean);
	void doItemSelectAnima(/*Vec2 pos*/int index);//����Ԫ��ѡ�ж���
	void dealConnectANim();//�������������߶���
	void bombAnim();//����ը�㶯��
	void clearClickState();//���������UI����
	void deawLine(int x1,int y1,int x2,int y2,bool line);//�Ƿ���ֱ�������㡾����߽�������
	void dealDoubleHit(float dt);//������������1.5s��һ��

	void resetMap();//�ػ�����
	void nextMap(float dt);
	void newMap(float dt);
	void startGame(float dt);
	void drawMapBg();
};
#endif
