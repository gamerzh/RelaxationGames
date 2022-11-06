#pragma once
#include "cocos2d.h"
#include "domain/bankrupt/BankruptManager.h"
USING_NS_CC;
class GetRewardNode : public Sprite
{
public:
	virtual bool init(Bankrupt bankrupt);

	static  GetRewardNode*create(Bankrupt baknrupt);

private:
	void closeButtonCallBack(Ref*psend);
	virtual bool onTouchBegan(Touch *touch, Event *unused_event);
	void update(float dt);
	Bankrupt m_baknrupt;
	bool isTimeOut = false;

};
