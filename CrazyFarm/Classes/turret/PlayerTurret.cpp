#include "Turret/PlayerTurret.h"
#include "bullet/BulletManage.h"
#include "utill/AnimationUtil.h"
#include "domain/user/User.h"
#include "config/ConfigRoom.h"
#include "data/GameData.h"
#include "config/ConfigVipTurrent.h"
#include "config/ConfigNormalTurrent.h"
#include "domain/bonuspool/BonusPoolManager.h"
#include "core/GameLayer.h"
#include "domain/mermaid/MermaidTask.h"
#include "core/showTurretLayer.h"
#include "domain/bankrupt/BankruptManager.h"
#include "domain/bag/BagManager.h"
#include "core/GameGuiLayer.h"
#include "utill/Audio.h"
#include "core/GetRewardNode.h"
#include "domain/logevent/LogEventMannger.h"
#include "domain/game/GameManage.h"
#include "lobby/Nobility/NobilityLayer.h"
#include "domain/logevent/LogEventPageChange.h"
#include "bullet/Laster.h"
#include "domain/gameConfig/gameConfig.h"
#include "config/ConfigChest.h"
#include "config/ConfigNewbieFishCatch.h"
#include "domain/ToolTip/TwiceSureDialog.h"
#include "domain/logevent/LogEventTurrentUpgrade.h"
#include "core/GameScene.h"
#include "domain/loading/LoadingSceneLbToGm.h"
#include "core/showLockTurretLayer.h"
#include "widget/MyLabelAtlas.h"
enum
{
	kTagBankrupt = 20
};


bool PlayerTurret::init(){
	if (!Sprite::initWithFile("turretBg.png")){
		return false;
	}
	setIsShowInfo(false);

	m_turret = Turret::create();

	m_turret->setPosition(getContentSize().width / 2, getContentSize().height*0.6);
	addChild(m_turret, 1);

	setisUsingLight(false);
	scheduleUpdate();
	return true;
}
void PlayerTurret::setUpgradeButton()
{
	auto upgradeButton = MenuItemImage::create("add_nor.png", "add_click.png", CC_CALLBACK_1(PlayerTurret::upgradeTurret, this));
	upgradeButton->setPosition(this->getContentSize().width*0.9, this->getContentSize().height*0.2);
	auto degradeButton = MenuItemImage::create("minus_nor.png", "minus_click.png", CC_CALLBACK_1(PlayerTurret::degradeTurret, this));
	degradeButton->setPosition(this->getContentSize().width*0.1, this->getContentSize().height*0.2);
	auto menu = Menu::create(upgradeButton, degradeButton, nullptr);
	menu->setPosition(Point::ZERO);
	addChild(menu, 10, "menuUpDe");
}
void PlayerTurret::initTurretWithType(){
	auto vipLevel = User::getInstance()->getVipLevel();
	if (vipLevel == 0)
	{
		auto var = ConfigNormalTurrent::getInstance()->getNormalTurrent(User::getInstance()->getMaxTurrentLevel());
		turretdata.init(var.normal_turrent_id, var.turrent_ui_id, var.net_per, var.catch_per, var.ui_type, var.net_type);
	}
	else
	{
		auto var = ConfigVipTurrent::getInstance()->getVipTurrent(User::getInstance()->getVipLevel());
		turretdata.init(var.vip_turrent_id, var.turrent_ui_id, var.net_per, var.catch_per, var.ui_type, var.net_type);
	}


	m_turret->initWithType(turretdata.turrent_ui_id);

}

void PlayerTurret::changeNewTurret()
{
	auto vipLevel = User::getInstance()->getVipLevel();
	if (vipLevel == 0)
	{
		auto var = ConfigNormalTurrent::getInstance()->getNormalTurrent(User::getInstance()->getMaxTurrentLevel());
		turretdata.init(var.normal_turrent_id, var.turrent_ui_id, var.net_per, var.catch_per, var.ui_type, var.net_type);
	}
	else
	{
		auto var = ConfigVipTurrent::getInstance()->getVipTurrent(User::getInstance()->getVipLevel());
		turretdata.init(var.vip_turrent_id, var.turrent_ui_id, var.net_per, var.catch_per, var.ui_type, var.net_type);
	}


	m_turret->changeToNewTurret(turretdata.turrent_ui_id);
}



void PlayerTurret::addGoldFishForAi()
{
	if (isRobot)
	{
		goldfishcounts++;
		//Ê¹ÓÃ±ù¶³
		if (goldfishcounts % 5 == 0 && GameData::getInstance()->getRoomID() > 1)
		{
			skillManager::getInstance()->robotUseSkillFreeze(this);
		}
		//Ê¹ÓÃÕÙ»½
		if (goldfishcounts % 30 == 0 && GameData::getInstance()->getRoomID() > 1)
		{
			skillManager::getInstance()->robotUseSkillFreeze(this);
		}
	}

}
void PlayerTurret::update(float delta)
{

	if (isRobot)
	{

	}
	else
	{
		auto num = User::getInstance()->getCoins();
		m_CoinLabel->setString(Value(num).asString().c_str());

		num = User::getInstance()->getDiamonds();
		auto lastnum = Value(m_DiamondLabel->getString()).asInt();
		if (num > lastnum)
		{
			GameManage::getInstance()->showLockTurrent();
		}
		m_DiamondLabel->setString(Value(num).asString().c_str());

		num = GameData::getInstance()->getnowLevel();
		nCurLevel->setString(Value(num).asString().c_str());
		if (GameData::getInstance()->getisOnBankrupt())
		{
			if (User::getInstance()->getCoins() > 0)
			{
				GameData::getInstance()->setisOnBankrupt(false);
				getChildByTag(kTagBankrupt)->removeFromParentAndCleanup(1);
			}
		}
	}


}
void PlayerTurret::initTurretWithTypeForRobot(){
	auto var = ConfigNormalTurrent::getInstance()->getNormalTurrent(m_robotData->getMaxTurretLevel());
	turretdata.init(var.normal_turrent_id, var.turrent_ui_id, var.catch_per, var.net_per, var.ui_type, var.net_type);

	m_turret->initWithType(turretdata.turrent_ui_id);
}

