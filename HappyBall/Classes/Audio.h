#ifndef _AUDIO_H_
#define _AUDIO_H_
#include <string>
#include "cocos2d.h"

class Audio{
public:
    static Audio* getInstance();
    void init();
    void playBGM();
	void playJump();
	void vibrate();//Υπ¶―;
	void controllSound(bool open);
	CC_SYNTHESIZE(int,bgmId,BgmId);
private:
    static Audio* m_instance;
	void preloadFiles();
	
};
#endif
