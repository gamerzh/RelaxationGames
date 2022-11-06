#include "AccountPanel.h"
#include "GameScene.h"
#include "Player.h"
#include "MahjongAnim.h"
#include "Room.h"
#include "MahjongEvent.h"
#include "PayEventMannger.h"
#include "PlayMenu.h"
#include "User.h"
#include "PxPayMannger.h"
#include "ToolTipMannger.h"
#include "HallScene.h"
Vec2 AccountPanel::typePos[4] =
{
	Vec2(400, 60),
	Vec2(720, 240),
	Vec2(400, 420),
	Vec2(50, 240),
};

//------------------------------- Head ---------------------------------
void AccountPanel::Head::setInfo(RESULT result, std::string scoreStr, string name, int photoID,int times, int zhongniaofen)
{
	scheduleOnce([this](float dt){
		auto posTo = this->getPosition();
		auto posFrom = posTo - Vec2(100.0f, .0f);
		this->setPosition(posFrom);
		this->setOpacity(.0f);
		auto move = EaseBackOut::create(MoveTo::create(0.5f, posTo));
		auto act = Spawn::create(move, FadeIn::create(0.5f), NULL);
		this->runAction(act);
	}, id * 0.2f, String::createWithFormat("%d", id)->_string);


	// 输赢logo--------------------------------------------------------------
	Sprite* frame;			// 背景	
	switch (result)
	{
	case HU:
	{
		frame = Sprite::create("Account/headFrame_0.png");
		this->addChild(frame);

		// 头像
		Sprite* headPhoto = Sprite::create("head_" + String::createWithFormat("%d", photoID)->_string + ".png");
		headPhoto->setPositionY(30);
		headPhoto->setScale(0.9f);
		this->addChild(headPhoto);
		break;
	}
	case ZIMO:
	{
		frame = Sprite::create("Account/headFrame_0.png");
		this->addChild(frame);

		// 头像
		Sprite* headPhoto = Sprite::create("head_" + String::createWithFormat("%d", photoID)->_string + ".png");
		headPhoto->setPositionY(30);
		headPhoto->setScale(0.9f);
		this->addChild(headPhoto);

		// 标识
		Sprite* logo = Sprite::create("Account/headLogo_0.png");
		logo->setPosition(-50,74);
		logo->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
		this->addChild(logo);
		break;
	}
	case DIANPAO:
	{
		frame = Sprite::create("Account/headFrame_1.png");
		this->addChild(frame);

		// 头像
		Sprite* headPhoto = Sprite::create("head_" + String::createWithFormat("%d", photoID)->_string + ".png");
		headPhoto->setPositionY(30);
		headPhoto->setScale(0.9f);
		this->addChild(headPhoto);

		// 标识
		Sprite* logo = Sprite::create("Account/headLogo_1.png");
		logo->setPosition(-50, 74);
		logo->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
		this->addChild(logo);
		break;
	}
	case LOSE:
	case NEUTRAL:
	default:
	{
		frame = Sprite::create("Account/headFrame_1.png");
		this->addChild(frame);
		// 头像
		Sprite* headPhoto = Sprite::create("head_" + String::createWithFormat("%d", photoID)->_string + ".png");
		headPhoto->setPositionY(30);
		headPhoto->setScale(0.9f);
		this->addChild(headPhoto);
		break;
	}
	}

	auto namelabel = Label::createWithSystemFont(name, "arial", 8);
	namelabel->setPosition(0, -10);
	namelabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	this->addChild(namelabel);
	// 分数
	auto Tab_Coin = Sprite::create("Account/Tab_Coin.png");
	Tab_Coin->setPosition(35, 61);
	frame->addChild(Tab_Coin);


	int score = Value(scoreStr).asFloat();
	bool isOverBaiWan = score >= 1000000;
	if (isOverBaiWan)
	{
		score /= 1000000;
	}
	string labelStr = (result < 3 ? ":" : ";") + Value(score).asString();
	label = LabelAtlas::create(labelStr, "Account/numScore.png", 6, 9, '0');
	label->setPosition(70,61);
	frame->addChild(label);
	label->setAnchorPoint(Point::ANCHOR_MIDDLE);
	if (isOverBaiWan)
	{
		auto wan = Sprite::create("Account/text_wan.png");
		wan->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		wan->setPosition(label->getPosition() + Vec2(label->getContentSize().width / 2, 0));
			frame->addChild(wan);
	}

	

	//倍数
	auto Tab_Time = Sprite::create("Account/Tab_Times.png");
	Tab_Time->setPosition(35, 40);
	frame->addChild(Tab_Time);
	auto timeLabel = Label::createWithCharMap("Account/numScore.png", 6, 9, '0');
	timeLabel->setString(Value(times).asString());
	timeLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	timeLabel->setPosition(70, 40);
	frame->addChild(timeLabel);



	//鸟数
	auto Tab_ZhuaNiao = Sprite::create("Account/Tab_ZhuaNiao.png");
	Tab_ZhuaNiao->setPosition(35, 19);
	frame->addChild(Tab_ZhuaNiao);
	auto ZhuaNiaoLabel = Label::createWithCharMap("Account/numScore.png", 6, 9, '0');
	ZhuaNiaoLabel->setString(Value(zhongniaofen).asString());
	ZhuaNiaoLabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	ZhuaNiaoLabel->setPosition(70, 19);
	frame->addChild(ZhuaNiaoLabel);
}