void PlayerTurret::upgradeTurret(Ref* psend)
{
	LogEventSpcEvent::getInstance()->addEventItems(1, 0);
	int nowlv = GameData::getInstance()->getnowLevel();
	if (User::getInstance()->getMaxTurrentLevel() < nowlv)
	{
	
		m_btType = 1;
		TouchTheLockNode(nullptr, nullptr);
	}
	else
	{
		m_turretdata = GameData::getInstance()->getTurrentData();
		m_turretdata = ConfigTurrent::getInstance()->getNextTurrent(m_turretdata.multiple);
		if (m_turretdata.turrentId == -1)
		{
			m_turretdata = GameData::getInstance()->getTurrentData();
			auto dioag = TwiceSureDialog::createDialog(ChineseWord("UpdataMaxTurrent").c_str(), nullptr);
			dioag->setPosition(0, 0);
			GameManage::getInstance()->getGuiLayer()->addChild(dioag, 20);
			return;
		}
		GameData::getInstance()->setnowLevel(m_turretdata.multiple);
		changeNewTurret();
		if (m_turretdata.turrentId > User::getInstance()->getMaxTurrentLevel())
		{
			m_btType = 1;
			ShowLockTurretTip();
		}
	}
}
void PlayerTurret::degradeTurret(Ref* psend)
{
	LogEventSpcEvent::getInstance()->addEventItems(2, 0);
	m_turretdata = GameData::getInstance()->getTurrentData();
	auto nowlevel = m_turretdata.turrentId;

	if (User::getInstance()->getMaxTurrentLevel() < nowlevel)
	{
		auto node = getChildByName("locknode");
		if (node)
		{
			node->removeFromParentAndCleanup(1);
		}
		m_turretdata = ConfigTurrent::getInstance()->getTurrent(User::getInstance()->getMaxTurrentLevel());
		GameData::getInstance()->setnowLevel(m_turretdata.multiple);
		changeNewTurret();
	}
	else
	{
		m_turretdata = ConfigTurrent::getInstance()->getLastTurrent(nowlevel);
		auto room = ConfigRoom::getInstance()->getRoombyId(GameData::getInstance()->getRoomID());

		if (m_turretdata.turrentId < room.unlock_turrent_level || m_turretdata.turrentId == -1)
		{
			m_turretdata = ConfigTurrent::getInstance()->getNextTurrent(User::getInstance()->getMaxTurrentLevel());
			if (m_turretdata.turrentId == -1)
			{
				m_turretdata = ConfigTurrent::getInstance()->getTurrent(User::getInstance()->getMaxTurrentLevel());
				GameData::getInstance()->setnowLevel(m_turretdata.turrentId);
				changeNewTurret();
			}
			else
			{
				changeNewTurret();
				GameData::getInstance()->setnowLevel(m_turretdata.turrentId);
				m_btType = -1;
				ShowLockTurretTip();
			}

			return;
		}
		changeNewTurret();
		nCurLevel->setString(Value(m_turretdata.turrentId).asString());
		m_turret->degradeTurret();
		GameData::getInstance()->setnowLevel(m_turretdata.turrentId);
	}

}



