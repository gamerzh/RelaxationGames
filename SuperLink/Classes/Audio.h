#ifndef _AUDIO_H_
#define _AUDIO_H_
#include <string>

#define BACKGORUNDMUSIC "raw/bg_music.mp3"

#define CLICK "raw/game_item_click.ogg"
#define ELECTRICITY "raw/game_conn_shine.ogg"//电流声
#define TIMEOVER "raw/time_over.mp3"
#define readyGo "raw/game_go.wav"
#define HITITEM "raw/paddle_hit.wav"

#define CONN_1 "raw/game_conn_1.ogg"//对应连击数
#define CONN_2 "raw/game_conn_2.ogg"
#define CONN_3 "raw/game_conn_3.ogg"
#define CONN_4 "raw/game_conn_4.ogg"
#define CONN_5 "raw/game_conn_5.ogg"
#define GAME_FAIL "raw/game_fail.wav"
#define GAME_SUCCESS "raw/game_success.ogg"

#define PAY_RESULT_FAIL "raw/pay_result_fail.ogg"
#define PAY_RESULT_SUCCESS "raw/pay_result_success.ogg"
#define TIME_LEAVE "raw/time_leave.ogg"
#define GAME_START "raw/game_start.ogg"

class Audio{
public:
	static Audio* getInstance();
	void playBGM();
	void playReadyGo();
	void playBtnEffect();
	void cleanitem();
	void playSound(char* soundName);
	void prepare();
	void hititems();
	void timeover();
private:
	static Audio* m_instance;
	
};
#endif