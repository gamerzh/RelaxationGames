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

int UserData::getBestRecord() {
	return UserDefault::getInstance()->getIntegerForKey("best_record", 0);
}

void UserData::setBestRecord(int num) {
	UserDefault::getInstance()->setIntegerForKey("best_record", num);
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
	std::vector<std::string> playerOldMods = StringTools::split(mods, ",");
	//�����ظ�����
	for (auto var : playerOldMods) {
		if (msg == var) {
			return;
		}
	}
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

const Data UserData::getBrickDataFromCsb() {
	return FileUtils::getInstance()->getDataFromFile("qqdh.csb");
}