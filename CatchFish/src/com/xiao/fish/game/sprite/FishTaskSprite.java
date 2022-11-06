package com.xiao.fish.game.sprite;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Rect;

import com.hifreshday.android.pge.engine.options.EngineOptions;
import com.hifreshday.android.pge.entity.shape.sprite.Sprite;
import com.hifreshday.android.pge.view.BitmapSpliter;
import com.hifreshday.android.pge.view.res.IBitmapRes;
import com.xiao.fish.PxGameConstants;
import com.xiao.fish.domain.PlayerInfo;
import com.xiao.fish.domain.task.FishTask;
import com.xiao.fish.game.GameScene;
import com.xiao.fish.game.res.FishGameRes;
import com.xiao.fish.game.res.SoundRes;

public class FishTaskSprite extends Sprite {

	public static final int X = 45;
	public static final int Y = 82;
	public static final int WIDTH = 165;
	public static final int HEIGHT = 77;
	public static final int FISH_WIDTH = 60;
	private static final int SIGN_WIDTH = 13;
	private static final int SIGN_HEIGHT = 20;
	private static final int POINT_WIDTH = 11;
	private static final int POINT_HEIGHT = 15;
	private static final int RIGHT_WIDTH = 94;

	private FishTask task = null;
	private Rect fishRect;
	private static int catchNumber;
	private double elapsed;
	private Rect numleft;
	private Rect numright;
	private Rect signRect;

	private Rect timeleft;
	private Rect timeright;
	private Rect pointRect;

	public FishTaskSprite(IBitmapRes bitmapRes, int pX, int pY, int width,
			int height) {
		super(bitmapRes, pX, pY, width, height);
		this.setVisible(false);
		this.setNeedRecyle(true);
	}

	private void initView() {
		double w = task.getFish().getWidth();
		double h = task.getFish().getHeight();
		double rate = h / w;
		fishRect = new Rect(
				(int) (getRect().left + 12 * EngineOptions.getScreenScaleX()),
				(int) (getRect().top + (HEIGHT - FISH_WIDTH * rate) / 2
						* EngineOptions.getScreenScaleY()),
				(int) (getRect().left + (FISH_WIDTH + 12)
						* EngineOptions.getScreenScaleX()),
				(int) (getRect().top + (HEIGHT + FISH_WIDTH * rate) / 2
						* EngineOptions.getScreenScaleY()));
		numleft = new Rect();
		numright = new Rect();
		signRect = new Rect();
		timeleft = new Rect();
		timeright = new Rect();
		pointRect = new Rect();
	}

