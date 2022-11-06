#include "SetNameLayer.h"
#include "GameFlow.h"
#include "Rules.h"
#include "MahjongDatas.h"
#include "Room.h"
#include "MahjongAnim.h"
#include "SystemUI.h"
#include "AIRules.h"
#include "PxPayMannger.h"
#include "PayEventMannger.h"
#include "User.h"
#include "DBManager.h"
#include "RedpackPanel.h"
#include "Audio.h"
#include "ReadpackNode.h"
#include "AnimationUtil.h"
//---------------------------------------   游戏流程    -------------------------------------------

//------------------------------------------ 初始化 ----------------------------------------------
bool GameFlow::init()
{
	CCLOG("GameFlow : init");

	if (!Node::init())
	{
		return false;
	}
	isGameOver = false;

	Room::getInstance()->init();
	//this->addChild( AddCoinPanel::create());

	
	pRules = Rules::getInstance();		// 麻将规则
	if (Room::getInstance()->getRoomType()==ROOM_QINGYISE)
	{
		pRules->init(Rule_QingYiSe);
	}
	else
	{
		pRules->init(Rule_Normal);
	}

	AIRules::getInstance()->init();		// AI策略

	MahjongDatas::getInstance()->initData();		// 麻将牌
	
	initPlayers();				// 玩家
	AIRules::getInstance()->setPlayerDrawer(players[0]->drawer);

	// 返回，设置，更多游戏，充值金币
	SystemUI* systemUI = SystemUI::create();
	this->addChild(systemUI,0,"SystemUI");

	// 结算面板
	panel = AccountPanel::create();
	panel->setLocalZOrder(10);
	this->addChild(panel);

	// 动画
	MahjongAnim::updateInstance();
	auto anim = MahjongAnim::getInstance();
	anim->setLocalZOrder(11);
	if (nullptr != anim->getParent())
	{
		anim->removeFromParent();
	}
	CCLOG("+++++++++++++++++ debug addAnim To1 GameFlow");
	this->addChild(anim);
	CCLOG("+++++++++++++++++ debug addAnim To2 GameFlow");

	MahjongAnim::getInstance()->playSound(SOUND::BGM);

	
	
	PayEventMannger::getInstance()->RecordInfoOnGamestart();
	/*if (PayEventMannger::getInstance()->getGamecount()==1)
	{
	Director::getInstance()->getEventDispatcher()->addCustomEventListener("setname", [=](EventCustom*event)
	{
	players[0]->updateName();
	Director::getInstance()->getEventDispatcher()->removeCustomEventListeners("setname");
	});
	auto setname = SetNameLayer::create();
	setname->setPosition(0, 0);
	addChild(setname);
	}
	else
	{
	if (PayEventMannger::getInstance()->isSatisfied_Event_9())
	{
	PxPayMannger::getInstance()->LaughPayLayer(9, this);
	}
	}*/
	/*panel->setVisible(true);
	panel->showAccountInfo(1, 1);*/
	return true;
}

void GameFlow::onEnter() 
{
	CCLOG("GameFlow : onEnter");
	Node::onEnter();
	addGameFlowEvent();
}

