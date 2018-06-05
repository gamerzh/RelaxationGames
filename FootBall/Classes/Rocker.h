#pragma once
#include "cocos2d.h"

#define ROCKER_NACKGROUMD_TAG  100
#define ROCKER_CONTENT_TAG  101

class Rocker :public cocos2d::Node {
public:
	//��ʼҡ�˱���ͼƬ���˵�ͼƬ��ͼƬ������λ��
	static Rocker* create(cocos2d::Vec2 pos);
	bool init(cocos2d::Vec2 pos);
	void openRocker();//����ҡ��
	void closeRocker(bool isVisible);	//�ر�ҡ��  isVisible�Ƿ�������ʾ
private:
	float rockerAngle;//ҡ�˵�״̬
	float rockerRad;//ҡ�˷�Χ
	cocos2d::Vec2 bgCenter;	//ҡ�˱���ͼ������
	cocos2d::Vec2 getAnglePos(float r, float angle);//���ݽǶȺͰ뾶�������
	float getAngle(cocos2d::Vec2 pos1, cocos2d::Vec2 pos2);	//�õ������ĽǶ�
	bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
};