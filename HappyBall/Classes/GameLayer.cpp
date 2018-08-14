#include "GameLayer.h"
#include "ResultLayer.h"
#include "GeometryTools.h"
#include "SetingLayer.h"
#include "ResultLayer.h"
#include "UserData.h"
#include "GameStatus.h"
#include "DreamLayer.h"
#include "GuideLayer.h"
#include "Dream.h"
#include "Audio.h"
#include "DreamEvent.h"

USING_NS_CC;

bool GameLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	auto mainLayerBg = Sprite::create("game_bg.png");
	mainLayerBg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(mainLayerBg);

	pillar = Pillar::create();
	pillar->setPosition(visibleSize.width / 2, ZHU_ZI_POS_Y);
	addChild(pillar, BRICK_START_ZORDER + 1);
	addBrick(BRICK_INIT_NUMBER);
	auto first_brick = brickVector.front();
	first_brick->createSafeShape();
	addHeroToGame();
	auto set = SetingLayer::create(1);
	addChild(set, BRICK_START_ZORDER + 1);


	auto socre = LabelAtlas::create(StringUtils::format("%d", GameStatus::getInstance()->getScore()), "game_score.png", 54, 67, '0');
	socre->setTag(615);
	socre->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	socre->setPosition(145, visibleSize.height - 100);
	addChild(socre, BRICK_START_ZORDER + 1);

	addTouchListener();

	scheduleUpdate();

	return true;
}

void GameLayer::showPlusScore(int plus) {
	auto plusIcon = Sprite::create("plus.png");
	plusIcon->setPosition(430, 980 - plus * 45);
	addChild(plusIcon, BRICK_START_ZORDER + 1);

	auto socrePlus = LabelAtlas::create(StringUtils::format("%d", plus), "game_score_plus.png", 34, 41, '0');
	socrePlus->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	socrePlus->setPosition(440, 980 - plus * 45);
	addChild(socrePlus, BRICK_START_ZORDER + 1);

	plusIcon->runAction(FadeOut::create(0.4f));
	socrePlus->runAction(FadeOut::create(0.5f));
}


void GameLayer::addHeroToGame() {
	hero = Hero::create();
	hero->setPosition(visibleSize.width / 2, BALL_STAY_POS_Y);
	addChild(hero, BRICK_START_ZORDER + 1);
}

void GameLayer::updateHeroSkin() {
	//auto pos = hero->getPosition();
	hero->removeFromParent();
	hero = Hero::create();
	hero->setPosition(visibleSize.width / 2, BALL_STAY_POS_Y);
	addChild(hero, BRICK_START_ZORDER + 1);
}


void GameLayer::addBrick(int num) {
	for (int i = 0; i < num; i++)
	{
		auto brick = Brick::create(random(0, BRICK_ANIM_NUM), GameStatus::getInstance()->getLevel());
		if (create_brick_num == 0) {
			brick->setPosition(visibleSize.width / 2, BALL_STAY_POS_Y - BRICK_HEIGHT * i);
		}
		else {
			brick->setPosition(visibleSize.width / 2, brickVector.at(brickVector.size() - 1)->getPositionY() - BRICK_HEIGHT);
		}
		addChild(brick, BRICK_START_ZORDER - i - create_brick_num);
		brickVector.push_back(brick);
	}
	create_brick_num += num;
}


void GameLayer::recycleBrick() {


}

void GameLayer::showGameOver() {
	if (NULL == getChildByTag(1024)) {
		if (GameStatus::getInstance()->getScore() > UserData::getInstance()->getBestRecord()) {
			UserData::getInstance()->setBestRecord(GameStatus::getInstance()->getScore());
		}
		auto res = ResultLayer::create();
		res->setTag(1024);
		addChild(res, BRICK_START_ZORDER + 1);
		GameStatus::getInstance()->setDreamLife(3);
	}
}


