#include "Player.h"
#include "MapNode.h"
#include "GeometryUtils.h"
#include "Audio.h"
#include "GameLayer.h"

bool Player :: init() {
	if (!Sprite::init()) {
		return false;
	}
	setResurgence(false);
	hero = CSLoader::createNode("rw.csb");
	hero->setScale(0.4f);
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
	auto target = Vec2(this->getPositionX() ,this->getPositionY());
	if (playerOnWood) {
		float x = floor(target.x / default_tmx_width)*default_tmx_width +
			(int)(floor(target.y / default_tmx_height)*PLAYER_JUMP_OFFSET) % default_tmx_width;
		target = Vec2(x+ PLAYER_JUMP_OFFSET, target.y + default_tmx_height);
	}
	else {
		target = Vec2(target.x + PLAYER_JUMP_OFFSET, target.y + default_tmx_height);
	}
	//log("aaaaa target %.1f,%.1f", target.x,target.y);
	this->runAction(Sequence::create(MoveTo::create(0.20, target),CallFunc::create([=]() {
		this->setLocalZOrder(MaxZorder - floor(this->getPositionY() / default_tmx_height));
		//log("Player Zorder %d", this->getLocalZOrder());
		setResurgence(false);
		log("Player postion = (%.1f,%.1f)", getPosition().x, getPosition().y);
	}), NULL));
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
	//猪脚没有发生任何偏移的位置
	auto target = Vec2(this->getPositionX(), this->getPositionY());
	if (playerOnWood) {
		float x = floor(target.x / default_tmx_width)*default_tmx_width +
			(int)(floor(target.y / default_tmx_height)*PLAYER_JUMP_OFFSET) % default_tmx_width;
		target = Vec2(x + PLAYER_JUMP_OFFSET, target.y + default_tmx_height);
	}
	else {
		target = Vec2(target.x - PLAYER_JUMP_OFFSET, target.y - default_tmx_height);
	}
	this->runAction(Sequence::create(MoveTo::create(0.20, target), CallFunc::create([=]() {
		this->setLocalZOrder(MaxZorder - floor(this->getPositionY() / default_tmx_height));
		setResurgence(false);
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
	auto target = Vec2(this->getPosition().x - default_tmx_width, this->getPosition().y);
	/*offset_path = ((int)offset_path) % default_tmx_width;
	if (offset_path > 0) {
		if (offset_path < default_tmx_width / 2) {
			target = Vec2(target.x - offset_path, target.y);
		}
		else {
			target = Vec2(target.x - offset_path + default_tmx_width, target.y);
		}
	}
	else if (offset_path < 0) {
		if (abs(offset_path) < default_tmx_width / 2) {
			target = Vec2(target.x + abs(offset_path), target.y);
		}
		else {
			target = Vec2(target.x + abs(offset_path) - default_tmx_width, target.y);
		}
	}
	offset_path = 0;*/
	this->runAction(Sequence::create(MoveTo::create(0.20, target), CallFunc::create([=]() {
		this->setLocalZOrder(MaxZorder - floor(this->getPositionY() / default_tmx_height));
		setResurgence(false);
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
	auto target = Vec2(this->getPosition().x + default_tmx_width, this->getPosition().y);
	//offset_path = ((int)offset_path) % default_tmx_width;
	//if (offset_path > 0) {
	//	if (offset_path < default_tmx_width / 2) {
	//		target = Vec2(target.x - offset_path, target.y);
	//	}
	//	else {
	//		target = Vec2(target.x - offset_path + default_tmx_width, target.y);
	//	}
	//}
	//else if (offset_path < 0) {
	//	if (abs(offset_path) < default_tmx_width / 2) {
	//		target = Vec2(target.x + abs(offset_path), target.y);
	//	}
	//	else {
	//		target = Vec2(target.x + abs(offset_path) - default_tmx_width, target.y);
	//	}
	//}
	//offset_path = 0;
	this->runAction(Sequence::create(MoveTo::create(0.20, target), CallFunc::create([=]() {
		this->setLocalZOrder(MaxZorder - floor(this->getPositionY() / default_tmx_height));
		setResurgence(false);
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
	if (speed == 0) {
		offset_path = 0;
	}
	this->speedX = speed;
}

float Player::getSpeedX() {
	return this->speedX;
}

void Player::update(float dt) {
	if (getPositionX() + speedX < defult_tmx_x_num*default_tmx_width && !getResurgence()) {
		setPosition(getPositionX() + speedX, getPositionY());
		offset_path += speedX;
	}
}

void Player::playerGoDie() {
	hero->setVisible(false);
	auto die = Sprite::create("player_die.png");
	die->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	die->setTag(901);
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

void Player::playerResurgence() {
	hero->setVisible(true);
	if (NULL != getChildByTag(901)) {
		getChildByTag(901)->removeFromParent();
	}
}

