package com.xiao.fish.game.sprite;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Rect;
import android.graphics.RectF;
import android.util.Log;

import com.hifreshday.android.pge.engine.options.EngineOptions;
import com.hifreshday.android.pge.entity.shape.sprite.Sprite;
import com.hifreshday.android.pge.view.res.GameBitmapUtil;
import com.hifreshday.android.pge.view.res.IBitmapRes;
import com.xiao.fish.constants.BirthPosition;
import com.xiao.fish.constants.MoveSpeed;
import com.xiao.fish.constants.MoveUtils;
import com.xiao.fish.domain.fish.Fish;

public class FishSprite extends Sprite {
	public RectF fishRect;
	public Rect collosionRect;
	private float rate = 0.75f;
	private float deltTime;
	private float replaceTime;
	private int index = 0;
	private int catchIndex = 0;
	private double degree;
	private int rotateDegree;
	private double rotate = 0;
	private int speed;
	public int gold;
	public int experience;
	public int fishType;
	private Bitmap[] fishBitmaps;
	private Bitmap[] catchBitmaps;
	private boolean isCapture = false;
	private int width;
	private int height;
	private BirthPosition birthPosition;
	private float[] animTiem;
	private float catchTime;
	private Fish fish;
	private float lucky = 0.75f;

	public FishSprite(IBitmapRes bitmapRes, int pX, int pY, int width,
			int height, Fish fish) {
		super(bitmapRes, pX, pY, width, height);
		this.fish = fish;
		this.degree = fish.getBirthPosition().degree;
		this.rotateDegree = fish.getBirthPosition().rotateDegree;
		this.speed = fish.getSpeed();
		this.gold = fish.getGold();
		this.experience = fish.getExperience();
		this.fishType = fish.getFishType();
		this.width = fish.getWidth();
		this.height = fish.getHeight();
		this.birthPosition = fish.getBirthPosition();
		this.animTiem = fish.getAnimTime();
		this.catchTime = fish.getCatchTime();
		this.fishRect = new RectF(getRect().left, getRect().top,
				getRect().right, getRect().bottom);
		this.collosionRect = new Rect();
		initBitmaps(fish.getAnims(), fish.getCatchAnims());
		setNeedRecyle(true);
	}

	public Fish getFish() {
		return fish;
	}

	private void initBitmaps(int[] key1, int[] key2) {
		switch (fishType) {
		case 1:
			rate = 0.75f;
			break;
		case 2:
			rate = 0.75f;
			break;
		case 3:
			rate = 0.70f;
			break;
		case 4:
			rate = 0.60f;
			break;
		case 5:
			rate = 0.62f;
			break;
		case 6:
			rate = 0.60f;
			break;
		default:
			rate = 1;
			break;
		}
		fishBitmaps = new Bitmap[key1.length];
		catchBitmaps = new Bitmap[key2.length];
		if (null != key1 && key1.length > 0) {
			for (int i = 0; i < key1.length; i++) {
				fishBitmaps[i] = bitmapRes.getBitmap(key1[i]);
			}
		} else {
			Log.e("com.poxiao.fish", "key1 is null");
		}
		if (null != key2 && key2.length > 0) {
			for (int j = 0; j < key2.length; j++) {
				catchBitmaps[j] = bitmapRes.getBitmap(key2[j]);
			}
		} else {
			Log.e("com.poxiao.fish", "key2 is null");
		}
	}

	@Override
	public void onDrawSelf(Canvas canvas) {
		if (outOfScreen()) {
			return;
		}
		if (!isCapture) {
			if (null != fishBitmaps && fishBitmaps.length > 0) {
				Bitmap bitmap = MoveUtils.getInstance().rotateBitmap(
						fishBitmaps[index], rotateDegree);
				canvas.save();
				canvas.rotate((float) rotate, fishRect.centerX(),
						fishRect.centerY());
				canvas.drawBitmap(bitmap, null, fishRect, null);
				canvas.restore();
			} else {
				Log.e("com.poxiao.fish", "fishBitmaps is null");
			}
		} else {
			if (null != catchBitmaps && catchBitmaps.length > 0) {
				Bitmap bitmap = MoveUtils.getInstance().rotateBitmap(
						catchBitmaps[catchIndex], rotateDegree);
				canvas.save();
				canvas.rotate((float) rotate, fishRect.centerX(),
						fishRect.centerY());
				canvas.drawBitmap(bitmap, null, fishRect, null);
				canvas.restore();
			} else {
				Log.e("com.poxiao.fish", "catchBitmaps is null");
			}
		}
	}