bool AccountPanel::Head::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}

float addX2World(Node*node,char* sign,int n)
{
	auto x2 = LabelAtlas::create(std::string(sign)+Value(n).asString(), "Account/fnt_result.png", 11, 18, '0');
	x2->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	x2->setPosition(node->getContentSize().width, node->getContentSize().height / 2);
	node->addChild(x2);

	return x2->getContentSize().width;
}

//------------------------------- Panel --------------------------------
bool AccountPanel::init()
{
	if (!Node::init())
	{
		return false;
	}

	this->setVisible(true);
	Vec2 center = _director->getWinSize() / 2;

	// 四个头像,113 * 150
	float dis = 20;
	float width = 113;
	Vec2 pos = Vec2(center.x - (width + dis) * 1.5, 230);

	CCLOG("AccountPanel : init");
	panel = Node::create();
	panel->setVisible(false);
	this->addChild(panel);

	// 背景模糊
	Sprite* bigBkg = Sprite::create("Account/accountBkg.jpg");
	bigBkg->setPosition(center);
	panel->addChild(bigBkg);

	Sprite* playerInfoFrame = Sprite::create("Account/playerInfoFrame.png");
	playerInfoFrame->setPosition(center.x, pos.y);
	panel->addChild(playerInfoFrame);
	playerInfoFrame->setScaleY(1.2f);
	Sprite* bigCoinSprite = Sprite::create("Account/coinBig.png");
	bigCoinSprite->setPosition(Vec2(center.x - 70.0f, 345.0f));
	panel->addChild(bigCoinSprite);

	for (int i = 0; i < 4; i++)
	{
		heads[i] = nullptr;
		heads[i] = Head::create();
		heads[i]->id = i;
		panel->addChild(heads[i]);
		heads[i]->setPosition(pos.x + (dis + width) * i, pos.y);
	}

	// 两个按钮
	MenuItemImage* backItem = MenuItemImage::create("Account/button_back_0.png", "Account/button_back_1.png", CC_CALLBACK_1(AccountPanel::backCallBack, this));
	backItem->setPosition(-100, -130.0f);
	MenuItemImage* againItem = MenuItemImage::create("Account/button_again_0.png", "Account/button_again_1.png", CC_CALLBACK_1(AccountPanel::againCallBack, this));
	againItem->setPosition(100, -130.0f);
	Menu* menu = Menu::create(backItem, againItem, NULL);
	panel->addChild(menu);

	wordBig = Node::create();
	wordBig->setVisible(false);
	wordBig->setPosition(400.0f, 305.0f);
	this->addChild(wordBig);
	string path = "Account/";
	wordBigFrame = addAnimNoAnimte(*wordBig, path, "WordBig_Frame");
	wordBigDaDiaoChe = addAnimNoAnimte(*wordBig, path, "WordBig_DiaoChe");
	wordBigPengPengHu = addAnimNoAnimte(*wordBig, path, "WordBig_PengPengHu");
	wordBigQingYiSe = addAnimNoAnimte(*wordBig, path, "WordBig_QingYiSe");
	wordBigMenQing = addAnimNoAnimte(*wordBig, path, "WordBig_MenQing");

	wordNode = Node::create();
	wordNode->setPosition(Vec2(320.0f, 55.0f));
	wordNode->setVisible(false);
	this->addChild(wordNode);

	// 牌型信息，杠开，大吊车，碰碰胡，清一色
	wordGangKai = addAnimNoAnimte(*wordNode, path, "Word_GangKai");
	wordGangKai->setVisible(false);

	wordDaDiaoChe = addAnimNoAnimte(*wordNode, path, "Word_DiaoChe");
	wordDaDiaoChe->setVisible(false);

	wordMenQing = addAnimNoAnimte(*wordNode, path, "Word_MenQing");
	wordMenQing->setVisible(false);

	wordPengPengHu = addAnimNoAnimte(*wordNode, path, "Word_PengPengHu");
	wordPengPengHu->setVisible(false);

	wordQingYiSe = addAnimNoAnimte(*wordNode, path, "Word_QingYiSe");
	wordQingYiSe->setVisible(false);

	
	



	////　中鸟分
	wordZhongNiaoFen = addAnimNoAnimte(*wordNode, path, "Word_ZhongNiao");
	wordZhongNiaoFen->setVisible(false);

	wordBeishu = addAnimNoAnimte(*wordNode, path, "Word_Beishu");
	wordBeishu->setVisible(false);
	//wordKuoHaoL = addAnimNoAnimte(*wordNode, path, "Word_KuoHao"); 
	//wordKuoHaoL->setVisible(false);
	//wordKuoHaoL->setPositionX(50.0f);

	//wordNiaoShu = addAnimNoAnimte(*wordNode, path, "Word_NiaoShu");
	//wordNiaoShu->setVisible(false);


	wordDiFen = addAnimNoAnimte(*wordNode, path, "Word_DiFen");
	wordDiFen->setVisible(false);
	wordDiFen->setPosition(57.0f, 20.0f);

	//wordKuoHaoR = addAnimNoAnimte(*wordNode, path, "Word_KuoHao");
	//wordKuoHaoR->setVisible(false);
	//wordKuoHaoR->setRotation(180.0f);
	//wordKuoHaoR->setPositionX(185.f);
	//

	return true;
}

