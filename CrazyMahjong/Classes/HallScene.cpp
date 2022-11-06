#include "HallScene.h"
#include "RulePanel.h"
#include "SignManager.h"
#include "ScrollTextEx.h"
#include "ShopPanel.h"
#include "SignInLayer.h"
#include "User.h"
#include "SetPanel.h"
#include "RanklistPanel.h"
#include "MahjongAnim.h"
#include "AnimationUtil.h"
#include "GameScene.h"
#include "NameMannger.h"
#include "SetNameLayer.h"
#include "PayEventMannger.h"
#include "PxPayMannger.h"
#include "RolePanel.h"
#include "ToolTipMannger.h"
#include "RedpackPanel.h"
#include "Audio.h"
#include "ui/setting/UserSetting.h"
Scene* HallScene::createScene()
{
	Scene* scene = Scene::create();
	Layer* layer = HallScene::create();
	scene->addChild(layer);
	return scene;
}

bool HallScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 centerPoint = Vec2(visibleSize.width/2, visibleSize.height/2);

	left = Node::create();
	left->setPosition(0, 0);
	addChild(left,1);

	right = Node::create();
	right->setPosition(0, 0);
	addChild(right,1);

	// 桌面背景
	Sprite* bkg = Sprite::create("hall_bg.png");
	bkg->setPosition(centerPoint);
	
	this->addChild(bkg);


	//头像
	auto headpath = String::createWithFormat("head_%d.png", User::getInstance()->getroleNowIndex());
	auto head = Sprite::create(headpath->getCString());
	head->setPosition(40, 444);
	addChild(head,1,"head");
	auto headbg = Sprite::create("headFrame.png");
	headbg->setPosition(head->getPosition());
	addChild(headbg, 0);

	auto headFrame = Sprite::create("head_frame.png");
	headFrame->setAnchorPoint(Point::ZERO);
	headFrame->setPosition(0, 480-headFrame->getContentSize().height);
	addChild(headFrame);

	//姓名
	auto nameFrame = Sprite::create("head_txtFrame.png");
	nameFrame->setPosition(136, headFrame->getContentSize().height / 2+8);
	headFrame->addChild(nameFrame);

	auto nameLabel = Label::createWithSystemFont(User::getInstance()->getMyName().c_str(), "arial", 18);
	nameLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	nameLabel->setPosition(nameFrame->getContentSize() / 2);
	nameFrame->addChild(nameLabel);

	//金币
	auto coinFrame = Sprite::createWithSpriteFrame(nameFrame->getSpriteFrame());
	coinFrame->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	coinFrame->setPosition(215, headFrame->getContentSize().height / 2+8);
	headFrame->addChild(coinFrame);

	auto BtnPlusCoin = Button::create("plus.png", "plus.png");
	BtnPlusCoin->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	BtnPlusCoin->setPosition(Vec2(coinFrame->getContentSize().width-4, coinFrame->getContentSize().height / 2));
	coinFrame->addChild(BtnPlusCoin);
	BtnPlusCoin->addTouchEventListener(this, toucheventselector(HallScene::addCoinCallback));

	auto coin = Sprite::create("coin.png");
	coin->setPosition(8, coinFrame->getContentSize().height / 2);
	coinFrame->addChild(coin);

	userCoin = LabelTTF::create(Value(User::getInstance()->getMyCoins()).asString(), "arial", 18);
	userCoin->setAnchorPoint(Point::ANCHOR_MIDDLE);
	userCoin->setPosition(coinFrame->getContentSize()/2+Size(-5,0));
	userCoin->setColor(Color3B(254, 248, 52));
	coinFrame->addChild(userCoin);

	//右上角功能按键
	float startX = 770;
	float startY = 450;
	float difx = -57;
	
	auto BtnMoreGame = Button::create("Btn_moregame_1.png", "Btn_moregame_2.png");
	BtnMoreGame->setPosition(Vec2(startX, startY));
	addChild(BtnMoreGame);
	BtnMoreGame->addTouchEventListener(this, toucheventselector(HallScene::BtnCallback));
	BtnMoreGame->setName("BtnMoreGame");

	startX += difx;
	auto BtnSetting= Button::create("Btn_Setting_1.png", "Btn_Setting_2.png");
	BtnSetting->setPosition(Vec2(startX, startY));
	addChild(BtnSetting);
	BtnSetting->addTouchEventListener(this, toucheventselector(HallScene::BtnCallback));
	BtnSetting->setName("BtnSetting");

	startX += difx;
	auto BtnHelp = Button::create("Btn_Help_1.png", "Btn_Help_2.png");
	BtnHelp->setPosition(Vec2(startX, startY));
	addChild(BtnHelp);
	BtnHelp->addTouchEventListener(this, toucheventselector(HallScene::BtnCallback));
	BtnHelp->setName("BtnHelp");

	startX += difx;
	auto BtnVip = Button::create("Btn_Vip_1.png", "Btn_Vip_2.png");
	BtnVip->setPosition(Vec2(startX, startY));
	addChild(BtnVip);
	BtnVip->addTouchEventListener(this, toucheventselector(HallScene::BtnCallback));
	BtnVip->setName("BtnVip");

	startX += difx;
	auto BtnShop = Button::create("Btn_shop_1.png", "Btn_shop_2.png");
	BtnShop->setPosition(Vec2(startX, startY));
	addChild(BtnShop);
	BtnShop->addTouchEventListener(this, toucheventselector(HallScene::BtnCallback));
	BtnShop->setName("BtnShop");

	startX += difx;

	//排行
	auto rankNode = RanklistPanel::create();
	rankNode->setPosition(132, 230);;
	left->addChild(rankNode);

	//房间
	auto Btn_chuji = Button::create("Btn_chuji_1.png", "Btn_chuji_2.png");
	Btn_chuji->setPosition(Vec2(506, 321));
	right->addChild(Btn_chuji);
	Btn_chuji->addTouchEventListener(this, toucheventselector(HallScene::RoomCallback));
	Btn_chuji->setName("Btn_chuji");
	auto ani = Sprite::create();
	ani->setPosition(Btn_chuji->getContentSize() / 2);
	ani->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("ani_piaoguang")));
	Btn_chuji->addChild(ani);
	auto score = Sprite::create("Tab_Roomscore_1.png");
	score->setPosition(Btn_chuji->getContentSize().width / 2, 45);
	Btn_chuji->addChild(score);

	auto Btn_zhongji = Button::create("Btn_zhongji_1.png", "Btn_zhongji_2.png");
	Btn_zhongji->setPosition(Vec2(506, 185));
	right->addChild(Btn_zhongji);
	Btn_zhongji->addTouchEventListener(this, toucheventselector(HallScene::RoomCallback));
	Btn_zhongji->setName("Btn_zhongji");
	ani = Sprite::create();
	ani->setPosition(Btn_zhongji->getContentSize() / 2);
	ani->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("ani_piaoguang")));
	Btn_zhongji->addChild(ani);
	score = Sprite::create("Tab_Roomscore_2.png");
	score->setPosition(Btn_zhongji->getContentSize().width / 2, 45);
	Btn_zhongji->addChild(score);

	auto Btn_gaoji = Button::create("Btn_gaoji_1.png", "Btn_gaoji_2.png");
	Btn_gaoji->setPosition(Vec2(675, 321));
	right->addChild(Btn_gaoji);
	Btn_gaoji->addTouchEventListener(this, toucheventselector(HallScene::RoomCallback));
	Btn_gaoji->setName("Btn_gaoji");
	ani = Sprite::create();
	ani->setPosition(Btn_gaoji->getContentSize() / 2);
	ani->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("ani_piaoguang")));
	Btn_gaoji->addChild(ani);
	score = Sprite::create("Tab_Roomscore_3.png");
	score->setPosition(Btn_gaoji->getContentSize().width / 2+10, 45);
	Btn_gaoji->addChild(score);

	auto Btn_qingyise = Button::create("Btn_qingyise_1.png", "Btn_qingyise_2.png");
	Btn_qingyise->setPosition(Vec2(600.5, 253));
	right->addChild(Btn_qingyise);
	Btn_qingyise->addTouchEventListener(this, toucheventselector(HallScene::RoomCallback));
	Btn_qingyise->setName("Btn_qingyise");

	
	auto Btn_quickstart = Button::create("Btn_quickstart_1.png", "Btn_quickstart_2.png");
	Btn_quickstart->setPosition(Vec2(705, 175));
	right->addChild(Btn_quickstart);
	Btn_quickstart->addTouchEventListener(this, toucheventselector(HallScene::RoomCallback));
	Btn_quickstart->setName("Btn_quickstart");
	ani = Sprite::create();
	ani->setPosition(Btn_quickstart->getContentSize() / 2);
	ani->runAction(RepeatForever::create(Sequence::createWithTwoActions(AnimationUtil::getInstance()->getAnimate("ani_quickstart"), AnimationUtil::getInstance()->getAnimate("ani_shanguang"))));
	Btn_quickstart->addChild(ani);

	//角色
	auto rolepath = String::createWithFormat("role_%d.png", User::getInstance()->getroleNowIndex());
	auto role = Sprite::create(rolepath->getCString());
	role->setPosition(350, 187);
	left->addChild(role,0,"role");

	auto light = Sprite::create();
	light->setPosition(role->getContentSize()/2);
	role->addChild(light, 0, "light");
	light->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("ani_huaguang")));
	
	auto Btn_Role = Button::create("Btn_changeHead_1.png", "Btn_changeHead_2.png");
	Btn_Role->setPosition(Vec2(345, 44));
	left->addChild(Btn_Role);
	Btn_Role->addTouchEventListener(this, toucheventselector(HallScene::BtnCallback));
	Btn_Role->setName("Btn_Role");

	auto DisplayBoard = ScrollTextEx::create();
	DisplayBoard->setPosition(400, 412);
	DisplayBoard->setAutoScroll(true);
	addChild(DisplayBoard,0,"DisplayBoard");

	auto rolepanel = RolePanel::create();
	rolepanel->setPosition(0, 0);
	addChild(rolepanel,0,"rolepanel");

	Audio::getInstance()->playBGM(1);
	//玩家第一次登陆
	if (User::getInstance()->getMyName()=="defulat")
	{
		Jniutill::getInstance()->logEvent("游戏_首次进入大厅");
		User::getInstance()->setMyName(NameMannger::getName());
		nameLabel->setString(User::getInstance()->getMyName());
	}
	else
	{
		Jniutill::getInstance()->logEvent("游戏_进入大厅");
		//VIP计费点
		if (!User::getInstance()->getisVip())
		{
			const std::function<void(EventCustom*)>& callback = [=](EventCustom*event){
			PayResult*reslt = (PayResult*)(event->getUserData());
				if (*reslt == Pay_Success)
				{

					showVipAddCoin();

				}
				Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(event->getEventName());
			};
			PxPayMannger::getInstance()->LaughPayLayer(VIPGIFT, this, callback);
		}
		else
		{
			if (!showVipAddCoin())
			{
				PxPayMannger::getInstance()->LaughCoinPayLayer(this);
			}
			
		}
	}

	scheduleUpdate();
	

	auto listern1 = EventListenerKeyboard::create();
	listern1->onKeyReleased = [=](EventKeyboard::KeyCode  keyCode, Event *event)
	{
	
		if (keyCode == EventKeyboard::KeyCode::KEY_BACK)
		{
			auto node = getChildByName("exit");
			if (node)
			{
				node->removeFromParentAndCleanup(1);
			}
			else
			{
				auto dg = ToolTipMannger::showDioag(this, ToolTipMannger::Tip_ShowExitGame);
				dg->setName("exit");
			}
			
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listern1, this);
	return true;
}