void PlayerTurret::rorateTurret(float angle)
{
	m_turret->setRotation(angle);
}
void PlayerTurret::ShowLockTurretTip()
{
	auto locknode = Node::create();
	locknode->setPosition(0, 0);
	addChild(locknode, 9, "locknode");
	auto lock = Sprite::create("lock.png");
	lock->setPosition(getContentSize() / 2 + Size(0, 10));
	lock->setVisible(false);
	lock->runAction(Sequence::create(DelayTime::create(0.15f), CallFunc::create([=]{lock->setVisible(true); }), nullptr));
	locknode->addChild(lock, 2);
	auto tip = Sprite::create("TXTClickLock.png");
	tip->setPosition(getContentSize() / 2 + Size(0, 70));
	locknode->addChild(tip);
	tip->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5f, Vec2(0, -30)), MoveBy::create(0.5f, Vec2(0, 30)), nullptr)));


	auto listenr1 = EventListenerTouchOneByOne::create();
	listenr1->onTouchBegan = CC_CALLBACK_2(PlayerTurret::TouchTheLockNode, this);
	listenr1->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, locknode);
}
void  PlayerTurret::onLockTheTurrent()
{
	GameManage::getInstance()->getGuiLayer()->anastole();


	m_btType = 0;
	auto node = getChildByName("locknode");
	if (node)
	{
		node->removeFromParentAndCleanup(1);
	}
	auto a = User::getInstance()->getMaxTurrentLevel();
	m_turretdata = ConfigTurrent::getInstance()->getNextTurrent(a);
	User::getInstance()->setMaxTurrentLevel(m_turretdata.multiple);
	LogEventTurrentUpgrade::getInstance()->sendDataToServer(m_turretdata.multiple, GlobalSchedule::getInstance()->getGameTime());
	User::getInstance()->addDiamonds(-m_turretdata.unlockPrice);
	auto vec = m_turretdata.rewardList;
	for (auto var : vec)
	{
		if (var.itemId == 1001)
		{
			User::getInstance()->addCoins(var.num);
		}
		else if (var.itemId == 1002)
		{
			User::getInstance()->addDiamonds(var.num);
		}
		else
		{
			BagManager::getInstance()->changeItemCount(var.itemId, var.num);
		}

	}
	GameData::getInstance()->setnowLevel(m_turretdata.multiple);
	//½âËø³É¹¦×ÖÑùÌáÊ¾
	auto layer = Director::getInstance()->getRunningScene()->getChildByTag(777);
	auto pos = GameManage::getInstance()->getGameLayer()->GetMyTurret()->getPosition();
	auto txt1 = Sprite::create("lockTurretTXT2.png");
	txt1->setPosition(pos.x + 5, pos.y + 150);
	GameManage::getInstance()->getGuiLayer()->addChild(txt1, 10);
	auto ttf = LabelAtlas::create(Value(m_turretdata.multiple).asString().c_str(), "unLockNumTTF.png", 13, 19, '0');
	ttf->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	ttf->setPosition(0, txt1->getContentSize().height / 2);
	txt1->addChild(ttf);
	auto txt2 = Sprite::create("lockTurretTXT1.png");
	txt2->setAnchorPoint(Point(1, 0.5));
	txt2->setPosition(0, ttf->getContentSize().height / 2);
	ttf->addChild(txt2);
	auto ttf1 = LabelAtlas::create(Value(m_turretdata.rewardList.at(0).num).asString().c_str(), "multipleNum.png", 15, 21, '0');
	ttf1->setPosition(txt1->getContentSize().width, txt1->getContentSize().height / 2);
	ttf1->setAnchorPoint(Point(0, 0.5));
	txt1->addChild(ttf1);
	txt1->runAction(Sequence::create(DelayTime::create(3.5f), RemoveSelf::create(1), nullptr));
	//½ð±ÒµôÂä
	for (int i = 0; i < 15; i++)
	{
		
		auto aniCoin = Sprite::create();
		aniCoin->setPosition(pos.x + 40 * (rand_0_1() - 0.5), pos.y + 70);
		aniCoin->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniGold")));
		aniCoin->runAction(Sequence::create(DelayTime::create(0.05f*i), CallFunc::create([=]{Audio::getInstance()->playSound(UPDATALEVELGAINCOIN); }), MoveBy::create(0.23f, Vec2(0, 86)), MoveBy::create(0.13f, Vec2(0, -86)), MoveBy::create(0.1f, Vec2(0, 27.5)), MoveBy::create(0.1f, Vec2(0, -27.5)), DelayTime::create(0.6f), MoveTo::create(0.16f, pos), RemoveSelf::create(1), nullptr));
		GameManage::getInstance()->getGuiLayer()->addChild(aniCoin, 5);
	}
	//½ð±ÒÊý×Ö
	auto str = String::createWithFormat(":%d", m_turretdata.rewardList.at(0).num);
	auto label = LabelAtlas::create(str->getCString(), "TTFaniGold.png", 23, 34, '0');
	label->setAnchorPoint(Point::ANCHOR_MIDDLE);
	label->setPosition(GameManage::getInstance()->getGameLayer()->GetMyTurret()->getCoinLabelPos() + Vec2(0, 60));
	label->setScale(0);
	label->runAction(ScaleTo::create(0.1, 1));
	label->runAction(Sequence::create(DelayTime::create(3.0f), RemoveSelf::create(), nullptr));
	GameManage::getInstance()->getGuiLayer()->addChild(label, 5);
	GameManage::getInstance()->getGameLayer()->RefreShmyPlayerTurret();
	//µ¯³öÏÂÒ»¼¶·¿¼äÌáÊ¾
	int maxlv = User::getInstance()->getMaxTurrentLevel();
	auto nextroom = ConfigRoom::getInstance()->getNextRoombyId(GameData::getInstance()->getRoomID());
	if (maxlv == nextroom.unlock_turrent_level)
	{
		auto dioag = TwiceSureDialog::createDialog(ChineseWord("LockNewRoom").c_str(), CC_CALLBACK_1(PlayerTurret::ChangeNextRoom, this));
		dioag->setPosition(0, 0);
		GameManage::getInstance()->getGuiLayer()->addChild(dioag, 20);
	}
}
void PlayerTurret::ChangeNextRoom(Ref*psend)
{
	auto nextroom = ConfigRoom::getInstance()->getNextRoombyId(GameData::getInstance()->getRoomID());

	auto node = BankruptManager::getInstance()->getgetRewardNode();
	if (node&&User::getInstance()->getCoins() <= 0)
	{
		node->retain();
		node->removeFromParentAndCleanup(false);

	}
	GameData::getInstance()->setRoomID(nextroom.room_id);
	Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::create()));
}