/*
win :

lose :
jiangyou :
liuju:

*/

bool AccountPanel::showWord(bool isShow, Node & node, Vec2 pos)
{
	if (isShow)
	{
		auto act = Spawn::create(ScaleTo::create(0.2f, 1.0f), FadeIn::create(0.2f), NULL);
		node.setScale(3.0f);
		node.setVisible(true);
		node.setPosition(pos);
		node.setOpacity(.0f);
		node.runAction(act);
		return true;
	}
	else
	{
		node.setVisible(false);
		return false;
	}
}

void AccountPanel::showBigAccountInfo(Player & player)
{
	GangKai = player.get_GangKai();
	DaDiaoChe = player.get_DaDiaoChe();
	PengPengHu = player.get_PengPengHu();
	QingYiSe = player.get_QingYiSe();
	MenQing = !DaDiaoChe;
	this->player = &player;
	wordBig->setVisible(true);

	int infoNum = 3;
	infoNum -= DaDiaoChe ? 1 : 0;
	infoNum -= PengPengHu ? 1 : 0;
	infoNum -= QingYiSe ? 1 : 0;
	infoNum -= MenQing ? 1 : 0;
	float startPosX = -70 + 35.0f * infoNum;
	float startPosY = wordBig->getPositionY();
	int index = 0;
	float width = 70.0f;
	if (showWord(DaDiaoChe, *wordBigDaDiaoChe, Vec2(startPosX + index * width, .0f))) { index++; }
	if (showWord(MenQing, *wordBigMenQing, Vec2(startPosX + index * width, .0f))) { index++; }
	if (showWord(PengPengHu, *wordBigPengPengHu, Vec2(startPosX + index * width, .0f))) { index++; }
	if (showWord(QingYiSe, *wordBigQingYiSe, Vec2(startPosX + index * width, .0f))) { index++; }
	if (showWord(GangKai, *wordGangKai, Vec2(startPosX + index * width, .0f))) { index++; }
	scheduleOnce([this](float dt){
		this->wordBig->setVisible(false);
	}, 3.0f, "hideBigWord");
}

