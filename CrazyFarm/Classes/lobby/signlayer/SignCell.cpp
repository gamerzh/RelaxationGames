#include "SignCell.h"

SignCell* SignCell::create(int propID, int propNum)
{
	SignCell* bRet = new SignCell();
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

bool SignCell::init(int propID, int propNum)
{
	auto spPath = String::createWithFormat("sign_%d.png", propID);
	initWithFile(spPath->getCString());
	bool bRet = false;
	while (!bRet)
	{

		auto num = LabelAtlas::create(Value(propNum).asString().c_str(),"payNum.png", 16,24,'0');
		num->setPosition(getContentSize().width*0.5, getContentSize().height*0.1);
		addChild(num);
		bRet = true;
	}
	return bRet;
}

void SignCell::setVipX2()
{
	auto sp = Sprite::create("x2.png");
	sp->setPosition(getContentSize().width*0.8, getContentSize().height*0.7);
	addChild(sp);
}