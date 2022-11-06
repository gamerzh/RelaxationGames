package com.xiao.fish.game.sprite;

import android.graphics.Canvas;

import com.hifreshday.android.pge.engine.options.EngineOptions;
import com.hifreshday.android.pge.entity.shape.sprite.Sprite;
import com.hifreshday.android.pge.view.res.IBitmapRes;
import com.xiao.fish.game.res.PaintManager;

public class TextMarqueeSprite extends Sprite {

	private static final int RECT_WIDTH = 320;
	private static final int RECT_HEIGHT = 40;
	private static final int INIT_X = 240;
	private static final int INIT_Y = 30;

	private static final int SPEED = 50;
	private int currentTextPosition = RECT_WIDTH;
	private float buffersecond = 0.0f;
	private String info;
	private float stringsize = 0.0f;
	private String temp = null;

	public TextMarqueeSprite(IBitmapRes bitmapRes, int pX, int pY, int width,
			int height) {
		super(bitmapRes, pX, pY, width, height);
		setVisible(false);
	}

	public void showInfo(String text) {
		if (!isVisible()) {
			info = text;
			stringsize = PaintManager.getInstance().getText24Yellow()
					.measureText(info);
			currentTextPosition = RECT_WIDTH;
			setVisible(true);
		} else {
			temp = text;
		}
	}

	@Override
	protected void onUpdateSelf(float secondsElapsed) {
		buffersecond += secondsElapsed;
		if ((buffersecond * SPEED) > 1) {
			int move = (int) (buffersecond * SPEED);
			currentTextPosition -= move;
			if (currentTextPosition + stringsize < 0) {
				currentTextPosition = RECT_WIDTH;
				setVisible(false);
				buffersecond = 0;
			}
			buffersecond = (buffersecond * SPEED - move) / SPEED;
		}
		if (null != temp && !isVisible()) {
			setVisible(true);
			info = temp;
			buffersecond += secondsElapsed;
			if ((buffersecond * SPEED) > 1) {
				int move = (int) (buffersecond * SPEED);
				currentTextPosition -= move;
				if (currentTextPosition + stringsize < 0) {
					currentTextPosition = RECT_WIDTH;
					setVisible(false);
					temp = null;
				}
				buffersecond = (buffersecond * SPEED - move) / SPEED;
			}
		}
	}

	@Override
	public void onDrawSelf(Canvas canvas) {
		canvas.save();
		canvas.translate(
				EngineOptions.getOffsetX() + INIT_X
						* EngineOptions.getScreenScaleX(),
				EngineOptions.getOffsetY() + INIT_Y
						* EngineOptions.getScreenScaleY());
		canvas.clipRect(0, 0, RECT_WIDTH * EngineOptions.getScreenScaleX(),
				RECT_HEIGHT * EngineOptions.getScreenScaleY());
		canvas.drawText(info,
				currentTextPosition * EngineOptions.getScreenScaleX(),
				20 * EngineOptions.getScreenScaleY(), PaintManager
						.getInstance().getText24Yellow());
		canvas.restore();
	}
}
