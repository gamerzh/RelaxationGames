#pragma once
#include "cocos2d.h"
USING_NS_CC;
struct RoleInfo
{
	int _nCostcoin;
	bool _isEnable;
	int _index;
};


class RoleShow :public Sprite
{
public:
	static RoleShow*create(int  index);
	void hideLight();
	void showLight();
private:
	bool init(int index);
	RoleInfo _roleinfo;

};


