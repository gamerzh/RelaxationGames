#pragma once
#include "cocos2d.h"

class ResultLayer : public cocos2d::Layer {
public:
	static ResultLayer* create(bool win);
	virtual bool init(bool win);
private:
    void continueGame();
    void gotoLobby();
};
