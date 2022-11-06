package com.xiao.fish.constants;

public class Rank {

	private static float LEVEL_1 = 1;
	private static float LEVEL_2 = 2;
	private static float LEVEL_3 = 3;
	private static float LEVEL_4 = 4;
	private static float LEVEL_5 = 5;
	private static float LEVEL_6 = 6;
	private static float LEVEL_7 = 7;
	private static float LEVEL_8 = 8;
	private static float LEVEL_9 = 9;
	private static float LEVEL_10 = 10;
	private static float LEVEL_11 = 11;
	private static float LEVEL_12 = 12;

	public static int getRankPer(int level) {
		if (level == LEVEL_1) {
			return 10;
		} else if (level == LEVEL_2) {
			return (int) (10 + Math.random() * 5);
		} else if (level == LEVEL_3) {
			return (int) (15 + Math.random() * 5);
		} else if (level == LEVEL_4) {
			return (int) (20 + Math.random() * 20);
		} else if (level == LEVEL_5) {
			return (int) (40 + Math.random() * 10);
		} else if (level == LEVEL_6) {
			return (int) (50 + Math.random() * 10);
		} else if (level == LEVEL_7) {
			return (int) (60 + Math.random() * 10);
		} else if (level == LEVEL_8) {
			return (int) (int) (70 + Math.random() * 5);
		} else if (level == LEVEL_9) {
			return (int) (int) (75 + Math.random() * 5);
		} else if (level == LEVEL_10) {
			return (int) (int) (80 + Math.random() * 5);
		} else if (level == LEVEL_11) {
			return (int) (int) (85 + Math.random() * 5);
		} else if (level == LEVEL_12) {
			return (int) (int) (90 + Math.random() * 10);
		} else {
			return 99;
		}
	}

}
