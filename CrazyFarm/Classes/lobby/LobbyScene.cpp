#include "lobby/LobbyScene.h"
#include "core/GameScene.h"
#include "utill/Chinese.h"
#include "utill/AnimationUtil.h"
#include "domain/user/User.h"
#include "fish/FishRouteData.h"
#include "lobby/bag/bagLayer.h"
#include "fish/FishAniMannage.h"
#include "fish/FishGroupData.h"
#include "server/HttpClientUtill.h"
#include "data/GameData.h"
#include "config/ConfigManager.h"
#include "config/ConfigSign.h"
#include "signlayer/SignInLayer.h"
#include "utill/Toast.h"
#include "viplayer/VipLayer.h"
#include "lobby/shop/paylayer.h"
#include "utill/dayUtil.h"
#include "lobby/ScrollText.h"
#include "lobby/Nobility/NobilityLayer.h"
#include "core/SettingDialog.h"
#include "domain/marquee/MarqueeManager.h"
#include "utill/FunUtil.h"
#include "domain/ranklist/RanklistLayer.h"
#include "utill/Audio.h"
#include "lobby/FeedbackLayer.h"
#include "lobby/FirstPayLayer.h"
#include "lobby/roomlayer/RoomLayer.h"
#include "lobby/FeedbackLayer.h"
#include "domain/ToolTip/TwiceSureDialog.h"
#include "widget/LightEffect.h"
#include "domain/bankrupt/BankruptManager.h"
#include "core/GetRewardNode.h"
#include "lobby/changeGift/ChangeGiftLayer.h"
#include "domain/Newbie/NewbieMannger.h"
#include "domain/Newbie/NewbieFirstGetRewardLayer.h"
#include "domain/logevent/LogEventMannger.h"
#include "utill/JniFunUtill.h"
#include "lobby/viplayer/VipGainCoinSureDialog.h"
#include "utill/CircleMoveTo.h"
#include "domain/pay/WaitCircle.h"
#include "domain/loading/LoadingSceneLbToGm.h"
#include "lobby/signlayer/SignMannger.h"
#include "widget/MyLabelAtlas.h"
const Vec2 roomPos[5] = { Vec2(-300, 300), Vec2(212, 300), Vec2(500, 300), Vec2(788, 300), Vec2(960 + 300, 300) };

roomCell * roomCell::createCell(const std::string& normalImage, const std::string& selectedImage, const ccMenuCallback& callback)
{
	roomCell *ret = new (std::nothrow) roomCell();
	if (ret && ret->initWithNormalImage(normalImage, selectedImage, "", callback))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}


Scene* LobbyScene::createScene()
{
	auto scene = Scene::create();

	auto layer = LobbyScene::create();

	scene->addChild(layer, 0, 888);

	return scene;
}

