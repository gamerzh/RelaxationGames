#pragma once
#include"cocos2d.h"
#include "FootMan.h"
#include "Ball.h"
USING_NS_CC;

//游戏场景的状态
enum GameState{
    game_start,
    game_playing,
    game_end
};

class GameStatus {
public:
    static  GameStatus* getInstance();
    std::vector<FootMan*> currentPlayerTeam;
    std::vector<FootMan*> currentComputerTeam;
    Ball* getGameBall();
    void setGameBall(Ball* ball);
    GameState getGameState();
    void setGameState(GameState state);
private:
    static  GameStatus* m_instance;
    GameStatus() {}
    Ball* current_ball = nullptr;
    GameState  gameState;
};

