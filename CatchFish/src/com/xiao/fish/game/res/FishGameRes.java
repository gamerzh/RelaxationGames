package com.xiao.fish.game.res;

import java.util.HashMap;

import android.content.res.Resources;
import android.graphics.Bitmap;

import com.hifreshday.android.pge.engine.Engine;
import com.hifreshday.android.pge.view.res.GameBitmapUtil;
import com.hifreshday.android.pge.view.res.IBitmapRes;
import com.kx.byno.R;

public class FishGameRes implements IBitmapRes {

	private Resources res;

	private HashMap<Integer, Integer> resMap = new HashMap<Integer, Integer>();
	private HashMap<Integer, Bitmap> resBitmapMap = new HashMap<Integer, Bitmap>();
	// fish 1
	public static final int KEY_FISH_1_1 = 1001;
	public static final int KEY_FISH_1_2 = 1002;
	public static final int KEY_FISH_1_3 = 1003;
	public static final int KEY_FISH_1_4 = 1004;
	public static final int KEY_FISH_1_5 = 1005;
	public static final int KEY_FISH_1_6 = 1006;
	public static final int KEY_FISH_1_7 = 1007;
	public static final int KEY_FISH_1_8 = 1008;
	public static final int KEY_FISH_1_9 = 1009;
	public static final int KEY_FISH_1_10 = 1010;
	// fish 2
	public static final int KEY_FISH_2_1 = 1011;
	public static final int KEY_FISH_2_2 = 1012;
	public static final int KEY_FISH_2_3 = 1013;
	public static final int KEY_FISH_2_4 = 1014;
	public static final int KEY_FISH_2_5 = 2015;
	public static final int KEY_FISH_2_6 = 1016;
	public static final int KEY_FISH_2_7 = 1017;
	public static final int KEY_FISH_2_8 = 1018;
	public static final int KEY_FISH_2_9 = 1019;
	public static final int KEY_FISH_2_10 = 1020;
	// fish 3
	public static final int KEY_FISH_3_1 = 1021;
	public static final int KEY_FISH_3_2 = 1022;
	public static final int KEY_FISH_3_3 = 1023;
	public static final int KEY_FISH_3_4 = 1024;
	public static final int KEY_FISH_3_5 = 2025;
	public static final int KEY_FISH_3_6 = 1026;
	public static final int KEY_FISH_3_7 = 1027;
	public static final int KEY_FISH_3_8 = 1028;
	// fish 4
	public static final int KEY_FISH_4_1 = 1031;
	public static final int KEY_FISH_4_2 = 1032;
	public static final int KEY_FISH_4_3 = 1033;
	public static final int KEY_FISH_4_4 = 1034;
	public static final int KEY_FISH_4_5 = 2035;
	public static final int KEY_FISH_4_6 = 1036;
	public static final int KEY_FISH_4_7 = 1037;
	public static final int KEY_FISH_4_8 = 1038;
	public static final int KEY_FISH_4_9 = 1039;
	public static final int KEY_FISH_4_10 = 1040;
	// fish 5
	public static final int KEY_FISH_5_1 = 1041;
	public static final int KEY_FISH_5_2 = 1042;
	public static final int KEY_FISH_5_3 = 1043;
	public static final int KEY_FISH_5_4 = 1044;
	public static final int KEY_FISH_5_5 = 2045;
	public static final int KEY_FISH_5_6 = 1046;
	public static final int KEY_FISH_5_7 = 1047;
	public static final int KEY_FISH_5_8 = 1048;
	public static final int KEY_FISH_5_9 = 1049;
	public static final int KEY_FISH_5_10 = 1050;
	// fish 6
	public static final int KEY_FISH_6_1 = 1051;
	public static final int KEY_FISH_6_2 = 1052;
	public static final int KEY_FISH_6_3 = 1053;
	public static final int KEY_FISH_6_4 = 1054;
	public static final int KEY_FISH_6_5 = 2055;
	public static final int KEY_FISH_6_6 = 1056;
	public static final int KEY_FISH_6_7 = 1057;
	public static final int KEY_FISH_6_8 = 1058;
	public static final int KEY_FISH_6_9 = 1059;
	public static final int KEY_FISH_6_10 = 1060;
	public static final int KEY_FISH_6_11 = 1061;
	public static final int KEY_FISH_6_12 = 1062;
	public static final int KEY_FISH_6_13 = 1063;
	public static final int KEY_FISH_6_14 = 1064;
	// catch 1
	public static final int KEY_CATCH_1_1 = 3001;
	public static final int KEY_CATCH_1_2 = 3002;
	// catch 2
	public static final int KEY_CATCH_2_1 = 3011;
	public static final int KEY_CATCH_2_2 = 3012;
	// catch 3
	public static final int KEY_CATCH_3_1 = 3021;
	public static final int KEY_CATCH_3_2 = 3022;
	public static final int KEY_CATCH_3_3 = 3023;
	public static final int KEY_CATCH_3_4 = 3024;
	public static final int KEY_CATCH_3_5 = 3025;
	public static final int KEY_CATCH_3_6 = 3026;
	public static final int KEY_CATCH_3_7 = 3027;
	public static final int KEY_CATCH_3_8 = 3028;
	// catch 4
	public static final int KEY_CATCH_4_1 = 3031;
	public static final int KEY_CATCH_4_2 = 3032;
	public static final int KEY_CATCH_4_3 = 3033;
	// catch 5
	public static final int KEY_CATCH_5_1 = 3041;
	public static final int KEY_CATCH_5_2 = 3042;
	public static final int KEY_CATCH_5_3 = 3043;
	public static final int KEY_CATCH_5_4 = 3044;
	// catch 6
	public static final int KEY_CATCH_6_1 = 3051;
	public static final int KEY_CATCH_6_2 = 3052;
	public static final int KEY_CATCH_6_3 = 3053;
	public static final int KEY_CATCH_6_4 = 3054;
	public static final int KEY_CATCH_6_5 = 3055;
	public static final int KEY_CATCH_6_6 = 3056;
	// cannon
	public static final int KEY_GAME_CANNON_1 = 4001;
	public static final int KEY_GAME_CANNON_2 = 4002;
	public static final int KEY_GAME_CANNON_3 = 4003;
	public static final int KEY_GAME_CANNON_4 = 4004;
	public static final int KEY_GAME_CANNON_5 = 4005;
	public static final int KEY_GAME_CANNON_6 = 4006;
	public static final int KEY_GAME_CANNON_7 = 4007;
	public static final int KEY_GAME_CANNON_8 = 4008;
	public static final int KEY_GAME_CANNON_9 = 4009;
	public static final int KEY_GAME_CANNON_10 = 4010;
	public static final int KEY_GAME_CANNON_1_HEAD = 4020;
	public static final int KEY_GAME_CANNON_2_HEAD = 4021;
	public static final int KEY_GAME_CANNON_3_HEAD = 4022;
	public static final int KEY_GAME_CANNON_4_HEAD = 4023;
	public static final int KEY_GAME_CANNON_5_HEAD = 4024;
	public static final int KEY_GAME_CANNON_6_HEAD = 4025;
	public static final int KEY_GAME_CANNON_7_HEAD = 4026;
	public static final int KEY_GAME_CANNON_8_HEAD = 4027;
	public static final int KEY_GAME_CANNON_9_HEAD = 4028;