bool LobbyScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto user = User::getInstance();
	auto leveldata = user->getLevelData();

	Audio::getInstance()->playBGM(LOBBYBGM);


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* lobby_bg = Sprite::create("lobbyBG.jpg");
	lobby_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(lobby_bg, -1);
	lobby_bg->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(2.25f, 1.02), ScaleTo::create(2.25f, 1), nullptr)));


	//头像框
	auto spHeadFrame = Sprite::create("HeadFrame.png");
	spHeadFrame->setPosition(visibleSize.width*0.05, visibleSize.height*0.94);
	addChild(spHeadFrame, 1, "spHeadFrame");


	auto spHead = Sprite::create();
	int sex = user->getUserGender();
	if (sex)
	{
		spHead->setTexture("headWomen.png");
	}
	else
	{
		spHead->setTexture("headMan.png");
	}
	spHead->setPosition(23, 30);
	spHeadFrame->addChild(spHead);


	auto userFrame = Sprite::create("coinFrame.png");
	userFrame->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	userFrame->setPosition(spHeadFrame->getPositionX(), spHeadFrame->getPositionY());
	addChild(userFrame);
	auto sssize = userFrame->getContentSize();

	userName = LabelTTF::create(user->getUserName(), "arial", 20);
	userName->setAnchorPoint(Point::ANCHOR_MIDDLE);
	userName->setPosition(sssize.width*0.5, sssize.height*0.5);
	userFrame->addChild(userName);


	auto viplevelFrame = Sprite::create("viplevelFrame.png");
	viplevelFrame->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	viplevelFrame->setPosition(sssize.width * 1, sssize.height*0.5);
	viplevel = LabelAtlas::create(Value(user->getVipLevel()).asString().c_str(), "vipLevelNum.png", 11, 16, '0');
	viplevel->setAnchorPoint(Point::ANCHOR_MIDDLE);
	viplevel->setPosition(Vec2(viplevelFrame->getContentSize() / 2));
	viplevelFrame->addChild(viplevel);
	userFrame->addChild(viplevelFrame);


	//金币
	auto coinFrame = Sprite::create("coinFrame.png");
	coinFrame->setPosition(visibleSize.width*0.39, visibleSize.height*0.94);
	addChild(coinFrame);
	sssize = coinFrame->getContentSize();
	auto coin = Sprite::create("coin.png");
	coin->setAnchorPoint(Point::ANCHOR_MIDDLE);
	coin->setPosition(5, sssize.height *0.5);
	coinFrame->addChild(coin);

	userCoin = LabelTTF::create(Value(user->getCoins()).asString().c_str(), "arial", 20);
	userCoin->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	userCoin->setPosition(sssize.width*0.83, sssize.height *0.5);
	userCoin->setColor(Color3B(254, 248, 52));
	coinFrame->addChild(userCoin);

	auto addCoin = MenuItemImage::create("addBtn_nor.png", "addBtn_click.png", CC_CALLBACK_1(LobbyScene::payCoinCallback, this));
	addCoin->setAnchorPoint(Point::ANCHOR_MIDDLE);
	addCoin->setPosition(coinFrame->getPositionX() + sssize.width*0.48, coinFrame->getPositionY());

	auto effect = LightEffect::create();
	effect->setPosition(0, 0);
	coin->addChild(effect);
	//钻石
	auto diamondFrame = Sprite::create("coinFrame.png");
	diamondFrame->setPosition(visibleSize.width*0.64, visibleSize.height*0.94);
	addChild(diamondFrame);
	sssize = diamondFrame->getContentSize();
	auto diamond = Sprite::create("diamond1.png");
	diamond->setAnchorPoint(Point::ANCHOR_MIDDLE);
	diamond->setPosition(5, sssize.height *0.5 + 2);
	diamondFrame->addChild(diamond);

	userdiamond = LabelTTF::create(Value(user->getDiamonds()).asString().c_str(), "arial", 20);
	userdiamond->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	userdiamond->setPosition(sssize.width*0.83, sssize.height *0.5);
	userdiamond->setColor(Color3B(254, 248, 52));
	diamondFrame->addChild(userdiamond);

	auto adddiamond = MenuItemImage::create("addBtn_nor.png", "addBtn_click.png", CC_CALLBACK_1(LobbyScene::payDiamondCallback, this));
	adddiamond->setAnchorPoint(Point::ANCHOR_MIDDLE);
	adddiamond->setPosition(diamondFrame->getPositionX() + sssize.width*0.48, diamondFrame->getPositionY());

	effect = LightEffect::create();
	effect->setPosition(0, 0);
	diamond->addChild(effect);





	MarqueeManager::getInstance()->init();

	//背包
	auto bag = MenuItemImage::create("bag.png", "bag.png", CC_CALLBACK_1(LobbyScene::bagButtonCallback, this));
	bag->setPosition(visibleSize.width*0.27, visibleSize.height*0.10);
	bag->setName("bag");
	//换奖品
	auto changeReward = MenuItemImage::create("changeReward.png", "changeReward.png", CC_CALLBACK_1(LobbyScene::changeRewardCallback, this));
	changeReward->setPosition(visibleSize.width*0.17, visibleSize.height*0.10);

	auto rankList = MenuItemImage::create("ranklist.png", "ranklist.png", CC_CALLBACK_1(LobbyScene::RankListCallback, this));
	rankList->setPosition(visibleSize.width*0.07, visibleSize.height*0.10);


	auto VIP = MenuItemImage::create("VIP.png", "VIP.png", CC_CALLBACK_1(LobbyScene::showVipCallBack, this));
	VIP->setPosition(visibleSize.width*0.044, visibleSize.height*0.77);

	auto sp = Sprite::create();
	sp->setPosition(VIP->getContentSize() / 2);
	VIP->addChild(sp);
	auto lightsp = Sprite::create();
	lightsp->setPosition(22, 39);
	VIP->addChild(lightsp, 1);

	scheduleOnce([=](float interval)
	{
		sp->runAction(getForeverAcByNameAndInterval("aniVipButton", 2.0));
		lightsp->runAction(getForeverAcByNameAndInterval("aniLightPoint", 2.0));

	}, 0.7f, "11");


	auto guizu = MenuItemImage::create("guizu.png", "guizu.png", CC_CALLBACK_1(LobbyScene::guizuCallback, this));
	guizu->setPosition(visibleSize.width*0.044, visibleSize.height*0.62);


	auto sp1 = Sprite::create();
	sp1->setPosition(guizu->getContentSize() / 2);
	guizu->addChild(sp1);
	auto 	lightsp1 = Sprite::create();

	lightsp1->setPosition(22, 39);
	guizu->addChild(lightsp1, 1);
	scheduleOnce([=](float interval)
	{
		sp1->runAction(getForeverAcByNameAndInterval("aniGuizu", 2.0));
		lightsp1->runAction(getForeverAcByNameAndInterval("aniLightPoint", 2.0));

	}, 0.1f, "111");



	fistPay = MenuItemImage::create("firstPayGIft.png", "firstPayGIft.png", CC_CALLBACK_1(LobbyScene::FirstPayCallback, this));
	fistPay->setPosition(visibleSize.width*0.044, visibleSize.height*0.47);
	auto sp2 = Sprite::create();
	sp2->setPosition(fistPay->getContentSize() / 2);
	fistPay->addChild(sp2);

	auto lightsp2 = Sprite::create();
	lightsp2->setPosition(22, 39);
	fistPay->addChild(lightsp2, 1);

	if (User::getInstance()->getIsHaveFirstPay())
	{
		fistPay->setVisible(false);
	}
	scheduleOnce([=](float interval)
	{
		sp2->runAction(getForeverAcByNameAndInterval("aniFirstPay", 2.0));
		lightsp2->runAction(getForeverAcByNameAndInterval("aniLightPoint", 2.0));

	}, 1.1f, "1");

	//快速开始
	auto quickBegin = MenuItemImage::create("quickbegin_1.png", "quickbegin_2.png", CC_CALLBACK_1(LobbyScene::quickBeginCallback, this));
	quickBegin->setPosition(820, 87);

	auto aninode1 = Sprite::create("quickStart.png");
	aninode1->setPosition(quickBegin->getPosition());
	addChild(aninode1);
	aninode1->runAction(RepeatForever::create(Sequence::create(Spawn::create(FadeIn::create(0.001), ScaleTo::create(0.001, 0), nullptr), Spawn::create(FadeOut::create(3.0), ScaleTo::create(3.0, 1.5), nullptr), nullptr)));

	auto aninode2 = Sprite::create("quickStart2.png");
	aninode2->setPosition(quickBegin->getContentSize() / 2+Size(0,7));
	quickBegin->addChild(aninode2);
	aninode2->runAction(RepeatForever::create(RotateBy::create(1.5,360)));





	////退出
	auto exitBt = MenuItemImage::create("onExit_1.png", "onExit_2.png", CC_CALLBACK_1(LobbyScene::onExitCallback, this));
	exitBt->setPosition(923, 495);
	//音量

	auto open = MenuItemImage::create("musicon_1.png", "musicon_2.png");
	auto close = MenuItemImage::create("musicoff_1.png", "musicoff_2.png");
	MenuItemToggle *close1;
	if (GameData::getInstance()->getMusicState()){
		close1 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(LobbyScene::onAudioOnOffCallback, this), open, close, nullptr);
		close1->setPosition(ccp(923, 495 - 74));
	}
	else{
		close1 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(LobbyScene::onAudioOnOffCallback, this), close, open, nullptr);
		close1->setPosition(ccp(923, 495 - 74));
	}
	//客服
	auto feedbackbt = MenuItemImage::create("kefu_1.png", "kefu_2.png", CC_CALLBACK_1(LobbyScene::feedBackCallback, this));
	feedbackbt->setPosition(923, 495 - 74 - 74);




	//破产
	auto node = BankruptManager::getInstance()->getgetRewardNode();
	if (node&&User::getInstance()->getCoins() <= 0)
	{
		node->setPosition(824, 480);
		addChild(node);
	}

	auto menu = Menu::create(addCoin, adddiamond, bag, guizu, changeReward, quickBegin, rankList, VIP, fistPay, exitBt, close1, feedbackbt, nullptr);
	menu->setPosition(Point::ZERO);
	addChild(menu, kZorderMenu-1,"menu");
	createRoomLayer();
	//添加系统返回键监听
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
		switch (code)
		{
		case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
			break;
		case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
			//TODO 展示退出界面
			break;
		default:
			break;
		}
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

	auto listenr1 = EventListenerTouchOneByOne::create();
	listenr1->onTouchBegan = CC_CALLBACK_2(LobbyScene::onTouchBegan, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);


	

	this->scheduleOnce(schedule_selector(LobbyScene::showMarquee), 1.0f);
	scheduleUpdate();

	////太阳光
	auto sun = Sprite::create("sunAni.png");
	sun->setPosition(480, 535);
	sun->runAction(RepeatForever::create(Sequence::create(Spawn::create(ScaleTo::create(3.0f, 0), FadeOut::create(2.0f), nullptr), DelayTime::create(1.0f), Spawn::create(ScaleTo::create(1.0f, 1), FadeIn::create(1.0f), DelayTime::create(1.0f), nullptr), nullptr)));
	addChild(sun, kZorderMenu);

	auto sunline = Sprite::create("sunlineAni.png");
	sunline->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	sunline->setPosition(sun->getPosition());
	sunline->setScaleX(0.5);
	addChild(sunline);
	sunline->setRotation(45);
	sunline->runAction(RepeatForever::create(Sequence::create(FadeIn::create(2.0f), DelayTime::create(1.0f), FadeOut::create(1.0f), DelayTime::create(1.0f), nullptr)));
	sunline = Sprite::create("sunlineAni.png");
	sunline->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	sunline->setPosition(sun->getPosition());
	addChild(sunline);
	sunline->setScaleX(0.5);
	sunline->setRotation(135);
	sunline->runAction(RepeatForever::create(Sequence::create(FadeIn::create(2.0f), DelayTime::create(1.0f), FadeOut::create(1.0f), DelayTime::create(1.0f), nullptr)));



	auto fish1 = Sprite::create();
	fish1->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniLobbyFish1")));
	fish1->setPosition(0, 78);
	fish1->runAction(RepeatForever::create(Sequence::create(MoveBy::create(10, Vec2(1000, 0)), DelayTime::create(10), MoveTo::create(0, Vec2(0, 78)), nullptr)));
	addChild(fish1);

	auto fish2 = Sprite::create();
	fish2->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniLobbyFish2")));
	fish2->setPosition(0, 101);
	fish2->runAction(RepeatForever::create(Sequence::create(MoveBy::create(15, Vec2(1000, 0)), DelayTime::create(5), MoveTo::create(0, Vec2(0, 101)), nullptr)));
	addChild(fish2);

	auto fish3 = Sprite::create();
	fish3->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("aniLobbyFish3")));
	fish3->setPosition(960, 59);
	fish3->runAction(RepeatForever::create(Sequence::create(MoveBy::create(18, Vec2(-1000, 0)), DelayTime::create(2), MoveTo::create(0, Vec2(960, 59)), nullptr)));
	addChild(fish3);

	langspEmpty = Sprite::create();
	langspEmpty->setPosition(visibleSize.width / 2 + 20, visibleSize.height*0.3 + 20);
	langspEmpty->runAction(RepeatForever::create((RotateBy::create(10.0f, 360))));
	addChild(langspEmpty);
	lang = Sprite::create("spindrift.png");
	lang->setPosition(10, 10);
	langspEmpty->addChild(lang);
	

	if (!NewbieMannger::getInstance()->getisGetFirstReward())
	{
		auto nblayer = NewbieFirstGetRewardLayer::create();
		nblayer->setPosition(Point::ZERO);
		addChild(nblayer, kZorderDialog);
	}
	else
	{
		SignMannger::getInstance()->setLobbyLayer(this);
		SignMannger::getInstance()->sendRequest();
		  
	}
	runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create([=]{LogEventMannger::getInstance()->sendMsg(); }), nullptr));

	
	auto aniNode = Sprite::create();
	aniNode->setPosition(385, 68);
	addChild(aniNode);
	aniNode->runAction(getForeverAcByNameAndInterval("aniBubble", 0));

	aniNode = Sprite::create();
	aniNode->setPosition(719,119);
	addChild(aniNode);
	runAction(Sequence::create(DelayTime::create(0.1f), CallFunc::create([=]{aniNode->runAction(getForeverAcByNameAndInterval("aniBubble", 0)); }), nullptr));


	//auto lba = MyLabelAtlas::create(Value(1).asString(), "vipLevelNum.png", 11, 16, '0', 100);
	//lba->setPosition(480, 270);
	//lba->runAction(RepeatForever::create(Sequence::create(DelayTime::create(0.5f), CallFunc::create([=]{ static int i = 1; i *= 10; lba->setString(Value(i).asString()); }), nullptr)));
	//addChild(lba, 2000);
	return true;
}
void LobbyScene::showSign(float dt)
{
	///TODO:VIP补足金币
	auto rewards = SignMannger::getInstance()->getSignItems();
	if (rewards.size() > 0)
	{
		auto sign = SignInLayer::createLayer(rewards);
		sign->setPosition(Point::ZERO);
		addChild(sign, 30);
	}

	//auto seqday = ConfigSign::getInstance()->CalculateTheDayToSign();
	//if (seqday == 0)
	//{

	//}
	//else if (seqday == -1)
	//{

	//}
	//else
	//{
	//	if (User::getInstance()->getVipLevel()>6)
	//	{
	//		VipGainCoinSureDialog*dialog = VipGainCoinSureDialog::create();
	//		dialog->setPosition(Point::ZERO);
	//		addChild(dialog, kZorderDialog);
	//		dialog->setseqDay(seqday);
	//	}
	//	else
	//	{
	//		auto sign = SignInLayer::createLayer(seqday);
	//		sign->setPosition(Point::ZERO);
	//		addChild(sign, 20);
	//	}
	//
	//}
}

