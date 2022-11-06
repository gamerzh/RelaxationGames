package com.xiao.fish.game.sprite.anim;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Rect;

import com.hifreshday.android.pge.engine.options.EngineOptions;
import com.hifreshday.android.pge.extend.animation.AnimationSprite;
import com.hifreshday.android.pge.view.BitmapSpliter;
import com.hifreshday.android.pge.view.res.IBitmapRes;
import com.xiao.fish.game.res.FishGameRes;

public class SmallGoldNumAnim extends AnimationSprite {
	public static final int PLUS_WIDTH = 17;
	public static final int PLUS_HEIGHT = 19;
	public static final int NUM_WIDTH = 14;
	public static final int NUM_HEIGHT = 19;
	public static final int SIGN_WIDTH = 20;
	public static final int SIGN_HEIGHT = 27;
	public static final int BIG_NUM_WIDTH = 20;
	public static final int BIG_NUM_HEIGHT = 27;
	private boolean isShow = false;
	private boolean isStart = false;
	private Rect numRect;
	private Rect goldNum;
	private float scale = 0.6f;
	private int money = 0;

	public SmallGoldNumAnim(IBitmapRes bitmapRes, int pX, int pY, int width,
			int height) {
		super(bitmapRes, pX, pY, width, height);
		setNeedRecyle(true);
		numRect = new Rect();
		goldNum = new Rect();
	}

	@Override
	public void onDrawSelf(Canvas canvas) {
		// 绘制左下角的小数字
		if (isShow && money != 0) {
			Bitmap plus = bitmapRes.getBitmap(FishGameRes.KEY_GAME_PLUS);
			numRect.set((int) ((225 - PLUS_WIDTH * scale) * EngineOptions
					.getScreenScaleX()), (int) (415 * EngineOptions
					.getScreenScaleY()), (int) (225 * EngineOptions
					.getScreenScaleX()),
					(int) ((415 + PLUS_HEIGHT * scale) * EngineOptions
							.getScreenScaleY()));
			canvas.drawBitmap(plus, null, numRect, null);
			int[] nums = FishGameRes.getIntArray(money);
			for (int i = 0; i < nums.length; i++) {
				goldNum.set(
						(int) (numRect.right + (i * NUM_WIDTH * scale)
								* EngineOptions.getScreenScaleX()),
						numRect.top,
						(int) (numRect.right + (i + 1) * NUM_WIDTH * scale
								* EngineOptions.getScreenScaleX()),
						(int) (numRect.top + NUM_HEIGHT * scale
								* EngineOptions.getScreenScaleY()));
				Bitmap num = bitmapRes
						.getBitmap(FishGameRes.KEY_GAME_GOLD_NUM_GET);
				Rect src = BitmapSpliter.splitBitmap2Rect(num, 10, nums[i],
						BitmapSpliter.HORIZONTAL);
				canvas.drawBitmap(num, src, goldNum, null);
			}
		}
	}

	private int anim_step = 0;
	private float time;
	private float showTime;
	private static final int STEP_ANIM_START = 0;
	private static final int STEP_ANIM_TWO = 1;
	private static final int STEP_ANIM_THREE = 2;

	@Override
	protected void onUpdateSelf(float secondsElapsed) {
		if (isStart) {
			time += secondsElapsed;
			if (time > 1.0) {
				isShow = true;
				switch (anim_step) {
				case STEP_ANIM_START:
					scale += 0.1;
					if (scale >= 1) {
						anim_step = STEP_ANIM_TWO;
					}
					break;
				case STEP_ANIM_TWO:
					showTime += secondsElapsed;
					if (showTime > 0.5) {
						anim_step = STEP_ANIM_THREE;
					}
					break;

				case STEP_ANIM_THREE:
					clean();
					break;
				}
			}
		}
	}

	private void clean() {
		showTime = 0;
		isShow = false;
		isStart = false;
		time = 0;
		scale = 0.6f;
	}

	public void playGoldNumSmall(int momey) {
		this.money = momey;
		isStart = true;
	}
}