	// bullet
	public static final int KEY_GAME_BULLET_1 = 5001;
	public static final int KEY_GAME_BULLET_2 = 5002;
	public static final int KEY_GAME_BULLET_3 = 5003;
	public static final int KEY_GAME_BULLET_4 = 5004;
	public static final int KEY_GAME_BULLET_5 = 5005;
	public static final int KEY_GAME_BULLET_6 = 5006;
	// fish net
	public static final int KEY_GAME_NET_1 = 6001;
	public static final int KEY_GAME_NET_2 = 6002;
	public static final int KEY_GAME_NET_3 = 6003;
	public static final int KEY_GAME_NET_4 = 6004;
	public static final int KEY_GAME_NET_5 = 6005;
	public static final int KEY_GAME_NET_6 = 6006;
	public static final int KEY_GAME_NET_7 = 6007;
	// level text
	public static final int KEY_GAME_LEVEL_1 = 8001;
	public static final int KEY_GAME_LEVEL_2 = 8002;
	public static final int KEY_GAME_LEVEL_3 = 8003;
	public static final int KEY_GAME_LEVEL_4 = 8004;
	public static final int KEY_GAME_LEVEL_5 = 8005;
	public static final int KEY_GAME_LEVEL_6 = 8006;
	public static final int KEY_GAME_LEVEL_7 = 8007;
	public static final int KEY_GAME_LEVEL_8 = 8008;
	public static final int KEY_GAME_LEVEL_9 = 8009;
	public static final int KEY_GAME_LEVEL_10 = 8010;
	public static final int KEY_GAME_LEVEL_11 = 8011;
	public static final int KEY_GAME_LEVEL_12 = 8012;
	// gold
	public static final int KEY_GAME_FISH_GOLD_1 = 9001;
	public static final int KEY_GAME_FISH_GOLD_2 = 9002;
	public static final int KEY_GAME_FISH_GOLD_3 = 9003;
	public static final int KEY_GAME_FISH_GOLD_4 = 9004;
	public static final int KEY_GAME_FISH_GOLD_5 = 9005;
	public static final int KEY_GAME_FISH_GOLD_6 = 9006;
	// laser
	public static final int KEY_GAME_LASER_1 = 10001;
	public static final int KEY_GAME_LASER_2 = 10002;
	public static final int KEY_GAME_LASER_3 = 10003;
	public static final int KEY_GAME_LASER_4 = 10004;
	public static final int KEY_GAME_LASER_5 = 10005;
	public static final int KEY_GAME_LASER_6 = 10006;
	// boom
	public static final int KEY_GAME_BOOM_1 = 10011;
	public static final int KEY_GAME_BOOM_2 = 10012;
	public static final int KEY_GAME_BOOM_3 = 10013;
	public static final int KEY_GAME_BOOM_4 = 10014;
	// boom
	public static final int KEY_GAME_SKILL_ANIM_1 = 10021;
	public static final int KEY_GAME_SKILL_ANIM_2 = 10022;
	public static final int KEY_GAME_SKILL_ANIM_3 = 10023;
	public static final int KEY_GAME_SKILL_ANIM_4 = 10024;
	public static final int KEY_GAME_SKILL_ANIM_5 = 10025;
	// beautiful girl
	public static final int KEY_GAME_BEAUTIFUL_GIRL_1 = 11001;
	public static final int KEY_GAME_BEAUTIFUL_GIRL_2 = 11002;
	public static final int KEY_GAME_BEAUTIFUL_GIRL_3 = 11003;
	public static final int KEY_GAME_BEAUTIFUL_GIRL_4 = 11004;
	public static final int KEY_GAME_BEAUTIFUL_GIRL_5 = 11005;
	public static final int KEY_GAME_BEAUTIFUL_GIRL_6 = 11006;
	public static final int KEY_GAME_BEAUTIFUL_GIRL_7 = 11007;
	public static final int KEY_GAME_BEAUTIFUL_GIRL_8 = 11008;
	public static final int KEY_GAME_BEAUTIFUL_GIRL_9 = 11009;
	public static final int KEY_GAME_BEAUTIFUL_GIRL_10 = 11010;
	public static final int KEY_GAME_BEAUTIFUL_GIRL_11 = 11011;
	public static final int KEY_GAME_BEAUTIFUL_GIRL_12 = 11012;
	public static final int KEY_GAME_BEAUTIFUL_GIRL_13 = 11013;
	
	
	
	
	// beautiful girl catch
	public static final int KEY_GAME_BEAUTIFUL_GIRL_CATCH_1 = 12001;
	public static final int KEY_GAME_BEAUTIFUL_GIRL_CATCH_2 = 12002;
	// others
	public static final int KEY_GAME_CANNON_UP_PRESSED = 7001;
	public static final int KEY_GAME_PLAYER_GOLD_NUM = 7002;
	public static final int KEY_GAME_TASK_BG = 7003;
	public static final int KEY_GAME_EXP_PROGRESS = 7004;
	public static final int KEY_GAME_TURRET = 7006;
	public static final int KEY_GAME_CANNON_DOWN_NORMAL = 7007;
	public static final int KEY_GAME_CANNON_DOWN_PRESSED = 7008;
	public static final int KEY_GAME_CANNON_UP_NORMAL = 7009;
	public static final int KEY_GAME_TASKNUM = 7010;
	public static final int KEY_GAME_TASKPOINT = 7011;
	public static final int KEY_GAME_TASKSIGN = 7012;
	public static final int KEY_GAME_TASKTIME = 7013;
	public static final int KEY_GAME_LEVEL_BG = 7014;
	public static final int KEY_GAME_LEVEL_NUM = 7015;
	public static final int KEY_GAME_LEVEL_PROGRESS = 7016;
	public static final int KEY_GAME_ALMS_NUM = 7017;
	public static final int KEY_GAME_NEWBEE = 7018;
	public static final int KEY_GAME_LEVEL_UP = 7019;
	public static final int KEY_GAME_LEVEL_UP_NUM = 7020;
	public static final int KEY_GAME_HUODE = 7021;
	public static final int KEY_GAME_JINBI = 7022;
	public static final int KEY_GAME_RECHARGE = 7023;
	public static final int KEY_GAME_SKILL_BOOM = 7024;
	public static final int KEY_GAME_BTN_BG_NORMAL = 7025;
	public static final int KEY_GAME_BTN_BG_PRESSED = 7026;
	public static final int KEY_GAME_BTN_SETTING = 7027;
	public static final int KEY_GAME_START = 7028;
	public static final int KEY_GAME_MUSIC_ON = 7031;
	public static final int KEY_GAME_MUSIC_OFF = 7032;
	public static final int KEY_GAME_PLUS = 7033;
	public static final int KEY_GAME_SIGN = 7034;
	public static final int KEY_GAME_GOLD_NUM_GET = 7035;
	public static final int KEY_GAME_GOLD_NUM_SCREEN = 7036;
	public static final int KEY_GAME_OPEN_WEAPON_1 = 7037;
	public static final int KEY_GAME_OPEN_WEAPON_2 = 7038;
	public static final int KEY_GAME_OPEN_WEAPON_3 = 7039;
	public static final int KEY_GAME_MORE_GAME = 7040;
	public static final int KEY_GAME_BGM_ON = 7041;
	public static final int KEY_GAME_BGM_OFF = 7042;
	public static final int KEY_GAME_TASK_FINISH = 7043;
	public static final int KEY_GAME_SKILL_NUM_BG = 7044;
	public static final int KEY_GAME_SKILL_NUM = 7045;
	public static final int KEY_GAME_SKILL_HINT = 7046;
	public static final int KEY_GAME_RECHARGE_NUM = 7047;
	public static final int KEY_GAME_OPTION = 7048;
	public static final int KEY_GAME_HOT_MARQUEE_BG = 7049;

	
	public static final int KEY_FISH_ITEM_HONGBAO = 300102;
	public static final int KEY_FISH_ITEM_HUAFEI = 300103;
	
