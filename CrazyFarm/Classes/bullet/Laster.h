#pragma once
#include "cocos2d.h" 
#include "turret/PlayerTurret.h"
#include "fish/Fish.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
USING_NS_CC_EXT;
using namespace cocos2d;

class Laster :public Sprite{
public:
	virtual bool init();
	CREATE_FUNC(Laster);
	void update(float delta);
	virtual void removeFromParentAndCleanup(bool cleanup = true);
private:
	CC_SYNTHESIZE(PlayerTurret*, pPlayerTurret, PlayerTurret);


};
