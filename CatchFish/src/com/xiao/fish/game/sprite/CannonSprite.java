package com.xiao.fish.game.sprite;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Point;
import android.graphics.Rect;

import com.hifreshday.android.pge.engine.options.EngineOptions;
import com.hifreshday.android.pge.entity.shape.sprite.Sprite;
import com.hifreshday.android.pge.view.res.IBitmapRes;
import com.xiao.fish.PxGameConstants;
import com.xiao.fish.constants.MoveUtils;
import com.xiao.fish.domain.PlayerInfo;
import com.xiao.fish.domain.cannon.Cannon;
import com.xiao.fish.domain.cannon.CannonManage;
import com.xiao.fish.game.GameScene;

public class CannonSprite extends Sprite {

	public static final int LASER_WIDTH = 63;
	public static final int LASER_HEIGHT = 130;
	public static int OFFSETY = 15;
	private float degree;
	private boolean isfire = false;
	private final float shockPath = 3;
	private float animpath = 0;
	private float path;
	private int type;
	private Bitmap cannonBitmap;
	private Bitmap headBitmap;
	private Rect cannonRect;
	private Rect headRect;
	private boolean isOut = false;
	private boolean isEnter = false;
	private int width;
	private int height;
	private int head_width;
	private int head_height;
	private int offset_head;
	private int png_offset = 0;

	public CannonSprite(IBitmapRes bitmapRes, int pX, int pY, int width,
			int height) {
		super(bitmapRes, pX, pY, width, height);
		setNeedRecyle(true);
		cannonRect = new Rect();
		headRect = new Rect();
		init(PxGameConstants.playerCannon);
	}

	private void init(int type) {
		Cannon cannon = CannonManage.getCannonByType(type);
		if (null != cannon) {
			this.type = type;
			this.width = cannon.getWidth();
			this.height = cannon.getHeight();
			this.head_width = cannon.getHead_width();
			this.head_height = cannon.getHead_height();
			cannonBitmap = bitmapRes.getBitmap(cannon.getBitmapID());
			if (type != 10) {
				headBitmap = bitmapRes.getBitmap(cannon.getHeadBimapID());
				if (type > 6) {
					offset_head = 70;
					OFFSETY = 15;
					png_offset = 0;
				} else {
					offset_head = height - 2;
					OFFSETY = 10;
					png_offset = 4;
				}
			}
		}
	}

	@Override
	public void onDrawSelf(Canvas canvas) {
		if (null != cannonBitmap) {
			if (PxGameConstants.playerCannon == 10) {
				canvas.save();
				// 以此为中心点旋转图片
				canvas.rotate(degree, cannonRect.centerX(),
						cannonRect.centerY() + OFFSETY);
				cannonRect
						.set((int) ((EngineOptions.getScreenWidth() - LASER_WIDTH
								* EngineOptions.getScreenScaleX()) / 2 + EngineOptions
								.getOffsetX()),
								(int) (EngineOptions.getScreenHeight() + (animpath
										- LASER_HEIGHT + 20)
										* EngineOptions.getScreenScaleY()),
								(int) ((EngineOptions.getScreenWidth() + LASER_WIDTH
										* EngineOptions.getScreenScaleX()) / 2 + EngineOptions
										.getOffsetX()), (int) (EngineOptions
										.getScreenHeight() + (animpath + 20)
										* EngineOptions.getScreenScaleY()));
				canvas.drawBitmap(cannonBitmap, null, cannonRect, null);
				canvas.restore();
			} else {
				canvas.save();
				// 以此为中心点旋转图片
				canvas.rotate(degree, cannonRect.centerX(),
						cannonRect.centerY() + OFFSETY);
				if (null != headBitmap) {
					headRect.set(
							(int) ((EngineOptions.getScreenWidth() - head_width
									* EngineOptions.getScreenScaleX()) / 2 + EngineOptions
									.getOffsetX()),
							(int) (EngineOptions.getScreenHeight() + (animpath
									+ png_offset - head_height - offset_head + path)
									* EngineOptions.getScreenScaleY()),
							(int) ((EngineOptions.getScreenWidth() + head_width
									* EngineOptions.getScreenScaleX()) / 2 + EngineOptions
									.getOffsetX()), (int) (EngineOptions
									.getScreenHeight() + (animpath + png_offset
									+ path - offset_head)
									* EngineOptions.getScreenScaleY()));
					canvas.drawBitmap(headBitmap, null, headRect, null);
				}
				cannonRect
						.set((int) ((EngineOptions.getScreenWidth() - width
								* EngineOptions.getScreenScaleX()) / 2 + EngineOptions
								.getOffsetX()),
								(int) (EngineOptions.getScreenHeight() + (animpath
										- height + png_offset)
										* EngineOptions.getScreenScaleY()),
								(int) ((EngineOptions.getScreenWidth() + width
										* EngineOptions.getScreenScaleX()) / 2 + EngineOptions
										.getOffsetX()),
								(int) (EngineOptions.getScreenHeight() + (animpath + png_offset)
										* EngineOptions.getScreenScaleY()));
				canvas.drawBitmap(cannonBitmap, null, cannonRect, null);
				canvas.restore();
			}
		}
	}

