#pragma once
#include "cocos2d.h"
USING_NS_CC;

class DreamCallback {
public:
	static  DreamCallback* getInstance();
	void jniCallBack(int a, int b);
private:
	static  DreamCallback* m_instance;
	DreamCallback() {};
};