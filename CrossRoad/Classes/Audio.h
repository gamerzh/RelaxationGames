#ifndef _AUDIO_H_
#define _AUDIO_H_
#include <string>
#include "cocos2d.h"

class Audio{
public:
    static Audio* getInstance();
    void init();
    void playBGM();
	void playSoundLight();
	void playSoundTrain();
	void playSoundCar();
	void playSoundJump();
	void playSoundHit();
	void playSoundWater();
	void playSoundGold();
	void playSoundHawk();
	void playSoundBoard();
	void controllSound(bool open);
    CC_SYNTHESIZE(int, musicId,MusicId);
private:
	const float soundValue = 0.8;
    static Audio* m_instance;
};
#endif
