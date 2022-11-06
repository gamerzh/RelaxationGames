#include "MahjongDrawer.h"
#include "Card.h"
#include "Player.h"
#include "Rules.h"
#include "GameFlow.h"
#include "MahjongAnim.h"

//------------------------------------ 初始位置 --------------------------------------
Vec2 MahjongDrawer::cardTablePos[4] = 
{
	Vec2(340*1.6, 180*1.5),
	Vec2(500 * 1.6, 220 *1.5),
	Vec2(455 * 1.6, 360 *1.5),
	Vec2(300 * 1.6, 310 *1.5),
};

Vec2 MahjongDrawer::cardSidePos[4] = 
{
	Vec2(150 * 1.6, 100),
	Vec2(1000, 120 *1.5),
	Vec2(320 * 1.6, 400 *1.5),
	Vec2(150 * 1.6, 320 *1.5),
};

Vec2 MahjongDrawer::cardOutHandDis[4] =
{
	Vec2(21 * 1.6, -26 *1.3),
	Vec2(27 * 1.6, 25 *1.3),
	Vec2(-21 * 1.6, 26 *1.3),
	Vec2(-27 * 1.6, -25*1.3),
};

Vec2 MahjongDrawer::cardPickDis[4] =
{
	Vec2(20 * 1.6, 0 *1.5),
	Vec2(0 * 1.6, 20 *1.5),
	Vec2(-20 * 1.6, 0 *1.5),
	Vec2(0 * 1.6, -20 *1.5),
};

float MahjongDrawer::timePickCard = 0.1f;
float MahjongDrawer::timePlayCard = 0.5f;
float MahjongDrawer::timePlayingCard = 0.3f;
float MahjongDrawer::timeKaiGang = 2.0f;

//------------------------------------  初始化  --------------------------------------
bool MahjongDrawer::init()
{
	if (!Node::init())
	{
		return false;
	}

	tableNode = Node::create();
	this->addChild(tableNode);

	sideNode = Node::create();
	this->addChild(sideNode);

	handNode = Node::create();
	this->addChild(handNode);

	return true;
}
void MahjongDrawer::setDrawer(PLAYER dir)
{
	set_dir(dir);
	switch (dir)
	{
	case PLAYER_0:
		for (int i = 0; i < 5; i++)
		{
			cardHandPos[i] = Vec2(300*1.6 + i * 47*1.6,65);
		}
		cardBigCard[dir] = cardHandPos[2] + Vec2(.0f, 54.0f);
		cardSidePos[dir] = cardHandPos[2] + Vec2(0.0f, 0.0f);

		break;

	case PLAYER_2:
		for (int i = 0; i < 5; i++)
		{
			cardHandPos[i] = Vec2(460*1.6 - i * 28*1.6, 10+450*1.5);
		}
		cardBigCard[dir] = cardHandPos[2] + Vec2(.0f, -54.0f);
		cardSidePos[dir] = cardHandPos[2] + Vec2(0.0f, 0.0f);;

		break;

	case PLAYER_1:
		for (int i = 0; i < 5; i++)
		{
			cardHandPos[i] = Vec2(698*1.6, 162*1.5 + i * 24*1.5);
		}
		cardBigCard[dir] = cardHandPos[2] + Vec2(-48.0f, .0f);
		cardSidePos[dir] = cardHandPos[0] + Vec2(.0f, 72.0f);

		break;

	case PLAYER_3:
		for (int i = 0; i < 5; i++)
		{
			cardHandPos[i] = Vec2(100*1.6, 350*1.5 - i * 24*1.5);
		}
		cardBigCard[dir] = cardHandPos[2] + Vec2(48.0f, .0f);
		cardSidePos[dir] = cardHandPos[2] + Vec2(.0f, 18.0f);
		break;
	}

	
}