	public static final int KEY_FISH_ITEM_BOMB_1 = 300101;
	public static final int KEY_FISH_ITEM_BOMB_2 = 300104;
	public static final int KEY_FISH_ITEM_BOMB_3 = 300105;
	public static final int KEY_FISH_ITEM_BOMB_4 = 300106;
	public static final int KEY_FISH_ITEM_BOMB_5 = 300107;
	public static final int KEY_FISH_ITEM_BOMB_6 = 300108;
	public static final int KEY_FISH_ITEM_BOMB_7 = 300109;

	public static final int KEY_DAILY_TASK_BG = 300110;
	public static final int KEY_DAILY_TASK_CONFIRM = 300111;
	public static final int KEY_DAILY_TASK_HAND = 300112;
	
	
	
	public FishGameRes(Resources res) {
		Engine.isRecycle = false;
		this.res = res;
		initRes();
	}

	private void initRes() {
		// fish1
		resMap.put(KEY_FISH_1_1, R.drawable.fish_1_1);
		resMap.put(KEY_FISH_1_2, R.drawable.fish_1_2);
		resMap.put(KEY_FISH_1_3, R.drawable.fish_1_3);
		resMap.put(KEY_FISH_1_4, R.drawable.fish_1_4);
		resMap.put(KEY_FISH_1_5, R.drawable.fish_1_5);
		resMap.put(KEY_FISH_1_6, R.drawable.fish_1_6);
		resMap.put(KEY_FISH_1_7, R.drawable.fish_1_7);
		resMap.put(KEY_FISH_1_8, R.drawable.fish_1_8);
		resMap.put(KEY_FISH_1_9, R.drawable.fish_1_9);
		resMap.put(KEY_FISH_1_10, R.drawable.fish_1_10);
		// fish2
		resMap.put(KEY_FISH_2_1, R.drawable.fish_2_1);
		resMap.put(KEY_FISH_2_2, R.drawable.fish_2_2);
		resMap.put(KEY_FISH_2_3, R.drawable.fish_2_3);
		resMap.put(KEY_FISH_2_4, R.drawable.fish_2_4);
		resMap.put(KEY_FISH_2_5, R.drawable.fish_2_5);
		resMap.put(KEY_FISH_2_6, R.drawable.fish_2_6);
		resMap.put(KEY_FISH_2_7, R.drawable.fish_2_7);
		resMap.put(KEY_FISH_2_8, R.drawable.fish_2_8);
		resMap.put(KEY_FISH_2_9, R.drawable.fish_2_9);
		resMap.put(KEY_FISH_2_10, R.drawable.fish_2_10);
		// fish3
		resMap.put(KEY_FISH_3_1, R.drawable.fish_3_1);
		resMap.put(KEY_FISH_3_2, R.drawable.fish_3_2);
		resMap.put(KEY_FISH_3_3, R.drawable.fish_3_3);
		resMap.put(KEY_FISH_3_4, R.drawable.fish_3_4);
		resMap.put(KEY_FISH_3_5, R.drawable.fish_3_5);
		resMap.put(KEY_FISH_3_6, R.drawable.fish_3_6);
		resMap.put(KEY_FISH_3_7, R.drawable.fish_3_7);
		resMap.put(KEY_FISH_3_8, R.drawable.fish_3_8);
		// fish4
		resMap.put(KEY_FISH_4_1, R.drawable.fish_4_1);
		resMap.put(KEY_FISH_4_2, R.drawable.fish_4_2);
		resMap.put(KEY_FISH_4_3, R.drawable.fish_4_3);
		resMap.put(KEY_FISH_4_4, R.drawable.fish_4_4);
		resMap.put(KEY_FISH_4_5, R.drawable.fish_4_5);
		resMap.put(KEY_FISH_4_6, R.drawable.fish_4_6);
		resMap.put(KEY_FISH_4_7, R.drawable.fish_4_7);
		resMap.put(KEY_FISH_4_8, R.drawable.fish_4_8);
		resMap.put(KEY_FISH_4_9, R.drawable.fish_4_9);
		resMap.put(KEY_FISH_4_10, R.drawable.fish_4_10);
		// fish5
		resMap.put(KEY_FISH_5_1, R.drawable.fish_5_1);
		resMap.put(KEY_FISH_5_2, R.drawable.fish_5_2);
		resMap.put(KEY_FISH_5_3, R.drawable.fish_5_3);
		resMap.put(KEY_FISH_5_4, R.drawable.fish_5_4);
		resMap.put(KEY_FISH_5_5, R.drawable.fish_5_5);
		resMap.put(KEY_FISH_5_6, R.drawable.fish_5_6);
		resMap.put(KEY_FISH_5_7, R.drawable.fish_5_7);
		resMap.put(KEY_FISH_5_8, R.drawable.fish_5_8);
		resMap.put(KEY_FISH_5_9, R.drawable.fish_5_9);
		resMap.put(KEY_FISH_5_10, R.drawable.fish_5_10);
		// fish5
		resMap.put(KEY_FISH_6_1, R.drawable.shark_blue_1);
		resMap.put(KEY_FISH_6_2, R.drawable.shark_blue_2);
		resMap.put(KEY_FISH_6_3, R.drawable.shark_blue_3);
		resMap.put(KEY_FISH_6_4, R.drawable.shark_blue_4);
		resMap.put(KEY_FISH_6_5, R.drawable.shark_blue_5);
		resMap.put(KEY_FISH_6_6, R.drawable.shark_blue_6);
		resMap.put(KEY_FISH_6_7, R.drawable.shark_blue_7);
		resMap.put(KEY_FISH_6_8, R.drawable.shark_blue_8);
		resMap.put(KEY_FISH_6_9, R.drawable.shark_blue_9);
		resMap.put(KEY_FISH_6_10, R.drawable.shark_blue_10);
		resMap.put(KEY_FISH_6_11, R.drawable.shark_blue_11);
		resMap.put(KEY_FISH_6_12, R.drawable.shark_blue_12);
		resMap.put(KEY_FISH_6_13, R.drawable.shark_blue_13);
		resMap.put(KEY_FISH_6_14, R.drawable.shark_blue_14);
		// catch1
		resMap.put(KEY_CATCH_1_1, R.drawable.catch_1_1);
		resMap.put(KEY_CATCH_1_2, R.drawable.catch_1_2);
		// catch2
		resMap.put(KEY_CATCH_2_1, R.drawable.catch_2_1);
		resMap.put(KEY_CATCH_2_2, R.drawable.catch_2_2);
		// catch3
		resMap.put(KEY_CATCH_3_1, R.drawable.catch_3_1);
		resMap.put(KEY_CATCH_3_2, R.drawable.catch_3_2);
		resMap.put(KEY_CATCH_3_3, R.drawable.catch_3_3);
		resMap.put(KEY_CATCH_3_4, R.drawable.catch_3_4);
		resMap.put(KEY_CATCH_3_5, R.drawable.catch_3_5);
		resMap.put(KEY_CATCH_3_6, R.drawable.catch_3_6);
		resMap.put(KEY_CATCH_3_7, R.drawable.catch_3_7);
		resMap.put(KEY_CATCH_3_8, R.drawable.catch_3_8);
		// catch4
		resMap.put(KEY_CATCH_4_1, R.drawable.catch_4_1);
		resMap.put(KEY_CATCH_4_2, R.drawable.catch_4_2);
		resMap.put(KEY_CATCH_4_3, R.drawable.catch_4_3);
		// catch5
		resMap.put(KEY_CATCH_5_1, R.drawable.catch_5_1);
		resMap.put(KEY_CATCH_5_2, R.drawable.catch_5_2);
		resMap.put(KEY_CATCH_5_3, R.drawable.catch_5_3);
		resMap.put(KEY_CATCH_5_4, R.drawable.catch_5_3);
		// catch6
		resMap.put(KEY_CATCH_6_1, R.drawable.shark_blue_catch_1);
		resMap.put(KEY_CATCH_6_2, R.drawable.shark_blue_catch_2);
		resMap.put(KEY_CATCH_6_3, R.drawable.shark_blue_catch_3);
		resMap.put(KEY_CATCH_6_4, R.drawable.shark_blue_catch_4);
		resMap.put(KEY_CATCH_6_5, R.drawable.shark_blue_catch_5);
		resMap.put(KEY_CATCH_6_6, R.drawable.shark_blue_catch_6);
		// cannon
		resMap.put(KEY_GAME_CANNON_1, R.drawable.cannon_1);
		resMap.put(KEY_GAME_CANNON_2, R.drawable.cannon_2);
		resMap.put(KEY_GAME_CANNON_3, R.drawable.cannon_3);
		resMap.put(KEY_GAME_CANNON_4, R.drawable.cannon_4);
		resMap.put(KEY_GAME_CANNON_5, R.drawable.cannon_5);
		resMap.put(KEY_GAME_CANNON_6, R.drawable.cannon_6);
		resMap.put(KEY_GAME_CANNON_7, R.drawable.cannon_7);
		resMap.put(KEY_GAME_CANNON_8, R.drawable.cannon_8);
		resMap.put(KEY_GAME_CANNON_9, R.drawable.cannon_9);
		resMap.put(KEY_GAME_CANNON_10, R.drawable.cannon_laser);
		resMap.put(KEY_GAME_CANNON_1_HEAD, R.drawable.cannon_1_head);
		resMap.put(KEY_GAME_CANNON_2_HEAD, R.drawable.cannon_2_head);
		resMap.put(KEY_GAME_CANNON_3_HEAD, R.drawable.cannon_3_head);
		resMap.put(KEY_GAME_CANNON_4_HEAD, R.drawable.cannon_4_head);
		resMap.put(KEY_GAME_CANNON_5_HEAD, R.drawable.cannon_5_head);
		resMap.put(KEY_GAME_CANNON_6_HEAD, R.drawable.cannon_6_head);
		resMap.put(KEY_GAME_CANNON_7_HEAD, R.drawable.cannon_7_head);
		resMap.put(KEY_GAME_CANNON_8_HEAD, R.drawable.cannon_8_head);
		resMap.put(KEY_GAME_CANNON_9_HEAD, R.drawable.cannon_9_head);
		// bullet
		resMap.put(KEY_GAME_BULLET_1, R.drawable.bullet_1);
		resMap.put(KEY_GAME_BULLET_2, R.drawable.bullet_2);
		resMap.put(KEY_GAME_BULLET_3, R.drawable.bullet_3);
		resMap.put(KEY_GAME_BULLET_4, R.drawable.bullet_4);
		resMap.put(KEY_GAME_BULLET_5, R.drawable.bullet_5);
		resMap.put(KEY_GAME_BULLET_6, R.drawable.bullet_6);
		// fish net
		resMap.put(KEY_GAME_NET_1, R.drawable.fishnet_1);
		resMap.put(KEY_GAME_NET_2, R.drawable.fishnet_2);
		resMap.put(KEY_GAME_NET_3, R.drawable.fishnet_3);
		resMap.put(KEY_GAME_NET_4, R.drawable.fishnet_4);
		resMap.put(KEY_GAME_NET_5, R.drawable.fishnet_5);
		resMap.put(KEY_GAME_NET_6, R.drawable.fishnet_6);
		resMap.put(KEY_GAME_NET_7, R.drawable.fishnet_7);
		// level text
		resMap.put(KEY_GAME_LEVEL_1, R.drawable.level_text_1);
		resMap.put(KEY_GAME_LEVEL_2, R.drawable.level_text_2);
		resMap.put(KEY_GAME_LEVEL_3, R.drawable.level_text_3);
		resMap.put(KEY_GAME_LEVEL_4, R.drawable.level_text_4);
		resMap.put(KEY_GAME_LEVEL_5, R.drawable.level_text_5);
		resMap.put(KEY_GAME_LEVEL_6, R.drawable.level_text_6);
		resMap.put(KEY_GAME_LEVEL_7, R.drawable.level_text_7);
		resMap.put(KEY_GAME_LEVEL_8, R.drawable.level_text_8);
		resMap.put(KEY_GAME_LEVEL_9, R.drawable.level_text_9);
		resMap.put(KEY_GAME_LEVEL_10, R.drawable.level_text_10);
		resMap.put(KEY_GAME_LEVEL_11, R.drawable.level_text_11);
		resMap.put(KEY_GAME_LEVEL_12, R.drawable.level_text_12);
		// gold
		resMap.put(KEY_GAME_FISH_GOLD_1, R.drawable.fish_gold_1);
		resMap.put(KEY_GAME_FISH_GOLD_2, R.drawable.fish_gold_2);
		resMap.put(KEY_GAME_FISH_GOLD_3, R.drawable.fish_gold_3);
		resMap.put(KEY_GAME_FISH_GOLD_4, R.drawable.fish_gold_4);
		resMap.put(KEY_GAME_FISH_GOLD_5, R.drawable.fish_gold_5);
		resMap.put(KEY_GAME_FISH_GOLD_6, R.drawable.fish_gold_6);
		// laser
		resMap.put(KEY_GAME_LASER_1, R.drawable.laser_1);
		resMap.put(KEY_GAME_LASER_2, R.drawable.laser_2);
		resMap.put(KEY_GAME_LASER_3, R.drawable.laser_3);
		resMap.put(KEY_GAME_LASER_4, R.drawable.laser_4);
		resMap.put(KEY_GAME_LASER_5, R.drawable.laser_5);
		resMap.put(KEY_GAME_LASER_6, R.drawable.laser_6);
		// boom
		resMap.put(KEY_GAME_BOOM_1, R.drawable.boom_1);
		resMap.put(KEY_GAME_BOOM_2, R.drawable.boom_2);
		resMap.put(KEY_GAME_BOOM_3, R.drawable.boom_3);
		resMap.put(KEY_GAME_BOOM_4, R.drawable.boom_4);
		// skill_anim
		resMap.put(KEY_GAME_SKILL_ANIM_1, R.drawable.skill_anim_1);
		resMap.put(KEY_GAME_SKILL_ANIM_2, R.drawable.skill_anim_2);
		resMap.put(KEY_GAME_SKILL_ANIM_3, R.drawable.skill_anim_3);
		resMap.put(KEY_GAME_SKILL_ANIM_4, R.drawable.skill_anim_4);
		resMap.put(KEY_GAME_SKILL_ANIM_5, R.drawable.skill_anim_5);

		// beautiful girl
		resMap.put(KEY_GAME_BEAUTIFUL_GIRL_1, R.drawable.beautiful_girl_1);
		resMap.put(KEY_GAME_BEAUTIFUL_GIRL_2, R.drawable.beautiful_girl_2);
		resMap.put(KEY_GAME_BEAUTIFUL_GIRL_3, R.drawable.beautiful_girl_3);
		resMap.put(KEY_GAME_BEAUTIFUL_GIRL_4, R.drawable.beautiful_girl_4);
		resMap.put(KEY_GAME_BEAUTIFUL_GIRL_5, R.drawable.beautiful_girl_5);
		resMap.put(KEY_GAME_BEAUTIFUL_GIRL_6, R.drawable.beautiful_girl_6);
		resMap.put(KEY_GAME_BEAUTIFUL_GIRL_7, R.drawable.beautiful_girl_7);
		resMap.put(KEY_GAME_BEAUTIFUL_GIRL_8, R.drawable.beautiful_girl_8);
		resMap.put(KEY_GAME_BEAUTIFUL_GIRL_9, R.drawable.beautiful_girl_9);
		resMap.put(KEY_GAME_BEAUTIFUL_GIRL_10, R.drawable.beautiful_girl_10);
		resMap.put(KEY_GAME_BEAUTIFUL_GIRL_11, R.drawable.beautiful_girl_11);
		resMap.put(KEY_GAME_BEAUTIFUL_GIRL_12, R.drawable.beautiful_girl_12);
		resMap.put(KEY_GAME_BEAUTIFUL_GIRL_13, R.drawable.beautiful_girl_13);
		// beautiful girl catch
		resMap.put(KEY_GAME_BEAUTIFUL_GIRL_CATCH_1,
				R.drawable.beautiful_girl_catch_1);
		resMap.put(KEY_GAME_BEAUTIFUL_GIRL_CATCH_2,
				R.drawable.beautiful_girl_catch_1);
		//
		// others
		resMap.put(KEY_GAME_TASK_BG, R.drawable.task_bg);
		resMap.put(KEY_GAME_EXP_PROGRESS, R.drawable.exp_progress);
		resMap.put(KEY_GAME_TURRET, R.drawable.game_turret);
		resMap.put(KEY_GAME_CANNON_DOWN_NORMAL, R.drawable.cannon_down_normal);
		resMap.put(KEY_GAME_CANNON_DOWN_PRESSED, R.drawable.cannon_down_pressed);
		resMap.put(KEY_GAME_CANNON_UP_NORMAL, R.drawable.cannon_up_normal);
		resMap.put(KEY_GAME_CANNON_UP_PRESSED, R.drawable.cannon_up_pressed);
		resMap.put(KEY_GAME_PLAYER_GOLD_NUM, R.drawable.palyer_gold_number);
		resMap.put(KEY_GAME_TASKNUM, R.drawable.game_task_num);
		resMap.put(KEY_GAME_TASKSIGN, R.drawable.game_task_sign);
		resMap.put(KEY_GAME_TASKPOINT, R.drawable.game_task_point);
		resMap.put(KEY_GAME_TASKTIME, R.drawable.game_task_time);
		resMap.put(KEY_GAME_LEVEL_BG, R.drawable.player_levelbg);
		resMap.put(KEY_GAME_LEVEL_NUM, R.drawable.player_level_num);
		resMap.put(KEY_GAME_LEVEL_PROGRESS, R.drawable.player_level_progress);
		resMap.put(KEY_GAME_NEWBEE, R.drawable.newbee);
		resMap.put(KEY_GAME_LEVEL_UP, R.drawable.level_up);
		resMap.put(KEY_GAME_LEVEL_UP_NUM, R.drawable.level_up_golg_num);
		resMap.put(KEY_GAME_HUODE, R.drawable.huode);
		resMap.put(KEY_GAME_JINBI, R.drawable.jinbi);
		resMap.put(KEY_GAME_RECHARGE, R.drawable.gold_recharge);
		resMap.put(KEY_GAME_SKILL_BOOM, R.drawable.skill_boom);
		resMap.put(KEY_GAME_BTN_BG_NORMAL, R.drawable.btn_bg_normal);
		resMap.put(KEY_GAME_BTN_BG_PRESSED, R.drawable.btn_bg_pressed);
		resMap.put(KEY_GAME_BTN_SETTING, R.drawable.btn_setting);
		resMap.put(KEY_GAME_MUSIC_OFF, R.drawable.muisc_off);
		resMap.put(KEY_GAME_MUSIC_ON, R.drawable.music_on);
		resMap.put(KEY_GAME_START, R.drawable.game_start);
		resMap.put(KEY_GAME_ALMS_NUM, R.drawable.alms_number);
		resMap.put(KEY_GAME_PLUS, R.drawable.gold_plus);
		resMap.put(KEY_GAME_SIGN, R.drawable.gold_multiply);
		resMap.put(KEY_GAME_GOLD_NUM_GET, R.drawable.gold_num_get);
		resMap.put(KEY_GAME_GOLD_NUM_SCREEN, R.drawable.gold_num_screen);
		resMap.put(KEY_GAME_OPEN_WEAPON_1, R.drawable.open_weapon_1);
		resMap.put(KEY_GAME_OPEN_WEAPON_2, R.drawable.open_weapon_2);
		resMap.put(KEY_GAME_OPEN_WEAPON_3, R.drawable.open_weapon_3);
		resMap.put(KEY_GAME_MORE_GAME, R.drawable.more_game);
		resMap.put(KEY_GAME_BGM_ON, R.drawable.bgm_on);
		resMap.put(KEY_GAME_BGM_OFF, R.drawable.bgm_off);
		resMap.put(KEY_GAME_TASK_FINISH, R.drawable.task_fish_bg);
		resMap.put(KEY_GAME_SKILL_NUM_BG, R.drawable.skill_num_bg);
		resMap.put(KEY_GAME_SKILL_NUM, R.drawable.skill_num);
		resMap.put(KEY_GAME_SKILL_HINT, R.drawable.skil_hint);
		resMap.put(KEY_GAME_RECHARGE_NUM, R.drawable.gold_recharge_number);
		resMap.put(KEY_GAME_OPTION, R.drawable.opinion);
		resMap.put(KEY_GAME_HOT_MARQUEE_BG, R.drawable.hot_marquee_bg);
		
		
		resMap.put(KEY_FISH_ITEM_HONGBAO, R.drawable.fish_hongbao);
		resMap.put(KEY_FISH_ITEM_HUAFEI, R.drawable.fish_huafei);
		resMap.put(KEY_FISH_ITEM_BOMB_1, R.drawable.fish_item_bomb_1);
		resMap.put(KEY_FISH_ITEM_BOMB_2, R.drawable.fish_item_bomb_2);
		resMap.put(KEY_FISH_ITEM_BOMB_3, R.drawable.fish_item_bomb_3);
		resMap.put(KEY_FISH_ITEM_BOMB_4, R.drawable.fish_item_bomb_4);
		resMap.put(KEY_FISH_ITEM_BOMB_5, R.drawable.fish_item_bomb_5);
		resMap.put(KEY_FISH_ITEM_BOMB_6, R.drawable.fish_item_bomb_6);
		resMap.put(KEY_FISH_ITEM_BOMB_7, R.drawable.fish_item_bomb_7);
		
		resMap.put(KEY_DAILY_TASK_BG, R.drawable.daily_task_bg);
		resMap.put(KEY_DAILY_TASK_CONFIRM, R.drawable.daily_task_confirm);
		resMap.put(KEY_DAILY_TASK_HAND, R.drawable.daily_hand);
		
	}

