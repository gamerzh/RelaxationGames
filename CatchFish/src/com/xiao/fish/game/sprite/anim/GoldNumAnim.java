package com.xiao.fish.game.sprite.anim;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Point;
import android.graphics.Rect;

import com.hifreshday.android.pge.engine.options.EngineOptions;
import com.hifreshday.android.pge.extend.animation.AnimationSprite;
import com.hifreshday.android.pge.view.BitmapSpliter;
import com.hifreshday.android.pge.view.res.IBitmapRes;
import com.xiao.fish.game.res.FishGameRes;

public class GoldNumAnim extends AnimationSprite {
	public static final int PLUS_WIDTH = 17;
	public static final int PLUS_HEIGHT = 19;
	public static final int NUM_WIDTH = 14;
	public static final int NUM_HEIGHT = 19;
	public static final int SIGN_WIDTH = 20;
	public static final int SIGN_HEIGHT = 27;
	public static final int BIG_NUM_WIDTH = 20;
	public static final int BIG_NUM_HEIGHT = 27;
	private boolean isPlay = true;
	private Rect numRect;
	private Rect goldNum;
	private float scale = 0.8f;
	private int money = 0;
	private Point point;

	public GoldNumAnim(IBitmapRes bitmapRes, int pX, int pY, int width,
			int height, Point point) {
		super(bitmapRes, pX, pY, width, height);
		setNeedRecyle(true);
		this.point = point;
		numRect = new Rect();
		goldNum = new Rect();
	}

	@Override
	public void onDrawSelf(Canvas canvas) {
		// 绘制屏幕金币数字
		if (isPlay && money != 0) {
			Bitmap sign = bitmapRes.getBitmap(FishGameRes.KEY_GAME_SIGN);
			numRect.set(
					(int) (point.x - SIGN_WIDTH * scale
							* EngineOptions.getScreenScaleX()), point.y,
					point.x, (int) (point.y + SIGN_HEIGHT * scale
							* EngineOptions.getScreenScaleY()));
			canvas.drawBitmap(sign, null, numRect, null);
			int[] nums = FishGameRes.getIntArray(money);
			for (int i = 0; i < nums.length; i++) {
				goldNum.set((int) (numRect.right + (i * BIG_NUM_WIDTH * scale)
						* EngineOptions.getScreenScaleX()), numRect.top,
						(int) (numRect.right + (i + 1) * BIG_NUM_WIDTH * scale
								* EngineOptions.getScreenScaleX()),
						(int) (numRect.top + BIG_NUM_HEIGHT * scale
								* EngineOptions.getScreenScaleY()));
				Bitmap num = bitmapRes
						.getBitmap(FishGameRes.KEY_GAME_GOLD_NUM_SCREEN);
				Rect src = BitmapSpliter.splitBitmap2Rect(num, 10, nums[i],
						BitmapSpliter.HORIZONTAL);
				canvas.drawBitmap(num, src, goldNum, null);
			}
		}
	}

	private float time;

	@Override
	protected void onUpdateSelf(float secondsElapsed) {
		time += secondsElapsed;
		if (time >1.0f) {
			setVisible(false);
		}
	}

	public void playGoldNum(int momey) {
		this.money = momey;
	}
}
