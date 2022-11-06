#include "Player.h"
#include "Audio.h"
#include "MahjongDatas.h"
#include "Rules.h"
#include "HeadPortrait.h"
#include "PlayMenu.h"
#include "MahjongAnim.h"
#include "Room.h"
#include "AIRules.h"

Vec2 Player::lightPos = Vec2(64.0f, 48.0f);

//-----------------------------------------  玩家类  --------------------------------------------

//-----------------------------------------  初始化  --------------------------------------------
PlayMenu* Player::playMenu = nullptr;

Player* Player::createPlayer(PLAYER playerIndex)
{
	CCLOG("-----------------------");
	CCLOG("Player : createPlayer");
	// 新建玩家，并初始化方向
	Player* player = Player::create();
	player->drawer->setDrawer(playerIndex);
	player->addHeadPortrait(playerIndex);
	if (PLAYER::PLAYER_0 == playerIndex)
	{
		player->set_CanOpera(false);
		player->set_isPlayer(true);
	}
	return player;
}

void Player::turnOnLight()
{
	CCLOG("Turn On Light ? %d", drawer->get_dir());
	if (nullptr != light)
	{
		CCLOG("Turn On Light Y");
		light->runAction(FadeIn::create(0.5f));
	}
}
void Player::turnOffLight(float dt)
{
	CCLOG("Turn Off Light ?");
	if (nullptr != light)
	{
		CCLOG("Turn Off Light Y, disPatch PlayCardEnd, GaneFlow::operaPlayEnd");
		dispatchMahjongEvent(OPERA_PLAY_END, NULL);
		light->runAction(FadeOut::create(0.5f));
	}
}

bool Player::initLogo()
{
	PLAYER dir = drawer->get_dir();
	Sprite* dirSpr;
	string dirStr = "dir_";
	if (!isZhuang)
	{
		dirStr += String::createWithFormat("%d", dir)->_string;
	}
	dirSpr = Sprite::create(dirStr + ".png");
	dirSpr->setRotation(dir * -90.0f);
	this->addChild(dirSpr);

	Size size = _director->getWinSize();
	Vec2 center = Vec2(size.width / 2, size.height / 2 +50);
	light = Sprite::create("light_" + String::createWithFormat("%d", (dir%2))->_string + ".png");
	switch (dir)
	{
	case PLAYER_0:
		light->setPosition(Vec2(center.x, center.y - lightPos.y));
		light->setRotation(180.0f);
		dirSpr->setPosition(Vec2(center.x, center.y - lightPos.y - 3.0f));
		break;
	case PLAYER_1:
		light->setPosition(Vec2(center.x + lightPos.x, center.y));
		dirSpr->setPosition(Vec2(center.x + lightPos.x + 2.0f, center.y));
		break;
	case PLAYER_2:
		light->setPosition(Vec2(center.x, center.y + lightPos.y));
		dirSpr->setPosition(Vec2(center.x, center.y + lightPos.y + 3.0f));
		break;
	case PLAYER_3:
		light->setPosition(Vec2(center.x - lightPos.x, center.y));
		light->setRotation(180.0f);
		dirSpr->setPosition(Vec2(center.x - lightPos.x - 2.0f, center.y));
		break;
	}
	light->setOpacity(0.0f);
	this->addChild(light);



	return true;
}

