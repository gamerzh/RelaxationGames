#pragma once

#include "cocos2d.h"
#include "config/ConfigSign.h"
#include "SignCell.h"
USING_NS_CC;
class SpliceCell :public Node
{
public:
	virtual bool init(int curIndex,float time);

	static SpliceCell* create(int curIndex,float time);

	void setBegin();
private:
	void update(float delta);
	float m_anitime = 0;
	Sprite*content1;
	Sprite*content2;
	int m_curindex;//½±ÀøËùÔÚÎ»ÖÃ

	bool temp = false;
};



