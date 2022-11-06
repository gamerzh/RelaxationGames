#include "PlayMenu.h"
#include "Room.h"
#include "Rules.h"
#include "MahjongEvent.h"
#include "AddCoinPanel.h"
#include "MahjongAnim.h"
#include "MahjongDatas.h"
#include "PxPayMannger.h"
bool PlayMenu::init()
{
	Menu* menu = Menu::create();

	// 碰杠胡的按钮
	Size size = Director::getInstance()->getWinSize();

	peng = MenuItemImage::create("menu_peng.png", "menu_peng.png", CC_CALLBACK_1(PlayMenu::pengCallback, this));
	peng->setPosition(130, -150);
	peng->setVisible(false);
	
	gang = MenuItemImage::create("menu_gang.png", "menu_gang.png", CC_CALLBACK_1(PlayMenu::gangCallback, this));
	gang->setPosition(130, -150);
	gang->setVisible(false);

	hu = MenuItemImage::create("menu_hu.png", "menu_hu.png", CC_CALLBACK_1(PlayMenu::ziMoCallback, this));
	hu->setPosition(130, -150);
	hu->setVisible(false);

	qi = MenuItemImage::create("menu_qi.png", "menu_qi.png", CC_CALLBACK_1(PlayMenu::qiPengCallback, this));
	qi->setPosition(330, -150);
	qi->setVisible(false);
	
	menu->addChild(peng);
	menu->addChild(gang);
	menu->addChild(hu);
	menu->addChild(qi);
	//menu->setPosition(size.width/2, size.height/2);

	
	MenuItemImage* pickBtn = MenuItemImage::create("System_UI/Btn_start_1.png", "System_UI/Btn_start_2.png", CC_CALLBACK_1(PlayMenu::dealBtnCallBack, this));
	pickBtn->setPosition(0, -110);
	menu->addChild(pickBtn);

	//MenuItemImage* pickGoodBtnLight = MenuItemImage::create("pickGoodBtn_light.png", "pickGoodBtn_light.png");
	//pickGoodBtnLight->setPosition(100, -110);
	//menu->addChild(pickGoodBtnLight);

	//pickGoodBtnLight->runAction(RepeatForever::create(Sequence::create(FadeIn::create(0.5f), FadeOut::create(0.5f), NULL)));
	//MenuItemImage* pickGoodBtn = MenuItemImage::create("pickGoodBtn_0.png", "pickGoodBtn_1.png", CC_CALLBACK_1(PlayMenu::dealGoodBtnCallBack, this));
	//pickGoodBtn->setPosition(100, -110);
	//menu->addChild(pickGoodBtn);
	this->addChild(menu);

	//Label* pickGoodTimesLabel = Label::createWithCharMap("coins_num.png", 11, 14, '0');
	//int goodTimes = UserDefault::getInstance()->getIntegerForKey("goodTimes", 3);
	//if (goodTimes != 0)
	//{
	//	pickGoodTimesLabel->setString(String::createWithFormat("%d", goodTimes)->_string);
	//	pickGoodTimesLabel->setPosition(563.0f, 150.0f);
	//	pickGoodTimesLabel->setOpacity(160.0f);
	//}
	//this->addChild(pickGoodTimesLabel);

	// 房间底分和倍数
	roomInfoNode = Node::create();
	roomInfoNode->setPosition(10.0f, .0f);
	this->addChild(roomInfoNode);

	Sprite* bkg = Sprite::create("score_frame.png");
	bkg->setPosition(100.0f, 450.0f);
	roomInfoNode->addChild(bkg);

	Sprite* score = Sprite::create("score_room.png");
	score->setPosition(75.0f, 440);
	roomInfoNode->addChild(score);



	int roomScore = Room::getInstance()->getRoomScore();
	string roomScoreStr = String::createWithFormat("%d", roomScore)->_string;
	label = LabelAtlas::create(roomScoreStr, "score_num.png", 14, 18, '0');
	label->setAnchorPoint(Vec2(0.5f, 0.5f));
	label->setPosition(120.0f, 440);
	roomInfoNode->addChild(label);

	int roomtype = Room::getInstance()->getRoomType();
	auto path = String::createWithFormat("Tab_ROOM_%d.png", roomtype);
	Sprite* Tab_room = Sprite::create(path->getCString());
	Tab_room->setPosition(80, 464);
	roomInfoNode->addChild(Tab_room);

	roomInfoNode->setVisible(true);


	
	return true;
}

