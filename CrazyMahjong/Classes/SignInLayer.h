#ifndef __SIGNINLAYER_H__
#define __SIGNINLAYER_H__
#include "cocos2d.h"

USING_NS_CC;

struct SignCellDate 
{
	int day;
	int num;
	Point pos;
};

class SignInLayer : public Layer
{
public:
	static SignInLayer* create(int day);

private:
	virtual bool init(int day);
	void geteveryGift(Ref* psender);
	bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void initsigndate();

private:
	int _currentDay;
	std::vector<SignCellDate> cells;
	Size bgsize;
};


class SignCell : public Node
{
private:
	////signtype  1可以签 2已签过  3不能签
	virtual bool init(int day, int propnum, int signtype);
public:
	static SignCell* create(int day, int propnum, int signtype);
};

#endif