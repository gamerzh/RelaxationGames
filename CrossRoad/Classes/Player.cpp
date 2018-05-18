#include "Player.h"
#include "MapNode.h"
#include "GeometryUtils.h"
#include "Audio.h"
#include "GameLayer.h"

bool Player :: init() {
	if (!Sprite::init()) {
		return false;
	}
	hero = CSLoader::createNode("rw.csb");
	hero->setScale(0.5f);
	hero->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	hero->setPosition(default_tmx_width/2,default_tmx_height/3);
	addChild(hero);
	scheduleUpdate();
	return true;
}



bool Player::playerJumpForward(vector<Block*> blocks) {

	for (auto bloc : blocks)
	{
		auto box = getPlayerCheckRect();
		auto checkBox = Rect(box.getMinX() + PLAYER_JUMP_OFFSET, box.getMinY() + default_tmx_height,
			box.getMaxX() - box.getMinX(), box.getMaxY() - box.getMinY());
		if (GeometryUtils::intersectsRect(bloc->getBlockCheckRect(), checkBox)) {
			//log("blockF Rect(%f,%f,%f,%f)",
			//	bloc->getBlockCheckRect().getMinX(),
			//	bloc->getBlockCheckRect().getMinY(),
			//	bloc->getBlockCheckRect().getMaxX() - bloc->getBlockCheckRect().getMinX(),
			//	bloc->getBlockCheckRect().getMaxY() - bloc->getBlockCheckRect().getMinY());

			//log("palyerF Rect(%f,%f,%f,%f)",
			//	checkBox.getMinX(),
			//	checkBox.getMinY(),
			//	checkBox.getMaxX() - checkBox.getMinX(),
			//	checkBox.getMaxY() - checkBox.getMinY());
			return false;
		}
	}
	playPlayerTiaoYue();
	int line = this->getPositionY() / default_tmx_height;
	auto posx = floor(this->getPosition().x / default_tmx_width)*default_tmx_width;
	//this->setPosition();
	auto nextPos = Vec2(posx + (line*PLAYER_JUMP_OFFSET) % default_tmx_width + PLAYER_JUMP_OFFSET, this->getPositionY() + default_tmx_height);
	this->runAction(Sequence::create(MoveTo::create(0.25, nextPos),CallFunc::create([=]() {
		this->setLocalZOrder(MaxZorder - floor(this->getPositionY() / default_tmx_height));
		log("Player Zorder %d", this->getLocalZOrder());
	}), NULL));
	log("Player postion = (%.1f,%.1f)", getPosition().x, getPosition().y);
	Audio::getInstance()->playSoundJump();
	return true;
}

bool Player::playerJumpBackwards(vector<Block*> blocks) {

	for (auto bloc : blocks)
	{
		auto box = getPlayerCheckRect();
		if (GeometryUtils::intersectsRect(bloc->getBlockCheckRect(), Rect(box.getMinX() - PLAYER_JUMP_OFFSET, box.getMinY() - default_tmx_height,
			box.getMaxX() - box.getMinX(), box.getMaxY() - box.getMinY()))) {
			//log("block Rect(%f,%f,%f,%f)",
			//	bloc->getBlockCheckRect(mapIndex).getMinX(),
			//	bloc->getBlockCheckRect(mapIndex).getMinY(),
			//	bloc->getBlockCheckRect(mapIndex).getMaxX() - bloc->getBlockCheckRect(mapIndex).getMinX(),
			//	bloc->getBlockCheckRect(mapIndex).getMaxY() - bloc->getBlockCheckRect(mapIndex).getMinY());

			//log("palyer Rect(%f,%f,%f,%f)",
			//	box.getMinX(),
			//	box.getMinY(),
			//	box.getMaxX() - box.getMinX(),
			//	box.getMaxY() - box.getMinY());
			return false;
		}
	}
	playPlayerTiaoYueBack();
	int line = this->getPositionY() / default_tmx_height;
	auto posx = floor(this->getPosition().x / default_tmx_width)*default_tmx_width;
	auto nextPos = Vec2(posx + (line*PLAYER_JUMP_OFFSET) % default_tmx_width - PLAYER_JUMP_OFFSET, this->getPositionY() - default_tmx_height);
	this->runAction(Sequence::create(MoveTo::create(0.25, nextPos), CallFunc::create([=]() {
		this->setLocalZOrder(MaxZorder - floor(this->getPositionY() / default_tmx_height));
		log("Player Zorder %d", this->getLocalZOrder());
	}), NULL));
	Audio::getInstance()->playSoundJump();
	return true;
}


bool Player::playerJumpLeft(vector<Block*> blocks) {
	for (auto bloc : blocks)
	{
		auto box = getPlayerCheckRect();
		if (GeometryUtils::intersectsRect(bloc->getBlockCheckRect(),Rect(box.getMinX() - default_tmx_width, box.getMinY(),
			box.getMaxX() - box.getMinX(), box.getMaxY() - box.getMinY()))) {
			//log("block Rect(%f,%f,%f,%f)",
			//	bloc->getBlockCheckRect(mapIndex).getMinX(),
			//	bloc->getBlockCheckRect(mapIndex).getMinY(),
			//	bloc->getBlockCheckRect(mapIndex).getMaxX()- bloc->getBlockCheckRect(mapIndex).getMinX(),
			//	bloc->getBlockCheckRect(mapIndex).getMaxY()- bloc->getBlockCheckRect(mapIndex).getMinY());

			//log("palyer Rect(%f,%f,%f,%f)",
			//	box.getMinX(),
			//	box.getMinY(),
			//	box.getMaxX() - box.getMinX(),
			//	box.getMaxY() - box.getMinY());
			return false;
		}
	}
	playPlayerTiaoYueLeft();
	auto nextPos = Vec2(this->getPosition().x - default_tmx_width, this->getPosition().y);
	this->runAction(Sequence::create(MoveTo::create(0.25, nextPos), CallFunc::create([=]() {
		this->setLocalZOrder(MaxZorder - floor(this->getPositionY() / default_tmx_height));
		log("Player Zorder %d", this->getLocalZOrder());
	}), NULL));
	Audio::getInstance()->playSoundJump();
	return true;
}


