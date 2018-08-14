#pragma once
#include"cocos2d.h"
USING_NS_CC;

//ÓÎÏ·ÁÙÊ±×´Ì¬¼ÇÂ¼
class GameStatus {
public:
	static  GameStatus* getInstance();
	int getScore();
	void setScore(int soc);
	int getLevel();
	void setLevel(int soc);
	bool getResurgence();
	void setResurgence(bool re);
	bool getDoubleScore();
	void setDoubleScore(bool d);
	bool getInvincible();
	void setInvincible(bool d);
	bool getGameStart();
	void setGameStart(bool d);
	int getDreamLife();
	void setDreamLife(int life);
private:
	static  GameStatus* m_instance;
	GameStatus() {}
	int socore = 0;
	int level = 0;
	int life = 3;
	bool gameStart = false;
	bool resurgence = false;
	bool doubleScore = false;
	bool invincible = false;
};

