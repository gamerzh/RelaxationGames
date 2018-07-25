#include "GameStatus.h"

//before invoke main
GameStatus* GameStatus::m_instance = new GameStatus();

GameStatus* GameStatus::getInstance()
{
	return m_instance;
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