	private int anim_step = 0;
	private static final int STEP_ANIM_START = 0;
	private static final int STEP_ANIM_TWO = 1;
	private static final int STEP_ANIM_THREE = 2;
	private float time;
	private int cannonStep = 0;
	private static final int STEP_CANNON_START = 0;
	private static final int STEP_CANNON_TWO = 1;
	private static final int STEP_CANNON_THREE = 2;

	@Override
	protected void onUpdateSelf(float secondsElapsed) {
		if (isfire) {
			switch (anim_step) {
			case STEP_ANIM_START:
				if (type == 10) {
					((GameScene) getParent()).createBullet(datumpoint,
							bulletAP, bulletBp);
					anim_step = STEP_ANIM_TWO;
				} else {
					path += 8;
					if (path > shockPath * 2) {
						((GameScene) getParent()).createBullet(datumpoint,
								bulletAP, bulletBp);
						anim_step = STEP_ANIM_TWO;
					}
				}
				break;
			case STEP_ANIM_TWO:
				time += secondsElapsed;
				if (time > 0.1) {
					anim_step = STEP_ANIM_THREE;
				}
				break;
			case STEP_ANIM_THREE:
				clean();
				break;
			}
		}
		if (PxGameConstants.IS_CHANGE_CANNON) {
			if (isOut) {
				switch (cannonStep) {
				case STEP_CANNON_START:
					if (animpath < (height + head_height)
							* EngineOptions.getScreenScaleY()) {
						animpath += 6;
					} else {
						cannonStep = STEP_CANNON_TWO;
					}
					break;
				case STEP_CANNON_TWO:
					// 2.炮塔切换到激光炮塔
					PxGameConstants.playerCannon = 10;
					((GameScene) getParent()).drawCannon();
					if (animpath > 0) {
						animpath -= 6;
					} else {
						cannonStep = STEP_CANNON_THREE;
					}
					break;
				case STEP_CANNON_THREE:
					animpath = 0;
					cannonStep = 0;
					PxGameConstants.IS_CHANGE_CANNON = false;
					isOut = false;
					break;
				}
			}
			if (isEnter) {
				switch (cannonStep) {
				case STEP_CANNON_START:
					if (animpath < (height + head_height)
							* EngineOptions.getScreenScaleY()) {
						animpath += 6;
					} else {
						cannonStep = STEP_CANNON_TWO;
					}
					break;
				case STEP_CANNON_TWO:
					// 2.炮塔切换到普通炮塔
					PlayerInfo info = PlayerInfo.getPlayerInfo();
					PxGameConstants.playerCannon = info.getCurrentCannon();
					((GameScene) getParent()).drawCannon();
					if (animpath > 0) {
						animpath -= 6;
					} else {
						cannonStep = STEP_CANNON_THREE;
					}
					break;
				case STEP_CANNON_THREE:
					animpath = 0;
					cannonStep = 0;
					PxGameConstants.IS_CHANGE_CANNON = false;
					isEnter = false;
					break;
				}
			}
		}
	}

	private void clean() {
		isfire = false;
		time = 0;
		anim_step = 0;
		path = 0;
	}

	public void setRotation(Point tp) {
		Point sp = new Point(EngineOptions.getScreenWidth() / 2,
				EngineOptions.getScreenHeight());
		Point bp = new Point(EngineOptions.getRealScreenWidth(),
				EngineOptions.getRealScreenHeight());
		if (tp.x - EngineOptions.getScreenWidth() / 2 == 0) {
			degree = 0;
		} else {
			degree = 90 + MoveUtils.getInstance().getRotation(sp, bp, tp);
		}
	}

	public void setCannonBitmap(int type) {
		init(type);
	}

	public Point getBulletStartPoint() {
		int x = cannonRect.centerX();
		int y = cannonRect.centerY() + OFFSETY;
		return new Point(x, y);
	}

	private Point datumpoint;
	private Point bulletAP;
	private Point bulletBp;

	public void playAnim(Point datumpoint, Point ap, Point bp) {
		isfire = true;
		this.datumpoint = datumpoint;
		this.bulletAP = ap;
		this.bulletBp = bp;
	}

	/**
	 * 炮塔出场动画
	 */
	public void playOutAnim() {
		degree = 0;
		isOut = true;
		PxGameConstants.IS_CHANGE_CANNON = true;
	}

	/**
	 * 炮塔进场动画
	 */
	public void playEnterAnim() {
		degree = 0;
		isEnter = true;
		PxGameConstants.IS_CHANGE_CANNON = true;
	}
}
