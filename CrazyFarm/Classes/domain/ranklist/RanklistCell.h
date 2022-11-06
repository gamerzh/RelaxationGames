#pragma once

#include "cocos2d.h"
#include "cocos-ext.h"
#include "domain/ranklist/RanklistManager.h"
using namespace cocos2d;
USING_NS_CC_EXT;


class RanklistCell : public TableViewCell{
public:
      virtual bool init();
	  CREATE_FUNC(RanklistCell);
	  void setCoinValue(int index);
	  void setExpValue(int index);
	  void IsBeToued();
private:
	LabelAtlas* VIPLvTTF;
	LabelAtlas* VIPLvSmallTTF;
	LabelAtlas* LvTTF;
	LabelAtlas* CoinNumTTF;
	LabelAtlas* rankIndexTTF;
	LabelTTF* NameTTF;
	Sprite* rankSprite;
	Sprite* sexSprite;
	Sprite* bg;
	Sprite*coinsp;
	LabelTTF* haveCoinTTF;

};
