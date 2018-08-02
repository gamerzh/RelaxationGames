#pragma once
#include"cocos2d.h"
#include "FootballTeam.h"
#include "Ball.h"
USING_NS_CC;


class GameStatus {
public:
    enum GameType{
        worldCup,
        masterCup
    };
    //游戏场景的状态
    enum GameState{
        game_start,
        game_playing,
        game_end
    };
    static  GameStatus* getInstance();
    Ball* getGameBall();
    void setGameBall(Ball* ball);
    GameState getGameState();
    void setGameState(GameState state);
    FootballTeam* getPlayerTeam();
    void setPlayerTeam(FootballTeam* team);
    FootballTeam* getComputerTeam();
    void setComputerTeam(FootballTeam* team);
    int getCurrentSelectedLevel();
    void setCurrentSelectedLevel(int level);
    GameType getCurrentGameType();
    void setCurrentGameType(GameType type);
    int getPlayerScore();
    void setPlayerScore(int s);
    int getComputerScore();
    void setComputerScore(int s);
private:
    static  GameStatus* m_instance;
    GameStatus() {}
    GameState  gameState;
    Ball* current_ball = nullptr;
    FootballTeam* playerTeam;//玩家操作的队伍
    FootballTeam* computerTeam;//AI控制的队伍
    int currentSelectedLevel = 0;//当前游戏官卡
    GameType currentGameType;
    int computerScore;
    int playerScore;
};

