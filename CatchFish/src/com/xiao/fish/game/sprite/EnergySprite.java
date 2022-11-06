package com.xiao.fish.game.sprite;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Rect;

import com.hifreshday.android.pge.engine.options.EngineOptions;
import com.hifreshday.android.pge.entity.shape.sprite.Sprite;
import com.hifreshday.android.pge.view.res.IBitmapRes;
import com.xiao.fish.PxGameConstants;
import com.xiao.fish.game.res.FishGameRes;

public class EnergySprite extends Sprite {

	public static final int X = 571;
	public static final int Y = 446;
	public static final int WIDTH = 141;
	public static final int HEIGHT = 26;
	private double rate = 0;
	private Rect dst;
	private Rect src;
	private Bitmap progress;

	// private Bitmap progress_bg;

	public EnergySprite(IBitmapRes bitmapRes, int pX, int pY, int width,
			int height) {
		super(bitmapRes, pX, pY, width, height);
		setNeedRecyle(true);
		dst = new Rect();
		src = new Rect();
		// PlayerInfo playerInfo = PlayerInfo.getPlayerInfo();
		this.rate = (float) PxGameConstants.playerEnergy
				/ (float) PxGameConstants.MAX_ENERGY;
	}

	@Override
	public void onDrawSelf(Canvas canvas) {
		// progress_bg =
		// bitmapRes.getBitmap(FishGameRes.KEY_GAME_EXP_PROGRESS_BG);
		// canvas.drawBitmap(progress_bg, null, getRect(), null);
		progress = bitmapRes.getBitmap(FishGameRes.KEY_GAME_EXP_PROGRESS);
		dst.set(getRect().left, getRect().top, (int) (getRect().left + WIDTH
				* EngineOptions.getScreenScaleX() * rate), getRect().bottom);
		src.set(0, 0, (int) (progress.getWidth() * rate), progress.getHeight());
		canvas.drawBitmap(progress, src, dst, null);
	}

	public void setProgress(double rate) {
		// Log.e("com.poxiao.fish", "rate=" + rate);
		this.rate = rate;
	}
}
