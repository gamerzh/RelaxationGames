#include "Rules.h"
#include "Card.h"
#include "MahjongDatas.h"
#include "Room.h"
#include "MahjongAnim.h"
#include "AnimationUtil.h"
Rules* Rules::instance = nullptr;

Rules::Rules()
{
	CCLOG("Rules : init");
}

bool Rules::init(RuleType type)
{
	static bool isFirstComing = false;
	set_pengPlayer(PLAYER_NULL);
	set_gangPlayer(PLAYER_NULL);
	if (!isFirstComing)
	{
		set_zhuangPlayer(PLAYER_0);
		isFirstComing = true;
	}

	set_currentCard(nullptr);
	set_isGameOver(false);
	set_isDianPao(false);
	set_isQiangGang(false);
	_ruleType = type;
	_niaoData.clear();
	return true;
}

//------------------------------------------- 总判断一 --------------------------------------------

// 在一个玩家摸牌之后的判断		1，自己是否可以胡， 2，自己是否可以杠， 3，是否流局
PICK_RESULT Rules::testAfterOnePick(GameFlow & gameFlow)
{
	auto result = testAfterPlayerPick(*(gameFlow.players[gameFlow.currentPlayer]->drawer));
	return result;
}
PICK_RESULT Rules::testAfterPlayerPick(MahjongDrawer & drawer)
{
	if (4 == MahjongDatas::getInstance()->getCardNum())
	{
		return PICK_LIUJU;
	}
	if (2 == drawer.cardInHand.size())
	{
		if (drawer[0] == drawer[1])
		{
			return PICK_ZIMO;
		}

		if (drawer.cardInSide.size() == 3)
		{
			int side = drawer.cardInSide.at(0)->get_type();
			if (drawer[0] == side || drawer[1] == side)
			{
				return PICK_PENGGANG;
			}
		}

		return PICK_NEXT;
	}
	else
	{
		if (testCanAnGang(drawer))		// 如果可以暗杠，则肯定是不能胡的。
		{
			return PICK_ANGANG;
		}
		else
		{
			return testCanHu5(drawer) ? PICK_ZIMO : PICK_NEXT;
		}   
	}
}
bool Rules::testCanAnGang(MahjongDrawer & drawer)
{
	int t = drawer[2];
	int diff = 0;
	for (int i = 0; i < 5; i++)
	{
		if (drawer[i] != t)
		{
			if ((++diff) == 2) return false;
		}
	}
	return true;
}
bool Rules::testIfHu(int card[5])
{
	bool isCanhu = false;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (i == j)
			{
				continue;;
			}
			if (card[i] == card[j])
			{
				int other[3];
				int m = 0;
				for (int k = 0; k < 5; k++)
				{
					if (k != i&&k != j)
					{
						other[m++] = card[k];
					}
				}
				isCanhu = isThreeSame(other[0], other[1], other[2]) || isThreeBehind(other[0], other[1], other[2]);
				if (isCanhu)
				{
					return isCanhu;
				}
			}
		}
	}
	return isCanhu;
}

bool Rules::testCanHu5(MahjongDrawer & drawer)
{
 	bool isQingyise = testSameType(drawer);

	int card[5];
	for (int i = 0; i < 5;i++)
	{
		card[i] = drawer[i];
	}
	bool isCanhu = testIfHu(card);

	if (_ruleType == Rule_QingYiSe)
	{
		return isCanhu&&isQingyise;
	}
	else
	{
		return isCanhu;
	}
}

//------------------------------------------- 总判断二 --------------------------------------------