void AccountPanel::showAccountInfo(int niaoNum,int beishu)
{
	CCLOG("AccountPanel::showAccountInfo(%d,%d)", niaoNum, beishu);
	panel->setVisible(true);
	if (-1 == niaoNum)
	{
		return;
	}
	int score = Room::getInstance()->getRoomScore();
	wordNode->setVisible(true);
	int infoNum = 3;
	infoNum -= GangKai ? 1 : 0;
	infoNum -= DaDiaoChe ? 1 : 0;
	infoNum -= PengPengHu ? 1 : 0;
	infoNum -= QingYiSe ? 1 : 0;
	float difwidth = 85;
	float startPosX = -70+40.0 * infoNum;
	int index = 0;
	//

	//wordBeishu->setVisible(true);
	//wordBeishu->setPositionX(startPosX);
	//addX2World(wordBeishu,":",beishu);
	//startPosX +=difwidth;
	//wordZhongNiaoFen->setVisible(true);
	//wordZhongNiaoFen->setPositionX(startPosX);
	//addX2World(wordZhongNiaoFen, ":",niaoNum);
	//startPosX += difwidth;
	if (GangKai)
	{
		wordGangKai->setVisible(true);
		wordGangKai->setPositionX(startPosX);
		startPosX += difwidth;
		addX2World(wordGangKai, ":",2);
		index++;
	}

	if (DaDiaoChe)
	{
		wordDaDiaoChe->setVisible(true);
		wordDaDiaoChe->setPositionX(startPosX );
		startPosX += difwidth;
		addX2World(wordDaDiaoChe, ":", 2);
		index++;
	}
	else
	{
		wordMenQing->setVisible(true);
		wordMenQing->setPositionX(startPosX);
		startPosX += difwidth;
		addX2World(wordMenQing, ":", 2);
		index++;
	}
	if (PengPengHu)
	{
		wordPengPengHu->setVisible(true);
		wordPengPengHu->setPositionX(startPosX );
		startPosX += difwidth;
		addX2World(wordPengPengHu, ":", 2);
		index++;
	}
	if (QingYiSe)
	{
		wordQingYiSe->setVisible(true);
		wordQingYiSe->setPositionX(startPosX );
		startPosX += difwidth;
		addX2World(wordQingYiSe, ":", 2);
		index++;
	}

	//

	//wordKuoHaoL->setVisible(true);
	//wordNiaoShu->setVisible(true);
	//wordKuoHaoR->setVisible(true);
	wordDiFen->setVisible(true);

	//string numNiaoStr = String::createWithFormat("%d:", niaoNum)->_string;
	//Label* numNiaoLabel = Label::createWithCharMap("Account/numZhongNiao.png", 11, 15, '0');
	//numNiaoLabel->setString(numNiaoStr);
	//numNiaoLabel->setPositionX(96.0f);
	//wordNode->addChild(numNiaoLabel);

	int diFen = Room::getInstance()->getRoomScore();
	string diFenStr = String::createWithFormat("%d", diFen)->_string;
	Label* diFenLabel = Label::createWithCharMap("Account/numZhongNiao.png", 11, 15, '0');
	diFenLabel->setString(diFenStr);
	diFenLabel->setPosition(102.0f, 20.0f);
	wordNode->addChild(diFenLabel);

	if (beishu == -1)
	{
		return;
	}
	//// 胡牌牌型
	Vector<Card*> cards;
	int cardNum = 0;

	for (Card* card : player->drawer->cardInHand)
	{
		auto newCard = Card::createTableCard(PLAYER_0, card->get_type());
		cards.pushBack(newCard);
		wordNode->addChild(newCard);
		newCard->setPositionY(-45.0f);
		cardNum++;
	}

	for (Card* card : player->drawer->cardInSide)
	{
		auto newCard = Card::createTableCard(PLAYER_0, card->get_type());
		cards.pushBack(newCard);
		wordNode->addChild(newCard);
		newCard->setPositionY(-45.0f);
		cardNum++;
	}
	startPosX = 80 - cardNum*14.0f;
	for (Card* card : cards)
	{
		card->setPositionX(--cardNum * 29.0f + startPosX);
	}


	
}

