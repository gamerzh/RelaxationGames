package com.xiao.fish.game.sprite;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.view.MotionEvent;

import com.hifreshday.android.pge.entity.shape.sprite.Sprite;
import com.hifreshday.android.pge.view.res.IBitmapRes;
import com.xiao.fish.game.GameScene;
import com.xiao.fish.game.res.FishGameRes;
import com.xiao.fish.game.res.SoundRes;

public class SettingSprite extends Sprite {
	public static final int X = 740;
	public static final int Y = 400;
	public static final int WIDTH = 60;
	public static final int HEIGHT = 62;
	private boolean pressed = false;

	public SettingSprite(IBitmapRes bitmapRes, int pX, int pY, int width,
			int height) {
		super(bitmapRes, pX, pY, width, height);
		setNeedRecyle(true);
	}

	@Override
	public void onDrawSelf(Canvas canvas) {
		if (pressed) {
			Bitmap recharge = bitmapRes
					.getBitmap(FishGameRes.KEY_GAME_BTN_BG_PRESSED);
			canvas.drawBitmap(recharge, null, getRect(), null);
		} else {
			Bitmap recharge = bitmapRes
					.getBitmap(FishGameRes.KEY_GAME_BTN_BG_NORMAL);
			canvas.drawBitmap(recharge, null, getRect(), null);
		}
		Bitmap setting = bitmapRes.getBitmap(FishGameRes.KEY_GAME_BTN_SETTING);
		canvas.drawBitmap(setting, null, getRect(), null);
	}

	@Override
	public boolean onTouchEvent(MotionEvent event) {
		if (isVisible() && event.getAction() == MotionEvent.ACTION_DOWN
				&& getRect().contains((int) event.getX(), (int) event.getY())) {
			pressed = true;
			SoundRes.playSound(SoundRes.gameclick);
			// TODO 方便测试
			// StatisticsConstants.updateCannonInfoToServer();
			// ((GameScene) getParent()).testFunc();
			((GameScene) getParent()).showSetting();
			return true;
		}
		pressed = false;
		return false;
	}
}
