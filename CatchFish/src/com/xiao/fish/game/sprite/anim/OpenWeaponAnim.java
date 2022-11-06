package com.xiao.fish.game.sprite.anim;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Rect;

import com.hifreshday.android.pge.engine.options.EngineOptions;
import com.hifreshday.android.pge.extend.animation.AnimationSprite;
import com.hifreshday.android.pge.view.res.IBitmapRes;
import com.xiao.fish.game.res.FishGameRes;

public class OpenWeaponAnim extends AnimationSprite {
	public static final int WEAPON_WIDTH = 169;
	public static final int WEAPON_HEIGHT = 100;
	private Rect weapon_rect;
	private Bitmap weapon = null;
	private int offsety = 0;
	private boolean isPlay = false;
	private float time = 0;

	public OpenWeaponAnim(IBitmapRes bitmapRes, int pX, int pY, int width,
			int height) {
		super(bitmapRes, pX, pY, width, height);
		init();
		setNeedRecyle(true);
		setVisible(false);
	}
	private void init() {
		weapon_rect = new Rect(
				(int) (EngineOptions.getOffsetX()+EngineOptions.getScreenWidth() / 2 - WEAPON_WIDTH / 2
						* EngineOptions.getScreenScaleX()),
				(int) (EngineOptions.getScreenHeight() - (100 + WEAPON_HEIGHT + offsety)
						* EngineOptions.getScreenScaleX()),
				(int) (EngineOptions.getOffsetX()+EngineOptions.getScreenWidth() / 2 + WEAPON_WIDTH / 2
						* EngineOptions.getScreenScaleX()),
				(int) (EngineOptions.getScreenHeight() - (100 + offsety)
						* EngineOptions.getScreenScaleX()));
	}

	@Override
	public void onDrawSelf(Canvas canvas) {
		if (null != weapon) {
			canvas.drawBitmap(weapon, null, weapon_rect, null);
		}
	}

	@Override
	protected void onUpdateSelf(float secondsElapsed) {
		if (isPlay) {
			time += secondsElapsed;
			if (time > 3) {
				isPlay = false;
				setVisible(false);
			}
		}
	}

	public void showOpenLockAnim(int type) {
		setVisible(true);
		isPlay = true;
		switch (type) {
		case 1:
			weapon = bitmapRes.getBitmap(FishGameRes.KEY_GAME_OPEN_WEAPON_1);
			break;
		case 2:
			weapon = bitmapRes.getBitmap(FishGameRes.KEY_GAME_OPEN_WEAPON_2);
			break;
		case 3:
			weapon = bitmapRes.getBitmap(FishGameRes.KEY_GAME_OPEN_WEAPON_3);
			break;
		}
	}
}
