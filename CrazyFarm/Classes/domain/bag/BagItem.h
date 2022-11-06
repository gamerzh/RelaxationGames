#pragma once

enum PropType
{
	InvalidType = -1,
	Prop_Currency = 0,
	Prop_upgradeBox = 1,
	Prop_ItemBox = 2,
	Prop_Skill = 3
};
struct BagItem {
    int itemId;
    int num;
	PropType type;
	BagItem(int i, int n, PropType t) :itemId(i), num(n), type(t){}
	BagItem(){};
};


