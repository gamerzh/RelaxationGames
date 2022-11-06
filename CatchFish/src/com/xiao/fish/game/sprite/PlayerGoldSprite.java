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

public class PlayerGoldSprite extends Sprite {

	public static final int X = 220;
	public static final int Y = 451;
	private static final int NUM_WIDTH = 12;
	private static final int NUM_HEIGHT = 17;
	private Bitmap numBitmap;
	private Rect numRect;

	public PlayerGoldSprite(IBitmapRes bitmapRes, int pX, int pY, int width,
			int height) {
		super(bitmapRes, pX, pY, width, height);
		setNeedRecyle(true);
		numRect = new Rect();
	}

	@Override
	public void onDrawSelf(Canvas canvas) {
		numBitmap = bitmapRes.getBitmap(FishGameRes.KEY_GAME_PLAYER_GOLD_NUM);
		int goledNumber = PxGameConstants.playerGold;
		if (goledNumber < 0) {
			goledNumber = 0;
		}
		int[] nums = FishGameRes.getIntArray(goledNumber);
		for (int i = 0; i < nums.length; i++) {
			Rect src = BitmapSpliter.splitBitmap2Rect(numBitmap, 10, nums[i],
					BitmapSpliter.HORIZONTAL);
			numRect.set(
					(int) (getRect().left + (i - nums.length) * NUM_WIDTH
							* EngineOptions.getScreenScaleX()),
					getRect().top,
					(int) (getRect().left + (i + 1 - nums.length) * NUM_WIDTH
							* EngineOptions.getScreenScaleX()),
					(int) (getRect().top + NUM_HEIGHT
							* EngineOptions.getScreenScaleY()));
			canvas.drawBitmap(numBitmap, src, numRect, null);
		}

	}
}
