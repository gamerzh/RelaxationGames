package com.xiao.fish.game.sprite;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Rect;
import android.view.MotionEvent;

import com.hifreshday.android.pge.entity.shape.sprite.Sprite;
import com.hifreshday.android.pge.view.res.IBitmapRes;
import com.xiao.fish.PxGameConstants;
import com.xiao.fish.domain.PlayerInfo;
import com.xiao.fish.domain.bullet.BulletManger;
import com.xiao.fish.game.GameScene;
import com.xiao.fish.game.res.FishGameRes;
import com.xiao.fish.game.res.SoundRes;

public class CannonUpSprite extends Sprite {

	public static final int X = 460;
	public static final int Y = 432;
	public static final int WIDTH = 71;
	public static final int HEIGHT = 49;

	private Bitmap normalBitmap;
	private Bitmap pressedBitmap;
	private boolean pressed = false;
	private Rect upRect;

	public CannonUpSprite(IBitmapRes bitmapRes, int pX, int pY, int width,
			int height) {
		super(bitmapRes, pX, pY, width, height);
		setNeedRecyle(true);
		normalBitmap = bitmapRes
				.getBitmap(FishGameRes.KEY_GAME_CANNON_UP_NORMAL);
		pressedBitmap = bitmapRes
				.getBitmap(FishGameRes.KEY_GAME_CANNON_UP_PRESSED);
		upRect = new Rect(getRect().left, getRect().top, getRect().right,
				getRect().bottom);
	}

	@Override
	public void onDrawSelf(Canvas canvas) {
		if (pressed) {
			canvas.drawBitmap(pressedBitmap, null, upRect, null);
		} else {
			canvas.drawBitmap(normalBitmap, null, upRect, null);
		}
	}

	@Override
	public boolean onTouchEvent(MotionEvent event) {
		if ((event.getAction() == MotionEvent.ACTION_DOWN && getRect()
				.contains((int) event.getX(), (int) event.getY()))) {
			pressed = true;
			SoundRes.playSound(SoundRes.gameclick);
			// 根据用户等级重新设定一次当前游戏允许的最大炮塔编号
			((GameScene) getParent()).getMaxCannonByLevel();
			if (PxGameConstants.playerCannon >= PxGameConstants.playerMaxCannon) {
				PxGameConstants.playerCannon = 1;
				// info.setCurrentCannon(temp);
			} else {
				if (PxGameConstants.playerGold < BulletManger.getBulletByType(
						PxGameConstants.playerCannon + 1).getGoldConsume()) {
					PxGameConstants.playerCannon = 1;
				} else {
					PxGameConstants.playerCannon += 1;
				}
			}
			PlayerInfo info = PlayerInfo.getPlayerInfo();
			info.setCurrentCannon(PxGameConstants.playerCannon);
			PlayerInfo.setPlayerInfo(info);
			((GameScene) getParent()).drawCannon();
			return true;
		} else {
			pressed = false;
		}
		return false;
	}
}
