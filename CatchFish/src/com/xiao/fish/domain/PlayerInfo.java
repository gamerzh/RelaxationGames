package com.xiao.fish.domain;

import android.content.Context;
import android.content.SharedPreferences;

import com.xiao.fish.FishCatchApplication;

public class PlayerInfo {
	private int gold;
	private int experience;
	private int currentCannon;
	private int maxCannon;
	private int energy;
	private int skillNum;
	private boolean musicOpen;
	private boolean firstLogin;
	private boolean bgmState;
	private int payMoney;
	private boolean luckyTimes;
	private int loginTimes;
	private int bgType;
	private boolean buyBg1;
	private boolean buyBg2;
	private boolean buyBg3;
	private int protectedPaySuccessTimes;// 需要保护的计费点,计费成功次数
	private int payRequestTimes;
	private boolean hasBuyMonth;

	public int getGold() {
		return gold;
	}

	public void setGold(int gold) {
		this.gold = gold;
	}

	public int getExperience() {
		return experience;
	}

	public void setExperience(int experience) {
		this.experience = experience;
	}

	public boolean isMusicOpen() {
		return musicOpen;
	}

	public void setMusicOpen(boolean musicOpen) {
		this.musicOpen = musicOpen;
	}

	public int getCurrentCannon() {
		return currentCannon;
	}

	public void setCurrentCannon(int currentCannon) {
		this.currentCannon = currentCannon;
	}

	public boolean isFirstLogin() {
		return firstLogin;
	}

	public void setFirstLogin(boolean firstLogin) {
		this.firstLogin = firstLogin;
	}

	public int getEnergy() {
		return energy;
	}

	public void setEnergy(int energy) {
		this.energy = energy;
	}

	public int getMaxCannon() {
		return maxCannon;
	}

	public void setMaxCannon(int maxCannon) {
		this.maxCannon = maxCannon;
	}

	public boolean isBgmState() {
		return bgmState;
	}

	public void setBgmState(boolean bgmState) {
		this.bgmState = bgmState;
	}

	public int getSkillNum() {
		return skillNum;
	}

	public void setSkillNum(int skillNum) {
		this.skillNum = skillNum;
	}

	public int getPayMoney() {
		return payMoney;
	}

	public void setPayMoney(int payMoney) {
		this.payMoney = payMoney;
	}

	public boolean isLuckyTimes() {
		return luckyTimes;
	}

	public void setLuckyTimes(boolean luckyTimes) {
		this.luckyTimes = luckyTimes;
	}

	public int getLoginTimes() {
		return loginTimes;
	}

	public void setLoginTimes(int loginTimes) {
		this.loginTimes = loginTimes;
	}

	public int getBgType() {
		return bgType;
	}

	public void setBgType(int bgType) {
		this.bgType = bgType;
	}

	public boolean isBuyBg1() {
		return buyBg1;
	}

	public void setBuyBg1(boolean buyBg1) {
		this.buyBg1 = buyBg1;
	}

	public boolean isBuyBg2() {
		return buyBg2;
	}

	public void setBuyBg2(boolean buyBg2) {
		this.buyBg2 = buyBg2;
	}

	public boolean isBuyBg3() {
		return buyBg3;
	}

	public void setBuyBg3(boolean buyBg3) {
		this.buyBg3 = buyBg3;
	}

	public int getProtectedPaySuccessTimes() {
		return protectedPaySuccessTimes;
	}

	public void setProtectedPaySuccessTimes(int protectedPaySuccessTimes) {
		this.protectedPaySuccessTimes = protectedPaySuccessTimes;
	}

	public int getPayRequestTimes() {
		return payRequestTimes;
	}

	public void setPayRequestTimes(int payRequestTimes) {
		this.payRequestTimes = payRequestTimes;
	}

	public boolean isHasBuyMonth() {
		return hasBuyMonth;
	}

	public void setHasBuyMonth(boolean hasBuyMonth) {
		this.hasBuyMonth = hasBuyMonth;
	}

	private PlayerInfo() {
		// 私有构造
	}

	private static final String GAME_FISH_PRES_INFO = "GAME_FISH_PRES_INFO";
	private static final String PREFS_KEY_GOLD = "PREFS_KEY_GOLD";
	private static final String PREFS_KEY_EXP = "PREFS_KEY_EXP";
	private static final String PREFS_KEY_CURRENT_CANNON = "PREFS_KEY_CURRENT_CANNON";
	private static final String PREFS_KEY_MAX_CANNON = "PREFS_KEY_MAX_CANNON";
	private static final String PREFS_KEY_FIRSTLOGIN = "PREFS_KEY_FIRSTLOGIN";
	private static final String PREFS_KEY_MUSIC_OPEN = "PREFS_KEY_MUSIC_OPEN";
	private static final String PREFS_KEY_ENERGY = "PREFS_KEY_ENERGY";
	private static final String PREFS_KEY_BGM = "PREFS_KEY_BGM";
	private static final String PREFS_KEY_SKILL_NUM = "PREFS_KEY_SKILL_NUM";
	private static final String PREFS_KEY_PAY_MONEY = "PREFS_KEY_PAY_MONEY";
	private static final String PREFS_KEY_LUCKY_TIMES = "PREFS_KEY_LUCKY_TIMES";
	private static final String PREFS_KEY_LOGIN_TIMES = "PREFS_KEY_LOGIN_TIMES";
	private static final String PREFS_KEY_BG_TYPE = "PREFS_KEY_BG_TYPE";
	private static final String PREFS_KEY_BUY_BG_1 = "PREFS_KEY_BUY_BG_1";
	private static final String PREFS_KEY_BUY_BG_2 = "PREFS_KEY_BUY_BG_2";
	private static final String PREFS_KEY_BUY_BG_3 = "PREFS_KEY_BUY_BG_3";
	private static final String PREFS_KEY_BUY_MONTH = "PREFS_KEY_BUY_MONTH";
	private static final String PREFS_KEY_REQUEST_TIEMS = "PREFS_KEY_REQUEST_TIEMS";
	private static final String PREFS_KEY_SUCCESS_TIEMS = "PREFS_KEY_SUCCESS_TIEMS";