// 在一个玩家打牌之后的判断		1，其他所有人是否可以胡，其他某个人是否可以碰
PLAY_RESULT Rules::testAfterOnePlayed(GameFlow & gameFlow)
{
	// 此处有ｂｕｇ，在同时有人碰和胡的时候，会直接碰，而屏蔽胡。
	//CCLOG("Rules : testAfterOnePlayed");

	PLAYER playerIndex = gameFlow.currentPlayer;
	PLAY_RESULT result;
	for (int i = 0; i < 3; i++)
	{
		playerPlusPlus(playerIndex);
		result = testAfterPlayerPlayed(*(gameFlow.players[playerIndex]->drawer));
		switch (result)
		{
		case PLAY_PENG:
			set_pengPlayer(playerIndex);
			//return PLAY_PENG;
			break;
		case PLAY_GANG:
			set_gangPlayer(playerIndex);
			//return PLAY_GANG;
			break;
		case PLAY_DIANPAO:
			gameFlow.players[playerIndex]->set_canHu(true);
			canHuNum++; 
			break;
		case PLAY_NEXT:
			continue;
			break;
		default:
			break;
		}
	}
	if (0 < canHuNum)
	{
		set_isDianPao(true);
		return PLAY_DIANPAO;
	}
	else
	{
		if (PLAYER_NULL != get_gangPlayer())
		{
			set_pengPlayer(PLAYER_NULL);
			return PLAY_GANG;
		}
		if (PLAYER_NULL != get_pengPlayer())
		{
			return PLAY_PENG;
		}
	}
	return PLAY_NEXT;
}

bool Rules::testAfterPlayerGang(MahjongDrawer & drawer)
{
	MahjongAnim::getInstance()->logScreen("testPGplayer : ", drawer.get_dir());

	int playedCard = currentCard->get_type();

	if (1 == drawer.cardInHand.size())
	{
		if (testCanHu1(drawer, playedCard))
		{
			return true;
		}
	}
	else
	{
		if (testCanHu4(drawer, playedCard))
		{
			return true;
		}
	}
	return false;
}

bool Rules::testAfterOneGang(GameFlow & gameFlow)
{
	MahjongAnim::getInstance()->logScreen("testQG : ", 0);

	PLAYER playerIndex = gameFlow.currentPlayer;
	bool result;
	for (int i = 0; i < 3; i++)
	{
		playerPlusPlus(playerIndex);
		result = testAfterPlayerGang(*(gameFlow.players[playerIndex]->drawer));
		if (result)
		{
			gameFlow.players[playerIndex]->set_canHu(true);
			canHuNum++;
		}
	}
	if (0 < canHuNum)
	{
		bool isQiangGang = true;
		return true;
	}
	return false;
}
PLAY_RESULT Rules::testAfterPlayerPlayed(MahjongDrawer & drawer)
{
	int playedCard = currentCard->get_type();

	if (1 == drawer.cardInHand.size())
	{
			if (testCanHu1(drawer, playedCard))
			{
			return PLAY_DIANPAO;
			}
	}
	else
	{
		if (testCanGang4(drawer, playedCard))
		{
			return PLAY_GANG;
		}
		if (testCanHu4(drawer, playedCard))
		{
			return PLAY_DIANPAO;
		}
		if (testCanPeng4(drawer, playedCard))
		{
			return PLAY_PENG;
		}
	}
	return PLAY_NEXT;
}
bool Rules::testCanHu(MahjongDrawer & drawer, const int playedCard)
{
	if (1 == drawer.cardInHand.size())
	{
		if (testCanHu1(drawer, playedCard))
		{
			return true;
		}
	}
	else
	{
		if (testCanHu4(drawer, playedCard))
		{
			return true;
		}
	}
	return false;
}
bool Rules::testCanHu1(MahjongDrawer & drawer, const int playedCard)
{
	MahjongAnim::getInstance()->logScreen("testHu1player : ", drawer.get_dir());

	int sign1 = getSignByInteger(drawer[0]);
	int sign2 = getSignByInteger(playedCard);
	int sign3 = getSignByInteger(drawer.cardInSide.at(0)->get_type());
	bool isQingYiSe = isThreeSame(sign1,sign2,sign3); 
	bool iscanhu = false;
	if (1 != drawer.cardInHand.size() || playedCard != drawer[0])
	{ 
		iscanhu = false;
	}
	else
	{
		iscanhu = true;
	}
	if (_ruleType == Rule_QingYiSe)
	{
		return iscanhu&&isQingYiSe;
	}
	else
	{
		return iscanhu;
	}
}
bool Rules::testCanGang1(MahjongDrawer & drawer, int playedCard)
{
	if (0 != drawer.cardInSide.size())
	{
		if (drawer.cardInSide.at(0)->get_type() == playedCard)
		{
			return true;
		}
	}
	return false;
}
bool Rules::testCanHu4(MahjongDrawer & drawer, const int playedCard)
{
	MahjongAnim::getInstance()->logScreen("testHu4player : ", drawer.get_dir());

	//清一色条件：判断第一张牌和最后张牌以及打的牌是否花色一致
	int sign1 = getSignByInteger(drawer[0]);
	int sign2 = getSignByInteger(playedCard);
	int sign3 = getSignByInteger(drawer[drawer.cardInHand.size()-1]);
	bool isQingYiSe = isThreeSame(sign1, sign2, sign3);

	int card[5];
	for (int i = 0; i < 4; i++)
	{
		card[i] = drawer[i];
	}
	card[4] = playedCard;
	bool iscanhu = testIfHu(card);

	if (_ruleType == Rule_QingYiSe)
	{
		return iscanhu&&isQingYiSe;
	}
	else
	{
		return iscanhu;
	}
}
bool Rules::testCanGang4(MahjongDrawer & drawer, int playedCard)
{
	if (4 != drawer.cardInHand.size())
	{
		return false;
	}
	int diff = 0;
	for (int i = 0; i < 4; i++)
	{
		if (drawer[i] != playedCard)
		{
			if ((++diff) == 2) return false;
		}
	}
	return true;
}
bool Rules::testCanPeng4(MahjongDrawer & drawer, const int playedCard)
{
	if (4 != drawer.cardInHand.size())
	{
		return false;
	}
	int diff = 0;
	for (int i = 0; i < 4; i++)
	{
		if (drawer[i] != playedCard)
		{
			if ((++diff) == 3) return false;
		}
	}
	return true;
}