void PlayerTurret::changeDataByBtnType()
{
	auto node = getChildByName("locknode");
	if (node)
	{
		node->removeFromParentAndCleanup(1);
	}
	else
	{
		return;
	}
	if (m_btType == 0)
	{
		return;
	}
	else if (m_btType == 1)
	{
		m_turretdata = ConfigTurrent::getInstance()->getTurrent(ConfigRoom::getInstance()->getRoombyId(GameData::getInstance()->getRoomID()).unlock_turrent_level);
	}
	else if (m_btType == -1)
	{
		m_turretdata = ConfigTurrent::getInstance()->getTurrent(User::getInstance()->getMaxTurrentLevel());
	}
	changeNewTurret();
	nCurLevel->setString(Value(m_turretdata.turrentId).asString());
	GameData::getInstance()->setnowLevel(m_turretdata.multiple);
	m_btType = 0;
}
bool PlayerTurret::TouchTheLockNode(Touch *pTouch, Event *pEvent)
{

	auto layer = showLockTurretLayer::create();
	layer->setPosition(Point::ZERO);
	GameManage::getInstance()->getGuiLayer()->addChild(layer, 20, 50);
	//µ¯¸¶·Ñ


	//if (m_btType == 1)
	//{
	//	m_turretdata = ConfigTurrent::getInstance()->getTurrent(ConfigRoom::getInstance()->getRoombyId(GameData::getInstance()->getRoomID()).unlock_turrent_level);
	//}
	//else if (m_btType == -1)
	//{
	//	m_turretdata = ConfigTurrent::getInstance()->getTurrent(User::getInstance()->getMaxTurrentLevel());
	//}
	//changeNewTurret();
	//nCurLevel->setString(Value(m_turretdata.turrentId).asString());
	//GameData::getInstance()->setnowLevel(m_turretdata.multiple);
	return true;
}


void PlayerTurret::shoot(float degree){

	if (!isRobot&&GameData::getInstance()->getisOnBankrupt())
	{
		return;
	}
	if (!isCanShoot())
	{
		return;
	}
	rorateTurret(degree);
	if (nChairNoIndex > 1)
	{
		degree = 180 + degree;
	}

	auto bullet = BulletManage::getInstance()->createBullet(turretdata, 90);
	bullet->setRotation(degree);
	bullet->setPosition(/*this->getPosition()*/m_turret->getTampionPos());
	bullet->setPlayerTurret(this);
	getParent()->addChild(bullet, 8);

	//ï¿½Ú¿ï¿½ï¿½ï¿½ï¿½ï¿½

	m_turret->shoot();

	costMoney();


	

}

void PlayerTurret::setAIinfo(AI*info)
{
	m_aiinfo = info;
	schedule(schedule_selector(PlayerTurret::doAIthing), info->getReqSteps(), CC_REPEAT_FOREVER, 0);
}

void PlayerTurret::doAIthing(float dt)
{

	auto walk = m_aiinfo->nextStep(nNowMoney, getPosition());
	auto angle = walk.getAngle();
	m_turret->setRotation(angle);
	if (walk.getFire())
	{
		runAction(Sequence::create(CallFunc::create([&]{shoot(m_turret->getRotation()); }), nullptr));

	}
}
void PlayerTurret::stopAI()
{
	unschedule(schedule_selector(PlayerTurret::doAIthing));
}


Point coinPos[4] =
{
	Vec2(-122, 42),
	Vec2(122 + 155, 42),
	Vec2(-122, 42),
	Vec2(122 + 155, 42)
};
void PlayerTurret::createPlayerCoin(User* user, int index)
{
	isRobot = false;
	auto spCoinBG = Sprite::create("coinAnddiamondBG.png");
	spCoinBG->setPosition(coinPos[index]);
	addChild(spCoinBG, 10, index);
	m_coinLabelPos = spCoinBG->getPosition();
	m_CoinLabel = MyLabelAtlas::create(Value(user->getCoins()).asString().c_str(), "multipleNum.png", 15, 21, '0',110);
	m_CoinLabel->setPosition(spCoinBG->getContentSize().width*0.9, spCoinBG->getContentSize().height*0.71);
	m_CoinLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	spCoinBG->addChild(m_CoinLabel);

	m_DiamondLabel = MyLabelAtlas::create(Value(user->getDiamonds()).asString().c_str(), "multipleNum.png", 15, 21, '0',110);
	m_DiamondLabel->setPosition(spCoinBG->getContentSize().width*0.9, spCoinBG->getContentSize().height*0.29);
	m_DiamondLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	spCoinBG->addChild(m_DiamondLabel);

}




void PlayerTurret::createPlayerCoin(RoomPlayer* user)
{
	m_turret->setIsRobot(true);
	auto spCoinBG = Sprite::create("coinAnddiamondBG.png");
	spCoinBG->setPosition(coinPos[user->getRoomPosition()]);
	addChild(spCoinBG, 10, user->getRoomPosition());
	m_coinLabelPos = spCoinBG->getPosition();
	nNowMoney = user->getCoins();
	m_CoinLabel = LabelAtlas::create(Value(user->getCoins()).asString().c_str(), "multipleNum.png", 15, 21, '0');
	m_CoinLabel->setPosition(spCoinBG->getContentSize().width*0.9, spCoinBG->getContentSize().height*0.71);
	m_CoinLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	spCoinBG->addChild(m_CoinLabel);

	m_DiamondLabel = LabelAtlas::create(Value(user->getDiamonds()).asString().c_str(), "multipleNum.png", 15, 21, '0');
	m_DiamondLabel->setPosition(spCoinBG->getContentSize().width*0.9, spCoinBG->getContentSize().height*0.29);
	m_DiamondLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	spCoinBG->addChild(m_DiamondLabel);

	if (user->getRoomPosition() > 1)
	{
		spCoinBG->setRotation(180);
	}
}



