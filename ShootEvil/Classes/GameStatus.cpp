#include "GameStatus.h"

//before invoke main
GameStatus* GameStatus::m_instance = new GameStatus();

GameStatus* GameStatus::getInstance()
{
	return m_instance;
}

void GameStatus::plusStepNum() {
	this->stepNum = this->stepNum +1;
	if (this->stepNum > this->socore) {
		this->socore = this->stepNum;
		if (this->isdouble) {
			doubleScore = socore;
		}
	}
}

void GameStatus::minusStepNum() {
	this->stepNum = this->stepNum - 1;
}

void GameStatus::cleanScore() {
	this->stepNum = 0;
	this->socore = 0;
	this->doubleScore = 0;
}

int GameStatus::getScore() {
	return this->socore+this->doubleScore;
}

void GameStatus::setScore(int soc) {
	this->socore = soc;
}

bool GameStatus::getGameStatus() {
	return this->paused;
}

void GameStatus::setGameStatus(bool p) {
	this->paused = p;
}

bool GameStatus::getInvincible() {
	return this->invincible;
}


void GameStatus::setInvincible(bool p) {
	this->invincible = p;
}

void GameStatus::setDoubleScore(bool d) {
	this->isdouble = d;
}

bool GameStatus::getResurgence() {
	return this->resurgence;
}

void GameStatus::setResurgence(bool r) {
	this->resurgence = r;
}