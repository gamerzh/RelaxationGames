#include "GiftCell.h"

GiftCell* GiftCell::create(int propID, int propNum)
{
	GiftCell* bRet = new GiftCell();
	if (bRet&&bRet->init(propID, propNum))
	{
		bRet->autorelease(); 
			return bRet; 
	}
	else 
	{ 
	  delete bRet; 
	  bRet = NULL; 
	  return NULL; 
	} 
}

bool GiftCell::init(int propID, int propNum)
{
	initWithFile("bagbox.png");
	bool bRet = false;
	while (!bRet)
	{
		auto spPath = String::createWithFormat("item_%d.png", propID);
		auto sp = Sprite::create(spPath->getCString());
		sp->setPosition(getContentSize()/2);
		addChild(sp);
		auto num = LabelAtlas::create(Value(propNum).asString().c_str(),"bagPropNum.png", 18,26,'0');
		num->setAnchorPoint(Point(1, 0));
		num->setPosition(getContentSize().width*0.65+27, getContentSize().height*0.1);
		addChild(num);


		if (propID == 1012)
		{
			auto ji = Sprite::create("txtLevel.png");
			ji->setPosition(getContentSize().width*0.65 + 27, getContentSize().height*0.1);
			ji->setAnchorPoint(Point(1, 0));
			addChild(ji);
			num->setPositionX(65+6);
		}
		bRet = true;
	}
	return bRet;
}

