package com.xiao.fish.game;

import java.util.Map;

import android.app.Dialog;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.SharedPreferences.Editor;
import android.view.WindowManager;
import android.view.WindowManager.LayoutParams;
import android.widget.Toast;

import com.b.a.AppApplication;
import com.d.avos.TbuCloudUtil;
import com.d.event.EventCallBack;
import com.d.event.EventResult;
import com.d.extend.quitgame.ExitGameInterface;
import com.hifreshday.android.pge.audio.sound.PgeSoundManager;
import com.hifreshday.android.pge.engine.Engine;
import com.hifreshday.android.pge.engine.options.EngineOptions;
import com.hifreshday.android.pge.engine.options.ScaleModel;
import com.hifreshday.android.pge.entity.scene.Scene;
import com.hifreshday.android.pge.ui.activity.BaseGameActivity;
import com.kx.byno.R;
import com.tallbigup.android.gds.sign.SignManager;
import com.tbu.androidtools.Debug;
import com.xiao.fish.FishCatchApplication;
import com.xiao.fish.PxGameConstants;
import com.xiao.fish.domain.PlayerInfo;
import com.xiao.fish.domain.fish.FishManage;
import com.xiao.fish.game.res.PaintManager;
import com.xiao.fish.game.res.SoundRes;
import com.xiao.fish.widget.HotDialog;
import com.xiao.fish.widget.SignInDialog;

public class GameActivity extends BaseGameActivity {
	public static final String SCENE_BG_TYPE = "SCENE_BG_TYPE";
	private int bg_type = 0;

	@Override
	public boolean coming() {
		getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		if (!FishCatchApplication.getInstance().isAppLaunch()) {
			return false;
		}
		Intent myIntent = this.getIntent();
		bg_type = myIntent.getIntExtra(SCENE_BG_TYPE, 0);
		return true;
	}

	@Override
	public int getGameViewResId() {
		return R.id.gameview;
	}

	@Override
	public int getLayoutResId() {
		return R.layout.game_layout;
	}

	@Override
	public int getSceneBgResId() {
		switch (bg_type) {
		case 0:
			return R.drawable.game_bg1;
		case 1:

			return R.drawable.game_bg1;
		case 2:

			return R.drawable.game_bg1;
		case 3:

			return R.drawable.game_bg1;
		default:
			return R.drawable.game_bg1;
		}

	}

	@Override
	public Engine onEngineLoaded() {
		if (getScreenWidth() <= 800) {
			Engine engine = new Engine(new EngineOptions(getScreenWidth(),
					getScreenHeight(), ScaleModel.FULLSCREEN, false,
					EngineOptions.ORIENTATION_HORIZONTAL));
			// engine.setShowFps(true);// 鏄剧ず甯х巼
			return engine;
		} else {
			Engine engine = new Engine(new EngineOptions(getScreenWidth(),
					getScreenHeight(), ScaleModel.CONSTRAIN, true,
					EngineOptions.ORIENTATION_HORIZONTAL // 鏄惁寮�鍚姉閿娇缁樺浘
					));
			// engine.setShowFps(true);// 鏄剧ず甯х巼
			return engine;
		}
	}

	@Override
	public Scene onLoadScene() {
		PaintManager.initPaintManager();
		PxGameConstants.init();
		// StatisticsConstants.init();
		BaseGameScene gameScene = new GameScene(this);
		gameScene.onLoadResources(getResources(), null);
		gameScene.setScreenSize(EngineOptions.getScreenWidth(),
				EngineOptions.getScreenHeight());
		gameScene.setBgResId(getResources(), getSceneBgResId());
		return gameScene;
	}

	@Override
	public void onLoadComplete() {
		PgeSoundManager manager = new PgeSoundManager(
				PgeSoundManager.MODEL_INITLATER);
		SoundRes.init(manager, this);
		if (!SignManager.isSignToday(GameActivity.this)) {
			GameActivity.this.runOnUiThread(new Runnable() {
				public void run() {
					Debug.i("GameActivity->sign day"
							+ SignManager.getCurrentSignDays(GameActivity.this));
					GameActivity.this.showDialog(GameActivity.SHOW_SING_DIALOG);
				}
			});
		}
		if (PlayerInfo.getPlayerInfo().isHasBuyMonth() && checkAllowGetGold()) {
			PlayerInfo info = PlayerInfo.getPlayerInfo();
			PxGameConstants.playerGold += 200;
			info.setGold(PxGameConstants.playerGold);
			PxGameConstants.IS_PLAY_GOLD_ANIM = true;
			GameActivity.this.runOnUiThread(new Runnable() {
				public void run() {
					Toast.makeText(GameActivity.this, "登录奖励:获得200金币",
							Toast.LENGTH_SHORT).show();
				}
			});
		}
		doEvent13();
	}

