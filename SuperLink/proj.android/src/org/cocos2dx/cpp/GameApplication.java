package org.cocos2dx.cpp;

import java.util.Random;

import android.app.Activity;
import android.app.ActivityManager;
import android.content.ComponentName;
import android.content.Context;
import android.util.Log;

import com.tallbigup.android.AppApplication;
import com.tallbigup.android.cloud.CloudPlayer;
import com.tallbigup.android.cloud.CreatePlayerCallback;
import com.tallbigup.android.cloud.TbuCallback;
import com.tallbigup.android.cloud.TbuCloud;
import com.tbu.androidtools.app.AppInfo;
import com.tbu.androidtools.device.DeviceInfo;

public class GameApplication extends AppApplication{
	
	public static final String TAG = GameApplication.class.getCanonicalName();
	
	private GameInfoUtil gameInfo;
	private String playerId;
	
	private static GameApplication instance;
		
	@Override
	public void onCreate() {
		super.onCreate();
		instance = this;
		gameInfo = GameInfoUtil.getInstance();
		gameInfo.init(this);
		//
		AppApplication.getInstance().startPush();
	
	}
	
	@Override
	public void fullExitApplication() {	
		GameApplication.getInstance().QuitPush();
		super.fullExitApplication();
	}
	
	public static GameApplication getInstance(){
		return instance;
	}
	
	public String getPlayerId(){
		return playerId;
	}
	
	public boolean isAppVisible(Context activity) {
        ActivityManager am = (ActivityManager) activity.getSystemService(Context.ACTIVITY_SERVICE);
        ComponentName cn = am.getRunningTasks(1).get(0).topActivity;
        if (cn.getPackageName().equals(activity.getPackageName())) {
            return true;
        }
        return false;
	}

}