void GameFlow::onExit()
{
	Node::onExit();	

	//_eventDispatcher->resumeEventListenersForTarget(this, true);
	removeMahjongListener(DEALCARDS);

	removeMahjongListener(OPERA_PICK_END);
	removeMahjongListener(OPERA_PLAY_END);
	removeMahjongListener(OPERA_PENGGANG_END);
	removeMahjongListener(QI_RETURN_BEFORE);
	removeMahjongListener(QI_QIANGGANG_BEFORE);
	removeMahjongListener(DELETE_TABLE_BEFORE);

	removeMahjongListener(OPERA_ZIMO_END);
	removeMahjongListener(OPERA_DIANPAO_END);
	removeMahjongListener(	OPERA_DIAMPAO_ENDALL);
	removeMahjongListener(OPERA_QIANGGANG_END);
	removeMahjongListener(OPERA_QIANGGANG_ENDALL);
	removeMahjongListener(GAME_OVER);

	removeMahjongListener(Refresh_Coin);
}
Vec2 rangecoin[3] = { Vec2(50000,300000), Vec2(300000,1000000), Vec2(1000000,5000000) };
void GameFlow::initPlayers()
{
	CCLOG("");
	CCLOG("GameFlow : init Players");
	//Vec2(*cardHandPos)[5] = getHandCardPos();
	auto room = Room::getInstance();

	// 如果主角是重新进游戏
	if (0 == room->getCoins(0))
	{
		int mainCoin = User::getInstance()->getMyCoins();

		
		room->updateCoins(0, mainCoin);
		
	}
	int roomID = Room::getInstance()->getRoomType();
	if (roomID != ROOM_QINGYISE)
	{
		
	}
	else
	{
		auto user = User::getInstance();
		int myCoin = user->getMyCoins();
		if (300000 > myCoin)
		{
			roomID = 0;
		}
		else if (300000 <= myCoin && myCoin < 1000000)
		{
			roomID = 1;
		}
		else if (1000000 <= myCoin)
		{
			roomID = 2;
		}
	}

	for (int i = 1; i < 4; i++)
	{
		int newCoins = random<int>(rangecoin[roomID].x, rangecoin[roomID].y);
		newCoins = newCoins / 100 * 100;
		room->updateCoins(i, newCoins);
	}
	//room->addFreeCoins();

	for (int i = 0; i < 4; i++)
	{
		players[i] = NULL;
		players[i] = Player::createPlayer((PLAYER)i);
		
		this->addChild(players[i],1);
		//players[i]->drawer->cardPos = cardHandPos[i];
		//players[i]->drawer->cardPos = getHandCardPs(i);	//两种方法
	}

	players[PLAYER_0]->set_isPlayer(true);
	Player::playMenu = initMenu();
	Player::playMenu->getPlayer(players[PLAYER_0]);
}
PlayMenu* GameFlow::initMenu()
{	
	CCLOG("");
	CCLOG("GameFlow : initMenu");
	PlayMenu* playMenu = PlayMenu::create();
	this->addChild(playMenu,10,"PlayMenu");
	return playMenu;
}
void GameFlow::addGameFlowEvent()
{
	CCLOG("GameFlow : addGameFlowEvent");
	addMahjongListener(FLOW_NAME::DEALCARDS, 
		CC_CALLBACK_1(GameFlow::onDealCardsBegin, this));

	addMahjongListener(FLOW_NAME::OPERA_PLAY_END, 
		CC_CALLBACK_1(GameFlow::onOperaPlayEnd, this) );
	addMahjongListener(FLOW_NAME::OPERA_PENGGANG_END,
		CC_CALLBACK_1(GameFlow::onOperaPengGangEnd, this));
	addMahjongListener(FLOW_NAME::QI_RETURN_BEFORE,
		CC_CALLBACK_1(GameFlow::returnBefore, this)); 
	addMahjongListener(FLOW_NAME::QI_QIANGGANG_BEFORE,
		CC_CALLBACK_1(GameFlow::returnPengGang, this));
	addMahjongListener(FLOW_NAME::DELETE_TABLE_BEFORE,
		CC_CALLBACK_1(GameFlow::deleteTableBefore, this));

	addMahjongListener(FLOW_NAME::Refresh_Coin,
		[=](EventCustom*event){
		for (int i = 0; i < 4;i++)
		{
			players[i]->updateCoin();
		}
		 });
	

	addMahjongListener(FLOW_NAME::OPERA_ZIMO_END,
		CC_CALLBACK_1(GameFlow::onOperaZiMoEnd, this));

	addMahjongListener(FLOW_NAME::OPERA_DIANPAO_END,
		CC_CALLBACK_1(Rules::subCanHuNumToNull, pRules));
	addMahjongListener(FLOW_NAME::OPERA_DIAMPAO_ENDALL,
		CC_CALLBACK_1(GameFlow::onOperaDianPaoEnd, this));

	addMahjongListener(FLOW_NAME::OPERA_QIANGGANG_END,
		CC_CALLBACK_1(Rules::subCanQiangNumToNull, pRules));
	addMahjongListener(FLOW_NAME::OPERA_QIANGGANG_ENDALL
		,CC_CALLBACK_1(GameFlow::onOperaQiangGangEnd, this));

	addMahjongListener(FLOW_NAME::GAME_OVER, 
		CC_CALLBACK_1(GameFlow::onGameOver, this));

	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("refreshCoin");
}

