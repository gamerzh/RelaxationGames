package com.xiao.fish.game.sprite;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Rect;

import com.hifreshday.android.pge.engine.options.EngineOptions;
import com.hifreshday.android.pge.entity.shape.sprite.Sprite;
import com.hifreshday.android.pge.view.BitmapSpliter;
import com.hifreshday.android.pge.view.res.IBitmapRes;
import com.xiao.fish.game.res.FishGameRes;

public class PlayerLevelSprite extends Sprite {

	public static final int X = 0;
	public static final int Y = 20;
	public static final int WIDTH = 230;
	public static final int HEIGHT = 67;
	public static final int NUM_WIDTH = 21;
	public static final int NUM_HEIGHT = 28;
	public static final int CIRCLE_WIDTH = 68;
	public static final int PROGRESS_WIDTH = 168;
	public static final int PROGRESS_HEIGHT = 20;
	private Rect numRect;
	private Rect progressDst;
	private Rect progressSrc;
	private Rect textRect;
	private int level;
	private double rate;

	public PlayerLevelSprite(IBitmapRes bitmapRes, int pX, int pY, int width,
			int height) {
		super(bitmapRes, pX, pY, width, height);
		setNeedRecyle(true);
		numRect = new Rect();
		progressDst = new Rect();
		progressSrc = new Rect();
		textRect = new Rect();
	}

	@Override
	public void onDrawSelf(Canvas canvas) {
		Bitmap bg = bitmapRes.getBitmap(FishGameRes.KEY_GAME_LEVEL_BG);
		canvas.drawBitmap(bg, null, getRect(), null);
		// Log.e("com.poxiao.fish", "getRect.top" + getRect().top);
		int[] nums = FishGameRes.getIntArray(level);
		Bitmap num = bitmapRes.getBitmap(FishGameRes.KEY_GAME_LEVEL_NUM);
		for (int i = 0; i < nums.length; i++) {
			Rect src = BitmapSpliter.splitBitmap2Rect(num, 10, nums[i],
					BitmapSpliter.HORIZONTAL);
			numRect.set((int) (getRect().left + ((CIRCLE_WIDTH - NUM_WIDTH
					* nums.length) / 2 + i * NUM_WIDTH)
					* EngineOptions.getScreenScaleX()),
					(int) (getRect().top + (HEIGHT - NUM_HEIGHT) / 2
							* EngineOptions.getScreenScaleY()),
					(int) (getRect().left + ((CIRCLE_WIDTH - NUM_WIDTH
							* nums.length) / 2 + (i + 1) * NUM_WIDTH)
							* EngineOptions.getScreenScaleX()),
					(int) (getRect().top + (HEIGHT + NUM_HEIGHT) / 2
							* EngineOptions.getScreenScaleY()));
			canvas.drawBitmap(num, src, numRect, null);
		}
		Bitmap textBitmap = getBitmapByLevel(level);
		textRect.set(
				(int) (getRect().left + 110 * EngineOptions.getScreenScaleX() - textBitmap
						.getWidth() / 2),
				(int) (getRect().top + 12 * EngineOptions.getScreenScaleY()),
				(int) (getRect().left + 110 * EngineOptions.getScreenScaleX() + textBitmap
						.getWidth() / 2), (int) (getRect().top + 12
						* EngineOptions.getScreenScaleY() + textBitmap
						.getHeight()));
		canvas.drawBitmap(textBitmap, null, textRect, null);
		Bitmap progress = bitmapRes
				.getBitmap(FishGameRes.KEY_GAME_LEVEL_PROGRESS);
		progressDst.set(
				(int) (getRect().left + 56 * EngineOptions.getScreenScaleX()),
				(int) (getRect().bottom - (PROGRESS_HEIGHT + 9)
						* EngineOptions.getScreenScaleY()),
				(int) (getRect().left + (56 + rate * PROGRESS_WIDTH)
						* EngineOptions.getScreenScaleX()),
				(int) (getRect().bottom - 9 * EngineOptions.getScreenScaleY()));
		progressSrc.set(0, 0, (int) (progress.getWidth() * rate),
				progress.getHeight());
		canvas.drawBitmap(progress, progressSrc, progressDst, null);
	}

	private Bitmap getBitmapByLevel(int level) {
		Bitmap textBitmap;
		switch (level) {
		case 1:
			textBitmap = bitmapRes.getBitmap(FishGameRes.KEY_GAME_LEVEL_1);
			break;
		case 2:
			textBitmap = bitmapRes.getBitmap(FishGameRes.KEY_GAME_LEVEL_2);
			break;
		case 3:
			textBitmap = bitmapRes.getBitmap(FishGameRes.KEY_GAME_LEVEL_3);
			break;
		case 4:
			textBitmap = bitmapRes.getBitmap(FishGameRes.KEY_GAME_LEVEL_4);
			break;
		case 5:
			textBitmap = bitmapRes.getBitmap(FishGameRes.KEY_GAME_LEVEL_5);
			break;
		case 6:
			textBitmap = bitmapRes.getBitmap(FishGameRes.KEY_GAME_LEVEL_6);
			break;
		case 7:
			textBitmap = bitmapRes.getBitmap(FishGameRes.KEY_GAME_LEVEL_7);
			break;
		case 8:
			textBitmap = bitmapRes.getBitmap(FishGameRes.KEY_GAME_LEVEL_8);
			break;
		case 9:
			textBitmap = bitmapRes.getBitmap(FishGameRes.KEY_GAME_LEVEL_9);
			break;
		case 10:
			textBitmap = bitmapRes.getBitmap(FishGameRes.KEY_GAME_LEVEL_10);
			break;
		case 11:
			textBitmap = bitmapRes.getBitmap(FishGameRes.KEY_GAME_LEVEL_11);
			break;
		case 12:
			textBitmap = bitmapRes.getBitmap(FishGameRes.KEY_GAME_LEVEL_12);
			break;
		default:
			textBitmap = bitmapRes.getBitmap(FishGameRes.KEY_GAME_LEVEL_12);
			break;
		}
		return textBitmap;
	}

	public void setPlayerLevel(int level, double rate) { this.level = level;
		this.rate = rate;
	}
}
