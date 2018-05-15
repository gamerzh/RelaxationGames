#pragma once
#include"cocos2d.h"
USING_NS_CC;

//��Ϸ��ʱ״̬��¼
class GameStatus {
public:
	static  GameStatus* getInstance();
	int getScore();
	void plusStepNum();
	void minusStepNum();
	bool getGameStatus();
	void setGameStatus(bool p);
private:
	static  GameStatus* m_instance;
	GameStatus() {}
	int stepNum = 0;
	int socore = 0;
	bool paused = true;
	void setScore(int soc);
};

