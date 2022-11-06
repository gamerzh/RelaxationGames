package com.xiao.fish.constants;

import android.graphics.Point;
import android.util.Log;

import com.hifreshday.android.pge.engine.options.EngineOptions;

public class BirthPosition {

	public static final int LEFT = 0;
	public static final int RIGHT = 1;
	public static final int TOP = 2;
	public static final int BOTTOM = 3;
	// 速度初始方向
	public static final int LEFTDEGREE = 0;
	public static final int RIGHTDEGREE = 180;
	public static final int TOPDEGREE = 90;
	public static final int BOTTOMDEGREE = 270;

	// 图片初始转角
	public static final int LEFTROTATE = 180;
	public static final int RIGHTROTATE = 0;
	public static final int TOPROTATE = 270;
	public static final int BOTTOMROTATE = 90;

	public Point point;
	public int degree;// 速度角度
	public int rotateDegree;// 初始图片旋转角度

	public BirthPosition(Point point, int degree, int rotateDegree) {
		super();
		this.point = point;
		this.degree = degree;
		this.rotateDegree = rotateDegree;
	}

	/**
	 * 获取鱼的出生点
	 * 
	 * @param fishWidth鱼的宽度
	 * @return
	 */
	public static BirthPosition getBirthPoint(int fishWidth,int positionType) {
		// Log.i("com.poxiao.fish", "Width=" + EngineOptions.getScreenWidth()
		// + ";Height=" + EngineOptions.getScreenHeight());
		switch (positionType) {
		case BirthPosition.LEFT:
			int lx = -fishWidth - EngineOptions.getOffsetX();
			int ly = (int) (Math.random() * EngineOptions.DEFAULT_SCREEN_HEIGHT
					* 0.7 + EngineOptions.DEFAULT_SCREEN_HEIGHT * 0.1);
			// Log.i("com.poxiao.fish", "lx=" + lx + ";ly=" + ly);
			Point p0 = new Point(lx, ly);
			BirthPosition birthPosition0 = new BirthPosition(p0,
					BirthPosition.LEFTDEGREE, BirthPosition.LEFTROTATE);
			return birthPosition0;
		case BirthPosition.RIGHT:
			int rx = (int) (fishWidth + EngineOptions.DEFAULT_SCREEN_WIDTH)
					- EngineOptions.getOffsetX();
			int ry = (int) (Math.random() * EngineOptions.DEFAULT_SCREEN_HEIGHT
					* 0.7 + EngineOptions.DEFAULT_SCREEN_HEIGHT * 0.1);
			// Log.i("com.poxiao.fish", "rx=" + rx + ";rx=" + rx);
			Point p2 = new Point(rx, ry);
			BirthPosition birthPosition2 = new BirthPosition(p2,
					BirthPosition.RIGHTDEGREE, BirthPosition.RIGHTROTATE);
			return birthPosition2;
		case BirthPosition.TOP:
			int tx = (int) (Math.random() * EngineOptions.DEFAULT_SCREEN_WIDTH);
			int ty = -fishWidth - EngineOptions.getOffsetY();
			Point p3 = new Point(tx, ty);
			BirthPosition birthPosition3 = new BirthPosition(p3,
					BirthPosition.TOPDEGREE, BirthPosition.TOPROTATE);
			return birthPosition3;
		case BirthPosition.BOTTOM:
			int tx2 = (int) (Math.random() * EngineOptions.DEFAULT_SCREEN_WIDTH);
			int ty2 = -fishWidth - EngineOptions.getOffsetY();
			Point p32 = new Point(tx2, ty2);
			BirthPosition birthPosition32 = new BirthPosition(p32,
					BirthPosition.TOPDEGREE, BirthPosition.TOPROTATE);
			return birthPosition32;
			// int bx = (int) (Math.random() *
			// EngineOptions.DEFAULT_SCREEN_WIDTH);
			// int by = (int) (EngineOptions.DEFAULT_SCREEN_HEIGHT -
			// TurretSprite.HEIGHT);
			// Point p4 = new Point(bx, by);
			// BirthPosition birthPosition4 = new BirthPosition(p4,
			// BirthPosition.BOTTOMDEGREE, BirthPosition.BOTTOMROTATE);
			// return birthPosition4;
		default:
			Log.e("com.poxiao.fish", "positionType is error " + positionType);
			return null;
		}
	}
}