void HallScene::update(float delta)
{
	auto headpath = String::createWithFormat("head_%d.png", User::getInstance()->getroleNowIndex());
	auto head = (Sprite*)(getChildByName("head"));
	head->setTexture(headpath->getCString());

	userCoin->setString(Value(User::getInstance()->getMyCoins()).asString());


	auto rolepath = String::createWithFormat("role_%d.png", User::getInstance()->getroleNowIndex());
	auto role = (Sprite*)(left->getChildByName("role"));
	role->setTexture(rolepath->getCString());
}

void HallScene::addCoinCallback(Ref* pSender, TouchEventType type)
{
	if (type==TouchEventType::TOUCH_EVENT_ENDED)
	{
		auto panel = ShopPanel::create();
		addChild(panel, 30);
	}
}

void HallScene::BtnCallback(Ref*psend, TouchEventType type)
{
	auto bt = (Button*)psend;
	auto btName = bt->getName();
	if (type == TouchEventType::TOUCH_EVENT_ENDED)
	{
		MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);
		if (btName == "BtnMoreGame")
		{
		
			CCLOG("BtnMoreGameis Click!");
			Jniutill::getInstance()->showMoreGame();
		}
		if (btName == "BtnSetting")
		{
		
			CCLOG("BtnSetting is Click!");
			auto panel = UserSetting::create();
			addChild(panel, 30);
		}
		if (btName == "BtnHelp")
		{
		
			CCLOG("BtnHelp is Click!");
			auto panle = RulePanel::create();
			addChild(panle,20);
		
		}
		if (btName == "BtnVip")
		{
			CCLOG("BtnVipis Click!");

			if (User::getInstance()->getisVip())
			{
				ToolTipMannger::showDioag(Director::getInstance()->getRunningScene(), ToolTipMannger::Tip_BeingVip);
			}
			else
			{
				const std::function<void(EventCustom*)>& callback = [=](EventCustom*event){
					PayResult*reslt = (PayResult*)(event->getUserData());
					if (*reslt == Pay_Success)
					{

						showVipAddCoin();

					}
					Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(event->getEventName());
				};
				PxPayMannger::getInstance()->LaughPayLayer(VIPGIFT, this, callback);
			}
			
		}
		if (btName == "BtnShop")
		{
			
			CCLOG("BtnShop is Click!");
			auto panel = ShopPanel::create();
			addChild(panel, 30);
		}
		if (btName == "Btn_Role")
		{
			hide();
			auto node = (RolePanel*)getChildByName("rolepanel");
			node->show();
		}

	}
}
void HallScene::RoomCallback(Ref*psend, TouchEventType type)
{
	auto bt = (Button*)psend;
	auto btName = bt->getName();
	if (type == TouchEventType::TOUCH_EVENT_ENDED)
	{
		if (btName == "Btn_chuji")
		{
			MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);
			EnterRoom(ROOM_CHUJI);
		}
		if (btName == "Btn_zhongji")
		{
			MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);
			EnterRoom(ROOM_ZHONGJI);
		}
		if (btName == "Btn_gaoji")
		{
			MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);
			EnterRoom(ROOM_GAOJI);
		}
		if (btName == "Btn_qingyise")
		{
			MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);
			EnterRoom(ROOM_QINGYISE);
		}
		if (btName == "Btn_quickstart")
		{
			MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);
			int mycoin = User::getInstance()->getMyCoins();
			int roommincoin = Room::getInstance()->getRoomMinScore(0);
			if (mycoin <roommincoin)
			{
				auto key = String::createWithFormat("Text_ROOM_%d", 0);
				ToolTipMannger::showDioag(this, ToolTipMannger::TipType::Tip_LackingCoinToEnterRoom, ChineseWord(key->getCString()).c_str(), Value(roommincoin).asString().c_str(), "");
			}
			else
			{
				for (int i = 2; i >= 0; i--)
				{

					roommincoin = Room::getInstance()->getRoomMinScore(i);
					if (mycoin >= roommincoin)
					{
						EnterRoom((ROOM)i);
						return;
					}
				}
			}
		
		
		}
		
	}
}
void HallScene::EnterRoom(ROOM roomid)
{
	int mycoin = User::getInstance()->getMyCoins();
	int roommincoin = Room::getInstance()->getRoomMinScore(roomid);
	if (mycoin >= roommincoin)
	{
		Room::getInstance()->setRoomType(roomid);
		Director::getInstance()->replaceScene(GameScene::createScene());
	}
	else
	{
		auto key = String::createWithFormat("Text_ROOM_%d", roomid);
		ToolTipMannger::showDioag(this, ToolTipMannger::TipType::Tip_LackingCoinToEnterRoom, ChineseWord(key->getCString()).c_str(), Value(roommincoin).asString().c_str(),"");
	}

}

void HallScene::hide()
{
	left->runAction(MoveBy::create(0.1f, Vec2(-1000, 0)));
	right->runAction(MoveBy::create(0.1f, Vec2(1000, 0)));
	getChildByName("DisplayBoard")->setVisible(false);
}
void HallScene::show()
{
	left->runAction(MoveBy::create(0.1f, Vec2(1000, 0)));
	right->runAction(MoveBy::create(0.1f, Vec2(-1000, 0)));
	getChildByName("DisplayBoard")->setVisible(true);
	
}






int XygGetToday()
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

bool IsEnableToGet()
{
	int val = CCUserDefault::sharedUserDefault()->getIntegerForKey("vipAddCoin", 0);
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
		return false;
	}
	else
	{
		return true;
	}
}
bool HallScene::showVipAddCoin()
{
	bool isShowGetCoin = false;
	if (User::getInstance()->getisVip())
	{
		isShowGetCoin = IsEnableToGet();
		if (isShowGetCoin)
		{
			User::getInstance()->addCoin(20000);
			int val = XygGetToday() * 100 + 1;
			UserDefault::sharedUserDefault()->setIntegerForKey("vipAddCoin", val+1);
		}
	}
	return isShowGetCoin;
}