void PlayerTurret::initWithDate(User* user, int index)
{
	m_turret->setIsRobot(false);


	int boxlv = user->getUserBoxLevel();

	if (boxlv > 0)
	{
		auto sp = Sprite::create("circyleLight.png");
		sp->setPosition(getContentSize().width / 2, 0);
		sp->runAction(RepeatForever::create(RotateBy::create(5.0, 360)));
		addChild(sp, -1);
	}


	auto str = String::createWithFormat("turretBg_%d.png", boxlv);
	setTexture(str->getCString());

	str = String::createWithFormat("multipleBg_%d.png", boxlv);
	auto levelBg = Sprite::create(str->getCString());
	levelBg->setPosition(getContentSize().width / 2, levelBg->getContentSize().height / 2);
	addChild(levelBg, 10, "multipleBg");
	nCurLevel = LabelAtlas::create("0", "multipleNum.png", 15, 21, '0');
	nCurLevel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	nCurLevel->setPosition(107.0 / 2, 33.0 / 2);
	levelBg->addChild(nCurLevel);

	GameData::getInstance()->setnowLevel(User::getInstance()->getMaxTurrentLevel());
	m_turretdata = GameData::getInstance()->getTurrentData();
	initTurretWithType();
	setUpgradeButton();
	nCurLevel->setString(Value(m_turretdata.turrentId).asString().c_str());

	createPlayerCoin(user, index);
	nChairNoIndex = index;
	if (GameData::getInstance()->getisOnBankrupt() || user->getCoins() <= 0)
	{
		onBankrupt();
	}
}
void PlayerTurret::initWithDate(RoomPlayer* user)
{
	int boxlv = rand() % 4;

	if (boxlv > 0)
	{
		auto sp = Sprite::create("circyleLight.png");
		sp->setPosition(getContentSize().width / 2, 0);
		sp->runAction(RepeatForever::create(RotateBy::create(5.0, 360)));
		addChild(sp, -1);
	}

	auto str = String::createWithFormat("turretBg_%d.png", boxlv);
	setTexture(str->getCString());

	str = String::createWithFormat("multipleBg_%d.png", boxlv);
	auto levelBg = Sprite::create(str->getCString());
	levelBg->setPosition(getContentSize().width / 2, levelBg->getContentSize().height / 2);
	addChild(levelBg, 10, "multipleBg");
	nCurLevel = LabelAtlas::create("0", "multipleNum.png", 15, 21, '0');
	nCurLevel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	nCurLevel->setPosition(107.0 / 2, 33.0 / 2);
	levelBg->addChild(nCurLevel);


	m_robotData = user;
	m_turretdata = ConfigTurrent::getInstance()->getTurrent(user->getMaxTurretLevel());
	nChairNoIndex = user->getRoomPosition();
	initTurretWithTypeForRobot();
	nCurLevel->setString(Value(m_turretdata.turrentId).asString().c_str());

	createPlayerCoin(user);
	setAIinfo(user->getAi());
	if (user->getRoomPosition() > 1)
	{
		setRotation(180);
	}


}
void PlayerTurret::getCoinByFish(Fish* fish)
{

	int num = 0;
	LogEventFish::getInstance()->addFishCatchTimes(fish->getFishID());


	if (isRobot)
	{
		if (fish->getFishType() == GoldFish)
		{
			addGoldFishForAi();
		}

		num = fish->getFishGold() * m_turretdata.multiple;
		auto nowNum = Value(m_CoinLabel->getString()).asInt();
		m_CoinLabel->setString(Value(nowNum + num).asString().c_str());

	}
	else
	{
		if (GameData::getInstance()->getisOnBankrupt())
		{
			return;
		}
		LogEventFish::getInstance()->addFishUserCatchTimes(fish->getFishID());
		m_turretdata = GameData::getInstance()->getTurrentData();

		
		num = fish->getFishGold()* m_turretdata.multiple*ConfigChest::getInstance()->getChestByLevel(User::getInstance()->getUserBoxLevel()).catch_per;
		m_CoinLabel->setString(Value(User::getInstance()->addCoins(+num)).asString().c_str());

		auto exp = fish->getFishExperience();
		if (User::getInstance()->addExp(exp))
		{
			onPlayerUpgrade();
		}

		BonusPoolManager::getInstance()->addCoins(fish->getBounsPoorGold());

		auto event = GameData::getInstance()->getDiamondevent();
		if (GameData::getInstance()->getShotDiamondCount() >= event.fireTimes)
		{
			GameManage::getInstance()->getGameLayer()->onGetRewardByfish(this, fish, 1002, event.num);
			LogEventMagnate::getInstance()->addMagnateNum(event.itemId, event.num);
			GameData::getInstance()->setShotDiamondCount(0);
			GameData::getInstance()->setDiamondevent(MagnateManager::getInstance()->getDiamandMagnateEvent());


		}
		event = GameData::getInstance()->getpropevent();
		if (GameData::getInstance()->getShotPropCount() >= event.fireTimes)
		{
			GameManage::getInstance()->getGameLayer()->onGetRewardByfish(this, fish, event.itemId, event.num);
			LogEventMagnate::getInstance()->addMagnateNum(event.itemId, event.num);
			GameData::getInstance()->setShotPropCount(0);
			GameData::getInstance()->setpropevent(MagnateManager::getInstance()->getItemMagnateEvent());

		}
	}
	fish->createDropOutAniByCoin(getPosition(), num);
	for (auto reward : fish->getFishRewards())
	{
		GameManage::getInstance()->getGameLayer()->onGetRewardByfish(this, fish, reward.item_id, reward.num);
	}


}

void PlayerTurret::onExit()
{
	Sprite::onExit();
	m_CoinLabel->removeFromParentAndCleanup(true);
	m_DiamondLabel->removeFromParentAndCleanup(true);
	m_turret->removeFromParentAndCleanup(true);

}