void PlayMenu::getInfo(int newCoins, int newTimes)
{
	CCLOG("update Room DiFen & Times");
	string str = String::createWithFormat("%d", newCoins)->_string;
	label->setString(str);
	//labelTimes->setString(String::createWithFormat("%d",newTimes)->_string);
	//labelTimes->setVisible(false);
	roomInfoNode->setVisible(true);
	hideBack();

}

// 显示碰杠胡的按钮
void PlayMenu::ShowPengButton()
{
	peng->setVisible(true);
	
	qi->setCallback(CC_CALLBACK_1(PlayMenu::qiPengCallback, this));
	qi->setVisible(true);
}

void PlayMenu::ShowAnGangButton()
{
	gang->setVisible(true);
	gang->setCallback(CC_CALLBACK_1(PlayMenu::anGangCallback, this));

	qi->setCallback(CC_CALLBACK_1(PlayMenu::qiAnGangCallback, this));
	qi->setVisible(true);
}

void PlayMenu::ShowPengGangButton()
{
	//controler->currentPlayer = player;
	gang->setVisible(true);
	gang->setCallback(CC_CALLBACK_1(PlayMenu::pengGangCallback, this));

	qi->setCallback(CC_CALLBACK_1(PlayMenu::qiPengGangCallback, this));
	qi->setVisible(true);
}



void PlayMenu::ShowPengAndGang()
{
	//controler->currentPlayer = player;
	peng->setVisible(true);
	peng->setPositionX(-70);

	gang->setCallback(CC_CALLBACK_1(PlayMenu::gangCallback, this));
	gang->setVisible(true);

	qi->setCallback(CC_CALLBACK_1(PlayMenu::qiPengCallback, this));
	qi->setVisible(true);
}

void PlayMenu::ShowZiMoButton()
{
	hu->setVisible(true);	// 
	hu->setCallback(CC_CALLBACK_1(PlayMenu::ziMoCallback, this));

	qi->setVisible(true);
	qi->setCallback(CC_CALLBACK_1(PlayMenu::qiZiMoHuCallback, this));
}

void PlayMenu::ShowDianPaoButton()
{
	hu->setVisible(true);	// hu
	hu->setCallback(CC_CALLBACK_1(PlayMenu::dianPaoCallback, this));

	qi->setVisible(true);
	qi->setCallback(CC_CALLBACK_1(PlayMenu::qiDianPaoCallback, this));
}
void PlayMenu::ShowDianPaoAndPengButton()
{
	peng->setVisible(true);
	peng->setPositionX(-70);
	peng->setCallback([=](Ref*psend){
	
		player->set_canHu(false);
		Rules::getInstance()->canHuNum--;
		pengCallback(psend);
	});

	hu->setVisible(true);	// hu
	hu->setCallback(CC_CALLBACK_1(PlayMenu::dianPaoCallback, this));

	qi->setVisible(true);
	qi->setCallback(CC_CALLBACK_1(PlayMenu::qiDianPaoCallback, this));
}
void PlayMenu::ShowQiangGangButton()
{
	hu->setVisible(true);
	hu->setCallback(CC_CALLBACK_1(PlayMenu::qiangGangCallback, this));

	qi->setVisible(true);
	qi->setCallback(CC_CALLBACK_1(PlayMenu::qiQiangGangCallback, this));
}


void PlayMenu::hide()
{
	peng->setVisible(false);
	peng->setPositionX(130);

	gang->setVisible(false);
	hu->setVisible(false);
	qi->setVisible(false);
}


