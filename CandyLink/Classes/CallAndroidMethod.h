#ifndef _CALLANDROIDMETHOD_H_
#define _CALLANDROIDMETHOD_H_

#include "cocos2d.h"

using namespace cocos2d;

class CallAndroidMethod{
public:
	static CallAndroidMethod* getInstance();
    void quit();
    void dream(int id);
private:
	CallAndroidMethod();
	static CallAndroidMethod* _instance;
};
#endif