//-------------------------------------------- 发牌 ----------------------------------------------
void GameFlow::onDealCardsBegin(EventCustom* event)
{



	auto systemUI = (SystemUI*)(getChildByName("SystemUI"));
	systemUI->hideAddCoin();
	
	
	auto room = Room::getInstance();
	Player::playMenu->getInfo(room->getRoomScore(), room->getRoomTimes(0));
	CCLOG("GameFlow : onDealCardsBegin");
	CCLOG("");
	currentPlayer = pRules->get_zhuangPlayer();
	// 每隔0.2s发一张牌，发17张
	MahjongAnim::getInstance()->playDealShaiZi();

	for (Player* player : players)
	{
		player->drawer->setVisible(true);
		player->set_multiple(Room::getInstance()->getRoomTimes(player->drawer->get_dir()));
		player->setTimes();
	}

	MahjongDatas::getInstance()->reviewAllCards();
	tmepIndex = 0;
	schedule(schedule_selector(GameFlow::dealACard), 0.2f, 15, 1.5f);
	schedule(schedule_selector(GameFlow::startGame), 7.0f, 0, 7.0f);
}

void GameFlow::dealACard(float dt)
{	
	CCLOG("GameFlow : dealACard");
	MahjongAnim::getInstance()->playSound(PICKCARD);
	auto card = players[currentPlayer]->operaPick();
	//if (++tmepIndex == 16)
	//{
	//	card->runAction(MoveBy::create(0.1f, MahjongDrawer::cardPickDis[currentPlayer]));
	//}
	playerPlusPlus(currentPlayer);
}

void GameFlow::startGame(float dt)
{
	CCLOG("");
	CCLOG("GameFlow : startGame");
	auto systemUI = (SystemUI*)(getChildByName("SystemUI"));
	
	systemUI->showFirstPlayTip();
	for (Player* player : players)
	{
		player->drawer->setVisible(true);
	}

	addMahjongListener(OPERA_PICK_END, CC_CALLBACK_1(GameFlow::onOperaPickEnd, this));
	currentPlayer = pRules->get_zhuangPlayer();
	players[currentPlayer]->set_isZhuang(true);
	for (int i = 0; i < 4; i++)
	{
		players[i]->initLogo();
	
	}
	players[currentPlayer]->turnOnLight();
	sortCardForAll();

	CCLOG("");
	//// 发牌之后，游戏开始，进行庄家的摸牌判断	
	//dispatchMahjongEvent(OPERA_PICK_END, NULL);
	runAction(Sequence::create(DelayTime::create(0.5f), CallFunc::create([=]{
		auto card = players[currentPlayer]->operaPick();
	/*	if (currentPlayer==0)
		{
			card->showPoint();
		}
	*/
		card->runAction(MoveBy::create(0.1f, MahjongDrawer::cardPickDis[currentPlayer]));
		card->setLocalZOrder(1 == players[currentPlayer]->drawer->get_dir() ? -10 : 10);
	}), nullptr));

}
//------------------------------------------- 摸牌后 ----------------------------------------------
void GameFlow::onOperaPickEnd(EventCustom* event)
{
	CCLOG("---------------------------------------------------------------");
	CCLOG("-------------------GameFlow : Player[%d]PickEnd-------------------", currentPlayer);
	CCLOG("---------------------------------------------------------------");
	auto result = pRules->testAfterOnePick(*this);

	if (currentPlayer == 0)
	{
		static bool isShowRedPack = false;
		if (!isShowRedPack)
		{
			int num = rand() %4;
			if (num==0)
			{
				showReadPack();
				isShowRedPack = true;
			}
		}
	}

	if (PICK_ZIMO != result)
	{
		players[currentPlayer]->set_GangKai(false);
	}

	switch (result)
	{
	case PICK_ZIMO:
		players[currentPlayer]->operaZiMo();
		break;
	case PICK_ANGANG:
		players[currentPlayer]->operaAnGang();
		break;
	case PICK_PENGGANG:
		players[currentPlayer]->operaPengGang();
		break;
	case PICK_NEXT:
		players[currentPlayer]->operaPlay();
		break;
	case PICK_LIUJU:
		Audio::getInstance()->playSoundLiuJu(Room::getInstance()->getPlayerHead(0));
		showAccount(true);
		break;
	default:
		break;
	}
}

