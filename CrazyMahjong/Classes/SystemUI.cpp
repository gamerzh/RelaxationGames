#include "SystemUI.h"
#include "MahjongAnim.h"
#include "AddCoinPanel.h"
#include "Jniutill.h"
#include "Toast.h"
#include "ChineseWorld.h"
#include "MahjongEvent.h"
#include "Room.h"
#include "User.h"
#include "DBManager.h"
#include "HallScene.h"
#include "ShopPanel.h"
#include "PayEventMannger.h"
bool SystemUI::init()
{
	if (!Node::init())
	{
		return false;
	}

	Vec2 coinPos = Vec2(-230.0f, -135.0f);
	auto light = Sprite::create("System_UI/GetCoinsLight.png");
	FadeTo* fadeOut = FadeTo::create(1.0f, 180.0f);
	FadeTo* fadeIn = FadeTo::create(.8f, 255.0f);
	Sequence* sequ = Sequence::create(fadeIn, fadeOut, NULL);

	light->runAction(RepeatForever::create(sequ));
	
	addCoinBtn = MenuItemImage::create("System_UI/GetCoins.png", "System_UI/GetCoins.png", CC_CALLBACK_1(SystemUI::onAddCoinBtnCallBack, this));
	addCoinBtn->setPosition(coinPos);
	backBtn = MenuItemImage::create("System_UI/button_back_0.png", "System_UI/button_back_1.png", CC_CALLBACK_1(SystemUI::onBackBtnCallBack, this));
	setBtn = MenuItemImage::create("System_UI/button_set_0.png", "System_UI/button_set_1.png", CC_CALLBACK_1(SystemUI::onSetBtnCallBack, this));
	gameBtn = MenuItemImage::create("System_UI/button_moreGame_0.png", "System_UI/button_moreGame_1.png", CC_CALLBACK_1(SystemUI::onGameBtnCallBack, this));


	Menu* menu = Menu::create();
	Size size = _director->getWinSize() / 2;
	backBtn->setPosition(-size.width + 30, size.height - 30);
	menu->addChild(backBtn);

	setBtn->setPosition(size.width - 30, size.height - 300);
	menu->addChild(gameBtn);

	gameBtn->setPosition(size.width - 30, size.height - 350);
	menu->addChild(setBtn);
	light->setPosition(addCoinBtn->getContentSize()/2);
	addCoinBtn->addChild(light,-1);
	menu->addChild(addCoinBtn);
	auto s = menu->getAnchorPoint();

	this->addChild(menu);




	auto scoring_text = Sprite::create("scoring_text.png");
	scoring_text->setPosition(Vec2(800, 480) - Vec2(scoring_text->getContentSize()*0.55));
	addChild(scoring_text);
	//Task
	//if (Jniutill::getInstance()->IsHdOpen())
	//{
	//	auto DisplayBoard = ScrollText::create();
	//	DisplayBoard->setPosition(400, 348);
	//	addChild(DisplayBoard, 10, 10);
	//	DisplayBoard->setGlobalZOrder(100);
	//	ResetTask();
	//}

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = [=](Touch*touch, Event*event){
		auto TaskNode = this->getChildByTag(10);
		if (TaskNode)
		{
			auto rect = TaskNode->getBoundingBox();
			auto scalerect = Rect(rect.getMinX()-283/2, rect.getMinY()-21/2 - rect.size.height / 2, rect.size.width, rect.size.height * 2);
			auto pos = touch->getLocation();
			if (scalerect.containsPoint(pos))
			{
				OnActive();
			}
		}

		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	return true;
}
void SystemUI::hideAddCoin()
{
	addCoinBtn->setVisible(true);
	backBtn->setVisible(false);
}
void SystemUI::onBackBtnCallBack(Ref* pSender)
{
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);
	Director::getInstance()->replaceScene(HallScene::createScene());
	CCLOG("Exit!");
}
void SystemUI::onInforBtnCallBack(Ref* pSender)
{
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);

	CCLOG("Infor!");
}
void SystemUI::onGameBtnCallBack(Ref* pSender)
{
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);
	Jniutill::getInstance()->showMoreGame();
	CCLOG("MoreGame!");
}
void SystemUI::onSetBtnCallBack(Ref* pSender)
{
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);
	setPanel = UserSetting::create();
	getParent()->addChild(setPanel,50);
	CCLOG("Set!");
}

