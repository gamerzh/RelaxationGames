#pragma once
#include "cocos2d.h"
USING_NS_CC;

class SelectLayer : public Layer {
	
public: 
	virtual bool init();
	CREATE_FUNC(SelectLayer);
private:
	void loadView();
	void closeView();

};