#pragma once
#include "cocos2d.h"

using namespace cocos2d;


struct RoutePoint  //������й켣��
{
	RoutePoint* next;
	float time;
	float delay;
	bool isRepeat;  //�Ƿ�ѭ��
	int moveState;  //1ֱ�� 2Բ 3֡����
	//ֱ������
	Point  MoveByPos;
	//Բ����
	Vec2 centrePos;
	float circleAngle;
	float ScaleDiff;
	bool isClockwise;
	//��������
	std::string aniName;
	
};

struct Route  //���й켣   
{
	RoutePoint* head;
};


class FishRouteData{
public:
	static FishRouteData* getInstance();
	static void destroyInstance();
	bool loadConfig();
	Route getRouteBytag(int tag); 
private:
	std::map<int,Route> map_TagToRoute;
	static FishRouteData* _pInstance;

};