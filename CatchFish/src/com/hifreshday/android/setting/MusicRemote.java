package com.hifreshday.android.setting;

import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.media.AudioManager;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;

import com.hifreshday.android.setting.aidl.MusicPlayAidlService;
import com.hifreshday.android.setting.service.MusicPlayService;
import com.kx.byno.R;
import com.tbu.androidtools.app.AppInfo;
import com.xiao.fish.PxGameConstants;

public class MusicRemote {

	private static MusicRemote instance;
	
	private ScreenBroadReciever screenBroadReciever;
	private boolean isScreenOff = false;
	private boolean isUnLock = false;
	private MusicPlayAidlService playerService;
	private boolean bindflag = false;
	protected String MUSIC_SERVICE_FILTER_ACTION = Setting.SERVICE_INTENT_FILTER_NAME;
	
	private Setting setting;

	private void initSetting(Context context) {
		setting = SettingImpl.getInstance(context);
	}
	
	public Setting getSetting() {
		return setting;
	}
	
	public static MusicRemote getInstance() {
		if(instance == null) {
			instance = new MusicRemote();
		}
		return instance;
	}
	
	public void init(Context context, String serviceFilterAction) {
		initSetting(context);
		MusicRemote.getInstance().setMUSIC_SERVICE_FILTER_ACTION(serviceFilterAction);
		registerMusicReciever(context);
		bindPlayerService(context);
	}
	
	/**
	 */
	public void registerMusicReciever(Context context) {
		if (null == screenBroadReciever) {
			IntentFilter filter = new IntentFilter();
			filter.addAction(Intent.ACTION_SCREEN_OFF);
			filter.addAction(Intent.ACTION_SCREEN_ON);
			filter.addAction(Intent.ACTION_USER_PRESENT);
			filter.addAction(PxGameConstants.MUSIC_DISABLED);
			filter.addAction(PxGameConstants.MUSIC_ENABLED);
			filter.addAction(PxGameConstants.MUSIC_PLAY);
			screenBroadReciever = new ScreenBroadReciever();
			context.registerReceiver(screenBroadReciever, filter);
		}
	}
	
	/**
	 * 
	 */
	public class ScreenBroadReciever extends BroadcastReceiver {

		@Override
		public void onReceive(Context context, Intent intent) {
			if (null != intent) {
				String a = intent.getAction();
				Log.e("com.poxiao.fish", "ScreenBroadReciever.onReceive:" + a);
				Setting setting = getSetting();
				if (a.equals(Intent.ACTION_USER_PRESENT)) {
					isUnLock = false;
				}
				if (a.equalsIgnoreCase(PxGameConstants.MUSIC_DISABLED)
						|| a.equalsIgnoreCase(Intent.ACTION_SCREEN_OFF)
						|| !AppInfo.isAppVisible(context)) {
					if (a.equalsIgnoreCase(Intent.ACTION_SCREEN_OFF)) {
						isScreenOff = true;
						isUnLock = true;
					}
					if (null != setting) {
						bgMusicPause();
					}
				}
				if (a.equalsIgnoreCase(PxGameConstants.MUSIC_ENABLED)
						|| a.equalsIgnoreCase(Intent.ACTION_SCREEN_ON)
						|| a.equals(Intent.ACTION_USER_PRESENT)) {
					if (a.equalsIgnoreCase(Intent.ACTION_SCREEN_ON)) {
						isScreenOff = false;
					}
					if (a.equals(Intent.ACTION_USER_PRESENT)) {
						isUnLock = false;
					}
					if (null != setting) {
						Boolean b = (Boolean) setting.getOtherProperties(
								PxGameConstants.BACKGROUND_MUSIC_SETTING_KEY,
								true);
						if (b && !isScreenOff && !isUnLock
								&& AppInfo.isAppVisible(context)) {
							bgMusicResume(context);
						}
					}
				}
				if (a.equalsIgnoreCase(PxGameConstants.MUSIC_PLAY)) {
					Boolean b = (Boolean) setting.getOtherProperties(
							PxGameConstants.BACKGROUND_MUSIC_SETTING_KEY, true);
					if (PxGameConstants.playerLogin) {
						setting.setOtherProperties(
								PxGameConstants.BACKGROUND_MUSIC_SETTING_KEY,
								true);
					}
					if (b) {
						bgMusicPlay(R.raw.fish_bgm);
					}
				}
			}
		}
	}
	
	/**
	 */
	public void unRegisterMusicReciver(Context context) {
		if (null != screenBroadReciever) {
			context.unregisterReceiver(screenBroadReciever);
			screenBroadReciever = null;
		}
	}

	public void stopMusicService(Context context) {
		if (null != playerService) {
			unbindPlayerService(context);
			playerService = null;
		}
		Log.d("com.poxiao.fish", "stop music service");
		Intent i = new Intent(context, MusicPlayService.class);
		context.stopService(i);
	}

