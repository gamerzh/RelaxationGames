#include "payCell.h"
#include "domain/user/User.h"
#include "lobby/LobbyScene.h"
#include "core/GameLayer.h"
#include "server/HttpMannger.h"
#include "lobby/Nobility/NobilityLayer.h"
#include "domain/user/DeviceInfo.h"
#include "domain/logevent/LogEventPageChange.h"
#include "domain/game/GameManage.h"
#include "lobby/shop/payLayer.h"
#include "widget/MyTableView.h"
bool PayCell::init(){
	if (!Sprite::initWithFile("payframe_1.png")){
		return false;
	}
	auto size = getContentSize();
	paySprite = Sprite::create();
	paySprite->setPosition(size.width *0.21, size.height / 2);
	addChild(paySprite);

	propNum = Sprite::create();
	propNum->setPosition(size.width*0.68, size.height*0.76);
	addChild(propNum);

	giftNum = Sprite::create();
	giftNum->setPosition(size.width*0.68, size.height*0.30);
	addChild(giftNum);
	
	hotTxt = Sprite::create("hottxt.png");
	hotTxt->setAnchorPoint(Point::ZERO);
	hotTxt->setPosition(0, size.height*0.5);
	addChild(hotTxt);
	hotTxt->setVisible(false);

	return true;
}
Good coingood[7] = { Good(18, 180000), Good(38, 380000), Good(108, 1080000), Good(388, 3880000), Good(688, 6880000) , Good(8, 40000), Good(58, 580000)};
Good diamondGood[5] = { Good(18, 180), Good(38, 418), Good(58, 650), Good(108, 1346), Good(388, 4768) };
int payCoinPoint[7] = { 2, 3, 5, 6, 7, 1, 4 };
int payDiamondPoint[5] = { 8, 9, 10, 11, 12};
void PayCell::setValue(int goodId)
{
	setgoodID(goodId);
	m_payPointID = payCoinPoint[goodId-1];
	m_PayType = 1;
	auto spPath = String::createWithFormat("coin_%d.png", goodId);
	paySprite->setTexture(spPath->getCString());
	spPath = String::createWithFormat("coinPropNum_%d.png", goodId);
	propNum->setTexture(spPath->getCString());
	spPath = String::createWithFormat("coinGiftNum_%d.png", goodId);
	giftNum->setTexture(spPath->getCString());
}


void PayCell::setDiamondValue(int goodId)
{
	setgoodID(goodId);
	m_payPointID = payDiamondPoint[goodId - 1];
	m_PayType = 2;
	auto spPath = String::createWithFormat("zuanshi_%d.png", goodId);
	paySprite->setTexture(spPath->getCString());
	spPath = String::createWithFormat("diamondPropNum_%d.png", goodId);
	propNum->setTexture(spPath->getCString());
	spPath = String::createWithFormat("diamondGiftNum_%d.png", goodId);
	giftNum->setTexture(spPath->getCString());
	if (goodId ==4)
	{
		hotTxt->setVisible(true);
	}
}

void PayCell::setVipValue()
{
	m_PayType = 3;
	paySprite->setTexture("payVip.png");
	propNum->setTexture("payVipNum.png");
	giftNum->setTexture("payVipGift.png");
}


void PayCell::IsBeToued()
{
	auto tableview = getParent()->getParent()->getParent();
	auto viewdelegate = (payView*)(((MyTableView*)tableview)->getDelegate());

	bool isallow = viewdelegate->getIsAllowTouch();
	if (!isallow)
	{
		return;
	}
	else
	{
		viewdelegate->setLastTouchTiem();
	}
	log("touch the pay");
	setTexture("payframe_2.png");
	runAction(Sequence::create(DelayTime::create(0.5f), CallFunc::create([=]{setTexture("payframe_1.png"); }), nullptr));
	auto level =  ConfigVipLevel::getInstance()->getVipLevel(User::getInstance()->getVipLevel());
	auto eventpoint = ((payView*)viewdelegate)->getEventPoint();
	switch (m_PayType)
	{
	case 1:
	case 2:
		Pay::getInstance()->Overbooking(m_payPointID,eventpoint,this);
		break;
	case 3:
	{
		auto layer = NobilityLayer::createLayer();
		layer->setPosition(0, 10);
		auto scene = Director::getInstance()->getRunningScene();
		auto node = scene->getChildByTag(888);
		if (node)
		{
			
			node->addChild(layer,40);
			if ((GameGuiLayer*)node == GameManage::getInstance()->getGuiLayer())
			{
				layer->setEventPoint(4);
				LogEventPageChange::getInstance()->addEventItems(2, 8, 0);
			}
			else
			{

				auto node = (MyTableView*)(getParent()->getParent()->getParent());
				auto delegate =(payView*)( node->getDelegate());
				int shoptype = delegate->getShopType();
				if (shoptype ==1)
				{
					layer->setEventPoint(22);
					LogEventPageChange::getInstance()->addEventItems(12, 8, 0);
				}
				else if (shoptype ==2)
				{
					layer->setEventPoint(23);
					LogEventPageChange::getInstance()->addEventItems(13, 8, 0);
				}
			}
		}
		break;
	}
	default:
		break;
	}
	


}
