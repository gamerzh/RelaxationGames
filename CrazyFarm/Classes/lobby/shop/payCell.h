#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "domain/pay/Pay.h"
#include "utill/dayUtil.h"
using namespace cocos2d;
USING_NS_CC_EXT;


struct Good
{
	int RMB;
	int count;
	Good(int r, int c){ RMB = r, count = c; }
};


class PayCell : public Sprite{
public:
      virtual bool init();
	  CREATE_FUNC(PayCell);
	  void setValue(int goodId);
	  void setDiamondValue(int goodId);
	  void setVipValue();
	  void IsBeToued();
private:
	CC_SYNTHESIZE(int, m_nGoodId, goodID);
	CC_SYNTHESIZE(int, m_payPointID, payPointID);
	int m_PayType;
	Sprite* paySprite;
	Sprite* propNum;
	Sprite* giftNum;
	Sprite* hotTxt;

};
