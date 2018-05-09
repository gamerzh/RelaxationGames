#include "Player.h"
#include "MapNode.h"
#include "GeometryUtils.h"

bool Player :: init() {
	if (!Sprite::init()) {
		return false;
	}
	hero = CSLoader::createNode("rw.csb");
	hero->setScale(0.5f);
	hero->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	hero->setPosition(0,default_tmx_height/3);
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
			log("blockF Rect(%f,%f,%f,%f)",
				bloc->getBlockCheckRect().getMinX(),
				bloc->getBlockCheckRect().getMinY(),
				bloc->getBlockCheckRect().getMaxX() - bloc->getBlockCheckRect().getMinX(),
				bloc->getBlockCheckRect().getMaxY() - bloc->getBlockCheckRect().getMinY());

			log("palyerF Rect(%f,%f,%f,%f)",
				checkBox.getMinX(),
				checkBox.getMinY(),
				checkBox.getMaxX() - checkBox.getMinX(),
				checkBox.getMaxY() - checkBox.getMinY());
			return false;
		}
	}
	playPlayerTiaoYue();
	//auto moveBack = MoveTo::create(0.1f, Vec2(this->getPosition().x + PLAYER_JUMP_OFFSET, this->getPosition().y + default_tmx_height));
	//this->runAction(moveBack);
	this->setPosition(Vec2(this->getPosition().x + PLAYER_JUMP_OFFSET,this->getPositionY()+ default_tmx_height));
	return true;
}

bool Player::playerJumpBackwards(vector<Block*> blocks) {

	for (auto bloc : blocks)
	{
		auto box = getPlayerCheckRect();
		if (GeometryUtils::intersectsRect(bloc->getBlockCheckRect(), Rect(box.getMinX() - PLAYER_JUMP_OFFSET, box.getMinY() - default_tmx_height,
			box.getMaxX() - box.getMinX(), box.getMaxY() - box.getMinY()))) {
			log("block Rect(%f,%f,%f,%f)",
				bloc->getBlockCheckRect().getMinX(),
				bloc->getBlockCheckRect().getMinY(),
				bloc->getBlockCheckRect().getMaxX() - bloc->getBlockCheckRect().getMinX(),
				bloc->getBlockCheckRect().getMaxY() - bloc->getBlockCheckRect().getMinY());

			log("palyer Rect(%f,%f,%f,%f)",
				box.getMinX(),
				box.getMinY(),
				box.getMaxX() - box.getMinX(),
				box.getMaxY() - box.getMinY());
			return false;
		}
	}
	playPlayerTiaoYueBack();
	auto moveBack = MoveTo::create(0.2f, Vec2(this->getPosition().x - PLAYER_JUMP_OFFSET, this->getPosition().y - default_tmx_height));
	this->runAction(moveBack);
	return true;
}


bool Player::playerJumpLeft(vector<Block*> blocks) {
	for (auto bloc : blocks)
	{
		auto box = getPlayerCheckRect();
		if (GeometryUtils::intersectsRect(bloc->getBlockCheckRect(),Rect(box.getMinX() - default_tmx_width, box.getMinY(),
			box.getMaxX() - box.getMinX(), box.getMaxY() - box.getMinY()))) {
			log("block Rect(%f,%f,%f,%f)",
				bloc->getBlockCheckRect().getMinX(),
				bloc->getBlockCheckRect().getMinY(),
				bloc->getBlockCheckRect().getMaxX()- bloc->getBlockCheckRect().getMinX(),
				bloc->getBlockCheckRect().getMaxY()- bloc->getBlockCheckRect().getMinY());

			log("palyer Rect(%f,%f,%f,%f)",
				box.getMinX(),
				box.getMinY(),
				box.getMaxX() - box.getMinX(),
				box.getMaxY() - box.getMinY());
			return false;
		}
	}
	playPlayerTiaoYueLeft();
	auto moveLeft = MoveTo::create(0.2f, Vec2(this->getPosition().x - default_tmx_width, this->getPosition().y));
	this->runAction(moveLeft);
	return true;
}


