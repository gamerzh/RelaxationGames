#pragma once
#include "cocos2d.h"
#include "PayDefine.h"
USING_NS_CC;

struct PropItem
{
	int index;
	int price;
	int propNum;
	int payType;
	PAYPOINT Paypoint;
};

class ShopCell : public Node
{
public:
	static ShopCell*create(PropItem item);
	void onTouched();
	Rect getTouchRect();
private:
	bool init(PropItem item);
	PropItem _item;
	
};