void PlayerTurret::onBankrupt()
{
	auto sp = Sprite::create("bankrupt.png");
	sp->setPosition(getContentSize() / 2);
	addChild(sp, 10, kTagBankrupt);
	m_CoinLabel->setString("0");
	nNowMoney = 0;

	if (isRobot)
	{
		auto bankrupt = BankruptManager::getInstance()->getRobotBankrupt();
		stopAI();

		int *k = new int();
		*k = bankrupt.coins;
		runAction(Sequence::create(DelayTime::create(bankrupt.wait_time), CallFunc::create(CC_CALLBACK_0(PlayerTurret::onAIResurgenceCallBack, this, this, k)), nullptr));
	}
	else
	{
		if (!BankruptManager::getInstance()->getgetRewardNode())
		{
			BankruptManager::getInstance()->RequestServerToBroke(this);
		}
		/*auto bankrupt = BankruptManager::getInstance()->getBankrupt();
		if (!BankruptManager::getInstance()->getgetRewardNode() && bankrupt.coins>0)
		{
		auto layer = Director::getInstance()->getRunningScene()->getChildByTag(888);
		auto node = GetRewardNode::create(bankrupt);
		node->setPosition(getPosition()+Vec2(0,150));
		layer->addChild(node, 10);
		BankruptManager::getInstance()->setgetRewardNode(node);
		int num = BankruptManager::getInstance()->getTodayRequestTimes();
		LogEventBankrupt::getInstance()->sendDataToServer(GameData::getInstance()->getRoomID(),2, num+1);
		}
		else if (bankrupt.coins==0)
		{
		auto pay = payLayer::createLayer(1);
		pay->setPosition(0, 0);
		pay->setEventPont(19);
		GameManage::getInstance()->getGuiLayer()->addChild(pay, 20);
		}*/

		GameData::getInstance()->setisOnBankrupt(true);

	}
}
void PlayerTurret::onAIResurgenceCallBack(Node* sender, void* data)
{

	setAIinfo(m_aiinfo);
	auto var = *((int*)data);
	nNowMoney += var;
	m_CoinLabel->setString(Value(nNowMoney).asString().c_str());
	getChildByTag(kTagBankrupt)->removeFromParentAndCleanup(1);
}

void PlayerTurret::refreshTurretInfo()
{
	auto vipLevel = User::getInstance()->getVipLevel();
	if (vipLevel == 0)
	{
		auto var = ConfigNormalTurrent::getInstance()->getNormalTurrent(User::getInstance()->getMaxTurrentLevel());
		turretdata.init(var.normal_turrent_id, var.turrent_ui_id, var.net_per, var.catch_per, var.ui_type, var.net_type);
	}
	else
	{
		auto var = ConfigVipTurrent::getInstance()->getVipTurrent(User::getInstance()->getVipLevel());
		turretdata.init(var.vip_turrent_id, var.turrent_ui_id, var.net_per, var.catch_per, var.ui_type, var.net_type);
	}


	changeNewTurret();
}
void PlayerTurret::setLightFish(Fish* fish)
{
	if (fish == nullptr)
	{
		lightFish = nullptr;
		auto node = getParent()->getChildByName("Laster");
		if (node)
		{
			node->removeFromParentAndCleanup(1);
			node = nullptr;
		}

		return;
	}
	else
	{
		if (lightFish)
		{
			if (lightFish->getTargeLightTurret() == this)
			{
				lightFish->stopLightShoot();
			}
		}


		fish->onLightShoot(this);
	}
	lightFish = fish;


	auto node = getParent()->getChildByName("Laster");
	if (node)
	{
		node->removeFromParentAndCleanup(1);

		node = nullptr;
	}
	auto spLaster = Laster::create();
	spLaster->setPlayerTurret(this);
	getParent()->addChild(spLaster, 9, "Laster");


}

void PlayerTurret::rorateAndShootOnlight(float dt)
{
	if (lightFish == nullptr)
	{
		return;
	}
	if (isRobot&&GameData::getInstance()->getisOnBankrupt())
	{
		return;
	};
	if (!isCanShoot())
	{
		return;
	}
	costMoney();

	auto pos = lightFish->getPosition();
	float degree = getTurretRotation(getPosition(), pos);
	rorateTurret(degree);
	lightFish->onHeart();
	LogEventFish::getInstance()->addFishUserCostCoin(lightFish->getFishID(), 2 * getTurrentMupltData().multiple);
	LogEventFish::getInstance()->addFishHitTimes(lightFish->getFishID());
	float k = rand_0_1();

	float per = lightFish->getGrabProbability();

	if (!isRobot)
	{
		float perForLevel = ConfigNewbieFishCatch::getInstance()->getperByLevelAndFishID(User::getInstance()->getLevelData().levelId, lightFish->getFishID());
		if (perForLevel != -1)
		{
			per = perForLevel;
		}
	}

	if (k < (per*turretdata.catch_per * 2))
	{
		GameManage::getInstance()->CatchTheFishOntheTurrent(lightFish, 1, this);
		lightFish = nullptr;
	}

}
void PlayerTurret::shootOnLight(float dt)
{

}