void SystemUI::onAddCoinBtnCallBack(Ref* pSender)
{
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);
	auto node = ShopPanel::create();
	getParent()->addChild(node, 20);
}



void SystemUI::showFirstPlayTip()
{
	if (Room::getInstance()->getRoomType()==ROOM_QINGYISE)
	{
		auto frame = Sprite::create("System_UI/showTipFrame.png");
		getParent()->addChild(frame, 5, "TXTTip");
		frame->setPosition(400, 190);
		frame->runAction(Sequence::create(DelayTime::create(5.0f), RemoveSelf::create(1), nullptr));
		auto txt = Sprite::create("System_UI/tip_qingyise.png");
		txt->setPosition(frame->getContentSize() / 2);
		frame->addChild(txt);
	}
	else
	{
		if (PayEventMannger::getInstance()->getGamecount() < 3)
		{
			auto frame = Sprite::create("System_UI/showTipFrame.png");
			getParent()->addChild(frame, 5, "TXTTip");
			frame->setPosition(400, 190);
			frame->runAction(Sequence::create(DelayTime::create(5.0f), RemoveSelf::create(1), nullptr));
			auto txt = Sprite::create("System_UI/tip_text.png");
			txt->setPosition(frame->getContentSize() / 2);
			frame->addChild(txt);
		}
	}
	
}


bool SystemUI::IsEnableToTask()
{
	int val = CCUserDefault::sharedUserDefault()->getIntegerForKey("activeflag", 0);
	if (val <= 0)
	{
		return true;
	}

	int day = XygGetToday();
	//不是今天
	if (val / 100 != day)
	{
		return true;
	}
	else if (val % 100 != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
int SystemUI::XygGetToday()
{
	int day = 1900;
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);

	day += timeinfo->tm_year;
	day = day * 100 + timeinfo->tm_mon + 1;
	day = day * 100 + timeinfo->tm_mday;

	return day;
	//返回20151013 格式
}
void SystemUI::ResetTask()
{
	int day = XygGetToday();
	int val = CCUserDefault::sharedUserDefault()->getIntegerForKey("activeflag", 0);
	if (val / 100 != day)//不是今天就清零
	{
		UserDefault::getInstance()->setIntegerForKey("record", 0);
		UserDefault::getInstance()->setIntegerForKey("activeflag", day * 100 + 0);
		DBManager::GetInstance()->initDayGameTimes();
	}
}
void SystemUI::OnActive()
{
	if (Jniutill::getInstance()->IsHdOpen() == false)
	{
		return;
	}


	auto data = DBManager::GetInstance();
	int val = CCUserDefault::sharedUserDefault()->getIntegerForKey("activeflag", 0);
	if (val == 0 || val % 100 == 0)
	{
		//完成时未发放奖励时
		if (data->getISTaskSuccess())
		{
			showdiog(0);
			EventListenerCustom* listener = EventListenerCustom::create("show_active_over", [=](EventCustom* event){
				getEventDispatcher()->removeCustomEventListeners("show_active_over");
			});
			getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
			User::getInstance()->setMyCoins(User::getInstance()->getMyCoins() + 3000);
			dispatchMahjongEvent(FLOW_NAME::Refresh_Coin, nullptr);
			Toast::show(ChineseWord("TaskSucess").c_str(), 3.0f, this);
			UserDefault::getInstance()->setIntegerForKey("activeflag", val + 1);

		}
		else
		{   //没有完成
			Toast::show(ChineseWord("TaskFailed").c_str(), 3.0f, this);
		}

	}
	else
	{
		//一天只限领取一次，明天再来哦！
		Toast::show(ChineseWord("AdayAtime").c_str(), 3.0f, this);
	}
}

void SystemUI::showdiog(float dt)
{
	Jniutill::getInstance()->showHdDialog();
}
