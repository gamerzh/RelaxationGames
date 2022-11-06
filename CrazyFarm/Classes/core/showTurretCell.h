#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
using namespace cocos2d;
USING_NS_CC_EXT;


class showTurretCell : public TableViewCell{
public:
      virtual bool init();
	  CREATE_FUNC(showTurretCell);
	  void setMultipleValue(int index);
	  void setVippaoValue(int index);
	  void IsBeToued();
	  void ButtonCallback(Ref* psend);

private:
	MenuItemImage* button;

	int m_type;
	Sprite*bg;
	Sprite*showVipPaoName;
	LabelAtlas* muptleTTF;
	LabelTTF* PriceDecTTF;
	Sprite*lock;
	Sprite*lockTTf;
	Sprite* propSprite;
	Sprite* ShowPaoshade;
	Sprite* ShowPaolight;
	Sprite* SendCoin;
	LabelAtlas* zengCoinTTf;
	Sprite*quex3;
	Sprite*quexprice3;
};
