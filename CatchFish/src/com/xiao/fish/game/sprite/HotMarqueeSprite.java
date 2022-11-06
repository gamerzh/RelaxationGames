package com.xiao.fish.game.sprite;

import android.content.Context;
import android.content.SharedPreferences;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.view.MotionEvent;
import android.widget.Toast;

import com.hifreshday.android.pge.engine.options.EngineOptions;
import com.hifreshday.android.pge.entity.shape.sprite.Sprite;
import com.hifreshday.android.pge.view.res.IBitmapRes;
import com.xiao.fish.PxGameConstants;
import com.xiao.fish.domain.PlayerInfo;
import com.xiao.fish.game.GameActivity;
import com.xiao.fish.game.GameScene;
import com.xiao.fish.game.res.FishGameRes;
import com.xiao.fish.game.res.PaintManager;
import com.xiao.fish.widget.MarqueeUpdater;
import com.xiao.fish.widget.MarqueeUpdater.MarqueeListener;

public class HotMarqueeSprite extends Sprite implements MarqueeListener {

	public static final int RECT_WIDTH = 336;
	public static final int RECT_HEIGHT = 27;
	public static final int X = 240;
	public static final int Y = 100;
	private static final int INIT_X = 270;
	private static final int WIDTH = 300;
	private float playTime = 0;
	private boolean clickabled = false;

	private static final float SPEED = 30.0f;
	private float currentTextPosition1 = 0;
	private float currentTextPosition2 = 0;
	private float buffersecond = 0.0f;
	private static String info = "游戏累计5分钟就送1000金币，还有机会赢实物大奖，点击此处领取奖励";
	private static String info2 = info;
	private float stringsize = 800.0f;

	public HotMarqueeSprite(IBitmapRes bitmapRes, int pX, int pY, int width,
			int height) {
		super(bitmapRes, pX, pY, width, height);
	}

	@Override
	protected void onUpdateSelf(float secondsElapsed) {
		playTime += secondsElapsed;
		if (playTime >= 60 * 5) {
			clickabled = true;
		}
		buffersecond += secondsElapsed;
		if ((buffersecond * SPEED) > 1) {
			float move = buffersecond * SPEED;
			currentTextPosition1 -= move;
			if (currentTextPosition1 < 0) {
				currentTextPosition2 = currentTextPosition1 + stringsize;
			} else {
				currentTextPosition2 -= move;
			}
			if (currentTextPosition2 < 0) {
				currentTextPosition1 = currentTextPosition2 + stringsize;
			}
			buffersecond = (buffersecond * SPEED - move) / SPEED;
		}
	}

	@Override
	public void onDrawSelf(Canvas canvas) {
		Bitmap marquee_bg = bitmapRes
				.getBitmap(FishGameRes.KEY_GAME_HOT_MARQUEE_BG);
		canvas.drawBitmap(marquee_bg, null, getRect(), null);
		canvas.save();
		canvas.translate(
				EngineOptions.getOffsetX() + INIT_X
						* EngineOptions.getScreenScaleX(),
				EngineOptions.getOffsetY() + Y
						* EngineOptions.getScreenScaleY());
		canvas.clipRect(0, 0, WIDTH * EngineOptions.getScreenScaleX(),
				RECT_HEIGHT * EngineOptions.getScreenScaleY());
		canvas.drawText(info,
				currentTextPosition1 * EngineOptions.getScreenScaleX(),
				20 * EngineOptions.getScreenScaleY(), PaintManager
						.getInstance().getText24Yellow());
		canvas.drawText(info2,
				currentTextPosition2 * EngineOptions.getScreenScaleX(),
				20 * EngineOptions.getScreenScaleY(), PaintManager
						.getInstance().getText24Yellow());
		canvas.restore();
	}

	@Override
	public boolean onTouchEvent(MotionEvent event) {
		if (getRect().contains((int) event.getX(), (int) event.getY())) {
			if (event.getAction() == MotionEvent.ACTION_DOWN
					|| event.getAction() == MotionEvent.ACTION_MOVE) {
				return true;
			} else if (event.getAction() == MotionEvent.ACTION_UP) {

				if (clickabled) {
					clickabled = false;
					long currenttime = System.currentTimeMillis();
					if (currenttime - getLastTime() > 12 * 60 * 60 * 100) {
						recordLastTime(currenttime);
						((GameScene) getParent()).getActivity().runOnUiThread(
								new Runnable() {
									public void run() {
										PlayerInfo info = PlayerInfo
												.getPlayerInfo();
										PxGameConstants.playerGold += 1000;
										info.setGold(PxGameConstants.playerGold);
										PxGameConstants.playerCannon = info
												.getMaxCannon();
										PlayerInfo.setPlayerInfo(info);
										((GameScene) getParent())
												.getActivity()
												.showDialog(
														GameActivity.SHOW_HOT_DIALOG);
									}
								});
					} else {
						final int time = 12 - (int) ((currenttime - getLastTime()) / 360000);
						((GameScene) getParent()).getActivity().runOnUiThread(
								new Runnable() {
									public void run() {
										Toast.makeText(
												((GameScene) getParent())
														.getActivity(),
												"每12小时领取一次,距下次领取还剩" + time
														+ "小时",
												Toast.LENGTH_SHORT).show();
									}
								});

					}
				} else {
					((GameScene) getParent()).getActivity().runOnUiThread(
							new Runnable() {
								public void run() {
									Toast.makeText(
											((GameScene) getParent())
													.getActivity(),
											"还不满足条件，继续努力吧", Toast.LENGTH_SHORT)
											.show();
								}
							});
				}
			}
		}
		return false;
	}

	@Override
	public void onUpdate() {
		info2 = MarqueeUpdater.getInstance().getMarquee();
	}

	private static final String HOT_TIME = "hot_time";
	private static final String LAST_GET_TIME = "last_get_time";

	/**
	 * 记录上一次的领取时间
	 */
	public void recordLastTime(long time) {
		SharedPreferences preferences = ((GameScene) getParent()).getActivity()
				.getSharedPreferences(HOT_TIME, Context.MODE_PRIVATE);
		SharedPreferences.Editor editor = preferences.edit();
		editor.putLong(LAST_GET_TIME, time);
		editor.commit();
	}

	/**
	 * 
	 * @param time
	 */
	public long getLastTime() {
		SharedPreferences preferences = ((GameScene) getParent()).getActivity()
				.getSharedPreferences(HOT_TIME, Context.MODE_PRIVATE);
		return preferences.getLong(LAST_GET_TIME, 0);

	}
}