bool Player::playerJumpRight(vector<Block*> blocks) {

	for (auto bloc : blocks)
	{
		auto box = getPlayerCheckRect();
		if (GeometryUtils::intersectsRect(bloc->getBlockCheckRect(), Rect(box.getMinX() + default_tmx_width, box.getMinY() ,
			box.getMaxX() - box.getMinX(), box.getMaxY() - box.getMinY()))) {
			log("blockR Rect(%f,%f,%f,%f)",
				bloc->getBlockCheckRect().getMinX(),
				bloc->getBlockCheckRect().getMinY(),
				bloc->getBlockCheckRect().getMaxX() - bloc->getBlockCheckRect().getMinX(),
				bloc->getBlockCheckRect().getMaxY() - bloc->getBlockCheckRect().getMinY());

			log("palyerR Rect(%f,%f,%f,%f)",
				box.getMinX(),
				box.getMinY(),
				box.getMaxX() - box.getMinX(),
				box.getMaxY() - box.getMinY());
			return false;
		}
	}
	playPlayerTiaoYueRight();
	auto moveRight = MoveTo::create(0.2f, Vec2(this->getPosition().x + default_tmx_width, this->getPosition().y));
	this->runAction(moveRight);
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

//void Player::playPlayerHuiTan(std::function<void()> listener) {
//	auto playerTimeLine = CSLoader::createTimeline("rw.csb");
//	playerTimeLine->play("huitan", false);
//	playerTimeLine->setLastFrameCallFunc(listener);
//	hero->runAction(playerTimeLine);
//}

void Player::playPlayerTiaoYue() {
	auto playerTimeLine = CSLoader::createTimeline("rw.csb");
	playerTimeLine->play("tiaoyue", false);
	hero->runAction(playerTimeLine);
}

void Player::playPlayerJiYaLeft() {
	auto playerTimeLine = CSLoader::createTimeline("rw.csb");
	playerTimeLine->play("jiyazuo", false);
	hero->runAction(playerTimeLine);
}

//void Player::playPlayerHuiTanLeft(std::function<void()> listener) {
//	auto playerTimeLine = CSLoader::createTimeline("rw.csb");
//	playerTimeLine->play("huitanzuo", false);
//	playerTimeLine->setLastFrameCallFunc(listener);
//	hero->runAction(playerTimeLine);
//}

void Player::playPlayerTiaoYueLeft() {
	auto playerTimeLine = CSLoader::createTimeline("rw.csb");
	playerTimeLine->play("tiaoyuezuo", false);
	hero->runAction(playerTimeLine);
}

void Player::playPlayerJiYaRight() {
	auto playerTimeLine = CSLoader::createTimeline("rw.csb");
	playerTimeLine->play("jiyayou", false);
	hero->runAction(playerTimeLine);
}

//void Player::playPlayerHuiTanRight(std::function<void()> listener) {
//	auto playerTimeLine = CSLoader::createTimeline("rw.csb");
//	playerTimeLine->play("huitanyou", false);
//	playerTimeLine->setLastFrameCallFunc(listener);
//	hero->runAction(playerTimeLine);
//}

void Player::playPlayerTiaoYueRight() {
	auto playerTimeLine = CSLoader::createTimeline("rw.csb");
	playerTimeLine->play("tiaoyueyou", false);
	hero->runAction(playerTimeLine);
}

void Player::playPlayerJiYaBack() {
	auto playerTimeLine = CSLoader::createTimeline("rw.csb");
	playerTimeLine->play("jyqian", false);
	hero->runAction(playerTimeLine);
}

//void Player::playPlayerHuiTanBack(std::function<void()> listener) {
//	auto playerTimeLine = CSLoader::createTimeline("rw.csb");
//	playerTimeLine->play("huitanqian", false);
//	playerTimeLine->setLastFrameCallFunc(listener);
//	hero->runAction(playerTimeLine);
//}

void Player::playPlayerTiaoYueBack() {
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

