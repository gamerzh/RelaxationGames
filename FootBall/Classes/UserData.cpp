#include "UserData.h"
#include "StringTools.h"

//before invoke main
UserData* UserData::m_instance = new UserData();

UserData* UserData::getInstance()
{
	return m_instance;
}

int UserData::getPlayerGoldNum() {
	return UserDefault::getInstance()->getIntegerForKey("user_gold", 0);
}

void UserData::setPlayerGoldNum(int num) {
	UserDefault::getInstance()->setIntegerForKey("user_gold", num);
}

std::string UserData::getCurrentMod() {
	return UserDefault::getInstance()->getStringForKey("user_mod", "0");
}

void UserData::setCurrentMod(std::string msg) {
	UserDefault::getInstance()->setStringForKey("user_mod", msg);
}

std::vector<std::string> UserData::getPlayerMod() {
	std::vector<std::string> playerMods;
	auto mods = UserDefault::getInstance()->getStringForKey("user_mod_lsit","0");
	playerMods = StringTools::split(mods,",");
	return playerMods;
}
void UserData::addPlayerMod(std::string msg) {
	if (msg == "" && msg.size() == 0) {
		return;
	}
	auto mods = UserDefault::getInstance()->getStringForKey("user_mod_lsit", "0");
	auto newMods = mods + "," + msg;
	UserDefault::getInstance()->setStringForKey("user_mod_lsit", newMods);
}


float UserData::getMusicStatus() {
	return UserDefault::getInstance()->getFloatForKey("music_status", 1.0);
}


void UserData::setMusicStatus(float open) {
	UserDefault::getInstance()->setFloatForKey("music_status", open);
}

bool UserData::getShowgGuide() {
	return UserDefault::getInstance()->getBoolForKey("show_guide", false);
}

void UserData::setShowGuide(bool show) {
	UserDefault::getInstance()->setBoolForKey("show_guide", show);
}

int UserData::getTeamSpeedLevel() {
	return UserDefault::getInstance()->getIntegerForKey("team_speed", 0);
}

void UserData::setTeamSpeedLevel(int level) {
	UserDefault::getInstance()->setIntegerForKey("team_speed", level);
}


int UserData::getTeamShootLevel() {
	return UserDefault::getInstance()->getIntegerForKey("team_shoot", 0);
}

void UserData::setTeamShootLevel(int level) {
	UserDefault::getInstance()->setIntegerForKey("team_shoot", level);
}

int UserData::getTeamEnergyLevel() {
	return UserDefault::getInstance()->getIntegerForKey("team_energy", 0);
}

void UserData::setTeamEnergyLevel(int level) {
	UserDefault::getInstance()->setIntegerForKey("team_energy", level);
}

int UserData::getWorldCupLevel() {
	return UserDefault::getInstance()->getIntegerForKey("world_level", 0);
}

void UserData::setWorldCupLevel() {
	UserDefault::getInstance()->setIntegerForKey("world_level", 0);
}

int UserData::getMasterCupLevel() {
	return UserDefault::getInstance()->getIntegerForKey("master_level", 0);
}

void UserData::setMasterCupLevel() {
	UserDefault::getInstance()->setIntegerForKey("master_level", 0);
}