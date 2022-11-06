package org.cocos2dx.cpp;





import android.app.Activity;
import android.app.Application;
import android.view.Window;
import android.view.WindowManager;
import android.view.WindowManager.LayoutParams;

import com.avos.avoscloud.AVAnalytics;
import com.avos.avoscloud.AVOSCloud;
import com.d.extend.ExtendGameRes;
import com.d.extend.moreapp.MoreGameDialog;
import com.meizu.gamesdk.offline.core.MzGameCenterPlatform;
import com.tbu.androidtools.TbuAndroidTools;



public class GameApplication extends Application{
	private static GameApplication instance;
		
	@Override
	public void onCreate() {
		super.onCreate();
		  AVAnalytics.setAppChannel("test");
		 AVOSCloud.initialize(this, "mbXcqbzwIOIYvk6JP9c5jEHP-gzGzoHsz", "8y5SyLSCMsl4jL5jvtGad14T");
	     AVAnalytics.enableCrashReport(this, true);
		ExtendGameRes.initResources();
		TbuAndroidTools.init(this);
		 MzGameCenterPlatform.init(this, GameConstants.GAME_ID, GameConstants.GAME_KEY);
		instance = this;
	}
	public static GameApplication getInstance(){
		return instance;
	}
	
	public void showMoreGame(final Activity activity) {
		activity.runOnUiThread(new Runnable() {

			@Override
			public void run() {
				MoreGameDialog moreGameDialog = new MoreGameDialog(activity,
						activity);
				moreGameDialog.requestWindowFeature(Window.FEATURE_NO_TITLE);
				moreGameDialog.getWindow().setFlags(
						WindowManager.LayoutParams.FLAG_FULLSCREEN,
						WindowManager.LayoutParams.FLAG_FULLSCREEN);
				moreGameDialog.show();
				moreGameDialog.getWindow().setLayout(LayoutParams.MATCH_PARENT,
						LayoutParams.MATCH_PARENT);
			}
		});
	}

}