	@Override
	public Bitmap getBitmap(int key) {
		Bitmap bmp = resBitmapMap.get(key);
		if (bmp == null) {
			bmp = GameBitmapUtil.loadBitmap(res, resMap.get(key));
			if (bmp != null) {
				resBitmapMap.put(key, bmp);
			}
		}
		return bmp;
	}

	@Override
	public Bitmap getDefalutBitmap() {
		return null;
	}

	@Override
	public String getResName() {
		return "FishGameRes";
	}

	@Override
	public void recycle() {
		Engine.isRecycle = true;
		if (resBitmapMap != null && resBitmapMap.size() > 0) {
			for (Bitmap bmp : resBitmapMap.values()) {
				GameBitmapUtil.recycleBitmap(bmp);
			}
		}
	}

	public static int[] getIntArray(int number) {
		if (number < 0) {
			return null;
		}
		String buffer = String.valueOf(Math.abs(number));
		int[] numbers = new int[buffer.length()];
		for (int i = 0; i < buffer.length(); i++) {
			numbers[i] = Integer.valueOf(buffer.substring(i, i + 1));
		}
		return numbers;
	}

	public static int[] getIntArray(String str) {
		String buffer = str;
		int[] numbers = new int[buffer.length()];
		for (int i = 0; i < buffer.length(); i++) {
			numbers[i] = Integer.valueOf(buffer.substring(i, i + 1));
		}
		return numbers;
	}
}
