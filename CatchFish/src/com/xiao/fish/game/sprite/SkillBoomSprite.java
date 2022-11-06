package com.xiao.fish.game.sprite;

import java.util.Map;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Rect;
import android.util.Log;
import android.view.MotionEvent;

import com.d.event.EventCallBack;
import com.d.event.EventResult;
import com.hifreshday.android.pge.engine.options.EngineOptions;
import com.hifreshday.android.pge.entity.shape.sprite.Sprite;
import com.hifreshday.android.pge.view.BitmapSpliter;
import com.hifreshday.android.pge.view.res.IBitmapRes;
import com.xiao.fish.FishCatchApplication;
import com.xiao.fish.PxGameConstants;
import com.xiao.fish.domain.PlayerInfo;
import com.xiao.fish.game.GameScene;
import com.xiao.fish.game.res.FishGameRes;

public class SkillBoomSprite extends Sprite {
	public static final int X = 720;
	public static final int Y = 30;
	public static final int WIDTH = 70;
	public static final int HEIGHT = 68;
	public static final int HINT_WIDTH = 127;
	public static final int HINT_HEIGHT = 153;
	private final int NUM_BG_WIDTH = 25;
	private final int NUM_BG_HEIGHT = 24;
	private final int NUM_WIDTH = 9;
	private final int NUM_HEIGHT = 12;
	private Rect numbg;
	private Rect numRect;
	private Rect hintRect;
	private int skillNum = 0;
	private Bitmap[] skillAimn;
	private int index;
	private float time;
	private boolean isShowHint = false;

	public SkillBoomSprite(IBitmapRes bitmapRes, int pX, int pY, int width,
			int height) {
		super(bitmapRes, pX, pY, width, height);
		setNeedRecyle(true);
		PlayerInfo info = PlayerInfo.getPlayerInfo();
		skillNum = info.getSkillNum();
		init();
	}

	private void init() {
		numbg = new Rect();
		numRect = new Rect();
		hintRect = new Rect();
		skillAimn = new Bitmap[5];
		for (int i = 0; i < skillAimn.length; i++) {
			skillAimn[i] = bitmapRes
					.getBitmap(FishGameRes.KEY_GAME_SKILL_ANIM_1 + i);
		}
	}

	@Override
	public void onUpdate(float secondsElapsed) {
		time += secondsElapsed;
		if (time > 0.2) {
			index = (++index) % 5;
			time -= 0.2;
		}
	}

	public void showSkillHint(boolean b) {
		if (PxGameConstants.playerLogin) {
			isShowHint = b;
			PxGameConstants.playerLogin = false;
		} else {
			isShowHint = false;
		}
	}

	@Override
	public void onDrawSelf(Canvas canvas) {
		Bitmap recharge = bitmapRes.getBitmap(FishGameRes.KEY_GAME_SKILL_BOOM);
		canvas.drawBitmap(recharge, null, getRect(), null);
		Bitmap num_bg = bitmapRes.getBitmap(FishGameRes.KEY_GAME_SKILL_NUM_BG);
		numbg.set(
				(int) (getRect().right - NUM_BG_WIDTH
						* EngineOptions.getScreenScaleX()),
				(int) (getRect().bottom - NUM_BG_HEIGHT
						* EngineOptions.getScreenScaleY()), getRect().right,
				getRect().bottom);
		canvas.drawBitmap(num_bg, null, numbg, null);
		Bitmap num = bitmapRes.getBitmap(FishGameRes.KEY_GAME_SKILL_NUM);
		int[] numArrayy = FishGameRes.getIntArray(skillNum);
		for (int i = 0; i < numArrayy.length; i++) {
			Rect numSrc = BitmapSpliter.splitBitmap2Rect(num, 10, numArrayy[i],
					BitmapSpliter.HORIZONTAL);
			numRect.set(
					(int) (numbg.centerX() + (i * NUM_WIDTH - NUM_WIDTH / 2)
							* EngineOptions.getScreenScaleX()),
					(int) (numbg.centerY() - NUM_HEIGHT / 2
							* EngineOptions.getScreenScaleY()),
					(int) (numbg.centerX() + (i * NUM_WIDTH + NUM_WIDTH / 2)
							* EngineOptions.getScreenScaleX()),
					(int) (numbg.centerY() + NUM_HEIGHT / 2
							* EngineOptions.getScreenScaleY()));
			canvas.drawBitmap(num, numSrc, numRect, null);
		}
		canvas.drawBitmap(skillAimn[index], null, getRect(), null);

		if (isShowHint) {
			Bitmap hint = bitmapRes.getBitmap(FishGameRes.KEY_GAME_SKILL_HINT);
			hintRect.set(
					(int) (getRect().left - 48 * EngineOptions
							.getScreenScaleX()),
					(int) (getRect().top - 3 * EngineOptions.getScreenScaleY()),
					(int) (getRect().left + (HINT_WIDTH - 48)
							* EngineOptions.getScreenScaleX()),
					(int) (getRect().top + (HINT_HEIGHT - 3)
							* EngineOptions.getScreenScaleY()));
			canvas.drawBitmap(hint, null, hintRect, null);
		}
	}