//------------------------------------------  胡牌  ---------------------------------------------
void Rules::subCanHuNumToNull(EventCustom* event)
{
	CCLOG("Rules    : subCanHuNumToNull");

	canHuNum--;
	
	if (0 == canHuNum)	// 如果所有人都选择完毕是否胡，Play结束。
	{
		dispatchMahjongEvent(OPERA_DIAMPAO_ENDALL, NULL);
	}
}

void Rules::subCanQiangNumToNull(EventCustom* event)
{
	canHuNum--;
	if (0 == canHuNum)
	{
		dispatchMahjongEvent(OPERA_QIANGGANG_ENDALL, NULL);
	}
}
void Rules::zhuaNiaoData(GameFlow* gameFlow)
{
	// 得到鸟数据
	for (int i = 0; i < 4;i++)
	{
		int type = MahjongDatas::getInstance()->popACard();
		if (0 > type)
		{
			type += 10;
		}
		int playerIndex = (type - 1 + zhuangPlayer) % 4;
		int cardIndex = gameFlow->players[playerIndex]->addNiaoNum();
		NiaoData data;
		data.dir = playerIndex;
		data.niaoType = type;
		data.posindex = cardIndex;
		_niaoData.push_back(data);
	}
	
}
//------------------------------------------  结算  ---------------------------------------------
void Rules::zhuaNiao(GameFlow * gameFlow)
{
	Node* sideCards = Node::create();
	sideCards->setPosition(0, 0);
	gameFlow->addChild(sideCards, 8, "sideCards");
	CCLOG("Rules    : zhuaNiao");
	auto ani = AnimationUtil::getInstance()->getAnimate("ani_zhuaniao");
	auto dt = ani->getDuration();
	auto sp = Sprite::create();
	sp->runAction(Sequence::create(DelayTime::create(dt), ani, CallFunc::create([=]{
		for (auto child:sideCards->getChildren())
		{
			child->runAction(ScaleTo::create(0.05f, 1.0f));
		}
	}),RemoveSelf::create(1), nullptr));
	gameFlow->addChild(sp, 10);
	sp->setPosition(400, 368);

	for (int i = 0; i < 4;i++)
	{
		auto sideCard = Card::createSideCard(PLAYER_0, DOWN, 1);
		sideCard->setPosition(400.0f-60+i*40, 272.0f);
		sideCard->setScale(0.0f);
		sideCards->addChild(sideCard, 10,i);
	}
	for (int i = 0; i < 4; i++)
	{
		// 得到鸟数据
		int type = _niaoData[i].niaoType;
		int playerIndex = _niaoData[i].dir;
		int cardIndex = _niaoData[i].posindex;
		
		// 得到鸟图案
		Card* cardNiao = Card::createTableCard(PLAYER_0,type);
		cardNiao->setLocalZOrder(9);
		// 鸟画到屏幕
		cardNiao->setPosition(400.0f -60 + i * 40, 272.0f);
		string str = String::createWithFormat("niao%d", i)->_string;
		gameFlow->addChild(cardNiao, 9, str);
		cardNiao->setVisible(false);

		auto node = Node::create();
		gameFlow->addChild(node);
		Vec2 pos = gameFlow->players[playerIndex]->getChildByName("Head")->getPosition();
		if (playerIndex != 2)
		{
			pos.x = pos.x - 50 + cardIndex * 30.0f * 1.0f;
		}
		else
		{
			pos.x = pos.x - 50 + cardIndex * 30.0f * 1.0f;
			pos.y = pos.y - 118;
		}
		

		node->scheduleOnce([i, pos, gameFlow](float dt){
			// 鸟飞向玩家头像的动画
			string strNiao = String::createWithFormat("niao%d", i)->_string;
			auto ani2 = AnimationUtil::getInstance()->getAnimate("ani_MJfanzhuan");
			auto dt2 = ani2->getDuration();
			auto niao = ((Card*)(gameFlow->getChildByName(strNiao)));

			auto sp2 = Sprite::create();
			sp2->setPosition(niao->getPosition());
			gameFlow->addChild(sp2, niao->getLocalZOrder());
			sp2->runAction(Sequence::create(DelayTime::create((i + 0.5) * (0.5f + dt2+0.3f)), CallFunc::create([=]{gameFlow->getChildByName("sideCards")->getChildByTag(i)->removeFromParentAndCleanup(1); }), ani2, CallFunc::create([=]{


				niao->setVisible(true);
				niao->setCascadeOpacityEnabled(true);
				niao->runAction(Sequence::create(DelayTime::create(0.3f),
					MoveTo::create(0.5f, Vec2(pos.x, pos.y + 50)),
					NULL));
			}),RemoveSelf::create(1),nullptr));
		}, dt+0.5f , str);
	}
}

