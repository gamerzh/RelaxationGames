#include "RanklistCell.h"
#include "utill/Chinese.h"
#include "domain/ranklist/RanklistManager.h"
#include "config/ConfigExp.h"
bool RanklistCell::init(){

	bg = Sprite::create("ranklistBar1.png");
	auto size = bg->getContentSize();
	bg->setPosition(size/2);
	addChild(bg);


	


	rankSprite = Sprite::create();
	rankSprite->setPosition(45,size.height/2);
	rankSprite->setVisible(false);
	addChild(rankSprite);

	rankIndexTTF = LabelAtlas::create("0", "rankListNum2.png", 26, 36, '0');
	rankIndexTTF->setAnchorPoint(Point::ANCHOR_MIDDLE);
	rankIndexTTF->setPosition(45, size.height / 2);
	rankIndexTTF->setVisible(false);
	addChild(rankIndexTTF);

	sexSprite = Sprite::create();
	sexSprite->setPosition(125, size.height / 2+3);
	sexSprite->setScale(0.7);
	addChild(sexSprite);

	auto vipSp = Sprite::create("VIPtxt.png");
	vipSp->setPosition(190, size.height / 2);
	vipSp->setScale(0.7);
	addChild(vipSp);

	VIPLvTTF = LabelAtlas::create("0", "VIPnum.png", 31, 43, '0');
	VIPLvTTF->setAnchorPoint(Point::ZERO);
	VIPLvTTF->setPosition(Point(vipSp->getContentSize().width, 0));
	vipSp->addChild(VIPLvTTF);


	auto vipLvFrame = Sprite::create("viplevelFrame.png");
	vipLvFrame->setPosition(278, size.height / 2);
	addChild(vipLvFrame);

	VIPLvSmallTTF = LabelAtlas::create("0", "vipLevelNum.png", 11, 16, '0');
	VIPLvSmallTTF->setAnchorPoint(Point::ANCHOR_MIDDLE);
	VIPLvSmallTTF->setPosition(vipLvFrame->getContentSize()/2);
	vipLvFrame->addChild(VIPLvSmallTTF);

	NameTTF = LabelTTF::create("", "arial", 20);
	NameTTF->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	NameTTF->setPosition(vipLvFrame->getPositionX() + vipLvFrame->getContentSize().width-5, vipLvFrame->getPositionY()+3);
	addChild(NameTTF);

	auto lvSp = Sprite::create("LVTXT.png");
	lvSp->setPosition(518, size.height / 2);
	addChild(lvSp);

	LvTTF = LabelAtlas::create("0", "LVtxtNum.png", 15, 21, '0');
	LvTTF->setAnchorPoint(Point::ZERO);
	LvTTF->setPosition(Point(lvSp->getContentSize().width, 0));
	lvSp->addChild(LvTTF);
	//拥有金币 和经验
	 haveCoinTTF = LabelTTF::create("", "arial", 20);
	haveCoinTTF->setAnchorPoint(Point::ANCHOR_MIDDLE);
	haveCoinTTF->setPosition(642, size.height / 2);
	addChild(haveCoinTTF);
    
	coinsp = Sprite::create("coin.png");
	coinsp->setAnchorPoint(Point::ANCHOR_MIDDLE);
	coinsp->setPosition(702, size.height / 2);
	coinsp->setVisible(false);
	addChild(coinsp,0,"coinsp");

	CoinNumTTF = LabelAtlas::create("0", "coinnumTxt.png", 14, 18, '0');
	CoinNumTTF->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	CoinNumTTF->setPosition(857, size.height / 2);
	addChild(CoinNumTTF);
	return true;
}


void RanklistCell::setCoinValue(int index)
{
	coinsp->setTexture("coin.png");
	if (index%2==1)
	{
		bg->setTexture("ranklistBar2.png");
	}
	else
	{
		bg->setTexture("ranklistBar1.png");
	}
	rankIndexTTF->setVisible(false);
	rankSprite->setVisible(false);
	rankIndexTTF->setString(Value(index + 1).asString().c_str());
	auto data = RanklistManager::getInstance()->getCoinRankListData();
	auto item = data.at(index);
	VIPLvTTF->setString(Value(item.vipLevel).asString().c_str());
	LvTTF->setString(Value(ConfigExp::getInstance()->getLevelData(item.exp).levelId).asString().c_str()); 

	getChildByName("coinsp")->setVisible(true);
	auto str = String::createWithFormat("%ld", item.coin);
	haveCoinTTF->setString(ChineseWord("haveCoin").c_str());
	CoinNumTTF->setString(str->getCString());


	NameTTF->setString(Value(item.name).asString().c_str());
	str = ((item.gender== 0) ? String::createWithFormat("bagMale.png") : String::createWithFormat("bagFamale.png"));
	sexSprite->setTexture(str->getCString());
	if (index + 1 <= 3)
	{
		str = String::createWithFormat("ranklist_%d.png", index + 1);
		rankSprite->setTexture(str->getCString());
		rankSprite->setVisible(true);
	}
	else
	{
		rankIndexTTF->setVisible(true);
	}

}

void RanklistCell::setExpValue(int index)
{
	coinsp->setTexture("EXP.png");
	if (index % 2 == 1)
	{
		bg->setTexture("ranklistBar2.png");
	}
	else
	{
		bg->setTexture("ranklistBar1.png");
	}
	rankIndexTTF->setVisible(false);
	rankSprite->setVisible(false);
	rankIndexTTF->setString(Value(index + 1).asString().c_str());
	auto data = RanklistManager::getInstance()->getExpRankListData();
	auto item = data.at(index);
	VIPLvTTF->setString(Value(item.vipLevel).asString().c_str());
	LvTTF->setString(Value(ConfigExp::getInstance()->getLevelData(item.exp).levelId).asString().c_str()); 
	auto str = String::createWithFormat("%ld", item.exp);
	haveCoinTTF->setString(ChineseWord("haveExp").c_str());
	CoinNumTTF->setString(str->getCString());
	NameTTF->setString(Value(item.name).asString().c_str());
	str = ((item.gender == 0) ? String::createWithFormat("bagMale.png") : String::createWithFormat("bagFamale.png"));
	sexSprite->setTexture(str->getCString());


	if (index+1<=3)
	{
		str = String::createWithFormat("ranklist_%d.png", index + 1);
		rankSprite->setTexture(str->getCString());
		rankSprite->setVisible(true);
	}
	else
	{
		rankIndexTTF->setVisible(true);
	}
	

}


void RanklistCell::IsBeToued()
{


}