bool Player::init()
{
	CCLOG("Player : init");
	if (!Node::init())
	{
		return false;
	}
	set_isPlayer(false);
	set_isZhuang(false);
	set_isPickGood(false);
	set_PengPengHu(false);
	set_DaDiaoChe(false);
	set_QingYiSe(false);
	set_GangKai(false);
	set_canHu(false);
	set_Result(RESULT::NEUTRAL);
	set_NiaoNum(0);
	set_FanShu(0);
	set_Score(0);

	drawer = MahjongDrawer::create();
	this->addChild(drawer);
	return true;
}
void Player::setTimes()
{
	int times = get_multiple();
	HeadPortrait* head = (HeadPortrait*)(getChildByName("Head"));
	head->setTimes(times);
}
void Player::updateName()
{
	PLAYER dir = drawer->get_dir();
	if (dir != PLAYER_0)
	{
		return;
	}
	HeadPortrait* head = (HeadPortrait*)(getChildByName("Head"));
	head->updateName();
}
void Player::updateCoin()
{
	HeadPortrait* head = (HeadPortrait*)(getChildByName("Head"));
	head->updateCoin();
}
void Player::addHeadPortrait(int dir)
{
	CCLOG("Player : addHeadPortrait %d", drawer->get_dir());
	HeadPortrait* head = HeadPortrait::create();
	int coins = Room::getInstance()->getCoins(dir);
	head->setHeadProtrait(dir, "name", dir, coins);
	this->addChild(head);
}

//-----------------------------------------  摸牌  --------------------------------------------
void Player::goOnOperaPick()
{
	CCLOG("No one QiangGang , goOnOperaPick ");
	turnOnLight();
	scheduleOnce([this](float dt){this->operaPick(); }, MahjongDrawer::timeKaiGang, "Pick__InKaiGang");
}

Card* Player::operaPick()
{
	turnOnLight();
	// 得到摸到的牌花色
	int type;
	if (isPickGood)
	{
		type = MahjongDatas::getInstance()->popAGoodCard(this->drawer->cardInHand);
	}
	else
	{
		type = MahjongDatas::getInstance()->popACard();
	}
	CCLOG("Player %d : pick %d", drawer->get_dir(), type);

	Card* playedCard = drawer->drawHandCard(type);

	MahjongAnim::getInstance()->logScreen("Pick : ", drawer->get_dir());
	MahjongAnim::getInstance()->addRemever(type);

	// 绘制摸到的一张手牌,摸牌动作在DrawHandCard
	scheduleOnce([](float dt){dispatchMahjongEvent(OPERA_PICK_END, NULL); }, MahjongDrawer::timePickCard, "Pick");
	return playedCard;
}

void Player::operaAnGang()
{
	CCLOG("Player %d : Can AnGang", drawer->get_dir());
	if (isPlayer)
	{
		playMenu->ShowAnGangButton();
	}
	else
	{
		//if (2 == drawer->get_dir() || 1 == drawer->get_dir())
		//{
		//	operaPlay();
		//	return;
		//}
		anGang();
	}
}

void Player::anGang()		// 摸牌之后
{
	CCLOG("Player %d: AnGang", drawer->get_dir());
	// 开暗杠
	scheduleOnce(CC_CALLBACK_0(Player::kaiGang, this, false), 1.0f, "KaiGang");
	scheduleOnce([this](float dt){this->operaPick(); }, MahjongDrawer::timeKaiGang, "Pick__InKaiGang");
}

void Player::operaPengGang()
{
	CCLOG("Player %d : Can PengGang", drawer->get_dir());

	if (isPlayer)
	{
		playMenu->ShowPengGangButton();
	}
	else
	{
		pengGang();
	}
}
void Player::pengGang()
{
	CCLOG("Player %d : PengGang", drawer->get_dir());

	turnOnLight();
	// 开明杠
	dispatchMahjongEvent(DELETE_TABLE_BEFORE, NULL);

	scheduleOnce([this](float dt){this->kaiGang(true); }, 1.0f, "KaiGang");
	scheduleOnce([this](float dt){
		dispatchMahjongEvent(OPERA_PENGGANG_END, NULL);
	}, 3.0f, "KaiPengGang");
}

