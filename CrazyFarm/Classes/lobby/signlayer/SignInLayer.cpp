#include"SignInLayer.h"
#include "utill/dayUtil.h"
#include "config/ConfigSign.h"
#include "utill/Toast.h"
#include "SignCell.h"
#include "SpliceCell.h"
#include "domain/user/User.h"
#include "lobby/LobbyScene.h"
#include "domain/bag/BagManager.h"
#include "utill/Audio.h"
#include "utill/FunUtil.h"
bool SignInLayer::init(std::vector<SignItem> items)
{
	if (!Layer::init()){
		return false;
	}	


	auto colorlayer = LayerColor::create();
	colorlayer->setColor(ccc3(0, 0, 0));
	colorlayer->setOpacity(180);
	addChild(colorlayer, -1,"color");
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	_items = items;
	auto bg = Sprite::create("signBg.png");
	bg->setPosition(visibleSize / 2);
	addChild(bg,0,"bg");


	auto frame = Sprite::create("signFrame.png");
	frame->setPosition(visibleSize.width / 2-8, visibleSize.height*0.58+9);
	addChild(frame,0,"signframe");

	int nSeqSignDay = _items.size();
	for (int i = 1; i <= 7;i++)
	{
		if (i>nSeqSignDay)
		{
			auto sp = Sprite::create("sign_lock.png");
			sp->setPosition(90.28 / 2 + (i - 1)*90.28,71);
			frame->addChild(sp,-1);
		}
		else
		{	
			int curindex = getCurindexByRewards(items.at(i - 1));

			auto sp = SpliceCell::create(curindex,4.0f+(i-1)*0.5f);
			sp->setAnchorPoint(Point::ANCHOR_MIDDLE);
			sp->setPosition(90.28 / 2 + (i - 1)*90.28-83/2, 71-142/2+13);
			frame->addChild(sp,-1);
			SpliceCells.pushBack(sp);
			CCLOG("day = %d,curindex = %d", i, curindex);
			curindexs.push_back(curindex);
		}
	}


	auto button = MenuItemImage::create("gainButton_1.png", "gainButton_2.png", CC_CALLBACK_1(SignInLayer::gainRewardsCallback, this));
	button->setPosition(bg->getContentSize().width / 2, bg->getContentSize().height*0.2+30);
	auto menu = Menu::create(button, nullptr);
	menu->setPosition(0, 0);
	bg->addChild(menu);

	

	auto listenr1 = EventListenerTouchOneByOne::create();
	listenr1->onTouchBegan = CC_CALLBACK_2(SignInLayer::onTouchBegan, this);
	listenr1->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);


	if (nSeqSignDay == -1)
	{
		runAction(Sequence::create(CallFunc::create([&]{Toast::show("time out", 3, getParent()); }), DelayTime::create(3.1), RemoveSelf::create(1),nullptr));
	}
	else if (nSeqSignDay == 0)
	{
		runAction(Sequence::create(CallFunc::create([&]{Toast::show("already signed", 3, getParent()); }), DelayTime::create(3.1), RemoveSelf::create(1),nullptr));
	}





	return true;

}
SignInLayer * SignInLayer::createLayer(std::vector<SignItem> items)
{
	SignInLayer *ret = new  SignInLayer();
	if (ret && ret->init(items))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}


void SignInLayer::gainRewardsCallback(Ref* psend)
{

	((MenuItemImage*)psend)->setEnabled(false);
	Audio::getInstance()->playSound(FRUITSIGN);
	CCLOG("begin");
	for (auto var : SpliceCells)
	{
		var->setBegin();
	}
	runAction(Sequence::create(DelayTime::create(_items.size()*0.5 + 4.0f + 1.0f), CallFunc::create([=]{
	getChildByName("signframe")->setVisible(false);
	getChildByName("bg")->setVisible(false);
	getChildByName("color")->setVisible(false);
	for (int i = 0; i < curindexs.size();i++)
	{
		auto sp = Sprite::create("signRewards.png", Rect(0, 406-83 * curindexs.at(i), 83, 83));
		sp->setPosition(213 + i*90.28, 330);
		sp->setScale(0);
		sp->runAction(Sequence::create(DelayTime::create(i*0.15f), Spawn::create(ScaleTo::create(0.5f, 1.0), MoveTo::create(0.5f, Vec2(281 + i * 130, 361)), nullptr), DelayTime::create(2.0f + i*0.1f), Spawn::create(MoveTo::create(0.5f, Vec2(259.2, 48)), ScaleTo::create(0.5f, 0.5f), nullptr), CallFunc::create(
			[=]{
			auto parent = this->getParent();
			auto menu = parent->getChildByName("menu");
			auto bag = menu->getChildByName("bag");
			bag->runAction(Sequence::createWithTwoActions(ScaleTo::create(0.1, 1.2f), ScaleTo::create(0.1, 1.0f)));

		}), RemoveSelf::create(), nullptr));
		if (User::getInstance()->getVipLevel()>0)
		{
			auto vipx2 = Sprite::create("VIPX2.png");
			vipx2->setPosition(41.5, 41.5);
			sp->addChild(vipx2);
		}
		getParent()->addChild(sp, 30);
	}
	runAction(Sequence::create(DelayTime::create(curindexs.size()*0.15 + 0.5 + 2.0 + curindexs.size()*0.1+0.5), CallFunc::create([=]{
	for (auto var : _items)
	{
		BagManager::getInstance()->addreward(var.itemId, var.num);
	}
	SignMannger::getInstance()->clearSignItem();

	((LobbyScene*)(this->getParent()))->guizuCallback(nullptr);
	this->removeFromParentAndCleanup(1);}), nullptr));
	

 }), nullptr));
	
}

void SignInLayer::updata(float dt)
{

}

int SignInLayer::getCurindexByRewards(SignItem item)
{
	std::vector<SignItem> items;
	items.push_back(SignItem(1003, 1));
	items.push_back(SignItem(1004, 1));
	items.push_back(SignItem(1002, 5));
	items.push_back(SignItem(1001, 800));
	items.push_back(SignItem(1002, 3));
	items.push_back(SignItem(1001, 500));
	
	for (int i = 0; i < items.size();i++)
	{
		if (item.itemId == items[i].itemId&&item.num == items[i].num)
		{
			return i;
		}
	}
	return 0;
}