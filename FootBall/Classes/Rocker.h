#pragma once
#include "cocos2d.h"

#define ROCKER_NACKGROUMD_TAG  100
#define ROCKER_CONTENT_TAG  101

class Rocker :public cocos2d::Node {
public:
	static Rocker* create(cocos2d::Vec2 pos);	
	bool init(cocos2d::Vec2 pos);//��ʼҡ������λ��
	void openRocker();//����ҡ��
	void closeRocker(bool isVisible);//�ر�ҡ��
	float getRockerAngle();//����ҡ�˵ĽǶ�
private:
	float rockerAngle;//ҡ�˵�״̬
	float rockerRad;//ҡ�˷�Χ
	cocos2d::Vec2 bgCenter;	//ҡ�˱���ͼ������
	cocos2d::Vec2 getPosByAngle(float r, float angle);//���ݽǶȺͰ뾶�������
	float calculateAngle(cocos2d::Vec2 pos1, cocos2d::Vec2 pos2);//�õ������ĽǶ�
	bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
	void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
	void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
};