package com.xiao.fish;

import com.xiao.fish.domain.PlayerInfo;

public class PxGameConstants {
	// 初始化音乐
	public static final String MUSIC_INIT = "com.poxiao.fish.activity.SplashActivity.MUSIC_INIT";
	// 背景音乐禁止
	public static final String MUSIC_DISABLED = "com.poxiao.fish.activity.SplashActivity.MUSIC_DISABLED";
	// 背景音乐启动
	public static final String MUSIC_ENABLED = "com.poxiao.fish.activity.SplashActivity.MUSIC_ENABLED";
	// 背景音乐播放
	public static final String MUSIC_PLAY = "com.poxiao.fish.activity.SplashActivity.MUSIC_PLAY";
	// 背景音乐在配置文件中保存的KEY
	public static final String BACKGROUND_MUSIC_SETTING_KEY = "com.poxiao.fish.activity.SettingActivity2.BACKGROUND_MUSIC_CHECK_KEY";

	public static final int POOL_SIZE = 25;// 屏幕中允许存在的鱼的数量
	public static final int MAX_ENERGY = 2500;// 能量池的上限
	public static boolean IS_CHANGE_CANNON = false;// true->炮塔不可操作
	public static boolean IS_SHOW_SETTING = false;// 设置界面是否在展现中
	public static boolean IS_PLAY_GOLD_ANIM = false;// 是否播放金币动画
	public static boolean IS_ON_PAY = false;// 是否已经在支付
	public static float RATE_20 = 0;
	public static boolean IS_IN_BOOM = false;// 是否在炸弹中
	public static boolean IS_SHOW_RECHARGE_NUM = true;
	public static final String MARQUEE_BEAUTIFUL_GIRL = "珍贵美人鱼出现，点击右上角高爆炸弹，轻松捕获美人鱼!";

	public static int playerGold = 0;
	public static int playerEnergy = 0;
	public static int playerCannon = 1;
	public static int playerExp = 0;
	public static int playerMaxCannon = 0;
	public static boolean playerMusic = true;
	public static boolean playerBgm = true;
	public static boolean playerLogin = false;
	public static boolean luckyTimes = false;
	public static boolean swtichState = false;
	public static boolean updatePropInfo = false;

	public static boolean isShowHotActivity = true;// 是否显示活动
	public static boolean isShowInstall = false;

	public static void init() {
		PlayerInfo playerInfo = PlayerInfo.getPlayerInfo();
		playerGold = playerInfo.getGold();
		playerCannon = playerInfo.getCurrentCannon();
		playerMaxCannon = playerInfo.getMaxCannon();
		playerEnergy = playerInfo.getEnergy();
		playerExp = playerInfo.getExperience();
		playerMusic = playerInfo.isMusicOpen();
		playerLogin = playerInfo.isFirstLogin();
		playerBgm = playerInfo.isBgmState();
		luckyTimes = playerInfo.isLuckyTimes();
		if (luckyTimes) {
			RATE_20 = 15;
		}

	}

	public static void savePlayerInfo() {
		if (playerCannon == 10) {
			playerCannon = PlayerInfo.getPlayerInfo().getCurrentCannon();
		}
		PlayerInfo playerInfo = PlayerInfo.getPlayerInfo();
		playerInfo.setGold(playerGold);
		playerInfo.setCurrentCannon(playerCannon);
		playerInfo.setEnergy(playerEnergy);
		playerInfo.setMaxCannon(playerMaxCannon);
		playerInfo.setExperience(playerExp);
		playerInfo.setMusicOpen(playerMusic);
		playerInfo.setBgmState(playerBgm);
		playerInfo.setFirstLogin(false);
		playerInfo.setLuckyTimes(luckyTimes);
		PlayerInfo.setPlayerInfo(playerInfo);
	}
}