//-------------------------------------- 绘制 -----------------------------------------
Card* MahjongDrawer::drawHandCard(int type)
{
	int index = cardInHand.size();

	// 创建手牌
	Card* newCard = Card::createHandCard(dir, type);
	newCard->setTag(index);
	if (PLAYER::PLAYER_1 == dir){ newCard->setLocalZOrder(-index); }

	// 添加手牌，
	handNode->addChild(newCard);

	// 数据，并排序数据。
	cardInHand.push_back(newCard);
	sortData();

	// 动画
	Size size = _director->getVisibleSize();
	newCard->setPosition(size.width / 2, size.height / 2);
	newCard->runAction(MoveTo::create(timePickCard, cardHandPos[index]));
	if (dir == 0)
	{

	}
	nowPickCard = newCard;
	return newCard;
}
Card* MahjongDrawer::drawTableCard(Card* card)
{
	if (0 == dir)
	{

		return drawTableCardPlayer(card);
	}
	else
	{
		return drawTableCardAI(card);
	}
}

Card* MahjongDrawer::drawTableCardPlayer(Card* card)
{
	// 牌
	int type = card->get_type();

	Card* newCard = Card::createTableCard(dir, type);
	tableNode->addChild(newCard);

	// 动画
	int index = cardInTable.size();
	int row = index % tableRow;
	int col = index / tableRow;
	if (1 == dir % 2)
	{
		swap(row, col);
	}
	int order = (0 == dir || 3 == dir) ? index : -index;
	newCard->setLocalZOrder(order);

	// 动画起始和结束位置
	Vec2 animStartPos = cardHandPos[2];
	Vec2 posTo = Vec2(cardTablePos[dir].x + row * cardOutHandDis[dir].x,
		cardTablePos[dir].y + col * cardOutHandDis[dir].y);
	
	// 手牌移动到结束位置
	float timeMoveTo = timePlayingCard * 0.5f;
	float timeMoveBy = timePlayingCard - timeMoveTo;
	Spawn* moveToPosAct = Spawn::create(ScaleTo::create(timeMoveTo, 0.4f), MoveTo::create(timeMoveTo, posTo), NULL);
	Sequence* act = Sequence::create(MoveBy::create(timeMoveBy, Vec2(.0f, 50.0f)), moveToPosAct, NULL);
	card->runAction(act);

	// 桌牌出现
	newCard->setPosition(posTo);
	newCard->setVisible(false);
	newCard->runAction(Sequence::create(DelayTime::create(timePlayingCard), Show::create(), CallFunc::create([=]{newCard->showPoint(); }), NULL));

	// 记录当前打牌 
	cardInTable.push_back(newCard);
	return newCard;
}

Card* MahjongDrawer::drawTableCardAI(Card* card)
{
	// 牌
	int type = card->get_type();
	Card* newCard = Card::createTableCard(dir, type);
	tableNode->addChild(newCard);
	// 动画
	int index = cardInTable.size();
	int row = index % tableRow;
	int col = index / tableRow;
	if (1 == dir % 2)
	{
		swap(row, col);
	}
	int order = (0 == dir || 3 == dir) ? index : -index;
	newCard->setLocalZOrder(order);
	Vec2 animStartPos = cardHandPos[2];
	//Vec2 animStartPos = card->getPosition();

	Vec2 posTo = Vec2(cardTablePos[dir].x + row * cardOutHandDis[dir].x,
		cardTablePos[dir].y + col * cardOutHandDis[dir].y);
	newCard->setPosition(animStartPos + 3 * cardPickDis[(dir + 1) % 4]);

	newCard->setOpacity(0.0f);


	newCard->cardFadeIn(0.5f, 0.2f, posTo, 1.0f);

	newCard->runAction(Sequence::createWithTwoActions(DelayTime::create(0.7f), CallFunc::create([=]{newCard->showPoint(); })));
	MahjongAnim::getInstance()->playPlayAnim(type, cardBigCard[dir]);
	// 记录当前打牌 
	cardInTable.push_back(newCard);
	return newCard;
}

