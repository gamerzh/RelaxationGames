package com.xiao.fish.activity;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;

import com.b.a.AppApplication;
import com.d.avos.TbuCloudUtil;
import com.kx.byno.R;
import com.xiao.fish.domain.PlayerInfo;
import com.xiao.fish.game.GameActivity;
public class SplashActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.splash_activity);
		libInit();
	}

	@Override
	protected void onStart() {
		super.onStart();
	}

	private void libInit() {
		new Handler().postDelayed(new Runnable() {
			public void run() {
				AppApplication.getInstance().initOnFirstActivity(
						SplashActivity.this);
				jumpToGame();
			}
		}, 1000);
	}
	
	// 直接跳转到游戏
	private void jumpToGame() {
		PlayerInfo info = PlayerInfo.getPlayerInfo();
		int loginTimes = info.getLoginTimes() + 1;
		int index = info.getBgType();
		info.setLoginTimes(loginTimes);
		PlayerInfo.setPlayerInfo(info);
		Intent intent = new Intent(SplashActivity.this, GameActivity.class);
		intent.putExtra(GameActivity.SCENE_BG_TYPE, index);
		startActivity(intent);
	}

	@Override
	protected void onDestroy() {

		super.onDestroy();
	}
	
	@Override
	protected void onPause() {
		super.onPause();
		TbuCloudUtil.markOnPause(SplashActivity.this);
	}

	@Override
	protected void onResume() {
		super.onResume();
		TbuCloudUtil.markOnResume(SplashActivity.this);
	}
}
