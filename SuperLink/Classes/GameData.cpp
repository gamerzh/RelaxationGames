#include "GAMEDATA.h"
#include "cocos2d.h"
using namespace cocos2d;

GAMEDATA* GAMEDATA::_instance = 0;

GAMEDATA::GAMEDATA(){
	this->init();
}
GAMEDATA* GAMEDATA::getInstance(){
	if (_instance == 0){
		_instance = new GAMEDATA();
	}
	return _instance;

}

void GAMEDATA::init(){
	this->level = 0;
	this->score = 1000000;
	this->lastClikTime = 0;
	this->Ascore = 0;
	this->percent = 100;
	this->needResetMap;
	this->needTipPos;
	this->updateScore;
	this->updateProcess = false;
	this->useTipProp = false;
	this->useResetProp = false;
	this->useAddProps = false;
	this->showWaring = false;
	this->updateBtnInfo=false;
	this->updateTimeInfo=false;
}


void GAMEDATA::setMonthCard(bool value){
	UserDefault::getInstance()->setBoolForKey("monthCard", value);
}
bool GAMEDATA::getMonthCard(){
	return UserDefault::getInstance()->getBoolForKey("monthCard", false);
}

void GAMEDATA::setSoundState(bool state) {
	UserDefault::getInstance()->setBoolForKey("soundState",state);
}

bool GAMEDATA::getSoundState() {
	return UserDefault::getInstance()->getBoolForKey("soundState",true);
}

void GAMEDATA::setMusicState(bool state) {
	UserDefault::getInstance()->setBoolForKey("musicState",state);
}

bool GAMEDATA::getMusicState() {
	return UserDefault::getInstance()->getBoolForKey("musicState",true);
}


void GAMEDATA::setDay(int value){

	UserDefault::getInstance()->setIntegerForKey("day",value);
}

int GAMEDATA::getDay(){

	return UserDefault::getInstance()->getIntegerForKey("day",0);

}

void GAMEDATA::setFirstPay(bool value){
	UserDefault::getInstance()->setBoolForKey("first_pay", value);
}

bool GAMEDATA::getFirstPay(){
	return UserDefault::getInstance()->getBoolForKey("first_pay", true);
}


int GAMEDATA::getScore(){
	return score;
}
void GAMEDATA::settime(int value){
	gametime = value;

}

int GAMEDATA::gettime(){

	return gametime;

}


void GAMEDATA::setAchievescore(float value){

	Ascore = value;
}

float GAMEDATA::getAchievescore(){
	return Ascore;
}



void GAMEDATA::setPercent(int value){
	percent = value;

}

int GAMEDATA::getPercent(){

	return percent;

}
int GAMEDATA::getTimes(){
	return UserDefault::getInstance()->getIntegerForKey("game_times", 0);

}

void GAMEDATA::setTimes(int value){
	UserDefault::getInstance()->setIntegerForKey("game_times", value);
}


void GAMEDATA::setScore(int score){
	this->score = score;
	auto record =UserDefault::getInstance()->getIntegerForKey("record",0);
	if(score>record){
		UserDefault::getInstance()->setIntegerForKey("record",score);
	}
}


int GAMEDATA::getLevel(){
	return level;
}

void GAMEDATA::setLevel(int level){
	this->level = level;
}


int  GAMEDATA::getReviveNum(){
	return UserDefault::getInstance()->getIntegerForKey("reviveNum",0);
}

void  GAMEDATA::setReviveNum(int num){
	UserDefault::getInstance()->setIntegerForKey("reviveNum",num);
}

int  GAMEDATA::getResetNum(){
	return UserDefault::getInstance()->getIntegerForKey("resetNum", 0);
}
void   GAMEDATA::setResetNum(int num){
	UserDefault::getInstance()->setIntegerForKey("resetNum", num);
}
int   GAMEDATA::getTimeNum(){
	return UserDefault::getInstance()->getIntegerForKey("timeNum", 0);
}
void   GAMEDATA::setTimeNum(int num){
	UserDefault::getInstance()->setIntegerForKey("timeNum", num);
}
int   GAMEDATA::getTipNum(){
	return UserDefault::getInstance()->getIntegerForKey("tipNum", 0);
}
void   GAMEDATA::setTipNum(int num){
	UserDefault::getInstance()->setIntegerForKey("tipNum", num);
}

 

int GAMEDATA::getLoginTimes(){
	return UserDefault::getInstance()->getIntegerForKey("loginTimes",0);
}


void GAMEDATA::setLoginTimes(int value){
	UserDefault::getInstance()->setIntegerForKey("loginTimes",value);
}

int  GAMEDATA::getLastClikTime(){
	return lastClikTime;
}


void GAMEDATA::setLastClikTime(int clickTime){
	this->lastClikTime = clickTime;
}


long GAMEDATA::getCurrentTime()   
{     
	struct tm *tm;
	time_t timep;
	time(&timep);
	tm = localtime(&timep);
	int day = tm->tm_mday;

	return day;
}  

