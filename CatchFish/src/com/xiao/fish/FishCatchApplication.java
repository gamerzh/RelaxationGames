package com.xiao.fish;

import android.app.Activity;

import com.b.a.AppApplication;
import com.d.event.EventCallBack;
import com.d.event.EventResult;
import com.hifreshday.android.setting.MusicRemote;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.app.AppInfo;
import com.xiao.fish.game.res.SoundRes;

public class FishCatchApplication extends AppApplication {

	private static FishCatchApplication instance;

	@Override
	public void onCreate() {
		super.onCreate();
		if (AppInfo.isAppVisible(getApplicationContext())) {
			MusicRemote
					.getInstance()
					.init(this,
							"com.poxiao.fish.setting.service.MusicPlayService.AIDLAction");
		}
		instance = this;
	}

	public static FishCatchApplication getInstance() {
		return instance;
	}

	public boolean doMyPayEvent(final Activity activity, final String id,
			final EventCallBack callback) {
		if (!AppApplication.getInstance().doPEvent(activity, id, true,
				new EventCallBack() {
					@Override
					public void setEventResult(EventResult eventResult) {
						if (eventResult.getPResult()) {
							SoundRes.playSound(SoundRes.gamewin);
						} else {
							SoundRes.playSound(SoundRes.gamelose);
						}
						callback.setEventResult(eventResult);
					}
				})) {
			EventResult ev = new EventResult();
			ev.setPResult(false);
			callback.setEventResult(ev);
			return false;
		}
		return true;
	}

	@Override
	public void fullExitApplication() {
		PxGameConstants.savePlayerInfo();
		try {
			MusicRemote.getInstance().unRegisterMusicReciver(this);
			MusicRemote.getInstance().bgMusicStop();
			MusicRemote.getInstance().stopMusicService(this);
		} catch (Exception e) {
			Debug.e("FishCatchApplication->fullExitApplication, e = "
					+ e.toString());
		}
		super.fullExitApplication();
	}

}
