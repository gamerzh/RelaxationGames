#ifndef __CIRCLE_H__
#define __CIRCLE_H__
#include "cocos2d.h"
using namespace cocos2d;

class CircleBy : public ActionInterval{
public:
	static CircleBy* create(Point curPos,float duration, float degrees,float speed, bool clockwise);
	bool initWithDuration(Point curPos, float duration, float degrees, float speed, bool clockwise);
	virtual void update(float dt);
private:
	Point currentPostion;//��ǰtarget������
	float degree;//����ת������
	float speed;//�ƶ��ٶ�
	int updateTimes;//ˢ�´���
	bool clockWise;
};
#endif