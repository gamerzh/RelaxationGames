#pragma once
#include"cocos2d.h"
USING_NS_CC;

//��Ϸ��ʱ״̬��¼
class GameStatus {
public:
	static  GameStatus* getInstance();
	int getScore();
	void setScore(int soc);
private:
	static  GameStatus* m_instance;
	GameStatus() {}
	int socore = 0;
};

