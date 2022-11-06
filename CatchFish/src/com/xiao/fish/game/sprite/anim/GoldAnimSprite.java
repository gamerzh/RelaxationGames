package com.xiao.fish.game.sprite.anim;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Point;
import android.graphics.RectF;

import com.hifreshday.android.pge.engine.options.EngineOptions;
import com.hifreshday.android.pge.extend.animation.AnimationSprite;
import com.hifreshday.android.pge.extend.tween.Ease;
import com.hifreshday.android.pge.view.res.IBitmapRes;
import com.xiao.fish.game.res.FishGameRes;
import com.xiao.fish.game.res.SoundRes;

public class GoldAnimSprite extends AnimationSprite {

	public static final int PNG_WIDTH = 38;
	public static final int PNG_HEIGHT = 39;
	private boolean isplay = true;
	private float chanegTime;
	private float distancey;
	private float offsetY = 0;
	private int x;
	private int y;
	private float rate = 1.0f;
	private RectF goldRect;
	private Bitmap[] goldBitmaps;
	private int index = 0;
	private final int Length = 6;
	private Point standard;
	private Point point;
	private int playIndex;

	public GoldAnimSprite(IBitmapRes bitmapRes, int pX, int pY, int width,
			int height) {
		super(bitmapRes, pX, pY, width, height);
		setNeedRecyle(true);
		initBitmap();
		standard = new Point(
				(int) (100 * EngineOptions.getScreenScaleX() + EngineOptions
						.getOffsetX()),
				(int) (455 * EngineOptions.getScreenScaleY() + EngineOptions
						.getOffsetY()));
		goldRect = new RectF();
	}

	private void initBitmap() {
		goldBitmaps = new Bitmap[Length];
		goldBitmaps[0] = bitmapRes.getBitmap(FishGameRes.KEY_GAME_FISH_GOLD_1);
		goldBitmaps[1] = bitmapRes.getBitmap(FishGameRes.KEY_GAME_FISH_GOLD_2);
		goldBitmaps[2] = bitmapRes.getBitmap(FishGameRes.KEY_GAME_FISH_GOLD_3);
		goldBitmaps[3] = bitmapRes.getBitmap(FishGameRes.KEY_GAME_FISH_GOLD_4);
		goldBitmaps[4] = bitmapRes.getBitmap(FishGameRes.KEY_GAME_FISH_GOLD_5);
		goldBitmaps[5] = bitmapRes.getBitmap(FishGameRes.KEY_GAME_FISH_GOLD_6);
	}

	@Override
	public void onDrawSelf(Canvas canvas) {
		if (isplay) {
			goldRect.set(
					(float) (point.x + (-PNG_WIDTH / 2 * rate)),
					(float) (point.y - offsetY
							* EngineOptions.getScreenScaleY()),
					(float) (point.x + (PNG_WIDTH / 2 * rate)
							* EngineOptions.getScreenScaleX()),
					(float) (point.y + (PNG_HEIGHT * rate - offsetY)
							* EngineOptions.getScreenScaleY()));
			canvas.drawBitmap(goldBitmaps[index], null, goldRect, null);
			// 图片的立体旋转
			// canvas.save();
			// Camera c = new Camera();
			// c.rotateY(degree);
			// Matrix bM = canvas.getMatrix();
			// c.getMatrix(bM);
			// float centerX = goldRect.left + goldRect.width() / 2;
			// float centerY = goldRect.top + goldRect.height() / 2;
			// bM.preTranslate(-centerX, -centerY);
			// bM.postTranslate(centerX, centerY);
			// canvas.setMatrix(bM);
			// canvas.drawBitmap(goldBitmap, null, goldRect, null);
			// canvas.restore();
		}
	}

	private int step = 0;
	private static final int STEP_START = 0;
	private static final int STEP_MOVE = 1;
	private static final int STEP_SCALE = 2;
	private static final int STEP_END = 3;
	private float time;
	private float delayTime;

	@Override
	protected void onUpdateSelf(float secondsElapsed) {
		if (isVisible()) {
			delayTime += secondsElapsed;
			if (delayTime > playIndex * 0.1) {
				chanegTime += secondsElapsed;
				if (chanegTime >= 0.06) {
					index = (++index) % 6;
					chanegTime -= 0.06;
				}
				switch (step) {
				case STEP_START:
					offsetY += 4 * secondsElapsed / 0.05;
					if (offsetY > 50) {
						offsetY = 50;
						step = STEP_MOVE;
					}
					break;
				case STEP_MOVE:
					time += secondsElapsed;
					if (time < 1) {
						float bili = (float) (time / 1);
						if (bili > 1) {
							bili = 1;
						}
						point.x = (int) (x + ((standard.x - x) * Ease
								.CubicOut(bili)));
						point.y = y
								+ (int) ((standard.y - y + offsetY) * Ease
										.CubicOut(bili));
						if (rate > 0.6) {
							rate -= 0.1;
						}
					} else {
						// 播放金币音效
						SoundRes.playSound(SoundRes.goldtopackage);
						step = STEP_END;
					}
					break;
				case STEP_SCALE:
					step = STEP_END;
					break;
				case STEP_END:
					claen();
					break;
				}
			}
		}
	}

	private void claen() {
		setVisible(false);
		isplay = false;
		rate = 1;
		step = 0;
		time = 0;
	}

	public void playGoldAnimtion(Point p, int playIndex) {
		isplay = true;
		setVisible(true);
		this.point = p;
		this.x = p.x;
		this.y = p.y;
		this.playIndex = playIndex;
	}
}