	@Override
	protected void onUpdateSelf(float secondsElapsed) {
		deltTime += secondsElapsed;
		replaceTime += secondsElapsed;
		// 移动

		if (!isCapture && deltTime > 0.035f) {
			setDirection(secondsElapsed / 0.035);
			MoveSpeed physicsSpeed = MoveUtils.getInstance().getSpriteSpeed(
					speed, degree);
			fishRect.set(
					(float) (fishRect.left + physicsSpeed.speedx
							* (secondsElapsed / 0.035)
							* EngineOptions.getScreenScaleX()),
					(float) (fishRect.top + physicsSpeed.speedy
							* (secondsElapsed / 0.035)
							* EngineOptions.getScreenScaleY()),
					(float) (fishRect.right + physicsSpeed.speedx
							* (secondsElapsed / 0.035)
							* EngineOptions.getScreenScaleX()),
					(float) (fishRect.bottom + physicsSpeed.speedy
							* (secondsElapsed / 0.035)
							* EngineOptions.getScreenScaleY()));
			collosionRect.set((int) (fishRect.centerX() - width * rate / 2
					* EngineOptions.getScreenScaleX()),
					(int) (fishRect.centerY() - height * rate / 2
							* EngineOptions.getScreenScaleY()),
					(int) (fishRect.centerX() + width * rate / 2
							* EngineOptions.getScreenScaleX()),
					(int) (fishRect.centerY() + height * rate / 2
							* EngineOptions.getScreenScaleY()));
			deltTime = deltTime - 0.035f;
		}
		// 换肤
		if (replaceTime > animTiem[index]) {
			replaceTime -= animTiem[index];
			index++;
			if (index >= fishBitmaps.length) {
				index = 0;
			}
			
		}
		if (isCapture) {
			if (replaceTime > catchTime) {
				catchIndex++;
				if (catchIndex >= catchBitmaps.length) {
					catchIndex = 0;
				}
				replaceTime -= catchTime;
			}
		}
	}

	/**
	 * 角度偏转 ,为了延长鱼在屏幕里的停留时间,分区段转向
	 */
	private void setDirection(double rate) {
		double ratio = 0;
		switch (rotateDegree) {
		case BirthPosition.LEFTROTATE:
			if (birthPosition.point.y < EngineOptions.DEFAULT_SCREEN_HEIGHT * 2 / 5) {
				ratio = Math.random() + 0.15;
			} else if (birthPosition.point.y > EngineOptions.DEFAULT_SCREEN_HEIGHT * 3 / 5) {
				ratio = -(Math.random() + 0.15);
			} else {
				ratio = -0.1;
			}
			break;
		case BirthPosition.RIGHTROTATE:
			if (birthPosition.point.y < EngineOptions.DEFAULT_SCREEN_HEIGHT * 2 / 5) {
				ratio = -(Math.random() + 0.15);
			} else if (birthPosition.point.y > EngineOptions.DEFAULT_SCREEN_HEIGHT * 3 / 5) {
				ratio = (Math.random() + 0.15);
			} else {
				ratio = 0.1;
			}
			break;
		case BirthPosition.TOPROTATE:
			if (birthPosition.point.x < EngineOptions.DEFAULT_SCREEN_WIDTH / 2) {
				ratio = -speed * 0.3;
				lucky = 0.4f;
			} else {
				ratio = speed * 0.3;
				lucky = 0.4f;
			}
			break;
		}
		if (Math.random() > lucky) {
			degree = degree + ratio * rate;
			rotate = rotate + ratio * rate;
		}
	}

	@Override
	public void recycle() {
		if (!isVisible()) {
			Log.e("com.poxiao.fish", "recycle recycle recycle");
			for (int i = 0; i < fishBitmaps.length; i++) {
				GameBitmapUtil.recycleBitmap(fishBitmaps[i]);
			}
			for (int i = 0; i < catchBitmaps.length; i++) {
				GameBitmapUtil.recycleBitmap(catchBitmaps[i]);
			}
		}
	}

	/**
	 * 出界判定
	 * 
	 * @param sprite
	 */
	public boolean outOfScreen() {
		// Log.e("com.poxiao.fish", "fishRect.centerX()" + fishRect.left);
		// Log.e("com.poxiao.fish",
		// "bound right" + EngineOptions.getRealScreenWidth());
		if (fishRect.bottom < -height * EngineOptions.getScreenScaleY()
				|| fishRect.top > EngineOptions.getScreenHeight()
						- TurretSprite.HEIGHT / 2
						* EngineOptions.getScreenScaleY()
				|| fishRect.right < -width * EngineOptions.getScreenScaleX()
				|| fishRect.left > EngineOptions.getScreenWidth() + width
						* EngineOptions.getScreenScaleX()) {
			this.setVisible(false);
			setNeedRemove(true);
			return true;
		} else {
			return false;
		}

	}

	/**
	 * 是否捕获
	 * 
	 * @param capture
	 */
	public void setCapture(boolean capture) {
		isCapture = capture;
	}

	public boolean isCapture() {
		return isCapture;
	}

}
