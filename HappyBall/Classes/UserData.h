#pragma once
#include"cocos2d.h"
USING_NS_CC;

class UserData {
public:
	static  UserData* getInstance();

	int getPlayerGoldNum();
	void setPlayerGoldNum(int num);

	int getBestRecord();
	void setBestRecord(int num);

	std::string getCurrentMod();
	void setCurrentMod(std::string msg);

	std::vector<std::string> getPlayerMod();
	void addPlayerMod(std::string msg);

	float getMusicStatus();
	void setMusicStatus(float open);

	bool getShowgGuide();
	void setShowGuide(bool show);

	const Data getBrickDataFromCsb();

private:
	static  UserData* m_instance;
	UserData() {};
};

