package com.xiao.fish.game.sprite.anim;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Rect;

import com.hifreshday.android.pge.engine.options.EngineOptions;
import com.hifreshday.android.pge.extend.animation.AnimationSprite;
import com.hifreshday.android.pge.view.res.IBitmapRes;
import com.xiao.fish.game.res.FishGameRes;

public class NewBeeAnim extends AnimationSprite {

	private Rect animRect;
	private float animScale = 0.2f;
	private boolean isPlay = false;
	public static final int ANIM_WIDTH = 373;
	public static final int ANIM_HEIGHT = 178;

	public NewBeeAnim(IBitmapRes bitmapRes, int pX, int pY, int width,
			int height) {
		super(bitmapRes, pX, pY, width, height);
		animRect = new Rect();
		setNeedRecyle(true);
		setVisible(false);
	}

	@Override
	public void onDrawSelf(Canvas canvas) {
		if (isPlay) {
			animRect.set(
					(int) ((EngineOptions.getScreenWidth() - ANIM_WIDTH
							* animScale * EngineOptions.getScreenScaleX()) / 2),
					(int) ((EngineOptions.getScreenHeight() - ANIM_HEIGHT
							* animScale * EngineOptions.getScreenScaleY()) / 2),
					(int) ((EngineOptions.getScreenWidth() + ANIM_WIDTH
							* animScale * EngineOptions.getScreenScaleX()) / 2),
					(int) ((EngineOptions.getScreenHeight() + ANIM_HEIGHT
							* animScale * EngineOptions.getScreenScaleY()) / 2));
			Bitmap bitmap = bitmapRes.getBitmap(FishGameRes.KEY_GAME_NEWBEE);
			canvas.drawBitmap(bitmap, null, animRect, null);
		}
	}

	private int anim_step = 0;
	private static final int STEP_ANIM_START = 0;
	private static final int STEP_ANIM_TWO = 1;
	private static final int STEP_ANIM_THREE = 2;
	private float time;

	@Override
	protected void onUpdateSelf(float secondsElapsed) {
		if (isPlay) {
			switch (anim_step) {
			case STEP_ANIM_START:
				animScale += 0.08;
				if (animScale >= 1.2) {
					anim_step = STEP_ANIM_TWO;
				}
				break;
			case STEP_ANIM_TWO:
				time += secondsElapsed;
				if (time > 0.8) {
					anim_step = STEP_ANIM_THREE;
				}
				break;
			case STEP_ANIM_THREE:
				animScale -= 0.04;
				if (animScale <= 0.8) {
					clean();
				}
				break;
			}
		}
	}

	private void clean() {
		isPlay = false;
		setVisible(false);
		animScale = 0.2f;
		anim_step = 0;
	}

	public void playNewBee() {
		setVisible(true);
		isPlay = true;
	}
}
