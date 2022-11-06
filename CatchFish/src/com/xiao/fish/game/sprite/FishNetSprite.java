package com.xiao.fish.game.sprite;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Point;
import android.graphics.Rect;

import com.hifreshday.android.pge.engine.options.EngineOptions;
import com.hifreshday.android.pge.entity.shape.sprite.Sprite;
import com.hifreshday.android.pge.extend.tween.Ease;
import com.hifreshday.android.pge.view.res.IBitmapRes;
import com.xiao.fish.domain.fishnet.FishingNet;
import com.xiao.fish.game.GameScene;

public class FishNetSprite extends Sprite {
	public Rect netRect;
	public Rect collosionRect;
	public FishingNet fishingNet;
	private Bitmap fishNet;
	private float rate = 1.0f;
	private Point point;
	private int type;

	public FishNetSprite(IBitmapRes bitmapRes, int pX, int pY, int width,
			int height, FishingNet fishingNet, Point point) {
		super(bitmapRes, pX, pY, width, height);
		this.fishingNet = fishingNet;
		this.point = point;
		this.type=fishingNet.getNetType();
		this.setNeedRecyle(true);
		initRect();
	}

	public void initRect() {
		switch (fishingNet.getNetType()) {
		case 1:
			rate = 0.40f;
			break;
		case 2:
			rate = 0.40f;
			break;
		case 3:
			rate = 0.50f;
			break;
		case 4:
			rate = 0.55f;
			break;
		case 5:
			rate = 0.60f;
			break;
		case 6:
			rate = 0.65f;
			break;
		case 7:
			rate = 0.80f;
			break;
		case 8:
			rate = 0.85f;
			break;
		case 9:
			rate = 0.90f;
			break;
		default:
			rate = 1;
			break;
		}
		this.fishNet = bitmapRes.getBitmap(fishingNet.getFishNetBitmap());
		netRect = new Rect((int) (point.x - fishingNet.getWidth() / 2 * scale
				* EngineOptions.getScreenScaleX()),
				(int) (point.y - fishingNet.getHeight() / 2 * scale
						* EngineOptions.getScreenScaleY()),
				(int) (point.x + fishingNet.getWidth() / 2 * scale
						* EngineOptions.getScreenScaleX()),
				(int) (point.y + fishingNet.getHeight() / 2 * scale
						* EngineOptions.getScreenScaleY()));
		collosionRect = new Rect((int) (point.x - fishingNet.getWidth() / 2
				* rate * EngineOptions.getScreenScaleX()),
				(int) (point.y - fishingNet.getHeight() / 2 * rate
						* EngineOptions.getScreenScaleY()),
				(int) (point.x + fishingNet.getWidth() / 2 * rate
						* EngineOptions.getScreenScaleX()),
				(int) (point.y + fishingNet.getHeight() / 2 * rate
						* EngineOptions.getScreenScaleY()));
	}

	@Override
	public void onDrawSelf(Canvas canvas) {
		netRect.set((int) (point.x - fishingNet.getWidth() / 2 * scale
				* EngineOptions.getScreenScaleX()),
				(int) (point.y - fishingNet.getHeight() / 2 * scale
						* EngineOptions.getScreenScaleY()),
				(int) (point.x + fishingNet.getWidth() / 2 * scale
						* EngineOptions.getScreenScaleX()),
				(int) (point.y + fishingNet.getHeight() / 2 * scale
						* EngineOptions.getScreenScaleY()));
		canvas.drawBitmap(fishNet, null, netRect, null);
	}

	// private float elsape = 0;
	private boolean isCheckeed = false;
	private float time = 0;
	private float scale = 0.0f;
	private static final int STEP_1 = 0;
	private static final int STEP_2 = 2;
	private static final int STEP_3 = 3;

	private int step = 0;
	private float scaleTime = 0;

	@Override
	protected void onUpdateSelf(float secondsElapsed) {
		// 一秒检测一次渔网，避免频繁的检测
		// elsape += secondsElapsed;
		// if (elsape > 0.2) {
		// elsape -= 0.1;
		// }
		if (!isCheckeed) {
			updateFishCollosion();
			isCheckeed = true;
		}
		if (isVisible()) {
			switch (step) {
			case STEP_1:
				scaleTime += secondsElapsed;
				float bili = (float) (scaleTime / 0.5);
				if (bili > 1) {
					bili = 1;
				}
				scale = (float) (0.2 + 0.65 * Ease.CubicOut(bili));
				if (scale > 0.85) {
					step = STEP_2;
				}
				break;
			case STEP_2:
				scale -= 0.02;
				if (scale <= 0.82f) {
					scale = 0.84f;
					step = STEP_3;
				}
				break;
			case STEP_3:
				time += secondsElapsed;
				if (time > 0.5) {
					setVisible(false);
					clean();
				}
				break;
			}
		}
	}

	private void clean() {
		time = 0;
		scale = 0.8f;
		step = STEP_1;
	}

	private void updateFishCollosion() {
		if (isVisible()) {
			// 开始检测渔网的碰撞
			((GameScene) getParent()).isNetCollision(this);
		}
	}

	public int getType() {
		return type;
	}
	
	
}
