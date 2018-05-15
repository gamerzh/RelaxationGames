#pragma once
#include "cocos2d.h"
USING_NS_CC;


class SelectItem : public Node {
public:
	static SelectItem* create(int type);
	virtual bool init();
private:
	void useModle();
};