#pragma once
#include"cocos2d.h"
USING_NS_CC;

class GameStatus {
public:
	static  GameStatus* getInstance();
	int getPlayerTeamId();
	void setPlayerTeamId(int id);
	int getComputerTeamId();
	void setComputerTeamId(int id);
private:
	static  GameStatus* m_instance;
	GameStatus() {}
	int playerTeamId = 0;
	int computerTeamId = 0;
};

