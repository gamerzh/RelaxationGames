#ifndef _AUDIO_H_
#define _AUDIO_H_
#include <string>
#include "cocos2d.h"
#include "AudioConfig.h"

class Audio{
public:
    static Audio* getInstance();
    void init();
    void pauseBackgroundMusic();
    void playLobbyBackgroundMusic();
    void playGameBackgroundMusic();
    void playEffect(std::string name);
private:
    static Audio* m_instance;
	void preloadFiles();
    int lobbyMusicId;
    int gameMusicId;
};
#endif
