#pragma once
#include "cocos2d.h"

class PauseLayer:public cocos2d::Layer{
public:
	virtual bool init();
	CREATE_FUNC(PauseLayer);
private:
    void gobackLobby();
};
