#include "Audio.h"
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
void Audio::playLobbyBackgroundMusic(){
    AudioEngine::stop(gameMusicId);
    lobbyMusicId = AudioEngine::play2d(MUSIC_BGM_1,true, UserData::getInstance()->getMusicStatus());
}

void Audio::playGameBackgroundMusic(){
    AudioEngine::stop(lobbyMusicId);
    gameMusicId = AudioEngine::play2d(MUSIC_BGM_2,true, UserData::getInstance()->getMusicStatus());
}

void Audio::playEffect(std::string name){
    
}

void Audio::preloadFiles() {
    AudioEngine::preload(MUSIC_BGM_1);
    AudioEngine::preload(MUSIC_BGM_2);
    AudioEngine::preload(PASS_BALL);
    AudioEngine::preload(RECIVE_BALL);
    AudioEngine::preload(GOAL_BALL);
    AudioEngine::preload(START_GAME);
    AudioEngine::preload(GOAL_KEEPER);
}