void LobbyScene::showMarquee(float dt)
{
	auto DisplayBoard = ScrollText::create();
	DisplayBoard->setPosition(498, 463);
	addChild(DisplayBoard, kZorderMenu);
	auto sp = Sprite::create("hot_marquee_bg2.png");
	sp->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
	sp->setPosition(DisplayBoard->getPositionX()-DisplayBoard->getContentSize().width/2,DisplayBoard->getPositionY());
	addChild(sp, kZorderMenu);

}


void LobbyScene::update(float delta)
{
	lang->setRotation(-langspEmpty->getRotation());
	userName->setString(User::getInstance()->getUserName());
	viplevel->setString(Value(User::getInstance()->getVipLevel()).asString().c_str());
	refreshCoinLabel();
}

void LobbyScene::createRoomLayer()
{
	auto visibisize = Director::getInstance()->getVisibleSize();
	auto layer = RoomLayer::createLayer();
	layer->setAnchorPoint(Point::ANCHOR_MIDDLE);
	layer->setPosition(visibisize / 2);
	addChild(layer, kZorderMenu - 2);
}


void LobbyScene::payCoinCallback(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	auto paylayer = payLayer::createLayer(1);
	paylayer->setPosition(Point::ZERO);
	paylayer->setEventPont(1);
	addChild(paylayer, kZorderDialog);
	LogEventPageChange::getInstance()->addEventItems(1, 12, 0);
}
void LobbyScene::payDiamondCallback(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	auto paylayer = payLayer::createLayer(2);
	paylayer->setPosition(Point::ZERO);
	paylayer->setEventPont(2);
	addChild(paylayer, kZorderDialog);
	LogEventPageChange::getInstance()->addEventItems(1, 13, 0);
}

