#pragma once
#include"cocos2d.h"
#include "FootMan.h"
#include "Ball.h"
USING_NS_CC;

class GameStatus {
public:
    static  GameStatus* getInstance();
    std::vector<FootMan*> currentPlayerTeam;
    std::vector<FootMan*> currentComputerTeam;
    int getPlayerTeamId();
    void setPlayerTeamId(int id);
    int getComputerTeamId();
    void setComputerTeamId(int id);
    Ball* getGameBall();
    void setGameBall(Ball* ball);
private:
    static  GameStatus* m_instance;
    GameStatus() {}
    int playerTeamId = 0;
    int computerTeamId = 0;
    Ball* current_ball = nullptr;
};

