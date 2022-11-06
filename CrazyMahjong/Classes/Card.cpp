#include "Card.h"
#include "MahjongAnim.h"
#include "Player.h"
#include "GameFlow.h"

bool Card::init()
{
	Node::init();
	setAnchorPoint(Point::ZERO);
	return true;
}

Card* Card::createHandCard(PLAYER dir, int type)
{
	if (0 == type || 9 < abs(type)){ type = 1; }
	Card* newCard = Card::create();
	newCard->set_type(type);
	newCard->setHandCard(dir, type, true);
	newCard->set_dir(dir);
	return newCard;
}

Card* Card::createShowCard()
{
	Card* newCard = Card::create();
	newCard->set_type(1);
	newCard->setHandCard(PLAYER::PLAYER_0, 1, false);
	newCard->set_dir(PLAYER::PLAYER_0);
	return newCard;
}

Card* Card::createPengGangCard()
{
	return createTableCard(PLAYER::PLAYER_0, 1);
}

Card* Card::createTableCard(PLAYER dir, int type)
{
	Card* newCard = Card::create();
	newCard->set_type(type);
	newCard->setTableCard(dir, type);
	newCard->set_dir(dir);
	return newCard;
}

Card* Card::createSideCard(PLAYER dir, CARD_SIDE side, int type)
{
	Card* newCard = Card::create();
	newCard->set_type(type);
	if (CARD_SIDE::UP == side)
	{
		newCard->setSideCardMing(dir, type);
	}
	else
	{
		newCard->setSideCardAn(dir, type);
	}
	newCard->set_dir(dir);
	return newCard;
}

Card* Card::createLieCard(PLAYER dir, CARD_SIDE side, int type)
{
	Card* newCard = Card::create();
	newCard->set_type(type);
	newCard->setLieCardMing(dir, type);
	newCard->set_dir(dir);
	return newCard;
}

//-----------------------------------------------------------------------------------
std::string Card::getTypeName(int type)
{
	if (0 < type)
	{
		return "Card/CardContent/chara_" + String::createWithFormat("%d", type)->_string + ".png";
	}
	else
	{
		type = 10 + type;
		return "Card/CardContent/circle_" + String::createWithFormat("%d", type)->_string + ".png";
	}
}

std::string Card::getBodyName(CARD_BODY bodyName)
{
	return "Card/CardBkg/" + String::createWithFormat("%d", bodyName)->_string + ".png";
}

Sprite* Card::createType(int type)
{
	string typeSpr = getTypeName(type);
	return Sprite::create(typeSpr);
}

void Card::changeCard(int type)
{
	if (nullptr != typeSpr)
	{
		typeSpr->setTexture(getTypeName(type));
	}
}
void Card::TurnCard()
{
	if (nullptr != bodySpr)
	{
		bodySpr->removeFromParentAndCleanup(1);
		bodySpr = nullptr;
	}
}

void Card::addBody(std::string bodyName)
{
	if (nullptr == bodySpr)
	{
		bodySpr = Sprite::create(bodyName);
		this->addChild(bodySpr);
	}
}

