package com.xiao.fish.game.sprite;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Rect;
import android.view.MotionEvent;

import com.hifreshday.android.pge.engine.options.EngineOptions;
import com.hifreshday.android.pge.entity.shape.sprite.Sprite;
import com.hifreshday.android.pge.view.res.IBitmapRes;
import com.xiao.fish.game.res.FishGameRes;

public class TurretSprite extends Sprite {
	private Bitmap turretBitmap;
	public final static int WIDTH = 659;
	public final static int HEIGHT = 89;
	private Rect turretRect;

	public TurretSprite(IBitmapRes bitmapRes, int pX, int pY, int width,
			int height) {
		super(bitmapRes, pX, pY, width, height);
		setNeedRecyle(true);
		turretRect = new Rect(
				(int) ((EngineOptions.getScreenWidth() - WIDTH
						* EngineOptions.getScreenScaleX()) / 2 + EngineOptions
						.getOffsetX()),
				(int) (EngineOptions.getScreenHeight() - HEIGHT
						* EngineOptions.getScreenScaleY()),
				(int) ((EngineOptions.getScreenWidth() + WIDTH
						* EngineOptions.getScreenScaleX()) / 2 + EngineOptions
						.getOffsetX()), EngineOptions.getRealScreenHeight());
	}

	@Override
	public void onDrawSelf(Canvas canvas) {
		turretBitmap = bitmapRes.getBitmap(FishGameRes.KEY_GAME_TURRET);
		canvas.drawBitmap(turretBitmap, null, turretRect, null);
	}

	@Override
	public boolean onTouchEvent(MotionEvent event) {
		if (turretRect.contains((int) event.getX(), (int) event.getY())) {
			return true;
		}
		return false;
	}
}
