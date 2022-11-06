#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_
#include "cocos2d.h"

using namespace cocos2d;

class GAMEDATA{
public:


	static GAMEDATA* getInstance();

	enum GameState
	{
		Playing = 1,
		Ready = 2,
		Pause = 3,
		End = 4,
		Over = 5,
		Start,
		Paying
	};
	GameState gameState;
	void init();
	void setMonthCard(bool value);
	bool getMonthCard();
	void setSoundState(bool state);
	bool getSoundState();
	void setMusicState(bool state);
	bool getMusicState();

	void setDay(int value);
	int getDay();
	int  getLoginTimes();
	void setLoginTimes(int value);

	void setScore(int score);
	int  getScore();


	int  getLastClikTime();
	void setLastClikTime(int clickTime);


	
	float getAchievescore();
	void setAchievescore(float value);

	int getPercent();
	void setPercent(int value);

	int getcurrentTime();
	void setcurrentTime(int level);

	int getLevel();//��Ϸ�ؿ���
	void setLevel(int level);
	void settime(int value);//��Ϸʱ��
	int  gettime();
	int getTimes();//��Ϸ����
	void setTimes(int value);
	long getCurrentTime();


	bool needResetMap;
	bool needTipPos; 
	bool updateScore;
	bool updateProcess;
	bool useTipProp;
	bool useResetProp;
	bool useAddProps;
	bool updateBtnInfo;
	bool updateTimeInfo;
	bool showWaring;
	//�Ʒѵ����
	void setFirstPay(bool value);
	bool getFirstPay();
	int  getReviveNum();//�������
	void  setReviveNum(int num);
	int  getResetNum();//����
	void  setResetNum(int num);
	int  getTimeNum();//��ʱ
	void  setTimeNum(int num);
	int  getTipNum();//��ʾ
	void  setTipNum(int num);
	bool openMoreGame;
	bool openTehui;

	//event 32 35 
	CC_SYNTHESIZE(bool, isPayThisCount, ispaythiscount);
	CC_SYNTHESIZE(bool, isAutoBegin, isautobegin);
	bool  getispay();
	void  setispay(bool bRet);
	std::vector<int>  levelvector;


private:
	GAMEDATA();
	CC_SYNTHESIZE(bool, isFirstTimeGame, isfirsttimegame);
	CC_SYNTHESIZE(bool,isReliveInThisLevel,isreliveinthislevel)
	static GAMEDATA* _instance;
	bool first_login;
	int score;//��ǰ��Ϸ����
	int level=0;//�ؿ�
	int lastClikTime;
	int gametime;//��Ϸʱ��

	float Ascore;
	int percent;
};

#endif
