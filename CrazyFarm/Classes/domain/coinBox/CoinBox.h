#pragma once
#include "cocos2d.h"
#include "config/ConfigBox.h"
#include "utill/define.h"
using namespace cocos2d;

class CoinBox {

public:
	static CoinBox* getInstance();

	BoxConfigInfo getBoxConfigInfoByItemID(int itemid);
	void addCoinBox(int money);
	int getPerCoinBox();
	float getCatchPer(int userboxlevel);
private:
	
	
	const char* USEITEM = "USEITEM";
	CoinBox();
    void init();
	static CoinBox* _instance;
	std::vector<int> CoinBoxs;
};