void MahjongDrawer::drawSideCard(int type, int sideNum, CARD_SIDE side)
{
	MahjongAnim::getInstance()->playSound(SOUND::PENGGANG);
	if (PLAYER_0 != dir)
	{
		if (3 == sideNum)
		{
			MahjongAnim::getInstance()->playWordPengAnim(cardHandPos[0]);
		}
		else
		{
			MahjongAnim::getInstance()->playWordGangAnim(cardHandPos[0]);
		}
	}
	if (3 == sideNum)
	{
		MahjongAnim::getInstance()->playPengAnim(type, cardHandPos[2]);
	}
	else
	{
		MahjongAnim::getInstance()->playGangAnim (type, cardHandPos[2]);//change 1
	}

	Vec2 dis;


	switch (dir)
	{
	case PLAYER_0:
		dis = Vec2(43*1.6f, .0f);
		break;
	case PLAYER_1:
		dis = Vec2(.0f, cardOutHandDis[dir].y);
		break;
	case PLAYER_2:
		dis = Vec2(cardOutHandDis[dir].x, .0f);
		break;
	case PLAYER_3:
		dis = Vec2(.0f, cardOutHandDis[dir].y);
		break;
	case PLAYER_NULL:
		break;
	default:
		break;
	}
	sideNode->removeAllChildrenWithCleanup(false);
	cardInSide.clear();
	for (int i = 0; i < sideNum; i++)
	{
		Card* newCard = Card::createSideCard(dir, side, type);

		newCard->setLocalZOrder(dir == 3 ? -i : i);

		Vec2 posTo = Vec2(	cardSidePos[dir].x - i * dis.x,
											cardSidePos[dir].y - i * dis.y);
		newCard->setPosition(posTo);
		sideNode->addChild(newCard);

		cardInSide.push_back(newCard);
	}// end for
	sideNode->setVisible(false);
	scheduleOnce([this](float dt){
		this->sideNode->setVisible(true);
	}, 2.15f, "addSideCard");
}
void MahjongDrawer::drawPengCard(int type, int pickDir)
{
	MahjongAnim::getInstance()->playSound(SOUND::PENGGANG);
	if (PLAYER_0 != dir)
	{
		MahjongAnim::getInstance()->playWordPengAnim(cardHandPos[0]);
	}
	MahjongAnim::getInstance()->playPengAnim(type, cardHandPos[2]);


	int difDir = dir - pickDir;
	difDir = difDir < 0 ?  difDir + 4: difDir;
	difDir = difDir >3 ? difDir - 4 : difDir;
	//difDir  1:left  2:mid 3:right
	Vec2 dis2[3];
	switch (dir)
	{
	case PLAYER_0:
		dis2[0] = Vec2(50, .0f);
		dis2[1] = Vec2(57, .0f);
		dis2[2] = Vec2(25, -50);
		break;
	case PLAYER_1:
		dis2[0] = Vec2(.0f, cardOutHandDis[dir].y);
		dis2[1] = Vec2(.0f, cardOutHandDis[dir].y*1.1);
		dis2[2] = Vec2(30*1.6, 14*1.5);
		break;
	case PLAYER_2:
		dis2[0] = Vec2(cardOutHandDis[dir].x , .0f);
		dis2[1] = Vec2(cardOutHandDis[dir].x*1.1 - 1.1*4, .0f);
		dis2[2] = Vec2((cardOutHandDis[dir].x - 3)/2.0, 36);
		break;
	case PLAYER_3:
		dis2[0] = Vec2(.0f, cardOutHandDis[dir].y);
		dis2[1] = Vec2(.0f, cardOutHandDis[dir].y*1.1f);
		dis2[2] = Vec2(-30*1.6, -14*1.5);
		break;
	case PLAYER_NULL:
		break;
	default:
		break;
	}
	//difDir  1:left  2:mid 3:right  
	Vec2 startPos = Vec2(cardSidePos[dir]);
	for (int i = 0; i < 3; i++)
	{
		Card* newCard;
		if (difDir == 3-i)
		{
			newCard = Card::createLieCard(dir, UP, type);
		}
		else
		{
			newCard = Card::createSideCard(dir, UP, type);
		}

		switch (difDir)
		{
		case 1:
			if (difDir == 3 - i/* || difDir == 3 - i - 1*/)
			{
				startPos -= (dis2[1]);
			}
			else
			{

				startPos -= (dis2[0]);
			}
			break;
		case 2:
			if (difDir == 3 - i) //2
			{
				startPos -= (dis2[2]);
			}
			else if (difDir == 3 - i + 1) //3
			{
				startPos = cardSidePos[dir] - (dis2[0] * 2);
			}
			else //1
			{
				startPos -= (dis2[0]);
			}
			break;
		case 3:
			if (difDir == 3 - i || difDir == 3 - i + 1)
			{
				startPos -= (dis2[1]);
			}
			else
			{
				startPos -= (dis2[0]);
			}
			break;
		default:
			break;
		}
	
		if (difDir==2)
		{
			if (dir==2)
			{
				newCard->setZOrder(difDir == 3 - i ? i + 5 : i);
			}
			else if (dir==3)
			{
				newCard->setZOrder(difDir == 3 - i ? i + 5 : 3-i);
			}
			else
			{
				newCard->setZOrder(difDir == 3 - i ? -i : i);
			}
			
		}
		else
		{
			newCard->setZOrder(dir == 3 ? -i : i);
		}
	
		newCard->setPosition(startPos);
		sideNode->addChild(newCard);
		
		cardInSide.push_back(newCard);
	}// end for
	for (auto var : cardInSide)
	{
		CCLOG("cardInSide pos = (%f,%f) zorder = %d", var->getPositionX(), var->getPositionY(),var->getZOrder());
	}
	sideNode->setVisible(false);
	scheduleOnce([this](float dt){
		this->sideNode->setVisible(true);
	}, 2.15f, "addSideCard");
}
//--------------------------------------- 移除 ----------------------------------------
void MahjongDrawer::remove4CardInHand()
{
	int index;
	// 判断移除前4张or后4张
	if ((*this)[3] == (*this)[4]){ index = 1; }
	else{ index = 0; }

	// 移除4张手牌。
	for (int i = 0; i < 4; i++)
	{
		cardInHand.at(index)->removeFromParentAndCleanup(1);
		cardInHand.erase(cardInHand.begin() + index);
	}

	cardHandPos[0] = cardHandPos[3];
	cardHandPos[1] = cardHandPos[4];
}

