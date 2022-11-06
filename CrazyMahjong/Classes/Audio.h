#ifndef _AUDIO_H_
#define _AUDIO_H_
#include <string>
#include "cocos2d.h"



#include "audio/include/AudioEngine.h"
USING_NS_CC;
using namespace experimental;


class Audio{
public:
    static Audio* getInstance();
    void init();
    void playBGM(int type);//1:´óÌü 2ÓÎÏ·

    void playMahjong(int type,int gender);
	void playMahjongByRole(int type, int roleindex);

	bool isOpenBgm();
	void setOpenBgm(bool isOpen);

	bool isOpenEffect();
	void setOpenEffect(bool isOpen);

	float getSoundValue(){ return UserDefault::getInstance()->getFloatForKey("soundvalue", 0.5);; };
	void setSoundValue(float value);

public:

    void playSoundPeng(int roleindex);
	void playSoundGang(int roleindex);
	void playSoundLiuJu(int roleindex);
	void playSoundHu(int type, int roleindex);
    
private:
	int play2d(const std::string& filePath, bool loop = false, float volume = 1.0f, const AudioProfile *profile = nullptr);
	int getSexByRole(int roleindex);
private:
    static Audio* m_instance;
    CC_SYNTHESIZE(int, bgmId, BgmId);
	float _soundValue;

};
#endif