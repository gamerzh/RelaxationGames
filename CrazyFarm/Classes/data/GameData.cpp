#include "data/GameData.h"
#include "cocos2d.h"
#include "domain/user/User.h"
using namespace cocos2d;

GameData* GameData::_instance = 0;

GameData::GameData(){
	this->init();
}

void GameData::init(){
	setRoomID(-1);
	setIsOnMaridTask(false);
	setisOnBankrupt(false);
	setisPlayerOneGame(false);
	setShotDiamondCount(0);
	setShotPropCount(0);
	setisOnGameScene(false);
	setisDirectUseSkill(false);
	setisOnGroupComing(false);
	setisLoadMsgOnGame(false);
}

GameData* GameData::getInstance(){
	if(_instance == 0){
		_instance = new GameData();
	}
	return _instance;
}
Turrent GameData::getTurrentData()
{
	auto turrent = ConfigTurrent::getInstance()->getTurrent(nNowLevel); 
	return turrent; 
}

void GameData::setSoundState(bool state) {
	UserDefault::getInstance()->setBoolForKey("soundState", state);
}

bool GameData::getSoundState() {
	return UserDefault::getInstance()->getBoolForKey("soundState", true);
}

void GameData::setMusicState(bool state) {
	UserDefault::getInstance()->setBoolForKey("musicState", state);
}

bool GameData::getMusicState() {
	return UserDefault::getInstance()->getBoolForKey("musicState", true);
}
