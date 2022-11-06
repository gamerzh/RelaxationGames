package com.hifreshday.android.setting.aidl;

import java.util.List;
import android.content.Context;
/**
 * 音乐播放服务
 */
interface MusicPlayAidlService{
	// 初始化音乐对象
	void bgMusicInit(in int resId);
	// 播放背景音乐
	void bgMusicPlay(in boolean loop);
	// 播放自定义背景音乐
	void bgMusicPlay2(int resId,boolean loop);
	// 暂停背景音乐
	void bgMusicPause();
	// 恢复背景音乐
	void bgMusicResume();
	// 停止背景音乐
	void bgMusicStop();
	// 播放游戏音乐
	void gameMusicPlay(int resId);
	// 获取背景音播放状态
	int getBGState();
	// 调整背景音量
	void adjustBgMusicVolume(float volumn);
}