void LobbyScene::bagButtonCallback(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	Director::getInstance()->replaceScene(BagLayer::createScene());
	if (psend)
	{
		LogEventPageChange::getInstance()->addEventItems(1, 3, 0);
	}
	else
	{
		LogEventPageChange::getInstance()->addEventItems(1, 3, 1);
	}
}

void LobbyScene::changeRewardCallback(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	auto layer = ChangeGiftLayer::create();
	layer->setPosition(Point::ZERO);
	addChild(layer, kZorderDialog);
	LogEventPageChange::getInstance()->addEventItems(1, 4, 0);
}
void LobbyScene::RankListCallback(Ref*psend)
{
	auto layer = RanklistLayer::create();
	layer->setPosition(Point::ZERO);
	addChild(layer, kZorderDialog);
	LogEventPageChange::getInstance()->addEventItems(1, 5, 0);

	Audio::getInstance()->playSound(CLICKSURE);
}


void LobbyScene::refreshCoinLabel()
{
	auto user = User::getInstance();
	userdiamond->setString(Value(user->getDiamonds()).asString());
	userCoin->setString(Value(user->getCoins()).asString());
	if (user->getIsHaveFirstPay())
	{
		fistPay->setVisible(false);
	}
}





bool LobbyScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	auto pos = touch->getLocation();
	if (getChildByName("spHeadFrame")->getBoundingBox().containsPoint(pos))
	{
		bagButtonCallback(nullptr);
		return false;
	}
	return false;
}


