package com.xiao.fish.game.sprite;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Rect;
import android.view.MotionEvent;

import com.b.a.AppApplication;
import com.hifreshday.android.pge.engine.options.EngineOptions;
import com.hifreshday.android.pge.entity.shape.sprite.Sprite;
import com.hifreshday.android.pge.view.res.IBitmapRes;
import com.hifreshday.android.setting.MusicRemote;
import com.xiao.fish.PxGameConstants;
import com.xiao.fish.domain.PlayerInfo;
import com.xiao.fish.game.GameScene;
import com.xiao.fish.game.res.FishGameRes;
import com.xiao.fish.game.res.PaintManager;
import com.xiao.fish.game.res.SoundRes;

public class SetViewSprite extends Sprite {
	private static final int WIDTH = 60;
	private static final int HEIGHT = 62;
	private final static int BTN_NUMBER = 4;
	private static final int BTN_OFFSET_Y = 100;
	private static final int BTN_SPLIT_Y = 20;
	private Rect[] btnRects;
	private boolean ispressed;
	public boolean showMoreGame = false;

	public SetViewSprite(IBitmapRes bitmapRes, int pX, int pY, int width,
			int height) {
		super(bitmapRes, pX, pY, width, height);
		setVisible(false);
		setNeedRecyle(true);
		initRect();

	}

	private void initRect() {
		btnRects = new Rect[BTN_NUMBER];
		for (int i = 0; i < BTN_NUMBER; i++) {
			btnRects[i] = new Rect(
					(int) ((EngineOptions.getScreenWidth() - (WIDTH + 20)
							* EngineOptions.getScreenScaleX())),
					(int) ((BTN_OFFSET_Y + i * HEIGHT + i * BTN_SPLIT_Y) * EngineOptions
							.getScreenScaleY()), (int) (EngineOptions
							.getScreenWidth() - 20 * EngineOptions
							.getScreenScaleX()), (int) ((BTN_OFFSET_Y + (i + 1)
							* (HEIGHT) + i * BTN_SPLIT_Y) * EngineOptions
							.getScreenScaleY()));
		}

	}

	@Override
	public void onDrawSelf(Canvas canvas) {
		canvas.drawRect(new Rect((int) (650 * EngineOptions.getScreenScaleX()),
				0, (int) (1000 * EngineOptions.getScreenScaleX()),
				EngineOptions.getScreenHeight()), PaintManager.getInstance()
				.getDialogBgPaint());
		if (ispressed) {
			Bitmap bg = bitmapRes
					.getBitmap(FishGameRes.KEY_GAME_BTN_BG_PRESSED);
			canvas.drawBitmap(bg, null, btnRects[1], null);
		} else {
			Bitmap bg = bitmapRes.getBitmap(FishGameRes.KEY_GAME_BTN_BG_NORMAL);
			canvas.drawBitmap(bg, null, btnRects[1], null);
		}
		if (PxGameConstants.playerMusic) {
			Bitmap music = bitmapRes.getBitmap(FishGameRes.KEY_GAME_MUSIC_ON);
			canvas.drawBitmap(music, null, btnRects[1], null);
		} else {
			Bitmap music = bitmapRes.getBitmap(FishGameRes.KEY_GAME_MUSIC_OFF);
			canvas.drawBitmap(music, null, btnRects[1], null);
		}
		if (ispressed) {
			Bitmap bg = bitmapRes
					.getBitmap(FishGameRes.KEY_GAME_BTN_BG_PRESSED);
			canvas.drawBitmap(bg, null, btnRects[0], null);
		} else {
			Bitmap bg = bitmapRes.getBitmap(FishGameRes.KEY_GAME_BTN_BG_NORMAL);
			canvas.drawBitmap(bg, null, btnRects[0], null);
		}
		if (PxGameConstants.playerBgm) {
			Bitmap music = bitmapRes.getBitmap(FishGameRes.KEY_GAME_BGM_ON);
			canvas.drawBitmap(music, null, btnRects[0], null);
		} else {
			Bitmap music = bitmapRes.getBitmap(FishGameRes.KEY_GAME_BGM_OFF);
			canvas.drawBitmap(music, null, btnRects[0], null);
		}
		// if (ispressed) {
		// Bitmap bg = bitmapRes
		// .getBitmap(FishGameRes.KEY_GAME_BTN_BG_PRESSED);
		// canvas.drawBitmap(bg, null, btnRects[2], null);
		// } else {
		// Bitmap bg = bitmapRes.getBitmap(FishGameRes.KEY_GAME_BTN_BG_NORMAL);
		// canvas.drawBitmap(bg, null, btnRects[2], null);
		// }
		// Bitmap option = bitmapRes.getBitmap(FishGameRes.KEY_GAME_OPTION);
		// canvas.drawBitmap(option, null, btnRects[2], null);
		// 强制关掉更多游戏按钮
		// showMoreGame = false;
		if (showMoreGame) {
			if (ispressed) {
				Bitmap bg = bitmapRes
						.getBitmap(FishGameRes.KEY_GAME_BTN_BG_PRESSED);
				canvas.drawBitmap(bg, null, btnRects[2], null);
			} else {
				Bitmap bg = bitmapRes
						.getBitmap(FishGameRes.KEY_GAME_BTN_BG_NORMAL);
				canvas.drawBitmap(bg, null, btnRects[2], null);
			}
			Bitmap continuebtn = bitmapRes
					.getBitmap(FishGameRes.KEY_GAME_MORE_GAME);
			canvas.drawBitmap(continuebtn, null, btnRects[2], null);
		}
	}