void GameFlow::onOperaZiMoEnd(EventCustom* event)
{
	if (ZIMO == players[currentPlayer]->get_Result())
	{
		PLAYER losePlayer = currentPlayer;
		for (int i = 0; i < 3; i++)
		{
			playerPlusPlus(losePlayer);
			players[losePlayer]->set_Result(LOSE);
		}
		if (players[currentPlayer]->get_GangKai())
		{
			dispatchMahjongEvent(GAME_OVER, (void*)2);
		}
		else
		{
			dispatchMahjongEvent(GAME_OVER, (void*)0);
		}
	}
	else
	{
		players[currentPlayer]->operaPlay();
	}
}
//------------------------------------------- 碰杠后 ---------------------------------------------------
void GameFlow::onOperaPengGangEnd(EventCustom* event)
{
	CCLOG("------------------GameFlow : Player[%d]PengGangEnd------------------", currentPlayer);
	if (pRules->testAfterOneGang(*this))
	{
		// 有人抢杠
		OperaWhenCanQiangGang();
	}
	else
	{
		// 没人抢杠
		MahjongAnim::getInstance()->logScreen("CantQG : ", -1);

		players[currentPlayer]->goOnOperaPick();
	}
}

void GameFlow::OperaWhenCanQiangGang()
{
	MahjongAnim::getInstance()->logScreen("RunQG : ", -1);

	beforePlayer = currentPlayer;

	CCLOG("GameFlow : OperaWhenCanQiangGang");

	for (int i = 0; i < 4; i++)
	{
		if (players[i]->get_canHu())
		{
			currentPlayer = (PLAYER)i;
			CCLOG("Player %d : canQiangGang", i);
			players[currentPlayer]->operaQiangGang();
		}
	}
}

