#pragma once
#include"cocos2d.h"
USING_NS_CC;

class UserData {
public:
	static  UserData* getInstance();

	int getPlayerGoldNum();
	void setPlayerGoldNum(int num);
	std::string getCurrentMod();
	void setCurrentMod(std::string msg);
	std::vector<std::string> getPlayerMod();
	void addPlayerMod(std::string msg);
	float getMusicStatus();
	void setMusicStatus(float open);
	bool getShowgGuide();
	void setShowGuide(bool show);
	bool getDreamTimes();
	void setDreamTimes(bool times);
private:
	static  UserData* m_instance;
	UserData() {};
	std::vector<std::string> split(std::string str, std::string pattern);
};

