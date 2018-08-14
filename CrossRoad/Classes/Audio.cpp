#include "Audio.h"
#include "UserData.h"
#include "audio/include/AudioEngine.h"

using namespace experimental;

Audio* Audio::m_instance = nullptr;

Audio* Audio::getInstance(){
    if(m_instance == nullptr){
        m_instance = new Audio();
        m_instance->init();
    }
    return m_instance;
}

void Audio::init(){
    setMusicId(-999);
	AudioEngine::preload("audio/main.mp3");
	AudioEngine::preload("audio/light.mp3");
	AudioEngine::preload("audio/train.mp3");
	AudioEngine::preload("audio/car.mp3");
	AudioEngine::preload("audio/jump.mp3");
	AudioEngine::preload("audio/hit.mp3");
	AudioEngine::preload("audio/water.mp3");
	AudioEngine::preload("audio/gold.mp3");
	AudioEngine::preload("audio/hawk.mp3");
	AudioEngine::preload("audio/board.mp3");
}

void Audio::playBGM(){
    int id = AudioEngine::play2d("audio/main.mp3",true, UserData::getInstance()->getMusicStatus()*0.6);
	setMusicId(id);
}


void Audio::playSoundLight() {
	AudioEngine::play2d("audio/light.mp3", false, UserData::getInstance()->getMusicStatus());
}

void Audio::playSoundTrain() {
	AudioEngine::play2d("audio/train.mp3", false, UserData::getInstance()->getMusicStatus());
}

void Audio::playSoundCar() {
	AudioEngine::play2d("audio/car.mp3", false, UserData::getInstance()->getMusicStatus());
}

void Audio::playSoundJump() {
	AudioEngine::play2d("audio/jump.mp3", false, UserData::getInstance()->getMusicStatus());
}

void Audio::playSoundHit() {
	AudioEngine::play2d("audio/hit.mp3", false, UserData::getInstance()->getMusicStatus());
}

void Audio::playSoundWater() {
	AudioEngine::play2d("audio/water.mp3", false, UserData::getInstance()->getMusicStatus());
}

void Audio::playSoundGold() {
	AudioEngine::play2d("audio/gold.mp3", false, UserData::getInstance()->getMusicStatus());
}

void Audio::playSoundHawk() {
	AudioEngine::play2d("audio/hawk.mp3", false, UserData::getInstance()->getMusicStatus());
}

void Audio::playSoundBoard() {
	AudioEngine::play2d("audio/board.mp3", false, UserData::getInstance()->getMusicStatus());
}

void Audio::controllSound(bool open) {
	if (open) {
		AudioEngine::setVolume(getMusicId(),soundValue);
		UserData::getInstance()->setMusicStatus(1.0f);
	}
	else {
		AudioEngine::setVolume(getMusicId(), 0);
		UserData::getInstance()->setMusicStatus(0);
	}
}





