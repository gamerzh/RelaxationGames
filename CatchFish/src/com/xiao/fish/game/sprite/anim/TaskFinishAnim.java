package com.xiao.fish.game.sprite.anim;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Point;
import android.graphics.Rect;

import com.hifreshday.android.pge.engine.options.EngineOptions;
import com.hifreshday.android.pge.extend.animation.AnimationSprite;
import com.hifreshday.android.pge.view.BitmapSpliter;
import com.hifreshday.android.pge.view.res.IBitmapRes;
import com.xiao.fish.PxGameConstants;
import com.xiao.fish.domain.PlayerInfo;
import com.xiao.fish.game.GameScene;
import com.xiao.fish.game.res.FishGameRes;

public class TaskFinishAnim extends AnimationSprite {

	private float animScale = 0.2f;
	private boolean isPlay = false;
	public static final int ANIM_WIDTH = 373;
	public static final int ANIM_HEIGHT = 178;
	public static final int NUM_WIDTH = 17;
	public static final int NUM_HEIGHT = 21;
	public static final int TEXT_WIDTH = 50;
	public static final int TEXT_HEIGHT = 26;
	private float pathx = 0;
	private float pathy = 0;
	private int godNum = 0;
	private Rect animRect;
	private Rect numRect;
	private Rect huodeRect;
	private Rect jinbiRect;

	public TaskFinishAnim(IBitmapRes bitmapRes, int pX, int pY, int width,
			int height) {
		super(bitmapRes, pX, pY, width, height);
		setVisible(false);
		setNeedRecyle(true);
		animRect = new Rect();
		numRect = new Rect();
		huodeRect = new Rect();
		jinbiRect = new Rect();
	}

	@Override
	public void onDrawSelf(Canvas canvas) {
		if (isPlay) {
			animRect.set(
					(int) ((EngineOptions.getScreenWidth() + (-2 * pathx - ANIM_WIDTH
							* animScale)
							* EngineOptions.getScreenScaleX()) / 2),
					(int) ((EngineOptions.getScreenHeight() + (-2 * pathy - ANIM_HEIGHT
							* animScale)
							* EngineOptions.getScreenScaleY()) / 2),
					(int) ((EngineOptions.getScreenWidth() + (-2 * pathx + ANIM_WIDTH
							* animScale)
							* EngineOptions.getScreenScaleX()) / 2),
					(int) ((EngineOptions.getScreenHeight() + (-2 * pathy + ANIM_HEIGHT
							* animScale)
							* EngineOptions.getScreenScaleY()) / 2));
			Bitmap bitmap = bitmapRes
					.getBitmap(FishGameRes.KEY_GAME_TASK_FINISH);
			canvas.drawBitmap(bitmap, null, animRect, null);
			int[] nums = FishGameRes.getIntArray(godNum);
			Bitmap goldnum = bitmapRes
					.getBitmap(FishGameRes.KEY_GAME_LEVEL_UP_NUM);
			for (int i = 0; i < nums.length; i++) {
				Rect src = BitmapSpliter.splitBitmap2Rect(goldnum, 10, nums[i],
						BitmapSpliter.HORIZONTAL);
				numRect.set((int) (animRect.centerX() + (i * NUM_HEIGHT
						* animScale - NUM_WIDTH * animScale * nums.length / 2)
						* EngineOptions.getScreenScaleX()),
						(int) (animRect.bottom - (18 + NUM_HEIGHT * animScale)
								* EngineOptions.getScreenScaleY()),
						(int) (animRect.centerX() + ((i + 1) * NUM_HEIGHT
								* animScale - NUM_WIDTH * animScale
								* nums.length / 2)
								* EngineOptions.getScreenScaleX()),
						(int) (animRect.bottom - 18 * EngineOptions
								.getScreenScaleY()));
				canvas.drawBitmap(goldnum, src, numRect, null);

			}
			huodeRect
					.set((int) (animRect.centerX() - (NUM_WIDTH * animScale
							* nums.length / 2 + TEXT_WIDTH * animScale)
							* EngineOptions.getScreenScaleX()),
							(int) (animRect.bottom - (16 + TEXT_HEIGHT
									* animScale)
									* EngineOptions.getScreenScaleY()),
							(int) (animRect.centerX() - NUM_WIDTH * animScale
									* nums.length / 2
									* EngineOptions.getScreenScaleX()),
							(int) (animRect.bottom - 16 * EngineOptions
									.getScreenScaleY()));
			Bitmap huode = bitmapRes.getBitmap(FishGameRes.KEY_GAME_HUODE);
			canvas.drawBitmap(huode, null, huodeRect, null);
			jinbiRect.set((int) (animRect.centerX() + (12 + NUM_WIDTH
					* animScale * nums.length / 2)
					* EngineOptions.getScreenScaleX()),
					(int) (animRect.bottom - (16 + TEXT_HEIGHT * animScale)
							* EngineOptions.getScreenScaleY()), (int) (animRect
							.centerX() + (12 + NUM_WIDTH * animScale
							* nums.length / 2 + TEXT_WIDTH * animScale)
							* EngineOptions.getScreenScaleX()),
					(int) (animRect.bottom - 16 * EngineOptions
							.getScreenScaleY()));
			Bitmap jinbi = bitmapRes.getBitmap(FishGameRes.KEY_GAME_JINBI);
			canvas.drawBitmap(jinbi, null, jinbiRect, null);
		}
	}

	private int anim_step = 0;
	private float time;
	private static final int STEP_ANIM_START = 0;
	private static final int STEP_ANIM_TWO = 1;

	@Override
	protected void onUpdateSelf(float secondsElapsed) {
		if (isPlay) {
			switch (anim_step) {
			case STEP_ANIM_START:
				animScale += 0.08;
				if (animScale >= 1.0) {
					anim_step = STEP_ANIM_TWO;
				}
				break;
			case STEP_ANIM_TWO:
				time += secondsElapsed;
				if (time > 0.6) {
					((GameScene) getParent()).playGoldAnim(
							new Point(animRect.centerX(), animRect.centerY()),
							godNum);
					// 加钱啦
					PxGameConstants.playerGold += godNum;
					PlayerInfo info = PlayerInfo.getPlayerInfo();
					info.setGold(PxGameConstants.playerGold);
					PlayerInfo.setPlayerInfo(info);
					clean();
				}
				break;
			}
		}
	}

	private void clean() {
		setVisible(false);
		isPlay = false;
		animScale = 0.2f;
		anim_step = 0;
		time = 0;
		pathx = 0;
		pathy = 0;
	}

	public void playTaskFinish(int goldNum) {
		setVisible(true);
		isPlay = true;
		this.godNum = goldNum;
	}
}
