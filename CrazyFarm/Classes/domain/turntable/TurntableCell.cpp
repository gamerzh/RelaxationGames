#include "TurntableCell.h"
#include "widget/MyLabelAtlas.h"
TurntableCell* TurntableCell::create(const char*path, int propNum)
{
	TurntableCell* bRet = new TurntableCell();
	if (bRet&&bRet->init(path, propNum))
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

bool TurntableCell::init(const char*path, int propNum)
{
	initWithFile(path);
	setContentSize(Size(83, 83));
	bool bRet = false;
	while (!bRet)
	{
		auto txt = String::createWithFormat(":%d", propNum);
		auto num = MyLabelAtlas::create(txt->getCString(), "turntableCellNum.png", 15, 23, '0',60);
		num->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
		addChild(num);
		num->setPosition(getContentSize().width*0.5, -5);
		
		bRet = true;
	}
	return bRet;
}