void AccountPanel::getInfoFromPlayer(Player & player)
{
	CCLOG("---------- Account : get Player[%d] info -----------", player.drawer->get_dir());
	int score = abs(player.get_Score());
	string scoreStr = String::createWithFormat("%d", score)->_string;
	auto result = player.get_Result();

	// 获得头像信息
	int headIndex = player.drawer->get_dir();
	if (nullptr != heads[headIndex])
	{
		heads[headIndex]->setInfo(result, scoreStr, Room::getInstance()->getName(headIndex), Room::getInstance()->getPlayerHead(headIndex),Room::getInstance()->getRoomTimes(headIndex),player.get_NiaoNum());
	}

	// 如果是主角，则获得主角本局信息。
	if (0 == player.drawer->get_dir())
	{
		Label* label;
		switch (result)
		{
		case HU:
		case ZIMO:
		{
			MahjongAnim::getInstance()->playWinBanner();
			label = Label::createWithCharMap("Account/numBigWin.png", 34, 42, '0');
			label->setString(scoreStr);
			label->setAdditionalKerning(-3.0f);
			label->setPosition(450.0f, 350.0f);
			label->setAnchorPoint(Vec2(0.5f, 0.5f));
			this->addChild(label);
			break;
		}
		case DIANPAO:
		case LOSE:
		{
			label = Label::createWithCharMap("Account/numBigLose.png", 34, 42, '0');
			label->setString(scoreStr);
			label->setAdditionalKerning(-3.0f);
			label->setPosition(450.0f, 350.0f);
			label->setAnchorPoint(Vec2(0.5f, 0.5f));
			this->addChild(label);

			Sprite* logoSprite = Sprite::create("Account/logo_lose.png");
			logoSprite->setPosition(400, 410);
			this->addChild(logoSprite);

			break;
		}
		case NEUTRAL:
			Sprite* logoSprite = Sprite::create("Account/logo_jiangYou.png");
			logoSprite->setPosition(400, 410);
			this->addChild(logoSprite);
			break;
		}

	}
}

void AccountPanel::getAccountInfo()
{

}

void AccountPanel::backCallBack(Ref* pSender)
{
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);

	MahjongAnim::getInstance()->hideWinBanner();
	this->setVisible(false);
	_director->replaceScene(HallScene::createScene());
}

void AccountPanel::againCallBack(Ref* pSender)
{
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);
	MahjongAnim::getInstance()->hideWinBanner();
	auto instance = MahjongAnim::getInstance();
	instance->removeFromParentAndCleanup(true);

	if (User::getInstance()->getMyCoins()>= Room::getInstance()->getRoomMinScore(Room::getInstance()->getRoomType()))
	{
		auto scene = GameScene::createScene();
		_director->replaceScene(scene);
		auto node = scene->getChildByName("gameflow")->getChildByName("PlayMenu");
		((PlayMenu*)node)->dealBtnCallBack(nullptr);
	}
	else
	{
		auto dg = ToolTipMannger::showDioag(this->getParent(), ToolTipMannger::TipType::Tip_LackingCoinOther);
		dg->setSureButtonCallback([=](Ref*psend){
			const std::function<void(EventCustom*)>& callback = [=](EventCustom*event){
				PayResult*reslt = (PayResult*)(event->getUserData());
				if (*reslt == Pay_Success)
				{

				}
				else
				{
					auto scene = HallScene::createScene();
					_director->replaceScene(scene);
				}
				Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(event->getEventName());
			};
			PxPayMannger::getInstance()->LaughPayLayer(COINGIFT, this->getParent(), callback);
		});
	}
	
}

void AccountPanel::showPayPoint(bool isUsePickGood, bool isWin)
{
	//int min = Room::getInstance()->getRoomMinScore(1);
	//int nextmin = Room::getInstance()->getRoomNextScore();
	//int score = User::getInstance()->getMyCoins();
	//bool isGainAlms = Room::getInstance()->isGainAlms;
	//Room::getInstance()->isGainAlms = false;
	//bool isDelevel = (score < min);
	//bool isCouldUpdate = (score > nextmin);
	///// 5 7 8 11 12 14 15
	//auto mannger = PayEventMannger::getInstance();
	//auto pay = PxPayMannger::getInstance();

	//mannger->RecordInfoOnGameend(isDelevel, isGainAlms, isWin, isCouldUpdate);
	//if (mannger->isSatisfied_Event_5(isUsePickGood))
	//{
	//	pay->LaughPayLayer(5, this);
	//}
	//if (mannger->isSatisfied_Event_7())
	//{
	//	pay->LaughPayLayer(7, this);
	//}
	//if (mannger->isSatisfied_Event_8(isUsePickGood) && isWin)
	//{
	//	pay->LaughPayLayer(8, this);
	//}
	//if (mannger->isSatisfied_Event_11())
	//{
	//	pay->LaughPayLayer(11, this);
	//}
	//if (mannger->isSatisfied_Event_12())
	//{
	//	pay->LaughPayLayer(12, this);
	//}
	//if (mannger->isSatisfied_Event_14())
	//{
	//	pay->LaughPayLayer(14, this);
	//}
	//if (mannger->isSatisfied_Event_15())
	//{
	//	pay->LaughPayLayer(15, this);
	//}
	//if (isDelevel)
	//{
	//	pay->LaughPayLayer(10, this);
	//}

}







