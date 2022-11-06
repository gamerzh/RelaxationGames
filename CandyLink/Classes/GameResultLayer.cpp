#include "GameResultLayer.h"
#include "GameData.h"
#include "LobbyScene.h"
#include "GameScene.h"
#include"Audio.h"
#include"Matrix.h"
#include"GameLayer.h"
#include"CallAndroidMethod.h"
#include "GameConfig.h"
#include "AnimationUtil.h"
bool GameResultLayer::init(){
	if (!Layer::init())
	{
		return false;
	}
	//add sprite to this layer
	animTime = 0;
	scoreNum = 0;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Sprite* result_bg = Sprite::create("pause_bg.jpg");
	result_bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(result_bg);
	//add result title
	Sprite* result_title = Sprite::create("game_result_curr_round_score.png");
	result_title->setPosition(240, 720-120);
	this->addChild(result_title);
	//get score from gamedata
	score = GAMEDATA::getInstance()->getAchievescore();
	labelnumber = LabelAtlas::create("0", "result_num.png", 36, 57, '0');
	labelnumber->setPosition(240, 650-120);
	labelnumber->setAnchorPoint(Point(0.5, 0.5));
	this->addChild(labelnumber);

	auto sprite0 = Sprite::create("w.png");
	auto action0 = Sequence::create(
		RotateTo::create(2.0f, -90),
		RotateTo::create(2.0f, 90),
		nullptr);
	auto rep0 = RepeatForever::create(action0->clone());
	sprite0->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	sprite0->setAnchorPoint(Vec2(0.5, 0.0));
	sprite0->setScale(0.7);
	addChild(sprite0);
	sprite0->runAction(rep0);

	//add tanzhaodeng right
	auto sprite1 = Sprite::create("w.png");
	auto action1 = Sequence::create(
		RotateTo::create(2.0f, 90),
		RotateTo::create(2.0f, -90),
		nullptr);
	auto rep1 = RepeatForever::create(action1->clone());
	sprite1->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	sprite1->setAnchorPoint(Vec2(0.5, 0.0));
	sprite1->setScale(0.7);
	addChild(sprite1);
	sprite1->runAction(rep1);

	//add touxiang
	auto touxiang = Sprite::create("rabbit1.png");
	touxiang->setPosition(Vec2(visibleSize.width / 2 + origin.x-10, visibleSize.height / 2 + origin.y));
	//touxiang->setScale(0.8);
	touxiang->retain();
	addChild(touxiang);
	AnimationUtil::getInstance()->addAnimationBySpriteName("rabbit", "rabbitdance", 0.5f, 2);
	touxiang->runAction(RepeatForever::create(AnimationUtil::getInstance()->getAnimate("rabbitdance")));

	auto sprite4 = Sprite::create("game_result_shine.png");
	sprite4->setPosition(Vec2(visibleSize.width / 2 + origin.x + 90, visibleSize.height / 2 + origin.y));
	auto action4 = FadeIn::create(5.0f);
	auto action1Back = action4->reverse();
	auto action4_0 = FadeOut::create(1.0f);
	auto action2Back = action4_0->reverse();
	auto action4_1 = Sequence::create(action4, action1Back, action4_0, action2Back, nullptr);
	auto rep4 = RepeatForever::create(action4_1->clone());
	addChild(sprite4);
	sprite4->runAction(rep4);

	schedule(schedule_selector(GameResultLayer::showRankNum), 2.0f, 0, 0);
	//add defeat
	auto defeat = Sprite::create("defeat.png");
	defeat->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - 200);

	addChild(defeat);
	//add btn
	auto menu = Menu::create();
	auto settingBtnOkItem = MenuItemImage::create("startagain_normal.png", "startagain_click.png", CC_CALLBACK_0(GameResultLayer::continueGame, this));
	settingBtnOkItem->setPosition(Point(250, 100));
	menu->addChild(settingBtnOkItem);
	menu->setPosition(Point(0, 0));
	this->addChild(menu);

	auto menu1 = Menu::create();
	auto settingBtnOkItem1 = MenuItemImage::create("back_normal.png", "back_click.png",  CC_CALLBACK_0(GameResultLayer::quitGame, this));
	settingBtnOkItem1->setPosition(Point(70, 100));
	menu1->addChild(settingBtnOkItem1);
	menu1->setPosition(Point(0, 0));
	this->addChild(menu1);

	this->scheduleUpdate();
	return true;
}

