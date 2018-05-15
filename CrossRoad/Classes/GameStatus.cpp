#include "GameStatus.h"

//外部初始化 before invoke main
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