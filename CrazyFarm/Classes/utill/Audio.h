#ifndef _AUDIO_H_
#define _AUDIO_H_
#include <string>
#include "utill/define.h"
//BGM
#define GAMEBGM "game/audio/bgm/gameBGM.mp3"
#define LOBBYBGM "game/audio/bgm/lobbyBGM.mp3"
#define FISHFLOCKBGM "game/audio/bgm/fishflockBGM.ogg"
#define BOSSBGM "game/audio/bgm/bossBGM.ogg"
//EFFECT
#define SKILLBOOM "game/audio/skillBoom.ogg"
#define SKILLFREEZE "game/audio/propEffect/freeze.ogg"
#define SKILLLASER "game/audio/propEffect/laser.ogg"
#define SKILLSUMMON "game/audio/skilSummon.ogg"
#define BOSSWARN "game/audio/BossWarn.ogg"
#define CATCHGIRLFISH "game/audio/CatchGirlFish.ogg"
#define CATCHGOLD "game/audio/catchgold.ogg"
#define CATCHGOLDTURNTABLE "game/audio/sfx_coin.mp3"
#define CLEARFISH "game/audio/clearFish.ogg"
#define CLICKCANCER "game/audio/clickcancer.ogg"
#define CLICKSURE "game/audio/clicksure.ogg"
#define GAINBOX "game/audio/gainBox.ogg"
#define GAINCOIN "game/audio/gainCoin.ogg"
#define GAINDIAMOND "game/audio/gainDiamond.ogg"
#define GIRLAPPEAR "game/audio/girlAppear.ogg"
#define GIRLMISSIONSUCCESS "game/audio/girlMissionSuccess.ogg"
#define LUCKYGAIN "game/audio/luckygain.ogg"
#define PROPINBOX "game/audio/propInBox.ogg"
#define SIGN "game/audio/sign.ogg"
#define UPDATALEVEL "game/audio/updataLevel.ogg"
#define UPDATATURRET "game/audio/updataTurret.ogg"
#define UPDATALEVELGAINCOIN "game/audio/updataTurretGainCoin.mp3"
#define ONGOLDFISHDEAD "game/audio/onGoldFishDead.mp3"
#define FISH50JUMP "game/audio/fish_50jump.ogg"
#define OPENNEWBBOX "game/audio/opennewbbox.ogg"
#define CHANGETURRENT "game/audio/changeTurret.mp3"
#define FRUITSIGN "game/audio/fruitsign.ogg"
#define GETCOIN "game/audio/getCoin.mp3"
class Audio{
public:
	static Audio* getInstance();
	void playBGM(const char* soundName);
	void playSound(const char* soundName);
	void pauseBGM();
	void resumeBGM();
	void prepare();
	void setBGMValue(float value);
	void setEffectValue(float value);
	//ÕæÈËÉùÒô
	void playZhenrenVoice();
	//¿ª»ð
	void playShootVoic();
private:
	static Audio* m_instance;
	Audio();
	const char* KEY_BGMPERCENT = "KEY_BGMPERCENT";
	CC_SYNTHESIZELOCALFLOAT(KEY_BGMPERCENT, BgmPercent, 0.6);
	const char* KEY_SOUNDPERCENT = "KEY_SOUNDPERCENT";
	CC_SYNTHESIZELOCALFLOAT(KEY_SOUNDPERCENT, SoundPercent, 0.6);

};
#endif