bool Player::playerJumpRight(vector<Block*> blocks) {

	for (auto bloc : blocks)
	{
		auto box = getPlayerCheckRect();
		if (GeometryUtils::intersectsRect(bloc->getBlockCheckRect(), Rect(box.getMinX() + default_tmx_width, box.getMinY() ,
			box.getMaxX() - box.getMinX(), box.getMaxY() - box.getMinY()))) {
		/*	log("blockR Rect(%f,%f,%f,%f)",
				bloc->getBlockCheckRect().getMinX(),
				bloc->getBlockCheckRect().getMinY(),
				bloc->getBlockCheckRect().getMaxX() - bloc->getBlockCheckRect().getMinX(),
				bloc->getBlockCheckRect().getMaxY() - bloc->getBlockCheckRect().getMinY());

			log("palyerR Rect(%f,%f,%f,%f)",
				box.getMinX(),
				box.getMinY(),
				box.getMaxX() - box.getMinX(),
				box.getMaxY() - box.getMinY());*/
			return false;
		}
	}
	playPlayerTiaoYueRight();
	auto nextPos = Vec2(this->getPosition().x + default_tmx_width, this->getPosition().y);
	this->runAction(Sequence::create(MoveTo::create(0.25, nextPos), CallFunc::create([=]() {
		this->setLocalZOrder(MaxZorder - floor(this->getPositionY() / default_tmx_height));
		log("Player Zorder %d", this->getLocalZOrder());
	}), NULL));
	Audio::getInstance()->playSoundJump();
	return true;
}

Point Player::getPlayerPoint() {
	return this->getPosition();
}

Rect Player::getPlayerCheckRect() {
	//log("rect %f,%f,%f,%f", getPositionX(), getPositionY(), default_tmx_width, default_tmx_height);
	return Rect(getPositionX(), getPositionY(),default_tmx_width,default_tmx_height);
}



void Player::playPlayerJiYa() {
	auto playerTimeLine = CSLoader::createTimeline("rw.csb");
	playerTimeLine->play("jiya", false);
	hero->runAction(playerTimeLine);
}


void Player::playPlayerTiaoYue() {
	hero->stopAllActions();
	auto playerTimeLine = CSLoader::createTimeline("rw.csb");
	playerTimeLine->play("tiaoyue", false);
	hero->runAction(playerTimeLine);
}

void Player::playPlayerJiYaLeft() {
	auto playerTimeLine = CSLoader::createTimeline("rw.csb");
	playerTimeLine->play("jiyazuo", false);
	hero->runAction(playerTimeLine);
}


void Player::playPlayerTiaoYueLeft() {
	hero->stopAllActions();
	auto playerTimeLine = CSLoader::createTimeline("rw.csb");
	playerTimeLine->play("tiaoyuezuo", false);
	hero->runAction(playerTimeLine);
}

void Player::playPlayerJiYaRight() {
	auto playerTimeLine = CSLoader::createTimeline("rw.csb");
	playerTimeLine->play("jiyayou", false);
	hero->runAction(playerTimeLine);
}


void Player::playPlayerTiaoYueRight() {
	hero->stopAllActions();
	auto playerTimeLine = CSLoader::createTimeline("rw.csb");
	playerTimeLine->play("tiaoyueyou", false);
	hero->runAction(playerTimeLine);
}

void Player::playPlayerJiYaBack() {
	auto playerTimeLine = CSLoader::createTimeline("rw.csb");
	playerTimeLine->play("jyqian", false);
	hero->runAction(playerTimeLine);
}

void Player::playPlayerTiaoYueBack() {
	hero->stopAllActions();
	auto playerTimeLine = CSLoader::createTimeline("rw.csb");
	playerTimeLine->play("tiaoyueqian", false);
	hero->runAction(playerTimeLine);
}

void Player::setSpeedX(float speed) {
	this->speedX = speed;
}

float Player::getSpeedX() {
	return this->speedX;
}

void Player::update(float dt) {
	if (getPositionX() + speedX < defult_tmx_x_num*default_tmx_width) {
		setPosition(getPositionX() + speedX, getPositionY());
	}
}

void Player::playerGoDie() {
	hero->setVisible(false);
	auto die = Sprite::create("player_die.png");
	die->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	die->setPosition(0, 0);
	die->setCameraMask(int(CameraFlag::USER1));
	addChild(die,2);
}

void Player::playerGoWater() {
	hero->setVisible(false);
	auto node = CSLoader::createNode("biaoxue.csb");
	node->setCameraMask((int)CameraFlag::USER1);
	node->setScale(0.3);
	node->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	node->setPosition(hero->getPosition());
	addChild(node);
	auto waterHua = CSLoader::createTimeline("biaoxue.csb");
	waterHua->play("bx", false); 
	node->runAction(waterHua);
	node->runAction(Sequence::create(DelayTime::create(0.5f), CallFunc::create([=]() {
		node->setVisible(false);
	}),NULL));
}

