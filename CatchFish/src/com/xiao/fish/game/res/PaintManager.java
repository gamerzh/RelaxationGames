package com.xiao.fish.game.res;

import android.graphics.Color;
import android.graphics.Paint;

import com.hifreshday.android.pge.engine.options.EngineOptions;

public class PaintManager {

	private static PaintManager instance;

	private Paint text16White;
	private Paint text16Red;
	private Paint text16Yellow;
	private Paint text16DkGray;
	private Paint text16GrayishPurple;
	private Paint text18White;

	private Paint text24Yellow;
	private Paint text30Yellow;
	private Paint text30White;
	private Paint text30Black;
	private Paint dialogBgPaint;

	public static PaintManager getInstance() {
		return instance;
	}

	public static void initPaintManager() {
		instance = new PaintManager();
	}

	private PaintManager() {
		initPaint();
	}

	private void initPaint() {
		float scale = EngineOptions.getScreenScaleX() > EngineOptions
				.getScreenScaleY() ? EngineOptions.getScreenScaleY()
				: EngineOptions.getScreenScaleX(); // 选择较小的缩放比例

		text16White = new Paint();
		text16White.setColor(Color.WHITE);
		text16White.setStyle(Paint.Style.FILL);
		text16White.setAntiAlias(true);
		text16White.setTextSize(16 * scale);

		text16Red = new Paint();
		text16Red.setColor(Color.RED);
		text16Red.setStyle(Paint.Style.FILL);
		text16Red.setAntiAlias(true);
		text16Red.setTextSize(16 * scale);

		text16Yellow = new Paint();
		text16Yellow.setColor(Color.YELLOW);
		text16Yellow.setStyle(Paint.Style.FILL);
		text16Yellow.setAntiAlias(true);
		text16Yellow.setTextSize(16 * scale);

		text16DkGray = new Paint();
		text16DkGray.setColor(Color.DKGRAY);
		text16DkGray.setStyle(Paint.Style.FILL);
		text16DkGray.setAntiAlias(true);
		text16DkGray.setTextSize(16 * scale);

		text16GrayishPurple = new Paint();
		text16GrayishPurple.setARGB(255, 0xA8, 0x90, 0xB4);
		text16GrayishPurple.setStyle(Paint.Style.FILL);
		text16GrayishPurple.setAntiAlias(true);
		text16GrayishPurple.setTextSize(16 * scale);

		text18White = new Paint();
		text18White.setColor(Color.WHITE);
		text18White.setStyle(Paint.Style.FILL);
		text18White.setAntiAlias(true);
		text18White.setTextSize(18 * scale);

		text24Yellow = new Paint();
		text24Yellow.setColor(Color.YELLOW);
		text24Yellow.setStyle(Paint.Style.FILL);
		text24Yellow.setAntiAlias(true);
		text24Yellow.setTextSize(24 * scale);

		text30White = new Paint();
		text30White.setColor(Color.WHITE);
		text30White.setStyle(Paint.Style.FILL);
		text30White.setAntiAlias(true);
		text30White.setTextSize(30 * scale);

		text30Yellow = new Paint();
		text30Yellow.setColor(Color.YELLOW);
		text30Yellow.setStyle(Paint.Style.FILL);
		text30Yellow.setAntiAlias(true);
		text30Yellow.setTextSize(30 * scale);

		text30Black = new Paint();
		text30Black.setColor(Color.BLACK);
		text30Black.setStyle(Paint.Style.FILL);
		text30Black.setAntiAlias(true);
		text30Black.setTextSize(30 * scale);

		dialogBgPaint = new Paint();
		dialogBgPaint.setARGB(225, 0, 0, 0);
		dialogBgPaint.setStyle(Paint.Style.FILL);
		dialogBgPaint.setAntiAlias(true);
	}

	public Paint getText16Yellow() {
		return text16Yellow;
	}

	public Paint getText16DkGray() {
		return text16DkGray;
	}

	public Paint getText16GrayishPurple() {
		return text16GrayishPurple;
	}

	public Paint getText16White() {
		return text16White;
	}

	public Paint getText16Red() {
		return text16Red;
	}

	public Paint getText30Yellow() {
		return text30Yellow;
	}

	public Paint getText24Yellow() {
		return text24Yellow;
	}

	public Paint getText30White() {
		return text30White;
	}

	public Paint getText18White() {
		return text18White;
	}

	public Paint getText30Black() {
		return text30Black;
	}

	public Paint getDialogBgPaint() {
		return dialogBgPaint;
	}

}