void Rules::accountFanshu(GameFlow & gameFlow)
{
	CCLOG("Rules    : accountFanshu");
	/*
		分数：便利四个玩家，分数 = 番数 * 底分，
		*/
	vector<Player*> playersWin;
	vector<Player*> playersLose;
	maxNiaoNum = 0;
	for (Player* player : gameFlow.players)
	{
		if (RESULT::HU == player->get_Result() || RESULT::ZIMO == player->get_Result())
		{
			player->set_QingYiSe(testSameType(*(player->drawer)));
			player->set_PengPengHu(testIfPengPengHu(*(player->drawer)));
			if (2 >= player->drawer->cardInHand.size())
			{
				player->set_DaDiaoChe(true);
			}

			playersWin.push_back(player);
			continue;
		}

		if (RESULT::LOSE == player->get_Result() || RESULT::DIANPAO == player->get_Result())
		{
			playersLose.push_back(player);
			continue;
		}
	}
	auto  winDir = playersWin.at(0)->drawer->get_dir();
	//更换庄家
	set_zhuangPlayer(winDir);
	if (isDianPao)
	{
		accountDianPao(playersWin, playersLose);
	}
	else if (isQiangGang)
	{
		accountQiangGang(playersWin, playersLose);
	}
	else
	{
		accountZiMo(playersWin, playersLose);
	}
	// -------------------------------  计算分数  ----------------------------
	CCLOG("----- Score -----");
	int index = 0;
	int roomScore = getRoomScore();
	int winscore = 0;
	for (auto player:playersLose)
	{
		int times = player->get_multiple();
		int fun = player->get_FanShu();
		int sign_fun = -1;
		int score = sign_fun*pow(2, abs(fun))*roomScore*times*player->get_ZhongNiaoFen();
		player->set_Score(/*player->get_FanShu() * roomScore * times*/score);
		Room::getInstance()->updateCoins(player->drawer->get_dir(), player->get_Score());
		winscore += score;
		CCLOG("Player [%d] fan : %d  score = %d zhongniaofen = %d mutiles = %d", player->drawer->get_dir(), player->get_FanShu(), player->get_Score(), player->get_ZhongNiaoFen(), player->get_multiple());
	}
	playersWin[0]->set_Score(-winscore);
	Room::getInstance()->updateCoins(playersWin[0]->drawer->get_dir(), playersWin[0]->get_Score());

}
void Rules::accountZiMo(vector<Player*> & playersWin, vector<Player*> & playersLose)
{
	/*点炮：
	牌型：自摸的人，根据自己的胡牌牌型，计算番数减给输者 == = 输者番数为负
	摸鸟：摸到输者，输者【加2】 | 摸到自摸者，所有输者【加2】
	摸鸟结束所有人番数之和加给自摸者 == = 最终赢番正，输番负，中立0
	*/
	for (Player* playerWin : playersWin)
	{
		CCLOG("----- Win[%d] -----", playerWin->drawer->get_dir());
		int fanshu = 0;
		CCLOG("%d : start", fanshu);

		/*if (playerWin->get_DaDiaoChe())		{*/ fanshu += 1; /*}*/
		CCLOG("%d : dadiaoche", fanshu);

		if (playerWin->get_PengPengHu())		{ fanshu += 1; }
		CCLOG("%d : peng", fanshu);

		if (playerWin->get_QingYiSe())			{ fanshu += 1; }
		CCLOG("%d : qingyise", fanshu);

		if (playerWin->get_GangKai())			{ fanshu += 1; }
		CCLOG("%d : gang", fanshu);


		for (Player* playerLose : playersLose)
		{
			playerLose->set_FanShu(-fanshu);
		}
		playerWin->set_FanShu(fanshu);
	}

	// 摸鸟
	CCLOG("----- zhuaNiao -----");
	int winzhongniaofen = 0;
	int winmultiple = 0;
	for (Player* playerLose : playersLose)
	{
		for (Player* playerWin : playersWin)
		{
			/*	playerWin->set_FanShu(playerLose->get_NiaoNum() + playerWin->get_FanShu());*/
			int zhongniaofen = pow(2, playerLose->get_NiaoNum() + playerWin->get_NiaoNum());
			playerLose->set_ZhongNiaoFen(zhongniaofen);
			winzhongniaofen += zhongniaofen;

			int multiple = playerLose->get_multiple()*playerWin->get_multiple();
			playerLose->set_multiple(multiple);
			winmultiple += multiple;
		}
	}
	playersWin.at(0)->set_multiple(winmultiple);
	playersWin.at(0)->set_ZhongNiaoFen(winzhongniaofen);
	

}
void Rules::accountDianPao(vector<Player*> & playersWin, vector<Player*> & playersLose)
{
	/*点炮：
	牌型：每个选择了胡牌的人，根据自己的胡牌牌型，计算番数加给自己 == = 赢者番数为正
	摸鸟：摸到输者，所有赢者【番数加2】 | 摸到赢者，赢着【自己加2】 | 摸到中立，不变
	摸鸟结束所有人番数之和减给输者 == = 最终赢番正，输番负，中立0
	*/
	// 计算牌型
	for (Player* playerWin : playersWin)
	{
		CCLOG("----- Win[%d] -----", playerWin->drawer->get_dir());
		int fanshu = 0;
		CCLOG("%d : start", fanshu);

		/*if (playerWin->get_DaDiaoChe())	*/	/*{ */fanshu += 1; /*}*/
		CCLOG("%d : dadiaoche", fanshu);

		if (playerWin->get_PengPengHu())		{ fanshu += 1; }
		CCLOG("%d : peng", fanshu);

		if (playerWin->get_QingYiSe())			{ fanshu += 1; }
		CCLOG("%d : qingyise", fanshu);

		if (playerWin->get_GangKai())			{ fanshu += 1; }
		CCLOG("%d : gang", fanshu);


		for (Player* playerL : playersLose)
		{
			playerL->set_FanShu(-fanshu);
		}
		playerWin->set_FanShu(fanshu);

	}

	// 计算摸鸟 倍数
	CCLOG("----- zhuaNiao -----");
	//for (Player* playerWin : playersWin)
	//{
	//	playerWin->set_FanShu(playerWin->get_NiaoNum() + playerWin->get_FanShu());
	//}
	int winzhongniaofen = 0;
	int winmultiple = 0;
	for (Player* playerLose : playersLose)
	{
		for (Player* playerWin : playersWin)
		{
		/*	playerWin->set_FanShu(playerLose->get_NiaoNum() + playerWin->get_FanShu());*/
			int zhongniaofen = pow(2, playerLose->get_NiaoNum() + playerWin->get_NiaoNum());
			playerLose->set_ZhongNiaoFen(zhongniaofen);
			winzhongniaofen += zhongniaofen;
			
			int multiple = playerLose->get_multiple()*playerWin->get_multiple();
			playerLose->set_multiple(multiple);
			winmultiple += multiple;
		}
	}
	playersWin.at(0)->set_multiple(winmultiple);
	playersWin.at(0)->set_ZhongNiaoFen(winzhongniaofen);
	//// -----------------------------------------
	//int fan = 0;
	//for (Player* playerWin : playersWin)
	//{
	//	fan += playerWin->get_FanShu();
	//}
	//for (Player* playerLose : playersLose)
	//{
	//	playerLose->set_FanShu(-fan);
	//	
	//}
	
}
void Rules::accountQiangGang(vector<Player*> & playersWin, vector<Player*> & playersLose)
{
	/*自摸:
	牌型：根据自己的胡牌牌型，计算出番数减去给其他所有人
	摸鸟：摸到自己，其他人【番数加倍】 | 摸到他人，他人【番数加倍】 |
	摸鸟结束所有番数之和绝对值加给自己【赢】 == = 最终自己【赢】为正，输番负，中立0
	*/
	// 计算牌型
	for (Player* playerWin : playersWin)
	{
		CCLOG("----- Win[%d] -----", playerWin->drawer->get_dir());
		int fanshu = 0;
		CCLOG("%d : start", fanshu);

	/*	if (playerWin->get_DaDiaoChe())	*/	/*{*/ fanshu += 1;/* }*/
		CCLOG("%d : dadiaoche", fanshu);

		if (playerWin->get_PengPengHu())		{ fanshu += 1; }
		CCLOG("%d : peng", fanshu);

		if (playerWin->get_QingYiSe())			{ fanshu += 1; }
		CCLOG("%d : qingyise", fanshu);

		if (playerWin->get_GangKai())			{ fanshu += 1; }
		CCLOG("%d : gang", fanshu);

		for (Player* playerL : playersLose)
		{
			playerL->set_FanShu(-fanshu);
		}
		playerWin->set_FanShu(fanshu);
	}

	// 计算摸鸟
	int winzhongniaofen = 0;
	int winmultiple = 0;
	for (Player* playerLose : playersLose)
	{
		for (Player* playerWin : playersWin)
		{
			/*	playerWin->set_FanShu(playerLose->get_NiaoNum() + playerWin->get_FanShu());*/
			int zhongniaofen = pow(2, playerLose->get_NiaoNum() + playerWin->get_NiaoNum());
			playerLose->set_ZhongNiaoFen(zhongniaofen);
			winzhongniaofen += zhongniaofen;

			int multiple = playerLose->get_multiple()*playerWin->get_multiple();
			playerLose->set_multiple(multiple);
			winmultiple += multiple;
		}
	}
	playersWin.at(0)->set_multiple(winmultiple);
	playersWin.at(0)->set_ZhongNiaoFen(winzhongniaofen);
}
int Rules::getRoomScore()
{
    return Room::getInstance()->getRoomScore();
}