	@Override
	public boolean onTouchEvent(MotionEvent event) {
		if (isVisible()) {
			if (event.getAction() == MotionEvent.ACTION_DOWN
					&& EngineOptions.getFullScreenRect().contains(
							(int) event.getX(), (int) event.getY())) {
				if (btnRects[0]
						.contains((int) event.getX(), (int) event.getY())) {
					SoundRes.playSound(SoundRes.gameclick);
					ispressed = true;
					PxGameConstants.playerBgm = !PxGameConstants.playerBgm;
					MusicRemote
							.getInstance()
							.getSetting()
							.setOtherProperties(
									PxGameConstants.BACKGROUND_MUSIC_SETTING_KEY,
									PxGameConstants.playerBgm);
					if (PxGameConstants.playerBgm) {
						((GameScene) getParent()).getActivity().sendBroadcast(
								new Intent(PxGameConstants.MUSIC_ENABLED));
					} else {
						((GameScene) getParent()).getActivity().sendBroadcast(
								new Intent(PxGameConstants.MUSIC_DISABLED));
					}
					PlayerInfo myinfo = PlayerInfo.getPlayerInfo();
					myinfo.setBgmState(PxGameConstants.playerBgm);
					PlayerInfo.setPlayerInfo(myinfo);

				} else if (btnRects[1].contains((int) event.getX(),
						(int) event.getY())) {
					SoundRes.playSound(SoundRes.gameclick);
					ispressed = true;
					PxGameConstants.playerMusic = !PxGameConstants.playerMusic;
					PlayerInfo myinfo = PlayerInfo.getPlayerInfo();
					myinfo.setMusicOpen(PxGameConstants.playerMusic);
					PlayerInfo.setPlayerInfo(myinfo);
				}
				// else if (btnRects[2].contains((int) event.getX(),
				// (int) event.getY())) {
				// // ispressed = true;
				// // SoundRes.playSound(SoundRes.gameclick);
				// ispressed = true;
				// SoundRes.playSound(SoundRes.gameclick);
				// AppApplication.showMoreGame(((GameScene) getParent())
				// .getActivity());
				// }
				else if (btnRects[2].contains((int) event.getX(),
						(int) event.getY())
						&& showMoreGame) {
					ispressed = true;
					SoundRes.playSound(SoundRes.gameclick);
					AppApplication.showMoreGame(((GameScene) getParent())
							.getActivity());
				} else {
					PxGameConstants.IS_SHOW_SETTING = false;
				}
			}
			ispressed = false;
			return true;
		}
		ispressed = false;
		return false;
	}
}