	/**
	 */
	private ServiceConnection sc;
	public ServiceConnection getServiceConnection(final Context context) {
		if(sc == null) {
			sc = new ServiceConnection() {
				@Override
				public void onServiceDisconnected(ComponentName arg0) {
					if (null != playerService) {
						playerService = null;
					}
				}

				@Override
				public void onServiceConnected(ComponentName name, IBinder binder) {
					playerService = MusicPlayAidlService.Stub.asInterface(binder);
					context.sendBroadcast(new Intent(PxGameConstants.MUSIC_PLAY));
				}
			};
		}
		return sc;
	}
	
	

	/**
	 */
	public void bindPlayerService(Context context) {
		String action = getMUSIC_SERVICE_FILTER_ACTION();
		Intent i = new Intent(action);
		Log.d("com.poxiao.fish", "action=" + i.getAction());
		if (!bindflag) {
			bindflag = context.bindService(i, getServiceConnection(context), Context.BIND_AUTO_CREATE);
		}
	}

	/**
	 */
	public void unbindPlayerService(Context context) {
		if (bindflag && null != playerService) {
			context.unbindService(getServiceConnection(context));
			bindflag = false;
		}
	}

	/**
	 * 
	 * @param rid
	 */
	private void bgMusicPlay(int rid) {
		try {
			if (null != playerService) {
				;
				switch (playerService.getBGState()) {
				case -1:
					playerService.bgMusicInit(rid);
					break;
				}
				if ((Boolean) setting.getOtherProperties(
						PxGameConstants.BACKGROUND_MUSIC_SETTING_KEY, true)) {
					playerService.bgMusicPlay(true);
				}
			}
		} catch (RemoteException e) {
			Log.e("com.poxiao.fish", e.getMessage());
		}
	}

	/**
	 */
	private void bgMusicPause() {
		try {
			if (null != playerService) {
				switch (playerService.getBGState()) {
				case 1:
					playerService.bgMusicPause();
					break;
				}
			}
		} catch (RemoteException e) {
			Log.e("com.poxiao.fish", e.getMessage());
		}
	}

	/**
	 */
	private void bgMusicResume(Context context) {
		try {
			if (null != playerService) {
				switch (playerService.getBGState()) {
				case -1:
					playerService.bgMusicInit(R.raw.fish_bgm);
					context.sendBroadcast(new Intent(PxGameConstants.MUSIC_ENABLED));
					playerService.bgMusicPlay(true);
					break;
				case 0:
					playerService.bgMusicPlay(true);
					break;
				case 1:
					break;
				case 2:
					playerService.bgMusicResume();
					break;
				case 3:
					playerService.bgMusicPlay(true);
					break;
				}
			}
		} catch (RemoteException e) {
			Log.e("com.poxiao.fish", e.getMessage());
		}
	}

	public void bgMusicStop() {
		try {
			if (null != playerService) {
				playerService.bgMusicStop();
			}
		} catch (RemoteException e) {
			Log.e("com.poxiao.fish", e.getMessage());
		}
	}

	public void adjuestBGMusic(Context context) {
		try {
			if (null != playerService) {
				float volumn = getAudioVolumn(context);
				float maxVolumn = getAudioMaxVolumn(context);
				float v = volumn / maxVolumn * 0.40f;
				playerService.adjustBgMusicVolume(v);
			}
		} catch (RemoteException e) {
			Log.e("com.poxiao.fish", e.getMessage());
		}
	}

	public int getAudioVolumn(Context context) {
		AudioManager mAudioManager = (AudioManager) context.getSystemService(Context.AUDIO_SERVICE);
		int mVolume = mAudioManager.getStreamVolume(AudioManager.STREAM_MUSIC);
		return mVolume;
	}

	protected int getAudioMaxVolumn(Context context) {
		AudioManager mAudioManager = (AudioManager) context.getSystemService(Context.AUDIO_SERVICE);
		int max = mAudioManager.getStreamMaxVolume(AudioManager.STREAM_MUSIC);
		return max;
	}

	/**
	 * @return the isScreenOff
	 */
	public boolean isScreenOff() {
		return isScreenOff;
	}

	/**
	 * 
	 * @param mUSIC_SERVICE_FILTER_ACTION
	 *            the mUSIC_SERVICE_FILTER_ACTION to set
	 */
	public void setMUSIC_SERVICE_FILTER_ACTION(
			String mUSIC_SERVICE_FILTER_ACTION) {
		this.MUSIC_SERVICE_FILTER_ACTION = mUSIC_SERVICE_FILTER_ACTION;
	}

	/**
	 * @return the mUSIC_SERVICE_FILTER_ACTION
	 */
	public String getMUSIC_SERVICE_FILTER_ACTION() {
		return MUSIC_SERVICE_FILTER_ACTION;
	}
}
