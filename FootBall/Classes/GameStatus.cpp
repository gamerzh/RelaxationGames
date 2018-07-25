#include "GameStatus.h"

//before invoke main
GameStatus* GameStatus::m_instance = new GameStatus();

GameStatus* GameStatus::getInstance()
{
	return m_instance;
}

int GameStatus::getPlayerTeamId() {
	return this->playerTeamId;
}

void GameStatus::setPlayerTeamId(int id) {
	this->playerTeamId = id;
}

int GameStatus::getComputerTeamId() {
	return this->computerTeamId;
}

void GameStatus::setComputerTeamId(int id) {
	this->computerTeamId = id;
}

Ball* GameStatus::getGameBall(){
    return this->current_ball;
}

void GameStatus::setGameBall(Ball* ball){
    this->current_ball = ball;
}

GameState GameStatus::getGameState(){
    return this->gameState;
}

void GameStatus::setGameState(GameState state){
    this->gameState = state;
}