// 测试是否清一色，true表示清一色，false表示没有清一色
bool Rules::testSameType(MahjongDrawer & drawer)
{
	CCLOG("Rules    : testSameType");
	int start = 0;
	int end = drawer.cardInHand.size() - 1;
	if (0 > drawer[start] * drawer[end])
	{
		return false;		// 手牌不同
	}
	if (0 != drawer.cardInSide.size())
	{
		if (0 > drawer[start] * drawer.cardInSide.at(0)->get_type())
		{
			return false;	// 手牌和碰杠牌不同
		}
	}
	return true;
}
// 测试是否碰碰胡，true表示碰碰胡，false表示没有碰碰胡
bool Rules::testIfPengPengHu(MahjongDrawer & drawer)
{
	CCLOG("Rules    : testIfPengPengHu");
	int start = 0;
	auto card = drawer.cardInHand;
	int size = card.size();
	if (size==2)
	{
		return true;
	}
	else
	{
		int UnSameCard =1;
		int type = card[0]->get_type();
		for (int i = 0; i<size;i++)
		{
			if (type != card[i]->get_type())
			{
				type = card[i]->get_type();
				UnSameCard++;
			}
		}
		if (UnSameCard<=2)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
// 从剩下的牌中摸四张鸟
// 没有引用，游戏开始时象征性扔筛子。。
Sprite* Rules::creatShaiZi()
{
	Size size = Director::getInstance()->getWinSize();
	Sprite *shaizi = Sprite::create();
	shaizi->setPosition(size.width / 2, size.height / 2);
	string strArray[6] =
	{
		"ShaiZi/1.png",
		"ShaiZi/2.png",
		"ShaiZi/3.png",
		"ShaiZi/4.png",
		"ShaiZi/5.png",
		"ShaiZi/6.png"
	};
	Vector<SpriteFrame*> spriteFrameVect;
	for (int i = 0; i < 6; i++)
	{
		SpriteFrame *oneFrame = SpriteFrame::create(strArray[i], Rect(0, 0, 41, 45));
		spriteFrameVect.pushBack(oneFrame);
	}
	Animation *anim = Animation::createWithSpriteFrames(spriteFrameVect, 0.15f);
	Animate *shaiziAnimate = Animate::create(anim);
	Sequence *seq = Sequence::create(Repeat::create(shaiziAnimate->clone(), 3),
		CallFunc::create([=](){
		int rand = random<int>(0, 5);
		shaizi->setSpriteFrame(spriteFrameVect.at(rand));
	}), NULL);
	shaizi->runAction(seq);
	return shaizi;
}

//-----------------------------------------  辅助函数  ---------------------------------------------

bool Rules::isThreeBehind(int a, int b, int c)
{
	int ar[3] = { a, b, c };
	for (int i = 0; i < 3;i++)
	{
		for (int j = 0; j < 3-i-1;j++)
		{
			if (ar[j]>ar[j + 1])
			{
				int temp = ar[j];
				ar[j] = ar[j + 1];
				ar[j + 1] = temp;
			}
		}
	}
	return (ar[2] - ar[1] == 1) && (ar[1] - ar[0] == 1);
}

bool Rules::isThreeSame(int a, int b, int c)
{
	if (a == b && b == c){ return true; }
	return false;
}

int Rules::getSignByInteger(int num)
{
	if (num == 0)
	{
		return 0;
	}
	return num / abs(num);
}
