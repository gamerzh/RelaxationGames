#pragma once
#include "cocos2d.h"
USING_NS_CC;

enum ItemStatus{
	did_not_have,
	have,
	use
};

class SelectItem : public Node {
public:
	static SelectItem* create(int type);
	virtual bool init(int type);
private:
	int type = 0;
	MenuItemImage* image;
	ItemStatus playerHasMod = ItemStatus::did_not_have;
	void useModle();
	int getPriceByType(int type);
	void changeBtnTexture(ItemStatus status);
	void update(float dt);
};