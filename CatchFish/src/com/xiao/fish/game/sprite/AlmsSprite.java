package com.xiao.fish.game.sprite;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Rect;

import com.hifreshday.android.pge.engine.options.EngineOptions;
import com.hifreshday.android.pge.entity.shape.sprite.Sprite;
import com.hifreshday.android.pge.view.BitmapSpliter;
import com.hifreshday.android.pge.view.res.IBitmapRes;
import com.xiao.fish.PxGameConstants;
import com.xiao.fish.game.res.FishGameRes;

public class AlmsSprite extends Sprite {

	public static final int X = 232;
	public static final int Y = 444;
	public static final int WIDTH = 30;
	public static final int HEIGHT = 30;
	public static final int NUM_WIDTH = 9;
	public static final int NUM_HEIGHT = 14;
	public static final int PLUS_WIDTH = 17;
	public static final int PLUS_HEIGHT = 15;

	private float time = 60;
	private Rect timeRect;
	private Rect plusRect;
	private Rect plusNum;
	private boolean start = false;
	private boolean isShow = false;
	private float scale = 0.8f;

	public AlmsSprite(IBitmapRes bitmapRes, int pX, int pY, int width,
			int height) {
		super(bitmapRes, pX, pY, width, height);
		timeRect = new Rect();
		plusRect = new Rect();
		plusNum = new Rect();
		setNeedRecyle(true);
	}

	@Override
	public void onDrawSelf(Canvas canvas) {
		if (time <= 0) {
			reset();
			isShow = true;
			PxGameConstants.playerGold += 10;
		}
		if (isShow) {
			drawPlusGlod(canvas);
		}
		int[] nums = FishGameRes.getIntArray((int) time);
		Bitmap num = bitmapRes.getBitmap(FishGameRes.KEY_GAME_ALMS_NUM);
		for (int i = 0; i < nums.length; i++) {
			Rect src = BitmapSpliter.splitBitmap2Rect(num, 10, nums[i],
					BitmapSpliter.HORIZONTAL);
			timeRect.set(
					(int) (getRect().left + ((WIDTH - NUM_WIDTH * nums.length) / 2 + i
							* NUM_WIDTH)
							* EngineOptions.getScreenScaleX()),
					(int) (getRect().top + (HEIGHT - NUM_HEIGHT) / 2
							* EngineOptions.getScreenScaleY()),
					(int) (getRect().left + ((WIDTH - NUM_WIDTH * nums.length) / 2 + (i + 1)
							* NUM_WIDTH)
							* EngineOptions.getScreenScaleX()),
					(int) (getRect().top + (HEIGHT + NUM_HEIGHT) / 2
							* EngineOptions.getScreenScaleY()));
			canvas.drawBitmap(num, src, timeRect, null);
		}
	}

	private void drawPlusGlod(Canvas canvas) {
		Bitmap plus = bitmapRes.getBitmap(FishGameRes.KEY_GAME_PLUS);
		plusRect.set((int) (getRect().left - (20 + PLUS_WIDTH * scale)
				* EngineOptions.getScreenScaleX()),
				(int) (getRect().top - 30 * EngineOptions.getScreenScaleY()),
				(int) (getRect().left - 20 * EngineOptions.getScreenScaleX()),
				(int) (getRect().top + (PLUS_HEIGHT * scale - 30)
						* EngineOptions.getScreenScaleY()));
		canvas.drawBitmap(plus, null, plusRect, null);
		plusNum.set(
				(int) (plusRect.right + (20 - PLUS_WIDTH * scale)
						* EngineOptions.getScreenScaleX()),
				plusRect.top,
				(int) (plusRect.right + 20 * EngineOptions.getScreenScaleX()),
				(int) (plusRect.top + PLUS_HEIGHT * scale
						* EngineOptions.getScreenScaleY()));
		Bitmap num = bitmapRes.getBitmap(FishGameRes.KEY_GAME_PLAYER_GOLD_NUM);
		int[] nums = FishGameRes.getIntArray(10);
		for (int i = 0; i < nums.length; i++) {
			plusNum.set(
					(int) (plusRect.right + (i * NUM_WIDTH * scale)
							* EngineOptions.getScreenScaleX()),
					plusRect.top,
					(int) (plusRect.right + (i + 1) * NUM_WIDTH * scale
							* EngineOptions.getScreenScaleX()),
					(int) (plusRect.top + NUM_HEIGHT * scale
							* EngineOptions.getScreenScaleY()));
			Rect src = BitmapSpliter.splitBitmap2Rect(num, 10, nums[i],
					BitmapSpliter.HORIZONTAL);
			canvas.drawBitmap(num, src, plusNum, null);
		}
	}

	private static final int STEP_START = 0;
	private static final int STEP_END = 1;
	private int step = 0;

	@Override
	protected void onUpdateSelf(float secondsElapsed) {
		if (start) {
			time -= secondsElapsed;
		} else {
			reset();
		}
		if (isShow) {
			switch (step) {
			case STEP_START:
				scale += 0.05;
				if (scale >= 1.2) {
					step = STEP_END;
				}
				break;
			case STEP_END:
				scale -= .02;
				if (scale <= 1.0) {
					isShow = false;
				}
				break;
			}
		}
	}

	private void reset() {
		scale = 0.8f;
		time = 60;
		step = 0;
	}

	public void setStart(boolean start) {
		this.start = start;
	}

}
