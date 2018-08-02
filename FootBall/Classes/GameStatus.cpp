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

GameStatus::GameState GameStatus::getGameState(){
    return this->gameState;
}

void GameStatus::setGameState(GameState state){
    this->gameState = state;
}

FootballTeam* GameStatus::getPlayerTeam(){
    return this->playerTeam ;
}

void GameStatus::setPlayerTeam(FootballTeam* team){
    this->playerTeam = team;
}

FootballTeam* GameStatus::getComputerTeam(){
    return  this->computerTeam;
}

void GameStatus::setComputerTeam(FootballTeam* team){
    this->computerTeam = team;
}

int GameStatus::getCurrentSelectedLevel(){
    return  this->currentSelectedLevel;
}

void GameStatus::setCurrentSelectedLevel(int level){
    this->currentSelectedLevel = level;
}

GameStatus::GameType GameStatus::getCurrentGameType(){
    return  this->currentGameType;
}

void GameStatus::setCurrentGameType(GameType type){
    this->currentGameType = type;
}

int GameStatus::getPlayerScore(){
    return  playerScore;
}
void GameStatus::setPlayerScore(int s){
    playerScore = s;
}

int GameStatus::getComputerScore(){
    return computerScore;
}

void GameStatus::setComputerScore(int s){
    computerScore = s;
}