void GameFlow::onOperaQiangGangEnd(EventCustom* event)
{
	CCLOG("GameFlow : onAllQiangGangOperaEnd");
	for (Player* player : players)
	{
		if (HU == player->get_Result())
		{
			pRules->set_isQiangGang(true);
			players[beforePlayer]->set_Result(DIANPAO);
			Card* card = Rules::getInstance()->get_currentCard();
		/*	player->drawer->cardInHand.push_back(card);*/
			player->drawer->sortData();
			CCLOG("Win : %d ----------- Lose : %d", player->drawer->get_dir(), beforePlayer);
			set_isGameOver(true);
			break;
		}
	}

	if (isGameOver)
	{
		dispatchMahjongEvent(GAME_OVER, (void*)2);
	}
	else
	{
		pRules->set_isQiangGang(false);
		dispatchMahjongEvent(QI_QIANGGANG_BEFORE, NULL);
	}
}
//------------------------------------------- 打牌后 ---------------------------------------------------
void GameFlow::onOperaPlayEnd(EventCustom* event)
{
	CCLOG("---------------------------------------------------------------");
	CCLOG("------------------GameFlow : Player[%d]PlayEnd------------------", currentPlayer);
	CCLOG("---------------------------------------------------------------");

	players[currentPlayer]->drawer->sortCard(true);

	PLAY_RESULT result = pRules->testAfterOnePlayed(*this);

	switch (result)
	{
	case PLAY_DIANPAO:
		OperaWhenCanDianPaoHu();
		break;

	case PLAY_PENG:
		CCLOG("Result : Peng");
		beforePlayer = currentPlayer;
		currentPlayer = pRules->get_pengPlayer();
		pRules->set_pengPlayer(PLAYER::PLAYER_NULL);
		players[currentPlayer]->operaPeng();
		break;

	case PLAY_GANG:
		beforePlayer = currentPlayer;
		currentPlayer = pRules->get_gangPlayer();
		pRules->set_gangPlayer(PLAYER_NULL);
		players[currentPlayer]->operaGang();
		break;

	case PLAY_NEXT:
		turnToNext();
		break;

	default:
		CCLOG("======== Rules : TestAfterOnePlayed : Wrong");
		break;
	}
}
void GameFlow::deleteTableBefore(EventCustom* event)
{
	players[beforePlayer]->drawer->remove1CardInTable();
}



void GameFlow::OperaWhenCanDianPaoHu()
{
	beforePlayer = currentPlayer;

	CCLOG("GameFlow : OperaWhenCanDianPaoHu");

	for (int i = 0; i < 4; i++)
	{
		if (players[i]->get_canHu())
		{
			currentPlayer = (PLAYER)i;
			CCLOG("Player %d : canDianPao", i);
			players[i]->operaDianPao();
		}
	}
}

Vec2 dianpaoPos[4] = {
	Vec2(340, 180),
	Vec2(490, 220),
	Vec2(455, 350),
	Vec2(300, 310),
};
Vec2 HuPos[4] = {
	Vec2(410, 50),
	Vec2(674, 244),
	Vec2(408, 433),
	Vec2(115, 311),
};
void GameFlow::onOperaDianPaoEnd(EventCustom* event)
{
	CCLOG("GameFlow : onAllHuOperaEnd");
	
	for (Player* player : players)
	{
		if (HU == player->get_Result())
		{
			Audio::getInstance()->playSoundHu(0, Room::getInstance()->getPlayerHead(player->drawer->get_dir()));
			players[beforePlayer]->set_Result(DIANPAO);
		
			CCLOG("Win : %d ----------- Lose : %d", player->drawer->get_dir(), beforePlayer);
			set_isGameOver(true);

			auto currentCard = Rules::getInstance()->get_currentCard();
			int dianpaotype = currentCard->get_type();
			int dianpaodir = currentCard->get_dir();
			int hudir = player->drawer->get_dir();
			auto anicard = Card::createTableCard(PLAYER_0, dianpaotype);
			anicard->setPosition(dianpaoPos[dianpaodir]);
			anicard->setVisible(false);
			anicard->setScale(0.8f);
			addChild(anicard, 10);
			auto ani = Sprite::create("MJAnim/thunder/ani_thunder_1.png");
			ani->setPosition(anicard->getPosition());
			ani->setScale(2.0f);
			ani->setOpacity(0);
			addChild(ani, 10);
			ani->runAction(
				Sequence::create(
				Spawn::createWithTwoActions(
				ScaleTo::create(0.2f, 1.0f), FadeIn::create(0.2f)),
				Spawn::create(AnimationUtil::getInstance()->getAnimate("ani_thunder"), nullptr),
				CallFunc::create([=]{anicard->setVisible(true), anicard->runAction(Sequence::create(DelayTime::create(0.2f), MoveTo::create(0.5f, HuPos[hudir]), CallFunc::create([=]{
				Card* card = Rules::getInstance()->get_currentCard();
				player->drawer->cardInHand.push_back(card);
				player->drawer->sortData();
				card->setVisible(false);
			}), RemoveSelf::create(1), nullptr)); }),
				RemoveSelf::create(true), nullptr));
		}
	}
	if (isGameOver)
	{
		dispatchMahjongEvent(GAME_OVER, (void*)1);
	}
	else
	{
		pRules->set_isDianPao(false);
		dispatchMahjongEvent(QI_RETURN_BEFORE, NULL);
	}
}