void PlayerTurret::beginLightShoot()
{
	setisUsingLight(true);
	getChildByName("menuUpDe")->setVisible(false);
	m_turret->changeToLightTurret();

	auto aniNode = Sprite::create();
	aniNode->setPosition(m_turret->getPosition());
	addChild(aniNode, 0, "aniTurretLight");
	auto ac = RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniJiGuangBottom"));
	aniNode->runAction(ac);
	setLightFish(lightFish);
	schedule(schedule_selector(PlayerTurret::rorateAndShootOnlight), GameConfig::getInstance()->getShootData().shootInterval);
}
void PlayerTurret::endLightShoot()
{
	setisUsingLight(false);
	getChildByName("aniTurretLight")->removeFromParentAndCleanup(1);
	getChildByName("menuUpDe")->setVisible(true);
	auto node = getParent()->getChildByName("Laster");
	if (node)
	{
		node->unscheduleUpdate();
		node->removeFromParentAndCleanup(1);
		node = nullptr;
	}
	m_turret->changeToNormalTurret();
	if (lightFish)
	{
		lightFish->stopLightShoot();
		setLightFish(nullptr);
	}
	stopActionByTag(123);


	unschedule(schedule_selector(PlayerTurret::rorateAndShootOnlight));
}


void PlayerTurret::setLockFish(Fish* fish)
{
	if (fish == nullptr)
	{
		auto node = getParent()->getChildByName("TXTTip");
		if (!node)
		{
			auto txt = Sprite::create("TXTUseLock.png");
			txt->setPosition(getPosition() + Vec2(0, 100));
			txt->runAction(RepeatForever::create(Sequence::create(FadeIn::create(0.8f), FadeOut::create(0.8f), nullptr)));
			getParent()->addChild(txt, kZorderDialog, "TXTTip");
		}
		
	}
	else
	{
		auto node = getParent()->getChildByName("TXTTip");
		if (node)
		{
			node->removeFromParentAndCleanup(1);
		}
		if (lockFish)
		{
			if (lockFish->getTargeLockTurret() == this)
			{
				lockFish->stopLockShoot();
			}
		}


		fish->onLockShoot(this);
	}
	lockFish = fish;
}


void PlayerTurret::beginLockShoot()
{
	auto aniNode = Sprite::create();
	aniNode->setPosition(m_turret->getPosition());
	addChild(aniNode, 5, "aniTurretLock");
	aniNode->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniTurretLock")));
	schedule(schedule_selector(PlayerTurret::rorateAndShootOnlock), GameConfig::getInstance()->getShootData().shootInterval);
}
void PlayerTurret::endLockShoot()
{
	getChildByName("aniTurretLock")->removeFromParentAndCleanup(1);
	if (lockFish)
	{
		lockFish->stopLockShoot();
		setLockFish(nullptr);
	}
	unschedule(schedule_selector(PlayerTurret::rorateAndShootOnlock));
}

void PlayerTurret::rorateAndShootOnlock(float dt)
{
	if (lockFish == nullptr)
	{
		return;
	}
	if (!isRobot&&GameData::getInstance()->getisOnBankrupt())
	{
		return;
	}
	auto pos = lockFish->convertToWorldSpace(lockFish->getCentrenPos());
	float degree = getTurretRotation(getPosition(), pos);
	rorateTurret(degree);
	shootOnLock(0);
	//scheduleOnce(schedule_selector(PlayerTurret::shootOnLock), GameConfig::getInstance()->getShootData().shootInterval);
}
void PlayerTurret::shootOnLock(float dt){

	if (lockFish == nullptr)
	{
		return;
	}
	if (!isCanShoot())
	{
		return;
	}

	auto degree = m_turret->getRotation();
	auto bullet = BulletManage::getInstance()->createBulletNoinPool(turretdata, 90);
	bullet->setRotation(degree);
	bullet->unscheduleUpdate();
	auto pos = m_turret->getTampionPos();
	bullet->setPosition(m_turret->getTampionPos());
	bullet->setPlayerTurret(this);
	auto duration = pos.distance(lockFish->convertToWorldSpace(lockFish->getCentrenPos())) / GameConfig::getInstance()->getShootData().shootSpeed;
	bullet->moveToLockfish(duration, lockFish);
	getParent()->addChild(bullet, 8);




	m_turret->shoot();


	costMoney();
}


void PlayerTurret::beginAutoShoot()
{
	setTargetPos(Vec2(-1, -1));

	schedule(CC_CALLBACK_1(PlayerTurret::rorateAndShootOnAuto, this), GameConfig::getInstance()->getShootData().shootInterval, "AutoShoot"); //TODO:ï¿½Óµï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Ù¶È¡ï¿½ï¿½ï¿½Òªï¿½ï¿½ï¿½ï¿½
}
void PlayerTurret::endAutoShoot()
{

	unschedule("AutoShoot");
}

void PlayerTurret::rorateAndShootOnAuto(float dt)
{
	CCLOG("%f", dt);
	if (targetPos == Point(-1, -1))
	{
		return;
	}
	if (!isRobot&&GameData::getInstance()->getisOnBankrupt())
	{
		return;
	}

	float degree = getTurretRotation(getPosition(), targetPos);
	rorateTurret(degree);
	scheduleOnce(schedule_selector(PlayerTurret::shootOnAuto), 0.1f);
}
void PlayerTurret::shootOnAuto(float dt){

	if (!isCanShoot())
	{
		return;
	}

	auto degree = m_turret->getRotation();
	auto bullet = BulletManage::getInstance()->createBullet(turretdata, 90);
	bullet->setRotation(degree);
	auto pos = m_turret->getTampionPos();
	bullet->setPosition(m_turret->getTampionPos());
	bullet->setPlayerTurret(this);
	getParent()->addChild(bullet, 8);
	m_turret->shoot();

	//ï¿½ï¿½ï¿½ð¶¯»ï¿½
	


	//ï¿½ï¿½ï¿½Ñ½ï¿½ï¿?
	costMoney();
}






