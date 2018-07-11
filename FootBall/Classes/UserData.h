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

	int getTeamSpeedLevel();
	void setTeamSpeedLevel(int level);

	int getTeamShootLevel();
	void setTeamShootLevel(int level);

	int getTeamEnergyLevel();
	void setTeamEnergyLevel(int level);

	int getWorldCupLevel();
	void setWorldCupLevel();

	int getMasterCupLevel();
	void setMasterCupLevel();

private:
	static  UserData* m_instance;
	UserData() {};
};