// 
void GameFlow::returnPengGang(EventCustom* event)
{
	currentPlayer = beforePlayer;
	players[currentPlayer]->goOnOperaPick();
}

void GameFlow::returnBefore(EventCustom* event)
{
	CCLOG("");
	CCLOG("GameFlow : onNext");
	currentPlayer = beforePlayer;

	if (PLAYER_NULL != pRules->get_pengPlayer())
	{
		CCLOG("return DianPao and : Peng");
		beforePlayer = currentPlayer;
		currentPlayer = pRules->get_pengPlayer();
		pRules->set_pengPlayer(PLAYER::PLAYER_NULL);
		players[currentPlayer]->operaPeng();
		return;
	}

	if (PLAYER_NULL != pRules->get_gangPlayer())
	{
		beforePlayer = currentPlayer;
		currentPlayer = pRules->get_gangPlayer();
		pRules->set_gangPlayer(PLAYER_NULL);
		players[currentPlayer]->operaGang();
		return;
	}

	turnToNext();
}
void GameFlow::turnToNext()
{
	CCLOG("GameFlow : turnToNext");
	currentPlayer = (PLAYER)((currentPlayer+1)%4);
	beforePlayer = currentPlayer;
	auto card = players[currentPlayer]->operaPick();
	card->runAction(MoveBy::create(0.1f, MahjongDrawer::cardPickDis[currentPlayer]));
	card->setLocalZOrder( 1 == players[currentPlayer]->drawer->get_dir() ? -10 : 10 );
	//if (currentPlayer==0)
	//{
	//	card->showPoint();
	//}
}
//------------------------------------------ 胜负已分 -------------------------------------------------------------
void GameFlow::onGameOver(EventCustom* event)
{
	CCLOG("---------------------------------------------------------------");
	CCLOG("------------------GameFlow : onGameOver---------------");
	CCLOG("---------------------------------------------------------------");
	
	pRules->zhuaNiaoData(this);
	pRules->accountFanshu(*this);

	int count = User::getInstance()->getgamecount();
	User::getInstance()->setgamecount(++count);
	Jniutill::getInstance()->logEvent("游戏_盘数_" + Value(count).asString(), Value(User::getInstance()->getMyCoins()).asString());

	auto result = (int)event->getUserData();
	if (0 == result)
	{
		scheduleOnce([this](float dt){ MahjongAnim::getInstance()->playAccountZiMoAnim(); }, 1.0f, "Acc_zimo");
	}
	else if (1 == result)
	{
		scheduleOnce([this](float dt){ MahjongAnim::getInstance()->playAccountHuAnim(*this); }, 1.0f, "Acc_hu");
	}
	else
	{
		scheduleOnce([this](float dt){ MahjongAnim::getInstance()->playAccountGangKaiAnim(); }, 1.0f, "Acc_gangkai");
	}

	int maxId = 0;
	int maxScore = 0;
	for (int index = 0; index < 4; index++)
	{
		if ((players[index]->get_Result()==ZIMO)||(players[index]->get_Result())==HU)
		{
			maxId = index;
		}
	}

	scheduleOnce([this, maxId](float dt){ panel->showBigAccountInfo(*players[maxId]); players[maxId]->showCards(); }, 1.6f, "showBigWord");
	
	auto node = getChildByName("Btn_RedPack");
	if (node)
	{
		node->removeFromParentAndCleanup(true);

	}
	//scheduleOnce([=](float dt){ 	
	//	auto readpack = RedpackPanel::create();
	//	readpack->setPrice(Room::getInstance()->getRoomScore());
	//	readpack->setPosition(0, 0);
	//	addChild(readpack, 50); 
	//}, 4.0f, "readpack");

	//Director::getInstance()->getEventDispatcher()->addCustomEventListener("RedPackOver",[=](EventCustom*event)
	//{
	//	Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(event->getEventName());
	//	pRules->zhuaNiao(this);
	//
	//	scheduleOnce([this](float dt){showAccount(false); }, 10.0f, "showAccount");
	//});
	scheduleOnce([this](float dt){pRules->zhuaNiao(this); }, 3.0f, "zhuaniao");
	

	scheduleOnce([this](float dt){showAccount(false); }, 10.0f, "showAccount");

	DBManager::GetInstance()->AddDayGameTimes();


	
}