bool PlayerTurret::onTurretTouch(Point pos)
{
	if (isTurretBeTouch(pos))
	{
		if (isRobot)
		{
			showRobotInfo();
		}
		else
		{
			showPlayerInfo();
			auto layer = (GameLayer*)(Director::getInstance()->getRunningScene()->getChildByTag(777));
			if (isScheduled("AutoShoot"))
			{

				layer->endAutoShoot();
			}
		}
		return true;
	}
	return false;
}

bool PlayerTurret::isTurretBeTouch(Point pos)
{
	auto rect = getBoundingBox();
	if (rect.containsPoint(pos))
	{
		return true;
	}
	return false;
}
void PlayerTurret::showRobotInfo()
{
	setIsShowInfo(true);
}

void PlayerTurret::showPlayerInfo()
{
	auto node = getChildByName("showPlayerInfo");
	if (node)
	{
		return;
	}
	setIsShowInfo(true);
	auto menu = Menu::create();
	menu->setPosition(Point::ZERO);
	addChild(menu, 10, "showPlayerInfo");
	auto changeTurrent = MenuItemImage::create("changeTurrent.png", "changeTurrent.png", CC_CALLBACK_1(PlayerTurret::changeTurrentCallback, this));
	changeTurrent->setPosition(15, 110);
	menu->addChild(changeTurrent);

	auto autoShoot = MenuItemImage::create("autoShoot.png", "autoShoot.png", CC_CALLBACK_1(PlayerTurret::autoShootCallback, this));
	autoShoot->setPosition(getContentSize().width - 15, 110);
	menu->addChild(autoShoot);
}

void PlayerTurret::removePlayerInfo()
{
	auto node = getChildByName("showPlayerInfo");
	if (node)
	{
		node->removeFromParentAndCleanup(1);
	}


}
void PlayerTurret::removeRobotInfo()
{

}
void PlayerTurret::changeTurrentCallback(Ref*psend)
{
	auto node = (Node*)psend;
	auto layer = showTurretLayer::create(1);
	layer->setPosition(Point::ZERO);
	GameManage::getInstance()->getGuiLayer()->addChild(layer, 20, 50);
	node->getParent()->removeFromParentAndCleanup(1);

}
void PlayerTurret::autoShootCallback(Ref*psend)
{
	auto node = (Node*)psend;
	node->getParent()->removeFromParentAndCleanup(1);

	auto layer = (GameLayer*)(Director::getInstance()->getRunningScene()->getChildByTag(777));
	if (isScheduled("AutoShoot"))
	{

		layer->endAutoShoot();
	}
	else
	{
		if (User::getInstance()->getNobillityCount() > 0)
		{
			layer->beginAutoShoot();
		}
		else
		{
			auto layer = NobilityLayer::createLayer();
			layer->setPosition(0,10);
			GameManage::getInstance()->getGuiLayer()->addChild(layer, 20);
		}

	}
}

void PlayerTurret::onPlayerUpgrade()
{
	GameManage::getInstance()->onPlayerUpgrade();
}

void PlayerTurret::costMoney()
{
	if (isRobot)
	{
		auto num = (Value(m_turretdata.multiple).asInt());
		nNowMoney -= num;
		m_CoinLabel->setString(Value(nNowMoney).asString().c_str());
		if (nNowMoney <= 0)
		{
			onBankrupt();
		}
	}
	else
	{
		Turrent data = m_turretdata;
		auto node = getChildByName("locknode");
		if (node)
		{
			node->removeFromParentAndCleanup(1);
		}


		GameData::getInstance()->setShotDiamondCount(1 + (GameData::getInstance()->getShotDiamondCount()));
		GameData::getInstance()->setShotPropCount(1 + (GameData::getInstance()->getShotPropCount()));
		auto num = Value(m_turretdata.multiple).asInt();
		auto nowCoin = User::getInstance()->addCoins(-num);
		if (nowCoin <= 0)
		{
			onBankrupt();
		}
		m_CoinLabel->setString(Value(nowCoin).asString().c_str());

		if (GameData::getInstance()->getIsOnMaridTask())
		{
			GameData::getInstance()->getmermaidTask()->addCoins(num);
		}
	}
}

void PlayerTurret::ShowAddCoinAni(int type, int num)
{
	auto str = String::createWithFormat(":%d", num);
	auto label = LabelAtlas::create(str->getCString(), "TTFaniGold.png", 23, 34, '0');
	label->setAnchorPoint(Point::ANCHOR_MIDDLE);
	label->setPosition(m_coinLabelPos);
	addChild(label, 15);

	auto coinpath = type == 1 ? "smallCoin.png" : "smallDiamond.png";
	auto sp = Sprite::create(coinpath);
	sp->setPosition(label->getContentSize().width, label->getContentSize().height / 2);
	sp->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	label->addChild(sp);

	label->runAction(Sequence::create(Spawn::create(MoveBy::create(1.0f, Vec2(0, 50)), ScaleTo::create(1.0f, 1.5), FadeOut::create(1.5f), nullptr), RemoveSelf::create(), nullptr));
}

bool PlayerTurret::isCanShoot()
{
	auto node = getChildByName("locknode");
	if (node)
	{
		return false;
	}
	if (GameData::getInstance()->getisOnGroupComing())
	{
		return false;
	}
	return true;

}

Vec2 PlayerTurret::getPaoWorldpos()
{
	return convertToWorldSpace(m_turret->getPosition());
}