void LobbyScene::guizuCallback(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	auto guizulayer = NobilityLayer::createLayer();
	guizulayer->setEventPoint(4);
	guizulayer->setPosition(0,0);
	addChild(guizulayer, kZorderDialog);
	if (psend)
	{
		LogEventPageChange::getInstance()->addEventItems(1, 8, 0);
	}
	
}


void LobbyScene::showVipCallBack(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	auto viplayer = VIPLayer::create();
	viplayer->setPosition(Point::ZERO);
	addChild(viplayer, kZorderDialog);
	LogEventPageChange::getInstance()->addEventItems(1, 7, 0);
}
void LobbyScene::quickBeginCallback(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	auto maxLevel = User::getInstance()->getMaxTurrentLevel();
	auto roomDatas = ConfigRoom::getInstance()->getRooms();
	///获得最大可进房间ID
	int i = roomDatas.size() - 1;
	for (; i > 0; i--)
	{
		if (roomDatas[i].unlock_turrent_level <= maxLevel)
		{
			break;
		}
	}

	auto node = BankruptManager::getInstance()->getgetRewardNode();
	if (node&&User::getInstance()->getCoins() <= 0)
	{
		node->retain();
		node->removeFromParentAndCleanup(false);

	}
	GameData::getInstance()->setRoomID(roomDatas.at(i).room_id);
	if (GameData::getInstance()->getisLoadMsgOnGame())
	{
		Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::create()));
	}
	else
	{
		Director::getInstance()->replaceScene(TransitionFade::create(1, LoadingSceneLbToGm::createScene()));
	}
	
	LogEventPageChange::getInstance()->addEventItems(1, 2, 0);
}

