package org.cocos2dx.cpp;

import android.app.Activity;
import android.view.Gravity;
import android.widget.Toast;

import com.tallbigup.android.AppApplication;
import com.tallbigup.android.extend.quitgame.ExitGameInterface;
import com.tbu.android.moreapp.MoreGameManager;
import com.tbu.android.moreapp.domain.MoreAppCallback;
import com.tbu.androidtools.Debug;

public class NetWorkService {

	private static Activity activity;
	private static boolean openMoreGame = false;

	public static void init(final Activity activity) {
		NetWorkService.activity = activity;
		
		setTehui(true);//特惠开关默认false
		
		MoreGameManager.init(activity, new MoreAppCallback() {
			@Override
			public void result(boolean changed) {
				if (MoreGameManager.allowShowMoreApps(activity)) {
					openMoreGame = true;
				} else {
					openMoreGame = false;
				}
				setOpenMoreGame();
			}
		});
		
	}

	public static void showMoreGame() {
		AppApplication.showMoreGame(activity);
	}

	public static void quit() {
		
		AppApplication.quitGame(activity, new ExitGameInterface() {

			@Override
			public void quitGame() {
				GameApplication.getInstance().fullExitApplication();
			}
		});
		
	}

	public static void setOpenMoreGame() {
		Debug.e("openMoreGame="+openMoreGame);
		JniPayCallbackHelper.showMoreGameNative(openMoreGame);
	}
	
	/**
	 * 是否开放特惠礼包按钮
	 */
	
	public static void setTehui(boolean open) {
		JniPayCallbackHelper.showTehui(open);
	}
	
	public static void showMonthCardToast(){
		activity.runOnUiThread(new Runnable(){

			@Override
			public void run() {
				Toast toast = Toast.makeText(activity,
					     "获得提示道具2个", Toast.LENGTH_LONG);
				toast.setGravity(Gravity.CENTER, 0, 0);
				toast.show();
				
			}
			
		});
	}
}