	public void doEvent13() {
		if (PxGameConstants.IS_ON_PAY) {
			return;
		}
		PxGameConstants.IS_ON_PAY = true;
		FishCatchApplication.getInstance().doMyPayEvent(GameActivity.this,
				"13", new EventCallBack() {
					@Override
					public void setEventResult(EventResult eventResult) {
						PxGameConstants.IS_ON_PAY = false;
						PlayerInfo info = PlayerInfo.getPlayerInfo();
						if (eventResult.getPResult()) {
							for (Map.Entry<Integer, Integer> entry : eventResult
									.getReward().entrySet()) {
								if (entry.getKey() == 1) {
									PxGameConstants.IS_PLAY_GOLD_ANIM = true;
									PxGameConstants.playerGold += entry
											.getValue();
								}
							}
							info.setGold(PxGameConstants.playerGold);
						}
						PlayerInfo.setPlayerInfo(info);
					}
				});
	}

	@Override
	public void onPauseGame() {
		PxGameConstants.savePlayerInfo();
		GameActivity.this.sendBroadcast(new Intent(
				PxGameConstants.MUSIC_DISABLED));
	}

	@Override
	public void onResumeGame() {
		FishManage.fishes.clear();
		GameActivity.this.sendBroadcast(new Intent(
				PxGameConstants.MUSIC_ENABLED));
	}

	@Override
	protected void onPause() {
		super.onPause();
		TbuCloudUtil.markOnPause(GameActivity.this);
	}

	@Override
	protected void onResume() {
		super.onResume();
		TbuCloudUtil.markOnResume(GameActivity.this);
	}

	@Override
	protected void onDestroy() {
		super.onDestroy();
	}

	@Override
	public void onBackPressed() {
		if (PxGameConstants.IS_SHOW_SETTING) {
			PxGameConstants.IS_SHOW_SETTING = false;
		} else {
			AppApplication.quitGame(GameActivity.this, new ExitGameInterface() {
				@Override
				public void quitGame() {
					FishCatchApplication.getInstance().fullExitApplication();
				}
			});
			// TODO 仅指易付88才打开
			// TbuCloudForCatchFish.zimonShowAdv(this);
		}
	}

	public static final int SHOW_SING_DIALOG = 2;
	public static final int SHOW_HOT_DIALOG = 3;

	@Override
	protected Dialog onCreateDialog(int id) {
		switch (id) {
		case SHOW_SING_DIALOG: {
			SignInDialog signInDialog = new SignInDialog(GameActivity.this);
			signInDialog.getWindow().setFlags(
					WindowManager.LayoutParams.FLAG_FULLSCREEN,
					WindowManager.LayoutParams.FLAG_FULLSCREEN);
			signInDialog.show();
			signInDialog.getWindow().setLayout(LayoutParams.MATCH_PARENT,
					LayoutParams.MATCH_PARENT);
			return signInDialog;
		}

		case SHOW_HOT_DIALOG: {
			HotDialog hotDialog = new HotDialog(GameActivity.this);
			hotDialog.getWindow().setFlags(
					WindowManager.LayoutParams.FLAG_FULLSCREEN,
					WindowManager.LayoutParams.FLAG_FULLSCREEN);
			hotDialog.show();
			hotDialog.getWindow().setLayout(LayoutParams.MATCH_PARENT,
					LayoutParams.MATCH_PARENT);
			return hotDialog;
		}
		}

		return super.onCreateDialog(id);
	}

	private static final String FISH_MONTH_TIME = "fish_month_time";

	/**
	 * 暂时先24小时领取一次
	 */
	private boolean checkAllowGetGold() {
		long currentTiem = System.currentTimeMillis();
		if ((currentTiem - getLastGetTime()) / (1000 * 60 * 60) >= 24) {
			SharedPreferences preferences = GameActivity.this
					.getSharedPreferences("fish_month", Context.MODE_PRIVATE);
			Editor editor = preferences.edit();
			editor.putLong(FISH_MONTH_TIME, currentTiem);
			editor.commit();
			return true;
		}
		return false;
	}

	private long getLastGetTime() {
		SharedPreferences preferences = GameActivity.this.getSharedPreferences(
				"fish_month", Context.MODE_PRIVATE);
		return preferences.getLong(FISH_MONTH_TIME, 0);
	}
}
