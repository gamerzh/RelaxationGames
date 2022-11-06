#pragma once
#include "cocos2d.h"

using namespace cocos2d;


struct MonmentEightRoutePoint  //������й켣��
{
	MonmentEightRoutePoint* next;
	float time;
	float delay;
	int moveState;  //1ֱ�� 2Բ 3֡���� 4������
	//ֱ������
	Point  MoveByPos;
	//Բ����
	Vec2 centrePos;
	float circleAngle;
	float ScaleDiff;
	bool isClockwise;
	//��������
	std::string aniName;
	//������By
	Point curPos;
	Point besizerPos1;
	Point besizerPos2;
	
};

struct MonmentEightRoute  //���й켣   
{
	Point startPos;
	MonmentEightRoutePoint* head;
};


class MonmetEightRoutedata{
public:
	static MonmetEightRoutedata* getInstance();
	static void destroyInstance();
	bool loadConfig();
	MonmentEightRoute getRouteBytag(int tag);
private:
	std::map<int, MonmentEightRoute> map_TagToRoute;
	static MonmetEightRoutedata* _pInstance;

};