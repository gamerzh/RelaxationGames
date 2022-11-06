package com.xiao.fish.game.res;

import android.content.Context;
import android.util.Log;

import com.hifreshday.android.pge.audio.sound.PgeSoundManager;
import com.hifreshday.android.pge.audio.sound.Sound;
import com.kx.byno.R;
import com.xiao.fish.PxGameConstants;

public class SoundRes {

	public static Sound gamewin;
	public static Sound gamelose;
	public static Sound gameclick;
	public static Sound goldtopackage;
	public static Sound levelup;
	public static Sound taskfail;
	public static Sound tasksuccess;
	public static Sound taskstart;
	public static Sound shark;
	public static Sound bullet;
	public static Sound fishnet;
	public static Sound boom;
	public static Sound beautifulGirl;

	public static void init(PgeSoundManager manager, Context context) {
		gamewin = manager.newSound(context, R.raw.result_sucess);
		gamelose = manager.newSound(context, R.raw.result_fail);
		gameclick = manager.newSound(context, R.raw.paddle_hit);
		goldtopackage = manager.newSound(context, R.raw.gold_to_package);
		levelup = manager.newSound(context, R.raw.levelup);
		tasksuccess = manager.newSound(context, R.raw.task_success);
		taskstart = manager.newSound(context, R.raw.task_start);
		bullet = manager.newSound(context, R.raw.bullet);
		fishnet = manager.newSound(context, R.raw.fisnnet);
		boom = manager.newSound(context, R.raw.boom);
		beautifulGirl = manager.newSound(context, R.raw.beautifulgirl);
	}

	public static void dispose() {
		gamewin.dispose();
		gamelose.dispose();
		gameclick.dispose();
		goldtopackage.dispose();
		levelup.dispose();
		taskfail.dispose();
		taskstart.dispose();
		tasksuccess.dispose();
		shark.dispose();
		bullet.dispose();
		fishnet.dispose();
		boom.dispose();
		beautifulGirl.dispose();
	}

	private static final float VOLOME = 1.0f;
	public static final String SOUND_SWITCH = "sound_switch";
	public static final String SOUND_SWITCH_OPEN = "sound_switch_open";

	public static boolean playSound(Sound sound) {
		Boolean allowPlay = PxGameConstants.playerMusic;
		Log.d("SoundRes", "音效是否播放->" + allowPlay);
		if (allowPlay && sound != null) {
			sound.play(VOLOME);
			return true;
		} else {
			return false;
		}
	}
}
