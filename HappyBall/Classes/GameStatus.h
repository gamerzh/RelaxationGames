#pragma once
#include"cocos2d.h"
USING_NS_CC;

//��Ϸ��ʱ״̬��¼
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
	void setDoubleScore(bool d);
	bool getResurgence();
	void setResurgence(bool r);
private:
	static  GameStatus* m_instance;
	GameStatus() {}
	int stepNum = 0;
	int socore = 0;
	int doubleScore = 0;
	bool paused = true;
	bool invincible = false;
	bool resurgence = false;
	bool isdouble = false;
	void setScore(int soc);
};

