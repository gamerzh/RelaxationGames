package com.xiao.fish.game.sprite;

import java.util.Map;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Rect;
import android.view.MotionEvent;

import com.d.event.EventCallBack;
import com.d.event.EventResult;
import com.hifreshday.android.pge.engine.options.EngineOptions;
import com.hifreshday.android.pge.entity.shape.sprite.Sprite;
import com.hifreshday.android.pge.view.res.IBitmapRes;
import com.tbu.androidtools.Debug;
import com.xiao.fish.FishCatchApplication;
import com.xiao.fish.PxGameConstants;
import com.xiao.fish.domain.PlayerInfo;
import com.xiao.fish.game.GameScene;
import com.xiao.fish.game.res.FishGameRes;

public class RechargeSprite extends Sprite {
	public static final int X = 10;
	public static final int Y = 410;
	public static final int WIDTH = 55;
	public static final int HEIGHT = 50;
	private Rect numRect;

	public RechargeSprite(IBitmapRes bitmapRes, int pX, int pY, int width,
			int height) {
		super(bitmapRes, pX, pY, width, height);
		setNeedRecyle(true);
		numRect = new Rect(
				(int) (getRect().right - 25 * EngineOptions.getScreenScaleX()),
				getRect().top, getRect().right,
				(int) (getRect().top + 24 * EngineOptions.getScreenScaleX()));
	}

	@Override
	public void onDrawSelf(Canvas canvas) {
		Bitmap recharge = bitmapRes.getBitmap(FishGameRes.KEY_GAME_RECHARGE);
		canvas.drawBitmap(recharge, null, getRect(), null);
		if (PxGameConstants.IS_SHOW_RECHARGE_NUM) {
			Bitmap num = bitmapRes.getBitmap(FishGameRes.KEY_GAME_RECHARGE_NUM);
			canvas.drawBitmap(num, null, numRect, null);
		}
	}

	@Override
	public boolean onTouchEvent(MotionEvent event) {
		if (isVisible()
				&& (event.getAction() == MotionEvent.ACTION_DOWN || event
						.getAction() == MotionEvent.ACTION_MOVE)
				&& getRect().contains((int) event.getX(), (int) event.getY())) {
			if (!PxGameConstants.IS_ON_PAY) {
				PxGameConstants.IS_SHOW_RECHARGE_NUM = false;
				eventDispatch();
			}
			return true;
		}
		return false;
	}

	private void eventDispatch() {
		if (PlayerInfo.getPlayerInfo().getProtectedPaySuccessTimes() == 0) {
			doEvent8();
		} else {
			doEvent9();
		}
	}

	private void doEvent8() {
		if (PxGameConstants.IS_ON_PAY) {
			return;
		}
		PxGameConstants.IS_ON_PAY = true;
		boolean result = FishCatchApplication.getInstance().doMyPayEvent(
				((GameScene) getParent()).getActivity(), "8",
				new EventCallBack() {

					@Override
					public void setEventResult(EventResult eventResult) {

						((GameScene) getParent()).getActivity().sendBroadcast(
								new Intent(PxGameConstants.MUSIC_ENABLED));
						PlayerInfo info = PlayerInfo.getPlayerInfo();
						if (eventResult.getPResult()) {
							// 成功完成包月
							if (eventResult.getHasBuy()) {
								// 已经是包月用户
							} else {
								PxGameConstants.IS_PLAY_GOLD_ANIM = true;
								PxGameConstants.playerGold += 1500;
								info.setGold(PxGameConstants.playerGold);

							}
							info.setHasBuyMonth(true);
						}
						// 保护计费点支付成功次数+1
						info.setProtectedPaySuccessTimes(info
								.getProtectedPaySuccessTimes() + 1);
						PlayerInfo.setPlayerInfo(info);
						PxGameConstants.IS_ON_PAY = false;
					}
				});
		Debug.e("RechargeSprite-> doPayEvent6,result = " + result);
		if (!result) {
			doEvent9();
		}
	}

	private void doEvent9() {
		if (PxGameConstants.IS_ON_PAY) {
			return;
		}
		PxGameConstants.IS_ON_PAY = true;
		FishCatchApplication.getInstance().doMyPayEvent(
				((GameScene) getParent()).getActivity(), "9",
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
									// TODO
								}
							}
							info.setGold(PxGameConstants.playerGold);
							PxGameConstants.playerCannon = info.getMaxCannon();
							if (PxGameConstants.playerCannon > 9) {
								((GameScene) getParent()).getMaxCannonByLevel();
							}
							int money = info.getPayMoney();
							info.setPayMoney(money + 10);
							PlayerInfo.setPlayerInfo(info);
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
