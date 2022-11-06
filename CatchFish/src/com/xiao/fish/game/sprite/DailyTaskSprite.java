package com.xiao.fish.game.sprite;

import java.util.Map;

import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Rect;
import android.util.Log;
import android.view.MotionEvent;

import com.b.a.AppApplication;
import com.d.event.EventCallBack;
import com.d.event.EventResult;
import com.hifreshday.android.pge.entity.shape.sprite.Sprite;
import com.hifreshday.android.pge.view.res.IBitmapRes;
import com.xiao.fish.PxGameConstants;
import com.xiao.fish.domain.PlayerInfo;
import com.xiao.fish.game.GameScene;
import com.xiao.fish.game.res.FishGameRes;

public class DailyTaskSprite extends Sprite{
	
	public static final int X = 0;
	public static final int Y = 200;

	public Rect confirmBtnRect = new Rect();
	
	public int  handX = 0;
	public int handY = 0;
	public Rect handRect = new Rect();
	public int handDirection = 3;
	long lastClick = 0;
	
	private int handMarginTopOrBottom = 10;
	
	public DailyTaskSprite(IBitmapRes bitmapRes) {
		super(bitmapRes, X, Y, 124, 193);
		Bitmap confirmBtn = bitmapRes.getBitmap(FishGameRes.KEY_DAILY_TASK_CONFIRM);
		int x = getRect().centerX() - confirmBtn.getWidth()/2;
		int y = getRect().bottom - 60 - confirmBtn.getHeight();
		
		confirmBtnRect.set(x, y, x+confirmBtn.getWidth(), y+confirmBtn.getHeight());
		
		Bitmap hand = bitmapRes.getBitmap(FishGameRes.KEY_DAILY_TASK_HAND);
		handX = getRect().centerX() - hand.getWidth()/2;
		handY = confirmBtnRect.top + handMarginTopOrBottom;
		handRect.set(handX, handY, handX+hand.getWidth(), handY + hand.getHeight());
	}

	@Override
	public void onDrawSelf(Canvas canvas) {
		Bitmap bg = bitmapRes.getBitmap(FishGameRes.KEY_DAILY_TASK_BG);
		canvas.drawBitmap(bg, null, getRect(), null);
		
		Bitmap confirmBtn = bitmapRes.getBitmap(FishGameRes.KEY_DAILY_TASK_CONFIRM);
		canvas.drawBitmap(confirmBtn, null, confirmBtnRect, null);
		
		if(handY + handMarginTopOrBottom >= confirmBtnRect.bottom ){
			handDirection = - Math.abs(handDirection);
		}else if(handY - handMarginTopOrBottom <= confirmBtnRect.top){
			handDirection = Math.abs(handDirection);
		}

		handY += handDirection;
		
		handRect.set(handRect.left, handY, handRect.right, handY + handRect.height());
		canvas.drawBitmap(bitmapRes.getBitmap(FishGameRes.KEY_DAILY_TASK_HAND), null, handRect, null);
	}
	
	
	@Override
	public boolean onTouchEvent(MotionEvent event) {
		if (isVisible()) {
			if ((event.getAction() == MotionEvent.ACTION_DOWN || event
					.getAction() == MotionEvent.ACTION_MOVE)
					&& confirmBtnRect.contains((int) event.getX(),
							(int) event.getY())) {
				return true;
			}
			if ((event.getAction() == MotionEvent.ACTION_UP)
					&& confirmBtnRect.contains((int) event.getX(),
							(int) event.getY())) {
				
				if (!PxGameConstants.IS_ON_PAY) {
					if (System.currentTimeMillis() - lastClick < 2200L) {
						return true;
					}
					lastClick = System.currentTimeMillis();
					doEvent11();
				}
				
				Log.e("com.poxiao.fish", "return true");
				return true;
			}
		}
		return false;
	}
	
	private void doEvent11() {
		PxGameConstants.IS_ON_PAY = true;
		if (!AppApplication.getInstance().doPEvent(((GameScene) getParent()).getActivity(), "14", false,
				new EventCallBack() {
			@Override
			public void setEventResult(EventResult eventResult) {
				((GameScene) getParent()).getActivity().sendBroadcast(
						new Intent(PxGameConstants.MUSIC_ENABLED));
				if (eventResult.getPResult()) {
					PlayerInfo info = PlayerInfo.getPlayerInfo();
					int skillNum = 0;
					for (Map.Entry<Integer, Integer> entry : eventResult
							.getReward().entrySet()) {
						if (entry.getKey() == 1) {
							PxGameConstants.IS_PLAY_GOLD_ANIM = true;
							PxGameConstants.playerGold += entry
									.getValue();
						} else if (entry.getKey() == 2) {
							skillNum = entry.getValue();
						}
					}
					info.setSkillNum(info.getSkillNum() + skillNum);
					int money = info.getPayMoney();
					info.setPayMoney(money + 10);
					PlayerInfo.setPlayerInfo(info);
					if (PxGameConstants.playerCannon > 9) {
						((GameScene) getParent()).getMaxCannonByLevel();
					}
					((GameScene) getParent()).setSkillNum(info.getSkillNum());
					((GameScene) getParent()).drawCannon();
					((GameScene) getParent())
							.getActivity()
							.sendBroadcast(
									new Intent(
											PxGameConstants.MUSIC_ENABLED));
				}
				PxGameConstants.IS_ON_PAY = false;
			}
		})) {
			
			
		}
		
	}
	
}
