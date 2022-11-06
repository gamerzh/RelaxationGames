#include "RedpackPanel.h"
#include "PayEventMannger.h"
#include "User.h"
#include "Room.h"
#include "ChineseWorld.h"
#include "MahjongEvent.h"
RedpackPanel*RedpackPanel::create(int index, int price)
{
	RedpackPanel*panel = new RedpackPanel();
	if (panel&&panel->init(index,price))
	{
		panel->autorelease();
		return panel;
	}
	else
	{
		CC_SAFE_DELETE(panel);
		return nullptr;
	}
}


bool RedpackPanel::init(int index, int price)
{
	if (!Node::init())
	{
		return false;
	}

	char* bgFramefile;
	if (index == 0)
	{
		Sprite* frame = Sprite::create("GrabSuccess.png");
		frame->setPosition(400, 240);
		this->addChild(frame);

		auto label = Label::createWithCharMap("fnt_redpack.png", 32, 41, '0');
		label->setString(Value(price).asString());
		label->setAnchorPoint(Point::ANCHOR_MIDDLE);
		label->setPosition(370, 232);
		addChild(label, 2);
		User::getInstance()->addCoin(price);
	}
	else
	{
		Sprite* frame = Sprite::create("GrabFailed.png");
		frame->setPosition(400, 240);
		this->addChild(frame);
		
		auto str1 = String::createWithFormat(ChineseWord("PlayerGrabCoin").c_str(), Room::getInstance()->getName(index).c_str());
		auto label1 = Label::createWithSystemFont(str1->getCString(), "arial", 15);
		label1->setColor(Color3B(0, 0, 0));
		label1->setAnchorPoint(Point::ANCHOR_MIDDLE);
		label1->setPosition(370, 252);
		addChild(label1, 2);

		auto label2 = Label::createWithCharMap("fnt_redpack.png", 32, 41, '0');
		label2->setString(Value(price).asString());
		label2->setAnchorPoint(Point::ANCHOR_MIDDLE);
		label2->setPosition(370, 222);
		addChild(label2, 2);
		label2->setScale(0.6);

		Room::getInstance()->updateCoins(index, price);
		
	}
	dispatchMahjongEvent(Refresh_Coin, nullptr);
	auto listenr1 = EventListenerTouchOneByOne::create();
	listenr1->onTouchBegan = [=](Touch*touch, Event*event){ removeFromParentAndCleanup(1); return true; };
	listenr1->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);
	scheduleUpdate();
	return true;
}

void RedpackPanel::update(float delta)
{
	totaltime += delta;
	if (totaltime>3)
	{
		removeFromParentAndCleanup(1);
	}
}