//-----------------------------------------  打牌  --------------------------------------------
void Player::operaPlay()
{
	CCLOG("Player %d : play", drawer->get_dir());
	if (isPlayer)	
	{	//  玩家，选择打牌
		set_CanOpera(true);
	}
	else				
	{	// A I ，随机打牌 
		this->runAction(Sequence::create(DelayTime::create(random<float>(1, 2)), 
			CallFunc::create([this](){
			if (MahjongDatas::getInstance()->isFalseCard)
			{
				playACard(drawer->cardInHand.at(drawer->cardInHand.size()-1));
			/*	playACard(AIRules::getInstance()->getCardToPlay(*drawer));*/

			}
			else
			{
				playACard(AIRules::getInstance()->getCardToPlay(*drawer));
			}
		}),
			NULL)); 
	}			
}
void Player::playACard(Card* card)
{
	Audio::getInstance()->playMahjongByRole(card->get_type(), Room::getInstance()->getPlayerHead(drawer->get_dir()));
	CCLOG("Player %d : playACard [%d]", drawer->get_dir(), card->get_type());
	// 锁住，在打牌动画没结束之前，就要关闭手动打牌权限
	set_CanOpera(false);
	// 在桌子上的下一个位置打出麻将，播放打牌动

	auto lastcard = Rules::getInstance()->get_currentCard();
	if (lastcard)
	{
		lastcard->hidePoint();
	}
	auto newcard = drawer->drawTableCard(card);
	//newcard->showPoint();
	Rules::getInstance()->set_currentCard(newcard);
	
	
	MahjongAnim::getInstance()->logScreen("Play : ", drawer->get_dir());
	if (0 == drawer->get_dir())
	{
		scheduleOnce([this, card](float dt){
			// 从手牌中移除打出的牌
			drawer->cardInHand.erase(find(drawer->cardInHand.begin(), drawer->cardInHand.end(), card));
			drawer->handNode->removeChild(card, true);
		}, MahjongDrawer::timePlayingCard, "RmPlayedHnd");
	}
	else
	{
		// 从手牌中移除打出的牌
		drawer->cardInHand.erase(find(drawer->cardInHand.begin(), drawer->cardInHand.end(), card));
		drawer->handNode->removeChild(card, true);
	}

	drawer->logHand();
	CCLOG("After Play, turnOffLight");
	scheduleOnce(CC_CALLBACK_1(Player::turnOffLight, this), MahjongDrawer::timePlayCard, "Played");
}
///////////////////
void Player::operaGang()			// 打牌之后
{
	turnOnLight();
	if (isPlayer)
	{
		playMenu->ShowPengAndGang();
	}
	else
	{
		gang();
	}
}
void Player::gang()
{

	// 开明杠
	dispatchMahjongEvent(DELETE_TABLE_BEFORE, NULL);

	scheduleOnce([this](float dt){this->kaiGang(true); }, 1.0f, "KaiGang");
	scheduleOnce([this](float dt){this->operaPick(); }, 2.0f, "Pick__InKaiGang");
}
//-----------------------------------------  碰牌  --------------------------------------------
void Player::operaPeng()
{
	CCLOG("player Peng");
	turnOnLight();
	if (isPlayer)
	{
		playMenu->ShowPengButton();
	}
	else
	{
		peng();
	}
}
void Player::peng()
{

	CCLOG("Player %d : peng", drawer->get_dir());
	// 摸进手牌
	scheduleOnce([this](float dt){kaiPeng(); }, MahjongDrawer::timePickCard, "Pick");
	scheduleOnce([this](float dt){this->operaPlay(); }, 1.0f, "Play__InKaiPeng");
}
bool Player::kaiPeng()
{
	Audio::getInstance()->playSoundPeng(Room::getInstance()->getPlayerHead(drawer->get_dir()));
	CCLOG("Player %d : kaiPeng", drawer->get_dir());
	set_PengPengHu(true);
	int pengType = Rules::getInstance()->get_currentCard()->get_type();
	drawer->drawPengCard(pengType, Rules::getInstance()->get_currentCard()->get_dir());
	drawer->remove2CardInHand(pengType);
	
	dispatchMahjongEvent(DELETE_TABLE_BEFORE, NULL);
	drawer->logHand();
	drawer->sortCard();
	return true;
}
int Player::getNewCardLocation(int type)
{
	CCLOG("Player %d : getNewCardLocation", drawer->get_dir());
	int size = drawer->cardInHand.size();
	if (0 == size || (*drawer)[0] > type)
	{
		return 0;
	}

	if ((*drawer)[size-1] <= type)
	{
		return size;
	}

	for (int i = 0; i < size - 1; i++)
	{
		if ((*drawer)[i] <= type && (*drawer)[i+1] > type)
		{
			return i + 1;
		}
	}
	return 0;
}

