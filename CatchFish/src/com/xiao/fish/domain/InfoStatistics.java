package com.xiao.fish.domain;

import android.content.Context;
import android.content.SharedPreferences;

import com.xiao.fish.FishCatchApplication;

public class InfoStatistics {
	private int cannon_1_times;
	private int cannon_2_times;
	private int cannon_3_times;
	private int cannon_4_times;
	private int cannon_5_times;
	private int cannon_6_times;
	private int cannon_7_times;
	private int cannon_8_times;
	private int cannon_9_times;
	private int cannon_1_gold;
	private int cannon_2_gold;
	private int cannon_3_gold;
	private int cannon_4_gold;
	private int cannon_5_gold;
	private int cannon_6_gold;
	private int cannon_7_gold;
	private int cannon_8_gold;
	private int cannon_9_gold;

	public int getCannon_1_times() {
		return cannon_1_times;
	}

	public void setCannon_1_times(int cannon_1_times) {
		this.cannon_1_times = cannon_1_times;
	}

	public int getCannon_2_times() {
		return cannon_2_times;
	}

	public void setCannon_2_times(int cannon_2_times) {
		this.cannon_2_times = cannon_2_times;
	}

	public int getCannon_3_times() {
		return cannon_3_times;
	}

	public void setCannon_3_times(int cannon_3_times) {
		this.cannon_3_times = cannon_3_times;
	}

	public int getCannon_4_times() {
		return cannon_4_times;
	}

	public void setCannon_4_times(int cannon_4_times) {
		this.cannon_4_times = cannon_4_times;
	}

	public int getCannon_5_times() {
		return cannon_5_times;
	}

	public void setCannon_5_times(int cannon_5_times) {
		this.cannon_5_times = cannon_5_times;
	}

	public int getCannon_6_times() {
		return cannon_6_times;
	}

	public void setCannon_6_times(int cannon_6_times) {
		this.cannon_6_times = cannon_6_times;
	}

	public int getCannon_7_times() {
		return cannon_7_times;
	}

	public void setCannon_7_times(int cannon_7_times) {
		this.cannon_7_times = cannon_7_times;
	}

	public int getCannon_8_times() {
		return cannon_8_times;
	}

	public void setCannon_8_times(int cannon_8_times) {
		this.cannon_8_times = cannon_8_times;
	}

	public int getCannon_9_times() {
		return cannon_9_times;
	}

	public void setCannon_9_times(int cannon_9_times) {
		this.cannon_9_times = cannon_9_times;
	}

	public int getCannon_1_gold() {
		return cannon_1_gold;
	}

	public void setCannon_1_gold(int cannon_1_gold) {
		this.cannon_1_gold = cannon_1_gold;
	}

	public int getCannon_2_gold() {
		return cannon_2_gold;
	}

	public void setCannon_2_gold(int cannon_2_gold) {
		this.cannon_2_gold = cannon_2_gold;
	}

	public int getCannon_3_gold() {
		return cannon_3_gold;
	}

	public void setCannon_3_gold(int cannon_3_gold) {
		this.cannon_3_gold = cannon_3_gold;
	}

	public int getCannon_4_gold() {
		return cannon_4_gold;
	}

	public void setCannon_4_gold(int cannon_4_gold) {
		this.cannon_4_gold = cannon_4_gold;
	}

	public int getCannon_5_gold() {
		return cannon_5_gold;
	}

	public void setCannon_5_gold(int cannon_5_gold) {
		this.cannon_5_gold = cannon_5_gold;
	}

	public int getCannon_6_gold() {
		return cannon_6_gold;
	}

	public void setCannon_6_gold(int cannon_6_gold) {
		this.cannon_6_gold = cannon_6_gold;
	}

	public int getCannon_7_gold() {
		return cannon_7_gold;
	}

	public void setCannon_7_gold(int cannon_7_gold) {
		this.cannon_7_gold = cannon_7_gold;
	}

	public int getCannon_8_gold() {
		return cannon_8_gold;
	}

