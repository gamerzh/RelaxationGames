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
    AudioEngine::play2d("audio/main.mp3",true, UserData::getInstance()->getMusicStatus());
}


void Audio::preloadFiles() {
	AudioEngine::preload(MUSIC_BGM);
	AudioEngine::preload(MUSIC_CLICK);
}