void LobbyScene::FirstPayCallback(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	auto layer = FirstPayLayer::create();
	layer->setPosition(0, 0);
	layer->setEventPoint(5);
	addChild(layer, kZorderDialog);
	LogEventPageChange::getInstance()->addEventItems(1, 9, 0);
}
void LobbyScene::onExitSureCallback(Ref*psend)
{
	quickBeginCallback(nullptr);
}
void LobbyScene::endGameCallback(Ref*psend)
{
	Director::getInstance()->end();
}
void LobbyScene::onExitCallback(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	auto isPlay = GameData::getInstance()->getisPlayerOneGame();
	if (isPlay)
	{
		auto str = ChineseWord("onExitTip3");
		auto dioag = TwiceSureDialog::createDialog(str.c_str(), CC_CALLBACK_1(LobbyScene::endGameCallback, this));
		dioag->setPosition(0, 0);
		addChild(dioag, kZorderDialog);
	}
	else
	{
		auto str = ChineseWord("onExitTip1");
		auto dioag = TwiceSureDialog::createDialog(str.c_str(), CC_CALLBACK_1(LobbyScene::onExitSureCallback, this));
		dioag->setPosition(0, 0);
		dioag->setCloseButtonCallback(CC_CALLBACK_1(LobbyScene::endGameCallback, this));
		addChild(dioag, kZorderDialog);
	}
}
void LobbyScene::onAudioOnOffCallback(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);
	MenuItemToggle* temp = (MenuItemToggle*)psend;
	if (GameData::getInstance()->getMusicState()){
		Audio::getInstance()->pauseBGM();
		GameData::getInstance()->setMusicState(false);
		GameData::getInstance()->setSoundState(false);
	}
	else{
		GameData::getInstance()->setMusicState(true);
		GameData::getInstance()->setSoundState(true);
		Audio::getInstance()->resumeBGM();
	}
}
void LobbyScene::feedBackCallback(Ref*psend)
{
	Audio::getInstance()->playSound(CLICKSURE);


#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	auto layer = FeedbackLayer::create();
	layer->setPosition(Point::ZERO);
	addChild(layer, kZorderDialog);
	LogEventPageChange::getInstance()->addEventItems(1, 6, 0);
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
	auto layer = FeedbackLayer::create();
	layer->setPosition(Point::ZERO);
	addChild(layer, kZorderDialog);
	LogEventPageChange::getInstance()->addEventItems(1, 6, 0);
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniFunUtill::getInstance()->showFeedBackDialog();
#endif
	


}