void MahjongDrawer::remove3CardInHand()
{
	int index;
	// 判断移除前3张or后3张
	if ((*this)[0] == (*this)[1]){ index = 0; }
	else{ index = 1; }

	// 移除4张手牌。
	for (int i =0; i < 3; i++)
	{
		cardInHand.at(index)->removeFromParentAndCleanup(1);
		cardInHand.erase(cardInHand.begin() + index);
	}

	cardHandPos[0] = cardHandPos[3];
	cardHandPos[1] = cardHandPos[4];
}

void MahjongDrawer::remove2CardInHand(int pengType)
{
	int index;
	// 判断移除前3张or后3张
	auto temp1 = (*this)[0];
	auto temp2 = (*this)[1];
	if ((*this)[0] == (*this)[1] && pengType==(*this)[0])
	{
		index = 0; 
	}
	else if ((*this)[1] == (*this)[2] && pengType == (*this)[1])
	{
		index = 1; 
	}
	else
	{
		index = 2;
	}

	// 移除4张手牌。
	for (int i = 0; i < 2; i++)
	{
		cardInHand.at(index)->removeFromParentAndCleanup(1);
		cardInHand.erase(cardInHand.begin() + index);
	}

	cardHandPos[0] = cardHandPos[3];
	cardHandPos[1] = cardHandPos[4];
}
void MahjongDrawer::remove1CardInHand()
{
	// 判断移除前1张or后1张
	if ((*this)[0] == cardInSide[0]->get_type())
	{	
		cardInHand[0]->removeFromParentAndCleanup(1);
		cardInHand.erase(cardInHand.begin());
	}
	else
	{
		// 第二张。
		cardInHand[1]->removeFromParentAndCleanup(1);
		cardInHand.pop_back();
	}
}

void MahjongDrawer::remove1CardInTable()
{
	auto card = Rules::getInstance()->get_currentCard();
	auto lastCard = cardInTable.at(cardInTable.size() - 1);
	if (card == lastCard)
	{
		Rules::getInstance()->set_currentCard(nullptr);
	}
	lastCard->removeFromParentAndCleanup(1);
	// 从玩家桌牌列表中移除桌牌数据
	cardInTable.pop_back();
}

