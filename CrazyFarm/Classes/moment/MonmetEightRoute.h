#pragma once
#include "cocos2d.h"

using namespace cocos2d;


struct MonmentEightRoutePoint  //鱼的运行轨迹点
{
	MonmentEightRoutePoint* next;
	float time;
	float delay;
	int moveState;  //1直线 2圆 3帧动画 4贝塞尔
	//直线配置
	Point  MoveByPos;
	//圆配置
	Vec2 centrePos;
	float circleAngle;
	float ScaleDiff;
	bool isClockwise;
	//动画配置
	std::string aniName;
	//贝塞尔By
	Point curPos;
	Point besizerPos1;
	Point besizerPos2;
	
};

struct MonmentEightRoute  //运行轨迹   
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