	long lastClick = 0;

	@Override
	public boolean onTouchEvent(MotionEvent event) {
		if (isVisible()) {
			if ((event.getAction() == MotionEvent.ACTION_DOWN || event
					.getAction() == MotionEvent.ACTION_MOVE)
					&& getRect().contains((int) event.getX(),
							(int) event.getY())) {
				return true;
			}
			if ((event.getAction() == MotionEvent.ACTION_UP)
					&& getRect().contains((int) event.getX(),
							(int) event.getY())) {
				showSkillHint(false);
				if (skillNum > 0) {
					if (!PxGameConstants.IS_IN_BOOM) {
						((GameScene) getParent()).playBoomAnim();
						--skillNum;
						PlayerInfo info = PlayerInfo.getPlayerInfo();
						info.setSkillNum(skillNum);
						PlayerInfo.setPlayerInfo(info);
					}
				} else {
					if (!PxGameConstants.IS_ON_PAY) {
						if (System.currentTimeMillis() - lastClick < 2200L) {
							return true;
						}
						lastClick = System.currentTimeMillis();
						doEvent11();
					}
				}
				Log.e("com.poxiao.fish", "return true");
				return true;
			}
		}
		return false;
	}
	
	public void setSkillNum(int skillNum) {
		this.skillNum = skillNum;
	}

	private void doEvent11() {
		PxGameConstants.IS_ON_PAY = true;
		FishCatchApplication.getInstance().doMyPayEvent(
				((GameScene) getParent()).getActivity(), "11",
				new EventCallBack() {
					@Override
					public void setEventResult(EventResult eventResult) {
						((GameScene) getParent()).getActivity().sendBroadcast(
								new Intent(PxGameConstants.MUSIC_ENABLED));
						if (eventResult.getPResult()) {
							PlayerInfo info = PlayerInfo.getPlayerInfo();
							for (Map.Entry<Integer, Integer> entry : eventResult
									.getReward().entrySet()) {
								if (entry.getKey() == 1) {
									PxGameConstants.IS_PLAY_GOLD_ANIM = true;
									PxGameConstants.playerGold += entry
											.getValue();
								} else if (entry.getKey() == 2) {
									skillNum += entry.getValue();
								}
							}
							info.setSkillNum(skillNum);
							int money = info.getPayMoney();
							info.setPayMoney(money + 10);
							PlayerInfo.setPlayerInfo(info);
							if (PxGameConstants.playerCannon > 9) {
								((GameScene) getParent()).getMaxCannonByLevel();
							}
							((GameScene) getParent()).drawCannon();
							((GameScene) getParent())
									.getActivity()
									.sendBroadcast(
											new Intent(
													PxGameConstants.MUSIC_ENABLED));
						}
						PxGameConstants.IS_ON_PAY = false;
					}
				});
	}
}
