#pragma once
#include"cocos2d.h"
USING_NS_CC;

//ÓÎÏ·ÁÙÊ±×´Ì¬¼ÇÂ¼
class GameStatus {
public:
	static  GameStatus* getInstance();
	int getScore();
	void cleanScore();
	void plusStepNum();
	void minusStepNum();
	bool getGameStatus();
	void setGameStatus(bool p);
	bool getInvincible();
	void setInvincible(bool p);
private:
	static  GameStatus* m_instance;
	GameStatus() {}
	int stepNum = 0;
	int socore = 0;
	bool paused = true;
	bool invincible = false;
	void setScore(int soc);
};