//-----------------------------------------  杠牌  --------------------------------------------
void Player::kaiGang(bool isMingGang)
{
	set_GangKai(true);
	set_PengPengHu(true);
	Audio::getInstance()->playSoundGang(Room::getInstance()->getPlayerHead(drawer->get_dir()));
	CARD_SIDE side = isMingGang ? UP : DOWN;

	// 自摸杠or碰杠
	if (0 == drawer->cardInSide.size())
	{	// 自摸杠，碰杠，5牌
		drawer->drawSideCard((*drawer)[2], 4, side);
		if (4 == drawer->cardInHand.size())
		{
			drawer->remove3CardInHand();
		}
		else
		{
			drawer->remove4CardInHand();
		}
	}
	else
	{	// 碰杠，2牌
		drawer->drawSideCard(drawer->cardInSide.at(0)->get_type(), 4, side);
		if (drawer->cardInHand.size() == 2)
		{
			drawer->remove1CardInHand();
		}
	}
	drawer->logHand();
	drawer->sortCard();
	set_GangKai(true);
}
//-----------------------------------------  胡牌  --------------------------------------------
void Player::operaZiMo()
{
	if (isPlayer)	//  A I ，随机打牌 
	{
		playMenu->ShowZiMoButton();
	}
	else					// 玩家，选择打牌
	{
		ziMo();
	}
}
void Player::ziMo()
{
	PLAYER playerIndex = drawer->get_dir();
	Audio::getInstance()->playSoundHu(1, Room::getInstance()->getPlayerHead(playerIndex));
	
	set_Result(ZIMO);
	CCLOG("Player[%d] : ZiMo", playerIndex);
	CCLOG("Win : %d", playerIndex);
	dispatchMahjongEvent(FLOW_NAME::OPERA_ZIMO_END,0);
}

void Player::operaDianPao()
{
	if (isPlayer)
	{
		turnOnLight();
		if (Rules::getInstance()->testCanPeng4(*drawer, Rules::getInstance()->get_currentCard()->get_type()))
		{
			playMenu->ShowDianPaoAndPengButton();
		}
		else
		{
			playMenu->ShowDianPaoButton();
		}
	}
	else
	{
		//// 电脑弃胡
		//set_canHu(false);
		//dispatchMahjongEvent(OPERA_DIANPAO_END, NULL);

		dianPao();
	}
}

void Player::dianPao()
{

	CCLOG("Player[%d] : dianPao", drawer->get_dir());
	set_Result(HU);

	dispatchMahjongEvent(OPERA_DIANPAO_END, NULL);
}

void Player::operaQiangGang()
{
	if (isPlayer)
	{
		turnOnLight();
		playMenu->ShowQiangGangButton();
	}
	else
	{
		qiangGang();
	}
}

void Player::qiangGang()
{
	MahjongAnim::getInstance()->logScreen("QGPlayer : ", drawer->get_dir());

	CCLOG("Player[%d] : qiangGang", drawer->get_dir());
	set_Result(HU);
	dispatchMahjongEvent(OPERA_QIANGGANG_END, NULL);
}

int Player::addNiaoNum()
{
	return ++NiaoNum;
}


void Player::showCards()
{
	drawer->showCards();
}