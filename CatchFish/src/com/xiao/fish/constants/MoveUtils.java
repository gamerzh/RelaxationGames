package com.xiao.fish.constants;


import android.graphics.Bitmap;
import android.graphics.Matrix;
import android.graphics.Point;

public class MoveUtils {
	private static MoveUtils instance;

	private MoveUtils() {

	}

	public static MoveUtils getInstance() {
		if (null != instance) {
			return instance;
		} else {
			return new MoveUtils();
		}
	}

	/**
	 * 拆解速度
	 * 
	 * @param speed速度
	 * @param ratation速度和坐标系的夹角
	 * @return
	 */
	public MoveSpeed getSpriteSpeed(int speed, double ratation) {
		double radians = ratation * Math.PI / 180;
		double speedx = speed * Math.cos(radians);
		double speedy = speed * Math.sin(radians);
		MoveSpeed physicsSpeed = new MoveSpeed(speedx, speedy);
		return physicsSpeed;
	}

	/**
	 * 获取角度
	 * 
	 * @param datumpoint基准点
	 * @param ap向量a的终点
	 * @param bp向量b的终点
	 * @return
	 */
	public int getRotation(Point datumpoint, Point ap, Point bp) {

		// Log.i("com.poxiao.fish", "tpoint.x=" + datumpoint.x + ";tpoint.y"
		// + datumpoint.y);
		// Log.i("com.poxiao.fish", "sp.x=" + ap.x + ";sp.y" + ap.y);
		// Log.i("com.poxiao.fish", "bp.x=" + bp.x + ";bp.y" + bp.y);
		int angle = 0; // 夹角
		// 向量Vector a的(x, y)坐标
		double va_x = ap.x - datumpoint.x;
		double va_y = ap.y - datumpoint.y;

		// 向量b的(x, y)坐标
		double vb_x = bp.x - datumpoint.x;
		double vb_y = bp.y - datumpoint.y;

		double productValue = (va_x * vb_x) + (va_y * vb_y); // 向量的乘积
		double va_val = Math.sqrt(va_x * va_x + va_y * va_y); // 向量a的模
		double vb_val = Math.sqrt(vb_x * vb_x + vb_y * vb_y); // 向量b的模
		double cosValue = productValue / (va_val * vb_val); // 余弦公式
		// Log.i("com.poxiao.fish", "cosValue=" + cosValue);
		// Log.i("com.poxiao.fish", "degree=" + Math.acos(cosValue) * 180
		// / Math.PI);
		// Log.i("com.poxiao.fish", "ScaleX=" + EngineOptions.getOffsetX());
		// acos的输入参数范围必须在[-1, 1]之间
		// 对输入参数作校验和处理
		if (cosValue < -1 && cosValue > -2)
			cosValue = -1;
		else if (cosValue > 1 && cosValue < 2)
			cosValue = 1;
		// acos返回的是弧度值，转换为角度值
		angle = -(int) (Math.acos(cosValue) * 180 / Math.PI);
		return angle;
	}

	public Bitmap rotateBitmap(Bitmap original,float degree) {
		Matrix matrix = new Matrix();
		matrix.preRotate(degree, original.getWidth() / 2, original.getHeight() / 2);
		Bitmap result = Bitmap.createBitmap(original, 0, 0,
				original.getWidth(), original.getHeight(), matrix, true);
		return result;
	}
}