	@Override
	public void onDrawSelf(Canvas canvas) {
		Bitmap task_bg = bitmapRes.getBitmap(FishGameRes.KEY_GAME_TASK_BG);
		canvas.drawBitmap(task_bg, null, getRect(), null);
		if (null != task) {
			Bitmap fish = bitmapRes.getBitmap(task.getFish().getAnims()[0]);
			canvas.drawBitmap(fish, null, fishRect, null);
			if (catchNumber >= task.getCatchNumber()) {
				// 任务完成
				this.setVisible(false);
				SoundRes.playSound(SoundRes.tasksuccess);
				catchNumber = 0;// 捕获数重置为0
				// 播放动画		
				((GameScene) getParent()).playTaskFinishAnim();
				PxGameConstants.playerGold+=task.getPride();
				PlayerInfo info = PlayerInfo.getPlayerInfo();
				info.setGold(PxGameConstants.playerGold);
				PlayerInfo.setPlayerInfo(info);
			} else {
				signRect.set(
						(int) (getRect().left + (RIGHT_WIDTH - SIGN_WIDTH + 144)
								/ 2 * EngineOptions.getScreenScaleX()),
						(int) (getRect().top + 25 * EngineOptions
								.getScreenScaleY()),
						(int) (getRect().left + (RIGHT_WIDTH + SIGN_WIDTH + 144)
								/ 2 * EngineOptions.getScreenScaleX()),
						(int) (getRect().top + (25 + SIGN_HEIGHT)
								* EngineOptions.getScreenScaleY()));
				Bitmap num = bitmapRes.getBitmap(FishGameRes.KEY_GAME_TASKNUM);
				Bitmap sign = bitmapRes
						.getBitmap(FishGameRes.KEY_GAME_TASKSIGN);
				int aim[] = FishGameRes.getIntArray(task.getCatchNumber());
				int current[] = FishGameRes.getIntArray(catchNumber);
				for (int i = 0; i < current.length; i++) {
					numleft.set(
							(int) (signRect.left + (i - current.length)
									* SIGN_WIDTH
									* EngineOptions.getScreenScaleX()),
							signRect.top,
							(int) (signRect.left + (i + 1 - current.length)
									* SIGN_WIDTH
									* EngineOptions.getScreenScaleX()),
							signRect.bottom);
					Rect src1 = BitmapSpliter.splitBitmap2Rect(num, 10,
							current[i], BitmapSpliter.HORIZONTAL);
					canvas.drawBitmap(num, src1, numleft, null);
				}
				canvas.drawBitmap(sign, null, signRect, null);
				for (int i = 0; i < aim.length; i++) {
					numright.set((int) (signRect.right + i * SIGN_WIDTH
							* EngineOptions.getScreenScaleX()), signRect.top,
							(int) (signRect.right + (i + 1) * SIGN_WIDTH
									* EngineOptions.getScreenScaleX()),
							signRect.bottom);
					Rect src2 = BitmapSpliter.splitBitmap2Rect(num, 10, aim[i],
							BitmapSpliter.HORIZONTAL);
					canvas.drawBitmap(num, src2, numright, null);
				}

			}
			if (elapsed > task.getPassTime()) {
				// TODO 任务失败
				SoundRes.playSound(SoundRes.taskfail);
				this.setVisible(false);
				catchNumber = 0;// 捕获数重置为0
				elapsed = 0;
			} else {
				int time = (int) (task.getPassTime() - elapsed);
				pointRect
						.set((int) (getRect().left + (144 + RIGHT_WIDTH - POINT_WIDTH)
								/ 2 * EngineOptions.getScreenScaleX()),
								(int) (signRect.bottom + 5 * EngineOptions
										.getScreenScaleY()),
								(int) (getRect().left + (144 + RIGHT_WIDTH + POINT_WIDTH)
										/ 2 * EngineOptions.getScreenScaleX()),
								(int) (signRect.bottom + (5 + POINT_HEIGHT)
										* EngineOptions.getScreenScaleY()));
				Bitmap num = bitmapRes.getBitmap(FishGameRes.KEY_GAME_TASKTIME);
				Bitmap point = bitmapRes
						.getBitmap(FishGameRes.KEY_GAME_TASKPOINT);
				int left[] = FishGameRes.getIntArray("0" + time / 60);
				int right[] = FishGameRes
						.getIntArray(String.valueOf((time % 60 < 10 ? "0"
								+ time % 60 : time % 60)));
				for (int i = 0; i < left.length; i++) {
					timeleft.set(
							(int) (pointRect.left + (i - left.length)
									* POINT_WIDTH
									* EngineOptions.getScreenScaleX()),
							pointRect.top,
							(int) (pointRect.left + (i + 1 - left.length)
									* POINT_WIDTH
									* EngineOptions.getScreenScaleX()),
							pointRect.bottom);
					Rect src1 = BitmapSpliter.splitBitmap2Rect(num, 10,
							left[i], BitmapSpliter.HORIZONTAL);
					canvas.drawBitmap(num, src1, timeleft, null);
				}
				canvas.drawBitmap(point, null, pointRect, null);
				for (int i = 0; i < right.length; i++) {
					timeright.set(
							(int) (pointRect.right + (i * POINT_WIDTH + 2)
									* EngineOptions.getScreenScaleX()),
							pointRect.top, (int) (pointRect.right + ((i + 1)
									* POINT_WIDTH + 2)
									* EngineOptions.getScreenScaleX()),
							pointRect.bottom);
					Rect src2 = BitmapSpliter.splitBitmap2Rect(num, 10,
							right[i], BitmapSpliter.HORIZONTAL);
					// Log.e("com.poxiao.fish", "POINT_WIDTH" + POINT_WIDTH
					// * EngineOptions.getScreenScaleX());
					// Log.e("com.poxiao.fish",
					// "numleft.width" + timeright.width());
					// Log.e("com.poxiao.fish", "src1.width" + src2.width());
					// Log.e("com.poxiao.fish", "num.width" + num.getWidth() /
					// 10);
					canvas.drawBitmap(num, src2, timeright, null);
				}

			}
		}
	}

	@Override
	protected void onUpdateSelf(float secondsElapsed) {
		if (visible) {
			elapsed += secondsElapsed;
		}
	}

	/**
	 * 设置任务
	 * 
	 * @param task
	 */
	public void setFishTask(FishTask task) {
		this.task = task;
		initView();
		this.setVisible(true);
	}

	/**
	 * 设置捕获的数字
	 * 
	 * @param number
	 */
	public void setCatchFish(int type) {
		if (isVisible() && type == task.getFish().getFishType()) {
			catchNumber++;
		}
	}

	/**
	 * 返回已捕获的值
	 * 
	 * @return
	 */
	public int getCatchNumber() {
		return catchNumber;
	}
}
