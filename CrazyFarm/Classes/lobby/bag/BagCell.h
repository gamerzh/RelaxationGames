#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "domain/bag/BagItem.h"
using namespace cocos2d;
USING_NS_CC_EXT;


class BagCell : public Sprite{
public:
      virtual bool init();
	  CREATE_FUNC(BagCell);
	  void setValue(BagItem item);
	  void IsBeToued();
private:
	CC_SYNTHESIZE(BagItem, m_Item, bagitem);
	Sprite* propSprite;
	Sprite*txt;
	Sprite*txtji;
	LabelAtlas* propNum;

};
