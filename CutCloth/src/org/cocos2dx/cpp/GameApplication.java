package org.cocos2dx.cpp;

import android.app.ActivityManager;
import android.content.ComponentName;
import android.content.Context;

import com.b.a.AppApplication;


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