void GameLayer::addTouchListener() {

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

bool GameLayer::onTouchBegan(Touch *touch, Event  *event) {
	preTouchPosition = touch->getLocation();
	return true;
}

void GameLayer::onTouchMoved(Touch *touch, Event  *event) {
	auto curpos = touch->getLocation();
	//auto prepos = touch->getPreviousLocation();
	int index = round((curpos.x - preTouchPosition.x) / visibleSize.width * BRICK_ANIM_NUM);
	for (auto var : brickVector) {
		int fin = var->getFrameIndex() - index;
		while (fin < 0)
		{
			fin += BRICK_ANIM_NUM;
		}
		var->setFrameIndex(fin % BRICK_ANIM_NUM);
	}
	preTouchPosition = touch->getLocation();
}


void GameLayer::onTouchEnded(Touch *touch, Event  *event) {

}

void GameLayer::resumeGame() {
	auto first_brick = brickVector.front();
	first_brick->removeDangousArea();
	if (NULL != hero)
		hero->resume();
	GameStatus::getInstance()->setDoubleScore(false);
}

void GameLayer::update(float dt) {
	//碰撞检测
	if (nullptr == hero) {
		return;
	}
	if (NULL != getChildByTag(615)) {
		((LabelAtlas*)getChildByTag(615))->setString(StringUtils::format("%d", GameStatus::getInstance()->getScore()));
	}

	if (GameStatus::getInstance()->getResurgence()) {
		GameStatus::getInstance()->setDreamLife(GameStatus::getInstance()->getDreamLife() - 1);
		GameStatus::getInstance()->setResurgence(false);
		resumeGame();
	}
	if (GameStatus::getInstance()->getInvincible()) {
		invincibleTime -= dt;
		if (invincibleTime < 0) {
			invincibleTime = 5;
			GameStatus::getInstance()->setInvincible(false);
		}
	}
	if (GameStatus::getInstance()->getGameStart()) {
		mysteryTime -= dt;
		if (mysteryTime < 0) {
			mysteryTime = 25;
			if (NULL == getChildByTag(500)) {
				auto mis = DreamLayer::create(6);
				mis->setTag(500);
				addChild(mis, BRICK_START_ZORDER + 1);
			}
		}
	}

	//判断最上面的节点是否允许通过
	if (hero->getPositionY() <= BALL_STAY_POS_Y && hero->isDirectionDown() && allowCheck) {
		auto first_brick = brickVector.front();
		//判断球是否可以继续往下掉
		bool canPassNode = false;//不允许掉落
		//游戏结束判断
		if (passCount < PAS_NODE_NUM) {
			for (auto dan : first_brick->getDangousAnglesByFrameIndex()) {
				auto start = dan.startFrame;
				auto end = dan.endFrame;
				auto cur = first_brick->getFrameIndex();
				if ((start <= cur && end >= cur)
					|| (start > end && ((cur >= start && cur <= BRICK_ANIM_NUM) || (cur >= 0 && cur <= end)))) {
					Dream::getInstance()->recordEvent(dead,dead);
					if (!GameStatus::getInstance()->getInvincible()) {
						if (GameStatus::getInstance()->getDreamLife() > 0) {
							if (NULL == getChildByTag(500)) {
								hero->pause();
								DreamLayer* drm = DreamLayer::create(7);
								drm->setTag(500);
								addChild(drm, BRICK_START_ZORDER + 1);
							}
						}
						else {
							hero->pause();
							showGameOver();
						}
					}
				}
			}
		}
		//掉落判断
		for (auto ang : first_brick->getOutAnglesByFrameIndex()) {
			auto start = ang.startFrame;
			auto end = ang.endFrame;
			auto cur = first_brick->getFrameIndex();
			if ((start <= cur && end >= cur)
				|| (start > end && ((cur >= start && cur <= BRICK_ANIM_NUM) || (cur >= 0 && cur <= end)))) {
				canPassNode = true;
			}
		}
		if (canPassNode) {
			++passCount;
			hero->pause();
			allowCheck = false;
			addBrick();
			first_brick->setLocalZOrder(BRICK_START_ZORDER + 1);
			pillar->setPositionY(ZHU_ZI_POS_Y - BRICK_HEIGHT - offset_y);
			offset_y += BRICK_HEIGHT;
			first_brick->setVisible(false);
			auto plus_score = passCount;
			if (GameStatus::getInstance()->getDoubleScore()) {
				GameStatus::getInstance()->setScore(GameStatus::getInstance()->getScore() + passCount*2);
				showPlusScore(passCount*2);
			}
			else {
				GameStatus::getInstance()->setScore(GameStatus::getInstance()->getScore() + passCount);
				showPlusScore(passCount);
			}
			//难度设置
			if (GameStatus::getInstance()->getScore() > 0 && GameStatus::getInstance()->getScore() <= 25) {
				GameStatus::getInstance()->setLevel(1);
			}
			else if (GameStatus::getInstance()->getScore() > 25 && GameStatus::getInstance()->getScore()<=100) {
				GameStatus::getInstance()->setLevel(2);
			}
			else {
				GameStatus::getInstance()->setLevel(3);
			}
		}
		else {
			//添加墨迹
			//auto wuji = Sprite::create("wu_3.png");
			//wuji->setPosition(0,-30);
			//first_brick->addChild(wuji);
			hero->flipSpeedY();
			if (passCount >= PAS_NODE_NUM) {
				first_brick->setBrickColor(Color3B::GREEN);
				first_brick->isAbandon = true;
			}
			if (GameStatus::getInstance()->getGameStart()) {
				Audio::getInstance()->playJump();
				Audio::getInstance()->vibrate();
			}
			passCount = 0;

		}
	}
	else {
		auto first_brick = brickVector.front();
		if (first_brick->isAbandon) {
			pauseTime += dt;
			if (pauseTime > 0.10 && pauseTime <= 0.20) {
				first_brick->setBrickColor(Color3B(77,77,77));
			}
			else if (pauseTime >0.20 && pauseTime <= 0.30) {
				first_brick->setBrickColor(Color3B::GREEN);
			}
			else if (pauseTime > 0.30) {
				pauseTime = 0;
				addBrick();
				first_brick->isAbandon = false;
				first_brick->setLocalZOrder(BRICK_START_ZORDER + 1);
				pillar->setPositionY(ZHU_ZI_POS_Y - BRICK_HEIGHT - offset_y);
				offset_y += BRICK_HEIGHT;
				first_brick->setVisible(false);
			}
		}
	}
	if (offset_y > 0) {
		pillar->setPositionY(pillar->getPositionY() + EVERY_FRAME_DISTANCE);
		//柱子整体向上升高距离
		for (auto b : brickVector) {
			b->setPositionY(b->getPositionY() + EVERY_FRAME_DISTANCE);
		}
		//brickVector.front()->brickOpacity(brickVector.front()->brickopacity - 12);
		path_record += EVERY_FRAME_DISTANCE;
		if (path_record >= BRICK_HEIGHT) {
			auto first_brick = brickVector.front();
			std::vector<Brick*>::iterator it;
			it = brickVector.begin();
			(*it)->removeFromParent();
			it = brickVector.erase(it);
			path_record = 0;
			allowCheck = true;
			hero->resume();
		}
		offset_y -= EVERY_FRAME_DISTANCE;
	}
	else {
		offset_y = 0;
	}
}