// 设置手牌，根据方向，设置body， 如果side是正面，则设置type，否则不设置type。
void Card::setHandCard(PLAYER dir, int type, bool canTouch)
{
	// 牌底
	switch (dir)
	{
	case PLAYER_0:
		addBody(getBodyName(CARD_BODY::UP_L_STAND));
		break;
	case PLAYER_1:
		addBody(getBodyName(CARD_BODY::SIDE));
		bodySpr->setFlippedX(true);
		break;
	case PLAYER_2:
		addBody(getBodyName(CARD_BODY::BACK_M_STAND));
		break;
	case PLAYER_3:
		addBody(getBodyName(CARD_BODY::SIDE));
		break;
	case PLAYER_NULL:
	default:
		addBody(getBodyName(CARD_BODY::UP_L_STAND));
		break;
	}

	//如果是玩家的牌，则给牌添加点击事件
	//if (PLAYER_0 != dir){ return; }
	addType(getTypeName(type));

	//// 以下为给牌面调整位置
	typeSpr->setPositionY(-8);
	if (PLAYER_0 != dir)
	{
		if (1 == dir)
		{
			typeSpr->setPositionX(-30.0f);
		}
		else if (3 == dir)
		{
			typeSpr->setPositionX(30.0f);
		}
		typeSpr->setPositionY(4.0f);
		typeSpr->setScale(0.5f);

		typeSpr->setVisible(IS_LOGINFO_ONSCREEN);

	}

	if (PLAYER_0 != dir){ return; }
	if (canTouch)
	{
		auto touchListener = EventListenerTouchOneByOne::create();	
		touchListener->setSwallowTouches(true);
		touchListener->onTouchBegan = CC_CALLBACK_2(Card::onCardTouchBegan, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);	
	}
}

void Card::setTableCard(PLAYER dir, int type)
{
	string bodyName;
	// 牌底
	if (PLAYER::PLAYER_0 == dir || PLAYER::PLAYER_2 == dir)
	{
		bodyName = getBodyName(CARD_BODY::UP_S_SHU);
	}
	else
	{
		bodyName = getBodyName(CARD_BODY::UP_S_HENG);
	}
	addBody(bodyName);

	// 桌牌都有花色
	addType(getTypeName(type));

	// 调整位置
	typeSpr->setPositionY(6.0f);
	typeSpr->setRotation(dir * -90.0f);
	typeSpr->setScale(0.4f);
}

void Card::addType(std::string typeName)
{
	if (nullptr == typeSpr)
	{
		typeSpr = Sprite::create(typeName);
		this->addChild(typeSpr);
	}
}

void Card::setSideCardAn(PLAYER dir, int type)
{
	// 牌底
	string bodyName;
	switch (dir)
	{
	case PLAYER_0:
		bodyName = getBodyName(CARD_BODY::BACK_L_DAO);
		break;
	case PLAYER_1:
		bodyName = getBodyName(CARD_BODY::BACK_S_HENG);
		break;
	case PLAYER_2:
		bodyName = getBodyName(CARD_BODY::BACK_S_SHU);
		break;
	case PLAYER_3:
		bodyName = getBodyName(CARD_BODY::BACK_S_HENG);
		break;
	case PLAYER_NULL:
	default:
		bodyName = getBodyName(CARD_BODY::BACK_L_DAO);
		break;
	}
	addBody(bodyName);

	return; // 花色
	addType(getTypeName(type));

	// 调整花色位置
	typeSpr->setPositionY(dir % 2 * 5);
	typeSpr->setScale(0.4f);
}
void Card::setLieCardMing(PLAYER dir, int type)
{
	string bodyName;

	
	
	// 牌底
	if (PLAYER::PLAYER_0 == dir )
	{
		bodyName = getBodyName(CARD_BODY::LIE);
	}
	else if ( PLAYER::PLAYER_2 == dir)
	{
		bodyName = getBodyName(CARD_BODY::UP_S_HENG);
		
	}
	else
	{
		bodyName = getBodyName(CARD_BODY::UP_S_SHU);
	
	}
	addBody(bodyName);
	addType(getTypeName(type));
	

	// 调整位置
	
	typeSpr->setRotation(-90.0f*(dir+1));
	typeSpr->setScale(0.4f);
	if (PLAYER::PLAYER_0 == dir)
	{
		typeSpr->setScale(0.58f);
		typeSpr->setPositionY(11.0f);
	}
	else
	{
		typeSpr->setPositionY(8.0f);
	}
}
void Card::setSideCardMing(PLAYER dir, int type)
{
	if (dir == 0)
	{
		string bodyName = getBodyName(CARD_BODY::UP_L_DAO);
		addBody(bodyName);
		// 牌面
		addType(getTypeName(type));
		typeSpr->setPositionY(10.0f);
		setScale(0.8);
		typeSpr->setScale(0.8);
		return;
	}

	setTableCard(dir, type);
}

