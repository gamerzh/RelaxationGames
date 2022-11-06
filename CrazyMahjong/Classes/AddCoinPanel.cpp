#include "AddCoinPanel.h"
#include "MahjongEvent.h"
#include "Room.h"
#include "User.h"
#include "MahjongAnim.h"
#include "PxPayMannger.h"
bool AddCoinPanel::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->setVisible(false);

	Sprite* frame = Sprite::create("AddCoin/AddCoinFrame.png");
	this->addChild(frame);

	Menu* menu = Menu::create();
	menu->ignoreAnchorPointForPosition(true);
	menu->setPosition(.0f, .0f);
	this->addChild(menu);

	std::string strBkg = "AddCoin/AddCoinWordBkg.png";
	std::string strBkg2 = "AddCoin/AddCoinWordBkg_1.png";
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			int index = i * 2 + j;
			MenuItemImage* bkg = MenuItemImage::create(strBkg, strBkg2, [=](Ref* pSender){
				CCLOG("--------------  add Coin : %d ---------------", index);
			/*	PxPayMannger::getInstance()->LaughPayLayer(index + 1,this);*/
			});
			menu->addChild(bkg);
			float dx = 120;
			float dy = 50;
			float xx = 0 == j ? -dx : dx;
			float yy = 0 == i ? dy : -dy;
			bkg->setPosition(xx, yy - 30.0f);
			
			Sprite* word = Sprite::create(String::createWithFormat("AddCoin/AddCoinWord_%d.png", index)->_string);
			word->setPosition(bkg->getContentSize() / 2);
			bkg->addChild(word);
		}
	}

	this->setPosition(400.0f, 240.0f);
	showPanel();

	auto close = MenuItemImage::create("SetSound/Close_0.png", "SetSound/Close_1.png", [=](Ref*psend){removeFromParentAndCleanup(1); });
	close->setPosition(275, 125);
	menu->addChild(close);
	//´¥ÃþÆÁ±Î
	listenr1 = EventListenerTouchOneByOne::create();
	listenr1->onTouchBegan = [=](Touch*touch, Event*event){return true; };
	listenr1->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);
	return true;
}

void AddCoinPanel::showPanel()
{
	this->setScale(.0f);
	this->setVisible(true);
	this->runAction(ScaleTo::create(time, 1.0f));
}
void AddCoinPanel::hidePanel()
{
	this->runAction(Sequence::create(ScaleTo::create(time, .0f), [this](){this->setVisible(false); }, NULL));
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

const int timesCost[4] = { 0, 200, 400, 800 };
bool ChooseTimesPanel::init()
{
	if (!Node::init())
	{
		return false;
	}
	this->setVisible(false);

	Sprite* frame = Sprite::create("Choose/Frame.png");
	this->addChild(frame);

	waitName = LabelTTF::create(Room::getInstance()->getName(0), "arial", 20);
	waitName->setPosition(14,-105);
	waitName->setAnchorPoint(Point::ANCHOR_MIDDLE);
	waitName->setColor(Color3B(245, 218, 112));
	addChild(waitName);

	Menu* menu = Menu::create();
	menu->ignoreAnchorPointForPosition(true);
	menu->setPosition(.0f, .0f);
	this->addChild(menu);

	for (int index = 0; index < 4; ++index)
	{
		std::string str = String::createWithFormat("Choose/Times_%d.png", index)->_string;
		MenuItemImage* bkg = MenuItemImage::create(str, str, [=](Ref* pSender){ 
			MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);
			int coin = User::getInstance()->getMyCoins();
			if (coin<1000)
			{
	/*			PxPayMannger::getInstance()->LaughPayLayer(13, this->getParent());*/
			}
			if (coin<timesCost[index])
			{
				//TODO: pay
			}
			User::getInstance()->addCoin(-timesCost[index]);
			Room::getInstance()->setRoomTimes(0,pow(2, index));
			dispatchMahjongEvent(Refresh_Coin, nullptr);
			menu->setEnabled(false);
			nextChoose(0);
		/*	schedule(CC_SCHEDULE_SELECTOR(ChooseTimesPanel::nextChoose), 1.0f,3,0.0f);*/
			CCLOG("--------------  chooseTimes : %d ---------------", index); });
		bkg->setPosition(-150.0f + index * 100.0f, .0f);
		menu->addChild(bkg);
	}
	Sprite* word = Sprite::create(String::createWithFormat("Choose/Wait.png")->_string);
	word->ignoreAnchorPointForPosition(true);
	word->setPosition(-170.0f, -120.0f);
	this->addChild(word);

	this->setPosition(400.0f, 240.0f);
	showPanel();
	//´¥ÃþÆÁ±Î
	auto listenr1 = EventListenerTouchOneByOne::create();
	listenr1->onTouchBegan = [=](Touch*touch, Event*event){return true; };
	listenr1->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);
	return true;
}

void ChooseTimesPanel::showPanel()
{
	this->setScale(.0f);
	this->setVisible(true);
	this->runAction(ScaleTo::create(time, 1.0f));
}
void ChooseTimesPanel::hidePanel()
{
	this->runAction(Sequence::create(ScaleTo::create(time, .0f), RemoveSelf::create(true), NULL));
}

void ChooseTimesPanel::nextChoose(float dt)
{	
	for (int i = 1; i <= 3;i++)
	{
		int index = rand() % 4;
		Room::getInstance()->setRoomTimes(i, pow(2, index));
		Room::getInstance()->updateCoins(i, -timesCost[index]);
	}
	dispatchMahjongEvent(Refresh_Coin, nullptr);
	dispatchMahjongEvent(DEALCARDS, NULL);
	hidePanel();
	
}