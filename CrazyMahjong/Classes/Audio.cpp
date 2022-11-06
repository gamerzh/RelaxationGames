#include "Audio.h"


Audio* Audio::m_instance = nullptr;

Audio* Audio::getInstance(){
    if(m_instance == nullptr){
        m_instance = new Audio();
        m_instance->init();
    }
    return m_instance;
}

void Audio::setSoundValue(float value)
{
	UserDefault::getInstance()->setFloatForKey("soundvalue", value);
	AudioEngine::setVolume(bgmId, getSoundValue()*isOpenBgm());
}
void Audio::init(){

}
bool Audio::isOpenBgm()
{
	return UserDefault::getInstance()->getBoolForKey("isOpenBgm", true);
}
void Audio::setOpenBgm(bool isOpen)
{
	UserDefault::getInstance()->setBoolForKey("isOpenBgm", isOpen);
	AudioEngine::setVolume(getBgmId(), getSoundValue()*isOpenBgm()*0.8);
}

bool Audio::isOpenEffect()
{
	return UserDefault::getInstance()->getBoolForKey("isOpenEffect", true);
}
void Audio::setOpenEffect(bool isOpen)
{
	UserDefault::getInstance()->setBoolForKey("isOpenEffect", isOpen);
}
void Audio::playBGM(int type){
	const char* path;
	if (type == 1)
	{
		path = "audio/hall_background_music.mp3";
	}
	else
	{
		path = "audio/mahjong_bgm.mp3";
	}

	AudioEngine::stop(bgmId);
	int id = AudioEngine::play2d(path, true, getSoundValue()*isOpenBgm());
	setBgmId(id);
}


int Audio::getSexByRole(int roleindex)
{
	if (roleindex == 1 || roleindex == 3 || roleindex == 4 || roleindex == 5 || roleindex == 8 || roleindex == 9)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
void Audio::playMahjongByRole(int type, int roleindex)
{
	playMahjong(type, getSexByRole(roleindex));
}
//1-9   一万-九万
//-1 - -9  九筒-一筒

void Audio::playMahjong(int type,int gender){
	String* path;
	if (type>0)
	{
		if (gender==0)
		{
			path = String::createWithFormat("audio/famale/Wan_%d.ogg", type);
		}
		else
		{
			path = String::createWithFormat("audio/male/Wan_%d.mp3", type);
		}
		
	}
	else
	{
		if (gender == 0)
		{
			path = String::createWithFormat("audio/famale/Tong_%d.ogg", type+10);
		}
		else
		{
			path = String::createWithFormat("audio/male/Tong_%d.mp3", type+10);
		}
	}
	play2d(path->getCString(), false, getSoundValue()*isOpenEffect());
	return;
}

void Audio::playSoundPeng(int roleindex){
	int gender = getSexByRole(roleindex);
	std::string path;
	if (gender == 0)
	{
		path = "audio/famale/Operate_Peng.ogg";
	}
	else
	{
		path = "audio/male/Operate_Peng.mp3";
	}
	play2d(path, false, getSoundValue()*isOpenEffect());
	return;
 
}

void Audio::playSoundGang(int roleindex){
	int gender = getSexByRole(roleindex);
	std::string path;
	if (gender == 0)
	{
		path = "audio/famale/Operate_Gang.ogg";
	}
	else
	{
		path = "audio/male/Operate_Gang.mp3";
	}
	play2d(path, false, getSoundValue()*isOpenEffect());
	return;
}

void Audio::playSoundLiuJu(int roleindex){
	/*int gender = getSexByRole(roleindex);
	if(gender==1){
	AudioEngine::play2d("audio/male/liuju_1.ogg",false,getSoundValue());
	}else{
	AudioEngine::play2d("audio/famale/liuju_1.ogg",false,getSoundValue());
	}*/
}







void Audio::playSoundHu(int type, int roleindex){

	int gender = getSexByRole(roleindex);
	std::string path;
	if (gender == 0)
	{
		if (type == 0)
		{
			path = "audio/famale/Operate_hu.ogg";
		}
		else
		{
			path = "audio/famale/Operate_ZiMo.ogg";
		}
	}
	else
	{
		if (type == 0)
		{
			path = "audio/male/Operate_hu.mp3";
		}
		else
		{
			path = "audio/male/Operate_ZiMo.mp3";
		}
	}
	play2d(path, false, getSoundValue()*isOpenEffect());
	return;
}


int Audio::play2d(const std::string& filePath, bool loop, float volume, const AudioProfile *profile)
{
	CCLOG("Audio play 2d = %s",filePath.c_str());
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	return -1;
#endif
	return AudioEngine::play2d(filePath, loop, volume, profile);
}