//-----------------------------------------------------------------------------------
void Card::cardFadeIn(float fadeInTime, float moveTime, Vec2 playerPos, float scaleTo)
{
	for (Node* card : getChildren())
	{
		card->setOpacity(0);
		card->runAction(FadeIn::create(fadeInTime));
	}
	this->runAction(Sequence::create(
		DelayTime::create(fadeInTime),
		Spawn::create(ScaleTo::create(moveTime, scaleTo), MoveTo::create(moveTime, Vec2(playerPos.x, playerPos.y)), NULL),
		NULL));
}

void Card::cardFadeIn(float delayTime, float fadeInTime, Vec2 playerPos)
{
	this->setVisible(true);
	for (Node* card : getChildren())
	{
		card->setOpacity(0);
		card->runAction(Sequence::create(
		DelayTime::create(delayTime),
		FadeIn::create(fadeInTime),
		NULL));	
	}
	this->runAction(Sequence::create(
		DelayTime::create(delayTime + fadeInTime),
		MoveTo::create(1.0f, Vec2(playerPos.x, playerPos.y + 50)),
		NULL));
}

bool Card::onCardTouchBegan(Touch *touch, Event *event)
{
	CCLOG("Touch+++++++++++++++++++++++++");
	// 得到目标【Card】，但此时还不能检测到【Card】是否被点击
	Card* target = static_cast<Card*>( event->getCurrentTarget() );
	
	// 如果目标【Card】所属的玩家，是被锁住的，则不触发点击事件
	Player* player = (Player*)target->getParent()->getParent()->getParent();
	if (!player->get_CanOpera())
	{
		//CCLOG("----------------CardTouched  Lock --------------------");
		return false;
	}
	//CCLOG("----------------CardTouched--------------------");

	// 检测是否touch到目标Card
	Vec2 touchPos = touch->getLocation();
	Vec2 cardPos = target->getPosition();
	Vec2 location = target->convertToNodeSpace(touchPos);

	Size size = target->bodySpr->getContentSize();
	Rect rect = Rect(-29.5, -42.5, size.width, size.height);
	/*auto type = target->getChildByName("type");
	CCLOG("childBodyName: %s", body->getName().c_str());
	CCLOG("childTypeName: %s", type->getName().c_str());*/
	
	/*CCLOG("Card     Size : %f, %f", size.width, size.height);
	CCLOG("");
	CCLOG("Card     Pos : %f, %f", cardPos.x, cardPos.y);
	CCLOG("");
	CCLOG("Touch Point : %f, %f", touchPos.x, touchPos.y);
	CCLOG("");
	CCLOG("Touch2 Card: %f, %f", location.x, location.y);
	CCLOG("");*/

	if (rect.containsPoint(location))
	{
		//CCLOG("Contains!!!");
		// 如果被点击，则调用玩家进行出牌
		player->playACard(this);
		/*for (auto var:player->drawer->cardInHand)
		{
			var->hidePoint();
		}*/
		return true;
	}
	else
	{
		//CCLOG("not contains!!");
		return false;
	}

	//CCLOG("");
}



void Card::showPoint()
{
	auto point = Sprite::create("location.png");
	point->setScale(0.8f);
	auto pos = convertToWorldSpace(Vec2(getContentSize().width / 2, 15));
	point->setPosition(pos);
	Director::getInstance()->getRunningScene()->getChildByName("gameflow")->addChild(point, 5, "point");
}
void Card::removeFromParentAndCleanup(bool cleanup)
{
	hidePoint();
	Node::removeFromParentAndCleanup(cleanup);
}
void Card::hidePoint()
{
	auto node = Director::getInstance()->getRunningScene()->getChildByName("gameflow")->getChildByName("point");
	if (node)
	{
		node->removeFromParentAndCleanup(1);
	}
}