void GameFlow::showAccount(bool isLiuJu)
{
	CCLOG("");
	CCLOG("------------------GameFlow : showAccount---------------");
	int beishu;
	int niaoNum = 0;//计算中鸟分

	RESULT result = DIANPAO;
	for (int i = 0; i < 4;i++)
	{
		if (players[i]->get_Result()==ZIMO)
		{
			result = ZIMO;
		}
		CCLOG("play[%d] zhuaniao:%d", i, players[i]->get_NiaoNum());

		if (players[i]->get_Result() == ZIMO||players[i]->get_Result()==HU)
		{
			beishu = Room::getInstance()->getRoomTimes(i);
		}
	}
	if (result == ZIMO)
	{
		for (int i = 0; i < 4;i++)
		{
			if (players[i]->get_Result()==ZIMO)
			{
				niaoNum += players[i]->get_NiaoNum()*3;
			}
			else
			{
				niaoNum += players[i]->get_NiaoNum();
			}
		}
	}
	else
	{
		for (int i = 0; i < 4;i++)
		{
			if (players[i]->get_Result() == HU||players[i]->get_Result()==DIANPAO)
			{
				niaoNum += players[i]->get_NiaoNum();
			}
		}
	}


	for (int index = 0; index < 4; index++)
	{
		panel->getInfoFromPlayer(*players[index]);
	
	}

	panel->setVisible(true);
	
	for (int i = 0; i < 4;i++)
	{
		if (players[i]->get_Result() == HU||players[i]->get_Result()==ZIMO)
		{
			niaoNum = players[i]->get_ZhongNiaoFen();
			break;
		}
	}

	if (isLiuJu)
	{
		beishu = -1;
	}

	panel->showAccountInfo(niaoNum,beishu);




	bool iswin = (players[0]->get_Result() >= 1 && players[0]->get_Result() <= 3);
	bool isUseGood = players[0]->get_isPickGood();
	panel->showPayPoint(isUseGood, iswin);
	CCLOG("Update RoomId");
}
//------------------------------------------ 支持函数 -------------------------------------------
void GameFlow::sortCardForAll()
{
	CCLOG("GameFlow : sortCardFowAll");
	for (Player* player : players)
	{
		player->drawer->sortCard();
	}
}

void GameFlow::showReadPack()
{
	auto node = getChildByName("Btn_RedPack");
	if (node)
	{
		return;
	}
	auto bt = ReadpackNode::create();
	addChild(bt, 10,"Btn_RedPack");

	struct packRoute 
	{
		Vec2 startpos;
		Vec2 endpos;
	} route[2];

	route[1].startpos = Vec2(850, 450);
	route[1].endpos = Vec2(-70, 100);

	route[0].startpos = Vec2(-50, 430);
	route[0].endpos = Vec2(860, 40);
	int num = rand() % 2;
	bt->setPosition(route[num].startpos);
	bt->runAction(Sequence::create(MoveTo::create(6.0f,route[num].endpos),RemoveSelf::create(1),nullptr));
}