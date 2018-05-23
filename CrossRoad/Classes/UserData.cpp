#include "UserData.h"

//外部初始化 before invoke main
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
	playerMods = split(mods,",");
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

//bool UserData::getDreamTimes() {
//	return UserDefault::getInstance()->getBoolForKey("dream_times", false);
//}
//
//void UserData::setDreamTimes(bool times) {
//	UserDefault::getInstance()->setBoolForKey("dream_times", times);
//}

std::vector<std::string> UserData::split(std::string str, std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str += pattern;
	int size = str.size();

	for (int i = 0; i < size; i++)
	{
		pos = str.find(pattern, i);
		if (pos < size)
		{
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}