#include "Audio.h"
#include "AudioConfig.h"
#include "UserData.h"
#include "audio/include/AudioEngine.h"

using namespace cocos2d::experimental;

Audio* Audio::m_instance = nullptr;

Audio* Audio::getInstance(){
    if(m_instance == nullptr){
        m_instance = new Audio();
        m_instance->init();
    }
    return m_instance;
}

void Audio::init(){

}

void Audio::playBGM(){
   int id =  AudioEngine::play2d(MUSIC_BGM,true, UserData::getInstance()->getMusicStatus());
   setBgmId(id);
}


void Audio::playJump() {
	AudioEngine::play2d(MUSIC_JUMP, false, UserData::getInstance()->getMusicStatus());
}

void Audio::preloadFiles() {
	AudioEngine::preload(MUSIC_BGM);
	AudioEngine::preload(MUSIC_JUMP);
}

void Audio::controllSound(bool open) {
	if (open) {
		UserData::getInstance()->setMusicStatus(1.0f);
		AudioEngine::setVolume(getBgmId(), UserData::getInstance()->getMusicStatus());
	}
	else {
		UserData::getInstance()->setMusicStatus(0);
		AudioEngine::setVolume(getBgmId(), UserData::getInstance()->getMusicStatus());
		
	}
}

void Audio::vibrate() {
	if (UserData::getInstance()->getMusicStatus() > 0) {
		Device::vibrate(0.01f);
	}
}