	public void setCannon_8_gold(int cannon_8_gold) {
		this.cannon_8_gold = cannon_8_gold;
	}

	public int getCannon_9_gold() {
		return cannon_9_gold;
	}

	public void setCannon_9_gold(int cannon_9_gold) {
		this.cannon_9_gold = cannon_9_gold;
	}

	private InfoStatistics() {
		// 私有构造
	}

	// cannon
	private static final String GAME_PRES_STATTISTICS_INFO = "GAME_PRES_STATTISTICS_INFO";
	private static final String GAME_PRES_STATTISTICS_CANNON_1 = "GAME_PRES_STATTISTICS_CANNON_1";
	private static final String GAME_PRES_STATTISTICS_CANNON_2 = "GAME_PRES_STATTISTICS_CANNON_2";
	private static final String GAME_PRES_STATTISTICS_CANNON_3 = "GAME_PRES_STATTISTICS_CANNON_3";
	private static final String GAME_PRES_STATTISTICS_CANNON_4 = "GAME_PRES_STATTISTICS_CANNON_4";
	private static final String GAME_PRES_STATTISTICS_CANNON_5 = "GAME_PRES_STATTISTICS_CANNON_5";
	private static final String GAME_PRES_STATTISTICS_CANNON_6 = "GAME_PRES_STATTISTICS_CANNON_6";
	private static final String GAME_PRES_STATTISTICS_CANNON_7 = "GAME_PRES_STATTISTICS_CANNON_7";
	private static final String GAME_PRES_STATTISTICS_CANNON_8 = "GAME_PRES_STATTISTICS_CANNON_8";
	private static final String GAME_PRES_STATTISTICS_CANNON_9 = "GAME_PRES_STATTISTICS_CANNON_9";
	// gold
	private static final String GAME_PRES_STATTISTICS_GOLD_1 = "GAME_PRES_STATTISTICS_GOLD_1";
	private static final String GAME_PRES_STATTISTICS_GOLD_2 = "GAME_PRES_STATTISTICS_GOLD_2";
	private static final String GAME_PRES_STATTISTICS_GOLD_3 = "GAME_PRES_STATTISTICS_GOLD_3";
	private static final String GAME_PRES_STATTISTICS_GOLD_4 = "GAME_PRES_STATTISTICS_GOLD_4";
	private static final String GAME_PRES_STATTISTICS_GOLD_5 = "GAME_PRES_STATTISTICS_GOLD_5";
	private static final String GAME_PRES_STATTISTICS_GOLD_6 = "GAME_PRES_STATTISTICS_GOLD_6";
	private static final String GAME_PRES_STATTISTICS_GOLD_7 = "GAME_PRES_STATTISTICS_GOLD_7";
	private static final String GAME_PRES_STATTISTICS_GOLD_8 = "GAME_PRES_STATTISTICS_GOLD_8";
	private static final String GAME_PRES_STATTISTICS_GOLD_9 = "GAME_PRES_STATTISTICS_GOLD_9";

