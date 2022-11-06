#include "MahjongAnim.h"
#include "Card.h"
#include "MahjongEvent.h"
#include "MahjongDatas.h"
#include "Rules.h"
#include "Audio.h"
#include "AnimationUtil.h"
#define CC_RETURNF_IF(cond) do{ if(cond) {return false;} } while(0)
MahjongAnim* MahjongAnim::instance = nullptr;

void MahjongAnim::playSound(SOUND sound)
{
	bool isPlayEffect = Audio::getInstance()->isOpenEffect();
	if (sound!=BGM)
	{
		if (!isPlayEffect)
		{
			return;
		}
	}
	switch (sound)
	{
	case BGM:
		Audio::getInstance()->playBGM(2);
		break;
	case ADDCOIN:
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/AddCoins.ogg");
		break;
	case BUTTONDOWN:
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/ButtonDown.ogg");
		break;
	case FAIL:
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/Fail.ogg");
		break;
	case PENGGANG:
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/PengGang.wav");
		break;
	case PLAYCARD:
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/PlayCard.mp3");
		break;
	case SHAIZI:
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/ShaiZi.wav");
		break;
	case PICKCARD:
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/snd_getdun.mp3");
		break;
	default:
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MahjongAnim::logScreen(string strLog, int index)
{
	if (!IS_LOGINFO_ONSCREEN)
	{
		return;
	}
	string str = strLog + String::createWithFormat("%d", index)->_string;
	screenLogLabel->setString(str);
}



void MahjongAnim::addRemever(int type)
{
	if (!IS_LOGINFO_ONSCREEN)
	{
		return;
	}
	int mahjongNum = MahjongDatas::getInstance()->getCardNum();
	tongLabels[0]->setString(String::createWithFormat("CardNum : %d", mahjongNum)->_string);

	string cardsStr = wanLabels[0]->getString();
	string newStr = String::createWithFormat("%d, ", type)->_string;
	wanLabels[0]->setString(cardsStr+newStr);

	// 上次摸的牌

	if (isCurrentWan && 0 != currentIndex)
	{
		wanLabels[currentIndex]->setColor(colorBefore);
	}
	else
	{
		tongLabels[currentIndex]->setColor(colorBefore);
	}
	//  
	


	if (type < 0)
	{
		isCurrentWan = false;
		type += 10;

		string tongStr = String::createWithFormat("%d T : %d", type, ++tongNum[type])->_string;
		tongLabels[type]->setString(tongStr);
		if (numError < tongNum[type])
		{
			tongLabels[type]->setScale(3.0f);
			tongLabels[type]->setColor(colorCurrent);

		}
		else
		{
			tongLabels[type]->setColor(colorCurrent);
		}
	}
	else
	{
		isCurrentWan = true;
		string wanStr = String::createWithFormat("%d W : %d", type, ++wanNum[type])->_string;
		wanLabels[type]->setString(wanStr);

		if (numError < wanNum[type])
		{
			wanLabels[type]->setScale(3.0f);
			tongLabels[type]->setColor(colorCurrent);

		}
		else
		{
			wanLabels[type]->setColor(colorCurrent);
		}
	}

	currentIndex = type;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




bool MahjongAnim::init()
{
	auto audioEngine = CocosDenshion::SimpleAudioEngine::getInstance();

	audioEngine->preloadBackgroundMusic("Sound/bgm.mp3");
	audioEngine->setBackgroundMusicVolume(.5f);
	audioEngine->preloadEffect("Sound/AddCoins.ogg");
	audioEngine->preloadEffect("Sound/ButtonDown.ogg");
	audioEngine->preloadEffect("Sound/Fail.ogg");
	audioEngine->preloadEffect("Sound/PengGang.wav");
	audioEngine->preloadEffect("Sound/PlayCard.mp3");
	audioEngine->preloadEffect("Sound/ShaiZi.wav");
	audioEngine->preloadEffect("Sound/snd_getdun.mp3");

	if (!Node::init())
	{
		return false;
	}

	if (IS_LOGINFO_ONSCREEN)
	{
		//////////////////////////////////////////////////////////////////////////////////////////////////////
		screenLogLabel = Label::createWithSystemFont("Error : ", "arial", 18.0f);
		screenLogLabel->setPosition(10.0f, 150.0f);
		screenLogLabel->setAnchorPoint(Vec2(.0f, .0f));
		this->addChild(screenLogLabel);

		wanLabels[0] = Label::createWithSystemFont("", "arial", 12.0f);		// 本局牌信息
		wanLabels[0]->setPosition(200.0f, 90.0f);
		wanLabels[0]->setColor(Color3B::BLACK);
		wanLabels[0]->setAnchorPoint(Vec2(.0f, .0f));
		wanLabels[0]->setDimensions(500.0f, 50.0f);
		this->addChild(wanLabels[0]);

		tongLabels[0] = Label::createWithSystemFont("", "arial", 12.0f);	// 剩余牌数
		tongLabels[0]->setPosition(700.0f, 50.0f * 9);
		this->addChild(tongLabels[0]);

		for (int i = 1; i < 10; i++)
		{
			wanNum[i] = 0;
			string wanStr = String::createWithFormat("%d W : %d", i, wanNum[i])->_string;
			wanLabels[i] = Label::createWithSystemFont("", "arial", 24.0f);
			wanLabels[i]->setString(wanStr);
			wanLabels[i]->setPosition(200.0f, 50.0f * (10 - i));
			this->addChild(wanLabels[i]);

			tongNum[i] = 0;
			string tongStr = String::createWithFormat("%d T : %d", i, tongNum[i])->_string;
			tongLabels[i] = Label::createWithSystemFont("", "arial", 24.0f);
			tongLabels[i]->setString(tongStr);
			tongLabels[i]->setPosition(600.0f, 50.0f * (10 - i));
			this->addChild(tongLabels[i]);
		}
		//////////////////////////////////////////////////////////////////////////////////////////////////////

	}


	if (!initAccountHuAnim())
	{
		return false;
	}
	if (!initDealAnim())
	{
		return false;
	}

	if (!initPlayPengGangFrames())
	{
		return false;
	}

	if (!initWordPengGangAnim())
	{
		return false;
	}


	if (!initAccountPanel())
	{
		return false;
	}

	return true;
}

MahjongAnim* MahjongAnim::getInstance()
{
	if (nullptr == instance)
	{
		instance = new (std::nothrow) MahjongAnim();
		instance->init();
	}
	
	return instance;
}

void MahjongAnim::updateInstance()
{
	if (nullptr != instance)
	{
		CC_SAFE_DELETE(instance);
	}
}

//------------------------------------------ 初始打碰杠 -------------------------------------------------------------
bool MahjongAnim::initPlayPengGangFrames()
{
	CCLOG("initAnim : PengGang");

	framePlay = Sprite::create("MJAnim/PlayCard/CardFrame_0.png");
	if (nullptr == framePlay){ return false; }
	Card* PlayedCard = Card::createShowCard();
	PlayedCard->setTag(0);
	PlayedCard->setPosition(75.0f, 105.0f);
	framePlay->addChild(PlayedCard);
	framePlay->setVisible(false);
	this->addChild(framePlay);

	framePlay->setScale(1.5);
	//
	framePengGang = Sprite::create("MJAnim/PlayCard/CardFrame_1.png");
	if (nullptr == framePengGang){ return false; }
	for (int index = 0; index < 4; ++index)
	{
		Card* pengGangCard = Card::createPengGangCard(); 
		pengGangCard->setTag(index);
		pengGangCard->setScale(0.80);
		pengGangCard->setPositionY(55.0f);
		framePengGang->addChild(pengGangCard);
	}
	framePengGang->setVisible(false);
	this->addChild(framePengGang);
	// debug
	/*playPengAnim (1, Vec2(300.0f, 300.0f));*/
	return true;
}
bool MahjongAnim::initWordPengGangAnim()
{
	CCLOG("initAnim : wordPengGang");

	// 创建图片

	animPengGangNode = Sprite::create("MJAnim/PengGang/light_6.png");
	animPengGangNode->setVisible(false);

	Sprite* wordSpr = Sprite::create("MJAnim/PengGang/word_gang.png");
	wordSpr->ignoreAnchorPointForPosition(true);
	wordSpr->setVisible(false);
	animPengGangNode->addChild(wordSpr);
	animPengGangNode->setPosition(200.0f, 200.0f);
	this->addChild(animPengGangNode);

	// 增加图片资源[碰][杠][6张light]
	CC_RETURNF_IF(!addToTextureCache("MJAnim/PengGang/", "light", 7));

	CC_RETURNF_IF(!addToTextureCache("MJAnim/PengGang/", "word_gang"));

	CC_RETURNF_IF(!addToTextureCache("MJAnim/PengGang/", "word_peng"));

	CC_RETURNF_IF(!addToTextureCache("", "menu_hu"));

	// 添加动画资源
	animPengGang = createAnimateFromTextureCache("light", 7, timeShanLight);
	return true;
}
//------------------------------------------ 播放打碰杠 -------------------------------------------------------------
//--------------打
void MahjongAnim::playPlayAnim(int type, Vec2 pos)
{
	auto card = framePlay->getChildByTag(0);
	((Card*)card)->changeCard(type);
	framePlay->setPosition(pos);
	framePlay->setVisible(true);
	framePlay->setScale(.2f);
	framePlay->runAction(Sequence::create(ScaleTo::create(.2f, 1.0f), 
		DelayTime::create(0.3f), 
		ScaleTo::create(.2f, .0f),
		NULL));
}

//--------------碰
void MahjongAnim::playPengAnim(int type, Vec2 pos)
{
	
	framePengGang->setTexture("MJAnim/PlayCard/CardFrame_1.png");
	framePengGang->getChildByTag(3)->setVisible(false);
	for (int index = 0; index < 3; ++index)
	{
		auto pengGangCard = ((Card*)framePengGang->getChildByTag(index));
		/*pengGangCard->setPositionX( (index-0.5) * framePengGang->getContentSize().width/3);
		pengGangCard->setPositionY(framePengGang->getContentSize().height / 2);*/
		/*pengGangCard->setPosition(30 + (index + 0.5) * 147.0f / 3, 85);*/
		pengGangCard->setPositionX(38.0f+index * 28.0f);
		pengGangCard->changeCard(type);
	}
	framePengGang->setScale(1.5f);
	framePengGang->setPosition(pos);
	framePengGang->setVisible(true);
	framePengGang->runAction(Sequence::create(DelayTime::create(1.0f), ScaleTo::create(.15f, .0f), Hide::create(), NULL));

}
void MahjongAnim::playWordPengAnim(Vec2 pos)
{
	CCLOG("playAnim : wordPeng");
	playSound(SOUND::PENGGANG);

	if (animPengGangNode && animPengGang)
	{
		animPengGangNode->setVisible(true);
		animPengGangNode->setPosition(pos);
		animPengGangNode->runAction(animPengGang->clone());

		scheduleOnce([&](float dt){
			Texture2D* tex = getTexFromeCache("word_peng");
			if (!tex){ CCLOG("Error : get tex"); }
			auto sp = ((Sprite*)animPengGangNode->getChildren().at(0));
			sp->setTexture(tex);
			sp->setVisible(true);
			sp->setScale(3.0f); 

			//sp->setOpacity(0.0f);
			// 缩小放大
			auto scaleSmall = ScaleTo::create(timeWordScale * 0.7, 1.0f);
			auto scaleBig = ScaleTo::create(timeWordScale * 0.3, 1.3f);
			auto smallAndBig = Sequence::create(scaleSmall, scaleBig, NULL);
			
			// 透明变化
			auto opacity = FadeIn::create(timeWordScale * 0.5f);

			auto act = Spawn::create(opacity, smallAndBig, NULL);
			sp->runAction(act);
		}, timeWordShowWord, "wordpeng");
		scheduleOnce([&](float dt){this->hideWordAnim(); }, 1.0f, "hide");
	}
	else
	{
		CCLOG("Failed : playWordPengAnim ! \r\n");
	}
}
//--------------杠
void MahjongAnim::playGangAnim(int type, Vec2 pos)
{
	
	framePengGang->setTexture("MJAnim/PlayCard/CardFrame_2.png");
	framePengGang->getChildByTag(3)->setVisible(true);
	for (int index = 0; index < 4; ++index)
	{
		auto card = ((Card*)framePengGang->getChildByTag(index));
		card->setPositionX(41.0f + index * 29.0f);
		card->changeCard(type);
	}
	framePengGang->setScale(1.5f);
	framePengGang->setPosition(pos);
	framePengGang->setVisible(true);
	framePengGang->runAction(Sequence::create(DelayTime::create(3.0f), ScaleTo::create(.15f, .0f), Hide::create(), NULL));

}
void MahjongAnim::playWordGangAnim(Vec2 pos)
{
	playSound(SOUND::PENGGANG);

		if (animPengGangNode && animPengGang)
		{
			animPengGangNode->setVisible(true);
			animPengGangNode->setPosition(pos);
			animPengGangNode->runAction(animPengGang->clone());

			scheduleOnce([&](float dt){
				Texture2D* tex = getTexFromeCache("word_gang");
				if (!tex){ CCLOG("Error : get tex"); }
				auto sp = ((Sprite*)animPengGangNode->getChildren().at(0));
				sp->setTexture(tex);
				sp->setVisible(true);
				sp->setScale(3.0f);

				//sp->setOpacity(0.0f);
				// 缩小放大
				auto scaleSmall = ScaleTo::create(timeWordScale * 0.7, 1.0f);
				auto scaleBig = ScaleTo::create(timeWordScale * 0.3, 1.3f);
				auto smallAndBig = Sequence::create(scaleSmall, scaleBig, NULL);

				// 透明变化
				auto opacity = FadeIn::create(timeWordScale * 0.5f);

				auto act = Spawn::create(opacity, smallAndBig, NULL);
				sp->runAction(act);
			}, timeWordShowWord, "wordgang");
			scheduleOnce([&](float dt){this->hideWordAnim(); }, 1.0f, "hide");
		}
		else
		{
			CCLOG("Failed : playWordPengAnim ! \r\n");
		}
}

void MahjongAnim::playWordHuAnim(Vec2 pos)
{
		if (animPengGangNode && animPengGang)
		{
			animPengGangNode->setVisible(true);
			animPengGangNode->setPosition(pos);
			animPengGangNode->runAction(animPengGang->clone());

			scheduleOnce([&](float dt){
				Texture2D* tex = getTexFromeCache("menu_hu");
				if (!tex){ CCLOG("Error : get tex"); }
				auto sp = ((Sprite*)animPengGangNode->getChildren().at(0));
				sp->setTexture(tex);
				sp->setVisible(true);
				sp->setScale(3.0f);

				//sp->setOpacity(0.0f);
				// 缩小放大
				auto scaleSmall = ScaleTo::create(timeWordScale * 0.7, 1.0f);
				auto scaleBig = ScaleTo::create(timeWordScale * 0.3, 1.3f);
				auto smallAndBig = Sequence::create(scaleSmall, scaleBig, NULL);

				// 透明变化
				auto opacity = FadeIn::create(timeWordScale * 0.5f);

				auto act = Spawn::create(opacity, smallAndBig, NULL);
				sp->runAction(act);
			}, timeWordShowWord, "menu_hu");
			scheduleOnce([&](float dt){this->hideWordAnim(); }, 3.0f, "hide");
		}
		else
		{
			CCLOG("Failed : playWordHuAnim ! \r\n");
		}
}

//--------------Hide
void MahjongAnim::hideWordAnim()
{
	CCLOG("----------HIde-------------");
	animPengGangNode->runAction(FadeOut::create(0.3f));
	animPengGangNode->getChildren().at(0)->runAction(FadeOut::create(0.3f));
}


//------------------------------------------ 结算【胡】【自摸】【抢杠】 -------------------------------------------------------------
//------------------------------------------ 胡&&点炮 -------------------------------------------------------------
bool MahjongAnim::initAccountHuAnim()	
{// flash_6, lightPoints_2, lightYellow_2, circlePurple, lightPink, ring, shadowCircle
	nodeAccountHu = Node::create();
	nodeAccountHu->setVisible(false);
	this->addChild(nodeAccountHu);

	std::string path = "MJAnim/Account/Hu/";
	//huShadowCircle = addAnimNoAnimte(*nodeAccountHu, path, "shadowCircle");

	huFlash = addAnimWithAnimate(*nodeAccountHu, animHuFlash, path, "flash", 7, timeShanLight);
	huCirclePurple = addAnimNoAnimte(*nodeAccountHu, path, "circlePurple");

	huLightPink = addAnimNoAnimte(*nodeAccountHu, path, "lightPink");
	huLightYellow = addAnimWithAnimate(*nodeAccountHu, animHuLightYellow, path, "lightYellow", 3, timeShanLight);

	huRing = addAnimNoAnimte(*nodeAccountHu, path, "ring");
	huLightPoints = addAnimWithAnimate(*nodeAccountHu, animHuLightPoints, path, "lightPoints", 3, timeShanLight);

	CCLOG("Finish InitAccount : Hu \r\n");
	return true;
}


void MahjongAnim::playAccountHuAnim(GameFlow & gameFlow)
{

	nodeAccountHu->setVisible(true);
	nodeAccountHu->setPosition(Vec2(400.0f, 400.0f));

	huFlash->runAction( animHuFlash->clone());

	huLightPink->runAction(ScaleTo::create(0.5f, 1.3f));
	huCirclePurple->runAction(ScaleTo::create(0.5f, 1.3f));
	huLightYellow->runAction(ScaleTo::create(0.5f, 1.3f));
	huLightPoints->runAction(ScaleTo::create(0.5f, 1.3f));
	huRing->runAction(ScaleTo::create(0.5f, 1.3f));

	huLightPoints->runAction(RepeatForever::create(animHuLightPoints->clone()));
	huLightYellow->runAction(RepeatForever::create(animHuLightYellow->clone()));

	playWordHuAnim(Vec2(413.0f, 400.0f));
	nodeAccountHu->runAction(Sequence::create(DelayTime::create(3.0f), ScaleTo::create(.3f, .0f), RemoveSelf::create(), NULL));
}
void MahjongAnim::playAccountZiMoAnim()
{
	nodeAccountHu->setVisible(true);
	nodeAccountHu->setPosition(Vec2(400.0f, 400.0f));

	huFlash->runAction(animHuFlash->clone());

	huLightPink->runAction(ScaleTo::create(0.5f, 1.3f));
	huCirclePurple->runAction(ScaleTo::create(0.5f, 1.3f));
	huLightYellow->runAction(ScaleTo::create(0.5f, 1.3f));
	huLightPoints->runAction(ScaleTo::create(0.5f, 1.3f));
	huRing->runAction(ScaleTo::create(0.5f, 1.3f));

	huLightPoints->runAction(RepeatForever::create(animHuLightPoints->clone()));
	huLightYellow->runAction(RepeatForever::create(animHuLightYellow->clone()));

	playWordHuAnim(Vec2(413.0f, 400.0f));
	nodeAccountHu->runAction(Sequence::create(DelayTime::create(3.0f), ScaleTo::create(.3f, .0f), RemoveSelf::create(), NULL));
}
void MahjongAnim::playAccountGangKaiAnim()
{
	nodeAccountHu->setVisible(true);
	nodeAccountHu->setPosition(Vec2(400.0f, 400.0f));

	huFlash->runAction(animHuFlash->clone());

	huLightPink->runAction(ScaleTo::create(0.5f, 1.3f));
	huCirclePurple->runAction(ScaleTo::create(0.5f, 1.3f));
	huLightYellow->runAction(ScaleTo::create(0.5f, 1.3f));
	huLightPoints->runAction(ScaleTo::create(0.5f, 1.3f));
	huRing->runAction(ScaleTo::create(0.5f, 1.3f));

	huLightPoints->runAction(RepeatForever::create(animHuLightPoints->clone()));
	huLightYellow->runAction(RepeatForever::create(animHuLightYellow->clone()));

	playWordHuAnim(Vec2(413.0f, 400.0f));
	nodeAccountHu->runAction(Sequence::create(DelayTime::create(3.0f), ScaleTo::create(.3f, .0f), RemoveSelf::create(), NULL));
}

//---------------------------------------------------------------------------
bool MahjongAnim::initAccountPanel()
{
	// Banner[15], CoinAnim[29]
	nodeWinBanner = Node::create();
	nodeWinBanner->setVisible(false);
	this->addChild(nodeWinBanner);

	std::string path = "MJAnim/AccountPanel/";

	winBanner = addAnimWithAnimate(*nodeWinBanner, animBanner, path, "Banner", 15, 1.0f);
	winBanner->ignoreAnchorPointForPosition(true);
	winBanner->setPosition(160.0f, 330.0f);

	winManyCoins = addAnimNoAnimte(*nodeWinBanner, path, "CoinOne");
	winManyCoins->ignoreAnchorPointForPosition(true);
	winManyCoins->setPosition(0.0f, 0.0f);
	CCLOG("Finish InitAccount : AccountPanel \r\n");
	return true;
}
void MahjongAnim::playWinBanner()
{
	nodeWinBanner->setVisible(true);

	winBanner->runAction(animBanner->clone());
	winManyCoins->runAction(Sequence::create(DelayTime::create(2.0f), Hide::create(),  NULL));
}

void MahjongAnim::hideWinBanner()
{
	nodeWinBanner->setVisible(false);
}


//------------------------发牌筛子
bool MahjongAnim::initDealAnim()
{//ShaiZiAnim_10, ShaiZi_5
	Vec2 size = Director::getInstance()->getVisibleSize();
	nodeDeal = Node::create();
	nodeDeal->setVisible(false);
	this->addChild(nodeDeal);

	std::string path = "MJAnim/DealCard/";

	dealShaiZi = addAnimWithAnimate(*nodeDeal, animShaiZi, path, "ShaiZiAnim", 11, timeShaiZi);
	dealShaiZi->setPosition(size/2);

	addToTextureCache(path, "ShaiZi", 6);
	
	dealShaiZiL = Sprite::create();
	dealShaiZiL->setPosition(365.0f/800*1280, 180.0/400*720.0f);
	dealShaiZiL->setOpacity(.0f);
	nodeDeal->addChild(dealShaiZiL);

	dealShaiZiR = Sprite::create();
	dealShaiZiR->setPosition(435.0f/800*1280, 180.0f/400*720.0f);
	dealShaiZiR->setOpacity(.0f);
	nodeDeal->addChild(dealShaiZiR);

	CCLOG("Finish InitDeal : ShaiZi \r\n");
	return true;
}
void MahjongAnim::playDealShaiZi()
{
	playSound(SOUND::SHAIZI);
	nodeDeal->setVisible(true);

	dealShaiZi->setVisible(true);
	dealShaiZi->runAction(animShaiZi->clone());
	std::string name = "MJAnim/DealCard/ShaiZi_";

	std::string strL = name + String::createWithFormat("%d", random<int>(0, 5))->_string + ".png";
	dealShaiZiL->setTexture(strL);
	dealShaiZiL->setOpacity(.0f);

	std::string strR = name + String::createWithFormat("%d", random<int>(0, 5))->_string + ".png";
	dealShaiZiR->setTexture(strR);
	dealShaiZiR->setOpacity(.0f);
	
	scheduleOnce([&](float dt){
		dealShaiZiL->runAction(FadeIn::create(0.2f));
		dealShaiZiR->runAction(FadeIn::create(0.2f));
		dealShaiZi->setVisible(false);
	}, 0.9f, "hee");

	scheduleOnce([&](float dt){nodeDeal->setVisible(false); }, 1.3f, "hideeee");
}
