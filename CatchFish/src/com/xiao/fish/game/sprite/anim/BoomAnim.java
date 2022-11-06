package com.xiao.fish.game.sprite.anim;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Point;
import android.graphics.Rect;

import com.hifreshday.android.pge.engine.options.EngineOptions;
import com.hifreshday.android.pge.extend.animation.AnimationSprite;
import com.hifreshday.android.pge.view.res.IBitmapRes;
import com.xiao.fish.game.res.FishGameRes;
import com.xiao.fish.game.res.SoundRes;

public class BoomAnim extends AnimationSprite {

	private Bitmap[] boomBitmaps;
	private Rect boomRect;
	private int index;
	private float time;
	private final int WIDTH = 200;
	private final int HEIGHT = 179;
	private Point point;

	public BoomAnim(IBitmapRes bitmapRes, int pX, int pY, int width, int height) {
		super(bitmapRes, pX, pY, width, height);
		setNeedRecyle(true);
		setVisible(false);
		init();
	}

	private void init() {
		boomBitmaps = new Bitmap[4];
		for (int i = 0; i < boomBitmaps.length; i++) {
			boomBitmaps[i] = bitmapRes.getBitmap(FishGameRes.KEY_GAME_BOOM_1
					+ i);
		}
		boomRect = new Rect(0, 0, 0, 0);
	}

	@Override
	public void onDrawSelf(Canvas canvas) {
		boomRect.set(
				(int) (point.x - WIDTH / 2 * EngineOptions.getScreenScaleX()),
				(int) (point.y - HEIGHT / 2 * EngineOptions.getScreenScaleY()),
				(int) (point.x + WIDTH / 2 * EngineOptions.getScreenScaleX()),
				(int) (point.y + HEIGHT / 2 * EngineOptions.getScreenScaleY()));
		canvas.drawBitmap(boomBitmaps[index], null, boomRect, null);
	}

	@Override
	protected void onUpdateSelf(float secondsElapsed) {
		if (isVisible()) {
			time += secondsElapsed;
			if (time > 0.3) {
				time -= 0.3;
				index++;
				if (index > 3) {
					setVisible(false);
					index = 0;
				}
			}
		}
	}

	public void startPlayBoom(int type) {
		switch (type) {
		case 0:
			this.point = new Point(
					(int) (150 * EngineOptions.getScreenScaleX()),
					(int) (300 * EngineOptions.getScreenScaleY()));
			break;
		case 1:
			this.point = new Point(
					(int) (200 * EngineOptions.getScreenScaleX()),
					(int) (100 * EngineOptions.getScreenScaleY()));
			break;
		case 2:
			this.point = new Point(
					(int) (50 * EngineOptions.getScreenScaleX()),
					(int) (400 * EngineOptions.getScreenScaleY()));
			break;
		case 3:
			this.point = new Point(
					(int) (550 * EngineOptions.getScreenScaleX()),
					(int) (100 * EngineOptions.getScreenScaleY()));
			break;
		case 4:
			this.point = new Point(
					(int) (700 * EngineOptions.getScreenScaleX()),
					(int) (400 * EngineOptions.getScreenScaleY()));
			break;
		case 5:
			this.point = new Point(
					(int) (450 * EngineOptions.getScreenScaleX()),
					(int) (200 * EngineOptions.getScreenScaleY()));
			break;
		case 6:
			this.point = new Point(
					(int) (300 * EngineOptions.getScreenScaleX()),
					(int) (350 * EngineOptions.getScreenScaleY()));
			break;
		case 7:
			this.point = new Point(
					(int) (600 * EngineOptions.getScreenScaleX()),
					(int) (140 * EngineOptions.getScreenScaleY()));
			break;

		}
		setVisible(true);
		SoundRes.playSound(SoundRes.boom);
	}
}
