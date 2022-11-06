package com.elsfk.main;

import android.app.Activity;

import com.b.a.AppApplication;
import com.d.extend.quitgame.ExitGameInterface;


public class NetWorkService {

	private static Activity activity;


	public static void init(final Activity activity) {
		NetWorkService.activity = activity;
	}
	public static void quit() {
		AppApplication.quitGame(activity, new ExitGameInterface() {
			@Override
			public void quitGame() {
				GameApplication.getInstance().fullExitApplication();
		
		}
		});
	}
}