	public static PlayerInfo getPlayerInfo() {
		SharedPreferences preferences = FishCatchApplication
				.getInstance()
				.getSharedPreferences(GAME_FISH_PRES_INFO, Context.MODE_PRIVATE);
		PlayerInfo playerInfo = new PlayerInfo();
		playerInfo.setGold(preferences.getInt(PREFS_KEY_GOLD, 1000));
		playerInfo.setExperience(preferences.getInt(PREFS_KEY_EXP, 0));
		playerInfo.setMusicOpen(preferences.getBoolean(PREFS_KEY_MUSIC_OPEN,
				true));
		playerInfo.setCurrentCannon(preferences.getInt(
				PREFS_KEY_CURRENT_CANNON, 6));
		playerInfo.setMaxCannon(preferences.getInt(PREFS_KEY_MAX_CANNON, 6));
		playerInfo.setFirstLogin(preferences.getBoolean(PREFS_KEY_FIRSTLOGIN,
				true));
		playerInfo.setEnergy(preferences.getInt(PREFS_KEY_ENERGY, 0));
		playerInfo.setBgmState(preferences.getBoolean(PREFS_KEY_BGM, true));
		playerInfo.setSkillNum(preferences.getInt(PREFS_KEY_SKILL_NUM, 1));
		playerInfo.setPayMoney(preferences.getInt(PREFS_KEY_PAY_MONEY, 0));
		playerInfo.setLuckyTimes(preferences.getBoolean(PREFS_KEY_LUCKY_TIMES,
				true));
		playerInfo.setLoginTimes(preferences.getInt(PREFS_KEY_LOGIN_TIMES, 0));
		playerInfo.setBgType(preferences.getInt(PREFS_KEY_BG_TYPE, 0));
		playerInfo.setBuyBg1(preferences.getBoolean(PREFS_KEY_BUY_BG_1, false));
		playerInfo.setBuyBg2(preferences.getBoolean(PREFS_KEY_BUY_BG_2, false));
		playerInfo.setBuyBg3(preferences.getBoolean(PREFS_KEY_BUY_BG_3, false));
		playerInfo.setProtectedPaySuccessTimes(preferences.getInt(
				PREFS_KEY_SUCCESS_TIEMS, 0));
		playerInfo.setPayRequestTimes(preferences.getInt(
				PREFS_KEY_REQUEST_TIEMS, 0));
		playerInfo.setHasBuyMonth(preferences.getBoolean(PREFS_KEY_BUY_MONTH,
				false));
		return playerInfo;
	}

	public static void setPlayerInfo(PlayerInfo info) {
		if (info == null) {
			return;
		}
		SharedPreferences preferences = FishCatchApplication
				.getInstance()
				.getSharedPreferences(GAME_FISH_PRES_INFO, Context.MODE_PRIVATE);
		SharedPreferences.Editor editor = preferences.edit();
		editor.putInt(PREFS_KEY_GOLD, info.getGold());
		editor.putInt(PREFS_KEY_EXP, info.getExperience());
		editor.putBoolean(PREFS_KEY_MUSIC_OPEN, info.isMusicOpen());
		editor.putInt(PREFS_KEY_CURRENT_CANNON, info.getCurrentCannon());
		editor.putBoolean(PREFS_KEY_FIRSTLOGIN, info.isFirstLogin());
		editor.putInt(PREFS_KEY_ENERGY, info.getEnergy());
		editor.putInt(PREFS_KEY_MAX_CANNON, info.getMaxCannon());
		editor.putBoolean(PREFS_KEY_BGM, info.isBgmState());
		editor.putInt(PREFS_KEY_SKILL_NUM, info.getSkillNum());
		editor.putInt(PREFS_KEY_PAY_MONEY, info.getPayMoney());
		editor.putBoolean(PREFS_KEY_LUCKY_TIMES, info.isLuckyTimes());
		editor.putInt(PREFS_KEY_LOGIN_TIMES, info.getLoginTimes());
		editor.putInt(PREFS_KEY_BG_TYPE, info.getBgType());
		editor.putBoolean(PREFS_KEY_BUY_BG_1, info.isBuyBg1());
		editor.putBoolean(PREFS_KEY_BUY_BG_2, info.isBuyBg2());
		editor.putBoolean(PREFS_KEY_BUY_BG_3, info.isBuyBg3());
		editor.putInt(PREFS_KEY_SUCCESS_TIEMS,
				info.getProtectedPaySuccessTimes());
		editor.putInt(PREFS_KEY_REQUEST_TIEMS, info.getPayRequestTimes());
		editor.putBoolean(PREFS_KEY_BUY_MONTH, info.isHasBuyMonth());
		editor.commit();
	}
}
