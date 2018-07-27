#pragma once
#include"cocos2d.h"
#include "FootballTeam.h"
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

    Ball* getGameBall();
    void setGameBall(Ball* ball);
    GameState getGameState();
    void setGameState(GameState state);
    FootballTeam* getPlayerTeam();
    void setPlayerTeam(FootballTeam* team);
    FootballTeam* getComputerTeam();
    void setComputerTeam(FootballTeam* team);
private:
    static  GameStatus* m_instance;
    GameStatus() {}
    GameState  gameState;
    Ball* current_ball = nullptr;
    FootballTeam* playerTeam;//玩家操作的队伍
    FootballTeam* computerTeam;//AI控制的队伍

};

