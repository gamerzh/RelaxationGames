#include "Player.h"

bool Player :: init() {
	if (!Sprite::init()) {
		return false;
	}
	initWithFile("player_1.png");
	setScale(0.3f);//²âÊÔÍ¼Æ¬Ëõ·Å±ÈÀý
	return true;
}

void Player::playerJumpStraight() {
	auto turnStraight = RotateTo::create(0.1f,0);
	auto moveStraight = MoveTo::create(0.1f,Vec2(this->getPosition().x, this->getPosition().y+50));
	auto spwan = Spawn::create(turnStraight, moveStraight, NULL);
	this->runAction(spwan);
}


void Player::playerJumpLeft() {
	auto turnLeft = RotateTo::create(0.1f,270);
	auto moveLeft = MoveTo::create(0.1f, Vec2(this->getPosition().x-50, this->getPosition().y ));
	auto spwan = Spawn::create(turnLeft,moveLeft,NULL);
	this->runAction(spwan);
}


void Player::playerJumpRight() {
	auto turnRight = RotateTo::create(0.1f, 90);
	auto moveRight = MoveTo::create(0.1f, Vec2(this->getPosition().x + 50, this->getPosition().y));
	auto spwan = Spawn::create(turnRight, moveRight, NULL);
	this->runAction(spwan);
}

Point Player::getPlayerPoint() {
	return this->getPosition();
}