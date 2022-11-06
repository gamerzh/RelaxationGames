package org.cocos2dx.cpp;

import java.util.Timer;
import java.util.TimerTask;

import android.app.Activity;
import android.view.Gravity;
import android.widget.Toast;

import com.b.a.AppApplication;
import com.d.analysis.TbuAnalysis;
import com.d.extend.quitgame.ExitGameInterface;
import com.tbu.android.moreapp.MoreGameManager;
import com.tbu.android.moreapp.domain.MoreAppCallback;


public class NetWorkService {

	private static Activity activity;
	private static boolean openMoreGame = false;

	public static void init(final Activity activity) {
		NetWorkService.activity = activity;
		
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
				//LOG EVENT		
				TimerTask timetask = new TimerTask() {
					
					@Override
					public void run() {
						// TODO Auto-generated method stub
						GameApplication.getInstance().fullExitApplication();
					}
				};	
				JniPayCallbackHelper.GameQuitLogEvent();
				final Timer timer=new Timer(); 
				timer.schedule(timetask, 500);

				}
			
		});
	}

	public static void setOpenMoreGame() {

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
	public  static void  logevent(String event,
			String eventExtend, String sessionTime){
		
	TbuAnalysis.uploadAnalysis(activity, event, eventExtend, sessionTime,null);
		}
}