void GameResultLayer::showRankNum(float dt){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	// add a label shows "number"
	int number = getScoreRank();
	int count = 0;
	int temp = 1;
	while (temp * 10<number){
		temp = temp * 10;
		count++;
	}
	LabelAtlas* labelnumber1 = LabelAtlas::create(StringUtils::format("%d", number), "rank_num.png", 19, 22, '0');
	labelnumber1->setAnchorPoint(Point(0.5, 0.5));
	labelnumber1->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2 - 150));
	labelnumber1->setScale(2);
	auto act3 = Sequence::create(DelayTime::create(0), ScaleTo::create(0.5, 1.3), nullptr);
	labelnumber1->runAction(act3);
	auto director = Director::getInstance();
	director->getActionManager()->pauseTarget(labelnumber1);
	this->addChild(labelnumber1, 1);

	//add mingci big
	auto sprite = Sprite::create("rank_label.png");
	sprite->setAnchorPoint(Point(0.5, 0.5));
	sprite->setPosition(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height / 2 - 150);
	sprite->setScale(2);
	addChild(sprite);
	auto act1 = Sequence::create(DelayTime::create(0), ScaleTo::create(0.5, 1), nullptr);
	sprite->runAction(act1);

	LabelAtlas* rank_percent = LabelAtlas::create(StringUtils::format("%d", getScorePacent()), "rank_num.png", 19, 22, '0');
	rank_percent->setAnchorPoint(Point(0.5, 0.5));
	rank_percent->setPosition(Vec2(origin.x + visibleSize.width / 2 + 70,
		origin.y + visibleSize.height *0.25));
	this->addChild(rank_percent, 2);
}

void GameResultLayer::update(float delta){
	if (this->isVisible()){
		animTime += delta / 0.05;


		if (animTime >= 60000000){
			animTime = 6000;
		}

		if (animTime >= 5){
			scoreNum = (animTime - 5) / 30 * score;
		}

		if (scoreNum > score){
			scoreNum = score;
		}
		labelnumber->setString(StringUtils::format("%d", (int)scoreNum));
	}
	if (animTime >= 40){

	}
}

void GameResultLayer::continueGame(){
	Audio::getInstance()->playBtnEffect();
	GAMEDATA::getInstance()->init();
	auto scene = GameConfig::getInstance()->getSceneOfChangeStyleByName(GameScene::create(), "ResultToGame");
	Director::getInstance()->replaceScene(scene);
	GAMEDATA::getInstance()->setAchievescore(0);
}
void GameResultLayer::quitGame(){
	Audio::getInstance()->playBtnEffect();
	auto scene = GameConfig::getInstance()->getSceneOfChangeStyleByName(LobbyScene::createScene(), "ResultToStart");
	Director::getInstance()->replaceScene(scene);
	GAMEDATA::getInstance()->setAchievescore(0);
}
void GameResultLayer::showMoreGame(){
	Audio::getInstance()->playBtnEffect();
//    CallAndroidMethod::getInstance()->showMoreGame();
}

int  GameResultLayer::getScoreRank(){
	float rank = 0;
	if (score>=190000){
		rank = 1;
	}
	else if (score >= 140000){
		rank = 518 + 10 * (1 - (190000 - score) / (50000.0));
	}
	else if (score >= 90000){
		rank = 3034 + 2400 * (1 - (140000 - score) / (50000.0));
	}
	else if (score >= 48000){
		rank = 7100  + 4000 * (1 - (90000 - score) / (42000.0));
	}
	else if (score >= 30000){
		rank = 13437 + 6000 * (1 - (48000 - score) / (18000.0));
	}
	else if (score >= 18000){
		rank = 45440 + 30000 * (1 - (30000 - score) / (12000.0));
	}
	else if (score >= 8000){
		rank = 125470 + 80000 * (1 - (18000 - score) / (10000.0));
	}
	else if (score >= 0){
		rank = 625472 + 500000 * (1 - (8000 - score) / (8000.0));
	}

	return (int)rank;
}
int  GameResultLayer::getScorePacent(){
	float pacent = 0;
	if (score >= 190000){
		pacent = 99;
	}
	else if (score >= 140000){
		pacent = 90 + 10 * (1 - (190000 - score) / (50000.0));
	}
	else if (score >= 90000){
		pacent = 80 + 10 * (1 - (140000 - score) / (50000.0));
	}
	else if (score >= 48000){
		pacent = 70 + 10 * (1 - (90000 - score) / (42000.0));
	}
	else if (score >= 30000){
		pacent = 50 + 20 * (1 - (48000 - score) / (18000.0));
	}
	else if (score >= 18000){
		pacent = 30 + 20 * (1 - (30000 - score) / (12000.0));
	}
	else if (score >= 8000){
		pacent = 20 + 10 * (1 - (18000 - score) / (10000.0));
	}
	else if (score >= 0){
		pacent = 10 + 10 * (1 - (8000 - score) / (8000.0));
	}

	return (int)pacent;
}
