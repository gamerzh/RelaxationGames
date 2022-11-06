#include "VipCell.h"
#include "utill/Chinese.h"
#include "domain/user/User.h"
bool VipCell::init(){

	auto bg = Sprite::create("VIPFrame.png");
	bg->setPosition(88, 121.5+40);
	addChild(bg);
	auto size = bg->getContentSize();

	propSprite = Sprite::create();
	propSprite->setPosition(size.width/2,size.height/2+40);
	addChild(propSprite);

	auto bottomFrame = Sprite::create("VIPbottomFrame.png");
	bottomFrame->setAnchorPoint(Point::ZERO);
	bottomFrame->setPosition(0,40);
	addChild(bottomFrame);


	 VIPtitle = Sprite::create("VIPtxt.png");
	VIPtitle->setPosition(size.width*0.45, size.height*0.8+58);
	addChild(VIPtitle);
	
	VIPTTF = LabelAtlas::create("0", "VIPnum.png", 31, 43, '0');
	VIPTTF->setAnchorPoint(Point::ANCHOR_MIDDLE);
	VIPTTF->setPosition(size.width*0.75, size.height*0.8+58);
	addChild(VIPTTF);



	VIPname = Sprite::create();
	VIPname->setPosition(size.width / 2, size.height*0.23+45);
	addChild(VIPname);

	VIPdec = Sprite::create();
	VIPdec->setPosition(size.width *0.51, size.height*0.1+40);
	addChild(VIPdec);


	auto priceFrame = Sprite::create("txtPriceDes.png");
	priceFrame->setPosition(size.width *0.51, -size.height*0.1+40);
	addChild(priceFrame);

	PriceDecTTF = LabelTTF::create("0", "arial", 20);
	PriceDecTTF->setPosition(priceFrame->getContentSize()/2);
	priceFrame->addChild(PriceDecTTF);

	sPoint = Sprite::create("sPoint.png");
	sPoint->setPosition(size.width*1.13, size.height*0.5+40);
	addChild(sPoint);
	sPoint->setVisible(false);


	upgradeTxt = Sprite::create("upgradeProp.png");
	upgradeTxt->setPosition(size.width / 2, 100+40);
	addChild(upgradeTxt);



	return true;
}

int VIPprice[9] = { 20, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000 };

void VipCell::setValue(int vipLevel)
{
	auto spPath = String::createWithFormat("game/ui/turret/pao_%d.png", vipLevel+2);
	propSprite->setTexture(spPath->getCString());
	spPath = String::createWithFormat("VIPname_%d.png", vipLevel);
	VIPname->setTexture(spPath->getCString());
	spPath = String::createWithFormat("VIPdec_%d.png", vipLevel);
	VIPdec->setTexture(spPath->getCString());

	VIPTTF->setString(Value(vipLevel).asString().c_str());
	auto viplv = User::getInstance()->getVipLevel();
	if (vipLevel>=viplv+6)
	{
		PriceDecTTF->setString("????");
	}
	else
	{
		auto dec = String::createWithFormat(ChineseWord("priceVIPdes").c_str(), VIPprice[vipLevel-1]);
		PriceDecTTF->setString(dec->getCString());
	}
	if (vipLevel<9)
	{
		sPoint->setVisible(true);
	}
	else
	{
		sPoint->setVisible(false);
	}
	if (vipLevel>3)
	{
		upgradeTxt->setVisible(true);
	}
	else
	{
		upgradeTxt->setVisible(false);
	}

}

void VipCell::IsBeToued()
{


}