//-------------------------------------- 发牌回调 ------------------------------------------
void PlayMenu::dealGoodBtnCallBack(Ref* pSender)
{
	CCLOG("");
	CCLOG("-----------------------");
	CCLOG("- Btn : Deal Good");
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);

	int times = UserDefault::getInstance()->getIntegerForKey("goodTimes", 3);
	MahjongDatas::getInstance()->goodCardTimes = times;
	if (0 < MahjongDatas::getInstance()->goodCardTimes)
	{
		player->set_isPickGood(true);
		UserDefault::getInstance()->setIntegerForKey("goodTimes", times - 1);
	}
	else
	{
	/*	PxPayMannger::getInstance()->LaughPayLayer(6, this->getParent());*/
		return;
	}

	auto s = getChildren();
	s.at(0)->getChildren().at(4)->setVisible(false);
	s.at(0)->getChildren().at(5)->setVisible(false);
	s.at(0)->getChildren().at(6)->setVisible(false);
	s.at(1)->setVisible(false);

	this->getParent()->addChild(ChooseTimesPanel::create());
}
void PlayMenu::dealBtnCallBack(Ref* pSender)
{
	CCLOG("");
	CCLOG("-----------------------");
	CCLOG("- Btn : Deal");
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);

	auto s = getChildren();
	s.at(0)->getChildren().at(4)->setVisible(false);
	///*s.at(0)->getChildren().at(5)->setVisible(false);*/
	////s.at(0)->getChildren().at(6)->setVisible(false);
	//s.at(1)->setVisible(false);
	this->getParent()->addChild(ChooseTimesPanel::create(),30);
}

//-------------------------------------- 碰杠胡回调 ------------------------------------------
void PlayMenu::pengCallback(Ref* pSender)		// 喷
{
	CCLOG("- Btn : peng");
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);

	hide();
	player->peng();

}
void PlayMenu::qiPengCallback(Ref* pSender)
{
	CCLOG("- Btn : qiPeng");
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);

	hide();
	dispatchMahjongEvent(QI_RETURN_BEFORE, NULL);
}

void PlayMenu::gangCallback(Ref* pSender)		// 杠
{
	CCLOG("- Btn : gang");
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);

	hide();
	player->gang();
}

void PlayMenu::pengGangCallback(Ref* pSender)
{
	CCLOG("- Btn : gang");
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);

	hide();
	player->pengGang();
}
void PlayMenu::qiPengGangCallback(Ref* pSender)
{
	CCLOG("- Btn : qiGang");
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);
	player->operaPlay();
}

void PlayMenu::anGangCallback(Ref* pSender)	// 暗杠
{
	CCLOG("- Btn : kaiGang");
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);

	hide();
	player->kaiGang(false);
	player->goOnOperaPick();
}
void PlayMenu::qiAnGangCallback(Ref* pSender)
{
	CCLOG("- Btn : qiAnGang");
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);

	hide();
	player->operaPlay();
}


void PlayMenu::ziMoCallback(Ref* pSender)		// 自摸
{
	CCLOG("- Btn : Hu");
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);

	hide();
	player->ziMo();
}
void PlayMenu::qiZiMoHuCallback(Ref* pSender)
{
	CCLOG("- Btn : qiZiMo");
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);

	hide();
	dispatchMahjongEvent(FLOW_NAME::OPERA_ZIMO_END, NULL);
}

void PlayMenu::dianPaoCallback(Ref* pSender)	// 点炮
{
	CCLOG("- Btn : DianPao");
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);


	hide();
	player->dianPao();
}
void PlayMenu::qiDianPaoCallback(Ref* pSender)
{
	CCLOG("- Btn : qiDianPao");
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);

	hide();
	player->set_canHu(false);
	dispatchMahjongEvent(OPERA_DIANPAO_END, NULL);
}


void PlayMenu::qiangGangCallback(Ref* pSender)
{
	CCLOG("- Btn : QiangGang");
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);


	hide();
	player->qiangGang();
}

void PlayMenu::qiQiangGangCallback(Ref* pSender)
{
	CCLOG("- Btn : qiQiangGang");
	MahjongAnim::getInstance()->playSound(SOUND::BUTTONDOWN);

	hide();
	player->set_canHu(false);
	dispatchMahjongEvent(OPERA_QIANGGANG_END, NULL);
}

void PlayMenu::getPlayer(Player* const player)
{
	this->player = player;
}