// 根据花色升序排序
bool sortByType(Card* card1, Card* card2)
{
	return card2->get_type() > card1->get_type();
}
void MahjongDrawer::sortData()
{
	std::sort(cardInHand.begin(), cardInHand.end(), sortByType);
	logHand();
}
void MahjongDrawer::sortCard(bool isAfterPick)
{
	if (!isAfterPick)
	{
		if (1 == cardInHand.size())
		{
			cardInHand[0]->runAction(MoveTo::create(0.6f, cardHandPos[0]));
			return;
		}
		float movedt = random<float>(0.2f, 0.6f);
		for (int i = 0; i < cardInHand.size(); i++)
		{
			if (cardInHand[i]->getPosition() != cardHandPos[i])
			{
				cardInHand[i]->runAction(MoveTo::create(movedt, cardHandPos[i]));
			}
			cardInHand[i]->setLocalZOrder(PLAYER::PLAYER_1 == dir ? -i : i);
		}
	}
	else
	{
		if (1 == cardInHand.size())
		{
			cardInHand[0]->runAction(MoveTo::create(0.6f, cardHandPos[0]));
			return;
		}
		float movedt = random<float>(0.2f, 0.6f)/2.0f;
		int size = cardInHand.size();
		for (int i = 0; i <size; i++)
		{
			if (cardInHand[i] == nowPickCard)
			{
			
					auto card = cardInHand[i];
					float sx = card->getPositionX();
					float sy = card->getPositionY();
					float ex = cardHandPos[i].x;
					float ey = cardHandPos[i].y;

					if ((Vec2(ex, ey) - Vec2(sx, sy)) == (cardHandPos[1] - cardHandPos[0]+cardPickDis[get_dir()]))
					{

						cardInHand[i]->runAction(MoveTo::create(0.3f, cardHandPos[i]));
					}
					else
					{
						ccBezierConfig bezier;
						bezier.controlPoint_1 = Point(sx, sy);
						bezier.controlPoint_2 = Point(sx + (ex - sx) * 0.5,
							sy + (ey - sy) * 0.5 + 50);
						bezier.endPosition = Point(ex, ey);

						cardInHand[i]->setLocalZOrder(6);
						cardInHand[i]->runAction(Sequence::create(DelayTime::create(movedt), BezierTo::create(movedt, bezier), CallFunc::create([=]{cardInHand[i]->setLocalZOrder(PLAYER::PLAYER_1 == dir ? -i : i); }), nullptr));
					}
					
			}
			else
			{
				if (cardInHand[i]->getPosition() != cardHandPos[i])
				{
					cardInHand[i]->runAction(MoveTo::create(movedt, cardHandPos[i]));
				}
				cardInHand[i]->setLocalZOrder(PLAYER::PLAYER_1 == dir ? -i : i);
			}
			
		}
	}
}

void MahjongDrawer::logHand()
{
	string cardstr = "Player " + String::createWithFormat("%d", dir)->_string + " : ";
	for (Card* card : cardInHand)
	{
		cardstr += String::createWithFormat("%d", card->get_type())->_string;
		cardstr += "  ";
	}
	CCLOG(cardstr.c_str());
}



void MahjongDrawer::showCards()
{
	std::vector<Card*> showcards;
	auto cards = cardInHand;
	for (int i = 0; i < cards.size(); i++)
	{
		auto var = cards[i];
		auto dir = get_dir();
		auto newCard = Card::createTableCard(dir, var->get_type());
		newCard->setZOrder(dir == 1 ? -i : i);
		cards[0]->getParent()->addChild(newCard);
		var->setVisible(false);
		newCard->setScale(1.2);
		showcards.push_back(newCard);
	}
	Vec2 dis;
	switch (get_dir())
	{
	case PLAYER_0:
		dis = Vec2(46, .0f);
		break;
	case PLAYER_1:
		dis = Vec2(.0f, 42);
		break;
	case PLAYER_2:
		dis = Vec2(-46, .0f);
		break;
	case PLAYER_3:
		dis = Vec2(.0f, -42);
		break;
	case PLAYER_NULL:
		break;
	default:
		break;
	}
	for (int i = 0; i < showcards.size(); i++)
	{

		showcards.at(i)->setPosition(cardHandPos[0] + i*dis);
		CCLOG("showcards %d pos = (%f,%f) zorder = %d", i, showcards.at(i)->getPositionX(), showcards.at(i)->getPositionY(), showcards.at(i)->getZOrder());
	}
}