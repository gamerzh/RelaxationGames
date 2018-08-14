#include "GameStatus.h"

//before invoke main
GameStatus* GameStatus::m_instance = new GameStatus();

GameStatus* GameStatus::getInstance()
{
	return m_instance;
}

int GameStatus::getScore() {
	return this->socore;
}

void GameStatus::setScore(int soc) {
	this->socore = soc;
}

int GameStatus::getLevel() {
	return this->level;
}

void GameStatus::setLevel(int soc) {
	this->level = soc;
}

bool GameStatus::getResurgence() {
	return resurgence;
}

void GameStatus::setResurgence(bool re) {
	resurgence = re;
}

bool GameStatus::getDoubleScore() {
	return doubleScore;
}

void GameStatus::setDoubleScore(bool d) {
	doubleScore = d;
}

bool GameStatus::getInvincible() {
	return invincible;
}

void GameStatus::setInvincible(bool d) {
	invincible = d;
}

bool GameStatus::getGameStart() {
	return gameStart;
}
void GameStatus::setGameStart(bool d) {
	gameStart = d;
}

int GameStatus::getDreamLife() {
	return life;
}

void GameStatus::setDreamLife(int life) {
	this->life = life;
}