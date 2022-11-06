package com.xiao.fish.game.sprite;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Point;
import android.graphics.Rect;
import android.graphics.RectF;

import com.hifreshday.android.pge.engine.options.EngineOptions;
import com.hifreshday.android.pge.entity.shape.sprite.Sprite;
import com.hifreshday.android.pge.view.res.GameBitmapUtil;
import com.hifreshday.android.pge.view.res.IBitmapRes;
import com.xiao.fish.constants.MoveSpeed;
import com.xiao.fish.constants.MoveUtils;
import com.xiao.fish.domain.bullet.Bullet;
import com.xiao.fish.game.GameScene;
import com.xiao.fish.game.res.FishGameRes;

public class BulletSprite extends Sprite {
	public RectF bulletRect;
	public Rect bulletCollision;
	private int degree;
	private int width;
	private int height;
	private Bitmap bulletBitmap;
	public int bulletType;
	private Point point;
	private int bulletSpeed;
	private float path;
	private Point touchPoint = null;
	public boolean isCollsion = false;
	private Bitmap[] lasers;
	private int index = 0;
	private float showtime;
	private float rate;

	public BulletSprite(IBitmapRes bitmapRes, int pX, int pY, int width,
			int height, Bullet bullet, Point point) {
		super(bitmapRes, pX, pY, width, height);
		this.bulletRect = new RectF(getRect().left, getRect().top,
				getRect().right, getRect().bottom);
		this.degree = bullet.getRotatetion();
		this.width = bullet.getWidth();
		this.height = bullet.getHeight();
		this.bulletSpeed = bullet.getBulletSpeed();
		this.bulletType = bullet.getBulletType();
		this.point = point;
		this.bulletBitmap = bitmapRes.getBitmap(bullet.getBulletBitmap());
		this.isCollsion = false;
		initView();
		setVisible(true);
		setNeedRecyle(true);
	}

	public void setTouchPoint(Point touchPoint) {
		this.touchPoint = touchPoint;
	}

	private void initView() {
		switch (bulletType) {
		case 1:
			rate = 0.5f;
			break;
		case 2:
			rate = 0.55f;
			break;
		case 3:
			rate = 0.60f;
			break;
		case 4:
			rate = 0.65f;
			break;
		case 5:
			rate = 0.70f;
			break;
		case 6:
			rate = 0.80f;
			break;
		case 7:
			rate = 0.80f;
			break;
		case 8:
			rate = 0.80f;
			break;
		case 9:
			rate = 0.80f;
			break;
		default:
			rate = 1.0f;
			break;
		}
		bulletCollision = new Rect();
		bulletRect = new RectF(point.x - width / 2
				* EngineOptions.getScreenScaleX(), point.y - height / 2
				* EngineOptions.getScreenScaleY(), point.x + width / 2
				* EngineOptions.getScreenScaleX(), point.y + height / 2
				* EngineOptions.getScreenScaleY());
		if (bulletType == 10) {
			lasers = new Bitmap[6];
			for (int i = 0; i < 6; i++) {
				lasers[i] = bitmapRes.getBitmap(FishGameRes.KEY_GAME_LASER_1
						+ i);
			}
			MoveSpeed speed = MoveUtils.getInstance().getSpriteSpeed(350,
					degree);
			bulletRect.set(
					(float) (bulletRect.left + speed.speedx
							* EngineOptions.getScreenScaleX()),
					(float) (bulletRect.top + speed.speedy
							* EngineOptions.getScreenScaleY()),
					(float) (bulletRect.right + speed.speedx
							* EngineOptions.getScreenScaleX()),
					(float) (bulletRect.bottom + speed.speedy
							* EngineOptions.getScreenScaleY()));
		}

	}

	@Override
	public void onDrawSelf(Canvas canvas) {
		if (bulletType != 10) {
			canvas.save();
			canvas.rotate(degree + 90, bulletRect.centerX(),
					bulletRect.centerY());
			canvas.drawBitmap(bulletBitmap, null, bulletRect, null);
			canvas.restore();
		} else {
			canvas.save();
			canvas.rotate(degree + 90, bulletRect.centerX(),
					bulletRect.centerY());
			canvas.drawBitmap(lasers[index], null, bulletRect, null);
			canvas.restore();
		}
	}

	@Override
	protected void onUpdateSelf(float secondsElapsed) {
		// Log.e("com.poxiao.fish", "secondsElapsed" + secondsElapsed);
		if (bulletType != 10) {
			path += bulletSpeed;
			MoveSpeed speed = MoveUtils.getInstance().getSpriteSpeed(
					bulletSpeed, degree);
			bulletRect.set(
					(float) (bulletRect.left + speed.speedx
							* (secondsElapsed / 0.035)
							* EngineOptions.getScreenScaleX()),
					(float) (bulletRect.top + speed.speedy
							* (secondsElapsed / 0.035)
							* EngineOptions.getScreenScaleY()),
					(float) (bulletRect.right + speed.speedx
							* (secondsElapsed / 0.035)
							* EngineOptions.getScreenScaleX()),
					(float) (bulletRect.bottom + speed.speedy
							* (secondsElapsed / 0.035)
							* EngineOptions.getScreenScaleY()));
			bulletCollision.set((int) (bulletRect.centerX() - width * rate / 2
					* EngineOptions.getScreenScaleX()),
					(int) (bulletRect.centerY() - height * rate / 2
							* EngineOptions.getScreenScaleY()),
					(int) (bulletRect.centerX() + width * rate / 2
							* EngineOptions.getScreenScaleX()),
					(int) (bulletRect.centerY() + height * rate / 2
							* EngineOptions.getScreenScaleY()));
			// 在子弹飞行一段时间后现形
			if (path > 40* EngineOptions.getScreenScaleY()) {
				this.isCollsion = true;
			}
		} else {

			if (isVisible()) {
				bulletCollision.set((int) (bulletRect.centerX() - width * rate
						/ 2 * EngineOptions.getScreenScaleX()),
						(int) (bulletRect.centerY() - height * rate / 2
								* EngineOptions.getScreenScaleY()),
						(int) (bulletRect.centerX() + width * rate / 2
								* EngineOptions.getScreenScaleX()),
						(int) (bulletRect.centerY() + height * rate / 2
								* EngineOptions.getScreenScaleY()));
				this.isCollsion = true;
				index = (index + 1) % 6;
				showtime += secondsElapsed;
				if (showtime > 3) {
					setVisible(false);
					((GameScene) ((BulletHoder) getParent()).getParent())
							.playCannonEnterAnim();
				}
			}
		}
	}

	// 碰撞模式二:到达指定点爆开
	public boolean checkRechTouchPoint() {
		if (null != touchPoint) {
			if (bulletRect.top < touchPoint.y) {
				setVisible(false);
				return true;
			}
		}
		return false;
	}

	public boolean outOfScreeen() {
		if (bulletRect.centerY() < -width * EngineOptions.getScreenScaleX()
				|| bulletRect.centerX() < -width
						* EngineOptions.getScreenScaleX()
				|| bulletRect.centerX() > EngineOptions.getScreenWidth()
						+ width * EngineOptions.getScreenScaleX()) {
			setVisible(false);
			setNeedRemove(true);
			return true;
		}
		return false;
	}

	@Override
	public void recycle() {
		super.recycle();
		GameBitmapUtil.recycleBitmap(bulletBitmap);
	}
}
