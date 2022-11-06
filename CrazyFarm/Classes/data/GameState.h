#ifndef _GAMESTATE_H_
#define _GAMESTATE_H_
#include <string>

class GAMESTATE {
public:
	static GAMESTATE* getInstance();
	void reset();
	void setGamePause(bool pause);
	bool getGamePause();
	void setGameOver(bool over);
	bool getGameOver();
	bool isUsePropFind();
	void setUsePropFind(bool b);
	bool isUsePropTime();
	void setUsePropTime(bool b);
	bool getIsPaying();
	void setIsPaying(bool b);
	bool getIsRevive();
	void setIsRevive(bool b);
	bool getIsShowPayTime();
	void setIsShowPayTime(bool b);
	bool getIsShowPayFind();
	void setIsShowPayFind(bool b);
	bool getIsFirstTask();
	void setIsFirstTask(bool b);
	bool getIsGuide();
	void setIsGuide(bool b);
	bool getIsCreateGuideTask();
	void setIsCreateGuideTask(bool b);
	bool getIsShowMoreGame();
	void setIsShowMoreGame(bool b);
	bool getIsShowPayLevel();
	void setIsShowPayLevel(bool b);
	bool getIsShowMarquee();
	void setIsShowMarquee(bool b);
	std::string getShowMarqueeInfo();
	void setShowMarqueeInfo(std::string info);
private:
	GAMESTATE();
	void init();
	static GAMESTATE* _instance;
	bool gamePause;
	bool gameOver;
	bool isUseFind;
	bool isUseTime;
	bool isRevive;
	bool isPaying; //�Ƿ��Ѿ���֧��
	bool isShowPayTime; //�����Ƿ��Ѿ���������ʱ�Ʒѵ�
	bool isShowPayFind; //�����Ƿ��Ѿ����������ҼƷѵ�
	bool isFirstTask; //�Ƿ��ǵ�һ��������
	bool isGuide;
	bool isCreate;
	bool isShowMoreGame;
	bool isShowPayLevel;
	bool isShowMarquee;
	std::string showNewMarquee;
};
#endif
