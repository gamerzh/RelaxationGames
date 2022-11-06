#include "RanklistCell.h"
RanklistCell*RanklistCell::create(RankListItem item, int rank)
{
	RanklistCell*cell = new (std::nothrow)RanklistCell();
	if (cell&&cell->init(item,rank))
	{
		cell->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(cell);
		cell == nullptr;
	}
	return cell;
}



bool RanklistCell::init(RankListItem item, int rank)
{
	char* bgPath;
	if (rank==1)
	{
		bgPath = "rankcellbg_1.png";
	}
	else
	{
		bgPath = "rankcellbg_2.png";
	}
	if (!Sprite::initWithFile(bgPath))
	{
		return false;
	}
	//rank
	Node*nodeRank;
	if (rank<=3)
	{
		auto rkpath = String::createWithFormat("rank_%d.png", rank);
		nodeRank = Sprite::create(rkpath->getCString());
	}
	else
	{
		nodeRank = LabelAtlas::create(Value(rank).asString(), "fnt_rank.png",22,30,'0');
	}
	nodeRank->setAnchorPoint(Point::ANCHOR_MIDDLE);
	nodeRank->setPosition(34, 28);
	addChild(nodeRank);
	nodeRank->setScale(0.8);

	//name 
	auto nameLabel = Label::createWithSystemFont(item.name, "arial", 15);
	nameLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	nameLabel->setPosition(116, 43);
	addChild(nameLabel);
	
	//coin
	auto coin = Sprite::create("coin.png");
	coin->setPosition(80, 18);
	coin->setScale(0.8);
	addChild(coin);
	
	auto userCoin = LabelTTF::create(Value(item.coin).asString(), "arial", 15);
	userCoin->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	userCoin->setPosition(coin->getPositionX()+coin->getContentSize().width/2,coin->getPositionY());
	userCoin->setColor(Color3B(254, 248, 52));
	addChild(userCoin);

	return true;
}