	public static InfoStatistics getInfoStatistics() {
		SharedPreferences preferences = FishCatchApplication.getInstance()
				.getSharedPreferences(GAME_PRES_STATTISTICS_INFO,
						Context.MODE_PRIVATE);
		InfoStatistics playerInfo = new InfoStatistics();
		// cannon
		playerInfo.setCannon_1_times(preferences.getInt(
				GAME_PRES_STATTISTICS_CANNON_1, 0));
		playerInfo.setCannon_2_times(preferences.getInt(
				GAME_PRES_STATTISTICS_CANNON_2, 0));
		playerInfo.setCannon_3_times(preferences.getInt(
				GAME_PRES_STATTISTICS_CANNON_3, 0));
		playerInfo.setCannon_4_times(preferences.getInt(
				GAME_PRES_STATTISTICS_CANNON_4, 0));
		playerInfo.setCannon_5_times(preferences.getInt(
				GAME_PRES_STATTISTICS_CANNON_5, 0));
		playerInfo.setCannon_6_times(preferences.getInt(
				GAME_PRES_STATTISTICS_CANNON_6, 0));
		playerInfo.setCannon_7_times(preferences.getInt(
				GAME_PRES_STATTISTICS_CANNON_7, 0));
		playerInfo.setCannon_8_times(preferences.getInt(
				GAME_PRES_STATTISTICS_CANNON_8, 0));
		playerInfo.setCannon_9_times(preferences.getInt(
				GAME_PRES_STATTISTICS_CANNON_9, 0));
		// gold
		playerInfo.setCannon_1_gold(preferences.getInt(
				GAME_PRES_STATTISTICS_GOLD_1, 0));
		playerInfo.setCannon_1_gold(preferences.getInt(
				GAME_PRES_STATTISTICS_GOLD_2, 0));
		playerInfo.setCannon_1_gold(preferences.getInt(
				GAME_PRES_STATTISTICS_GOLD_3, 0));
		playerInfo.setCannon_1_gold(preferences.getInt(
				GAME_PRES_STATTISTICS_GOLD_4, 0));
		playerInfo.setCannon_1_gold(preferences.getInt(
				GAME_PRES_STATTISTICS_GOLD_5, 0));
		playerInfo.setCannon_1_gold(preferences.getInt(
				GAME_PRES_STATTISTICS_GOLD_6, 0));
		playerInfo.setCannon_1_gold(preferences.getInt(
				GAME_PRES_STATTISTICS_GOLD_7, 0));
		playerInfo.setCannon_1_gold(preferences.getInt(
				GAME_PRES_STATTISTICS_GOLD_8, 0));
		playerInfo.setCannon_1_gold(preferences.getInt(
				GAME_PRES_STATTISTICS_GOLD_9, 0));
		return playerInfo;
	}

	public static void setPlayerInfo(InfoStatistics info) {
		if (info == null) {
			return;
		}
		SharedPreferences preferences = FishCatchApplication.getInstance()
				.getSharedPreferences(GAME_PRES_STATTISTICS_INFO,
						Context.MODE_PRIVATE);
		SharedPreferences.Editor editor = preferences.edit();
		// cannon
		editor.putInt(GAME_PRES_STATTISTICS_CANNON_1, info.getCannon_1_times());
		editor.putInt(GAME_PRES_STATTISTICS_CANNON_2, info.getCannon_2_times());
		editor.putInt(GAME_PRES_STATTISTICS_CANNON_3, info.getCannon_3_times());
		editor.putInt(GAME_PRES_STATTISTICS_CANNON_4, info.getCannon_4_times());
		editor.putInt(GAME_PRES_STATTISTICS_CANNON_5, info.getCannon_5_times());
		editor.putInt(GAME_PRES_STATTISTICS_CANNON_6, info.getCannon_6_times());
		editor.putInt(GAME_PRES_STATTISTICS_CANNON_7, info.getCannon_7_times());
		editor.putInt(GAME_PRES_STATTISTICS_CANNON_8, info.getCannon_8_times());
		editor.putInt(GAME_PRES_STATTISTICS_CANNON_9, info.getCannon_9_times());
		// gold
		editor.putInt(GAME_PRES_STATTISTICS_GOLD_1, info.getCannon_1_gold());
		editor.putInt(GAME_PRES_STATTISTICS_GOLD_2, info.getCannon_2_gold());
		editor.putInt(GAME_PRES_STATTISTICS_GOLD_3, info.getCannon_3_gold());
		editor.putInt(GAME_PRES_STATTISTICS_GOLD_4, info.getCannon_4_gold());
		editor.putInt(GAME_PRES_STATTISTICS_GOLD_5, info.getCannon_5_gold());
		editor.putInt(GAME_PRES_STATTISTICS_GOLD_6, info.getCannon_6_gold());
		editor.putInt(GAME_PRES_STATTISTICS_GOLD_7, info.getCannon_7_gold());
		editor.putInt(GAME_PRES_STATTISTICS_GOLD_8, info.getCannon_8_gold());
		editor.putInt(GAME_PRES_STATTISTICS_GOLD_9, info.getCannon_9_gold());
		editor.commit();
	}
}
