#pragma once
#include "cocos2d.h"
USING_NS_CC;


class ChangeGiftCell :public Sprite
{
public:
	virtual bool init();

	CREATE_FUNC(ChangeGiftCell);
	void setValue(int type); //1:��ʯ 2�������ͱ���
	virtual void update(float delta);
private:
	Sprite* giftCell;
	Sprite* giftName;
	Sprite*colorBg;
	MenuItemImage* bt;
	int m_type;
	void changeButtonCallback(Ref* psend);
	CC_SYNTHESIZE(bool, m_isSelected, isSelected);

};
