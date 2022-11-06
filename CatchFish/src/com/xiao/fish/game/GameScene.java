package com.xiao.fish.game;

import java.util.Timer;
import java.util.TimerTask;

import android.app.Activity;
import android.content.res.AssetManager;
import android.content.res.Resources;
import android.graphics.Point;
import android.util.Log;

import com.hifreshday.android.pge.engine.options.EngineOptions;
import com.hifreshday.android.pge.entity.shape.Shape;
import com.tbu.android.moreapp.MoreGameManager;
import com.tbu.android.moreapp.domain.MoreAppCallback;
import com.tbu.androidtools.Debug;
import com.xiao.fish.PxGameConstants;
import com.xiao.fish.constants.Rank;
import com.xiao.fish.domain.PlayerInfo;
import com.xiao.fish.domain.exp.ExpManage;
import com.xiao.fish.domain.fishnet.FishingNetManage;
import com.xiao.fish.domain.task.FishTaskManger;
import com.xiao.fish.game.res.FishGameRes;
import com.xiao.fish.game.res.SoundRes;
import com.xiao.fish.game.sprite.AlmsSprite;
import com.xiao.fish.game.sprite.BulletHoder;
import com.xiao.fish.game.sprite.CannonDownSprite;
import com.xiao.fish.game.sprite.CannonSprite;
import com.xiao.fish.game.sprite.CannonUpSprite;
import com.xiao.fish.game.sprite.DailyTaskSprite;
import com.xiao.fish.game.sprite.EnergySprite;
import com.xiao.fish.game.sprite.FishHolder;
import com.xiao.fish.game.sprite.FishNetSprite;
import com.xiao.fish.game.sprite.FishTaskSprite;
import com.xiao.fish.game.sprite.HotMarqueeSprite;
import com.xiao.fish.game.sprite.PlayerGoldSprite;
import com.xiao.fish.game.sprite.PlayerLevelSprite;
import com.xiao.fish.game.sprite.RechargeSprite;
import com.xiao.fish.game.sprite.SetViewSprite;
import com.xiao.fish.game.sprite.SettingSprite;
import com.xiao.fish.game.sprite.SkillBoomSprite;
import com.xiao.fish.game.sprite.TextMarqueeSprite;
import com.xiao.fish.game.sprite.TurretSprite;
import com.xiao.fish.game.sprite.anim.BoomAnim;
import com.xiao.fish.game.sprite.anim.GoldAnimSprite;
import com.xiao.fish.game.sprite.anim.GoldNumAnim;
import com.xiao.fish.game.sprite.anim.LevelUpAnim;
import com.xiao.fish.game.sprite.anim.NewBeeAnim;
import com.xiao.fish.game.sprite.anim.OpenWeaponAnim;
import com.xiao.fish.game.sprite.anim.SmallGoldNumAnim;
import com.xiao.fish.game.sprite.anim.TaskFinishAnim;

public class GameScene extends BaseGameScene {

	private GameActivity activity;
	private FishGameRes bitmapRes;
	private float elapsed;
	// --------------------------
	private FishHolder fishHolder;
	private CannonSprite cannonSprite;
	private BulletHoder bulletHoder;
	private PlayerGoldSprite playerGoldSprite;
	private FishTaskSprite fishTaskSprite;
	private EnergySprite energySprite;
	private TurretSprite turretSprite;
	private CannonDownSprite cannonDownSprite;
	private CannonUpSprite cannonUpSprite;
	private PlayerLevelSprite playerLevelSprite;
	private AlmsSprite almsSprite;
	private NewBeeAnim newBeeAnim;
	private LevelUpAnim levelUpAnim;
	private GoldAnimSprite goldAnimSprite;
	private RechargeSprite rechargeSprite;
	private SkillBoomSprite skillBoomSprite;
	private SettingSprite settingSprite;
	private SetViewSprite setViewSprite;
	private OpenWeaponAnim openWeaponAnim;
	private TaskFinishAnim taskFinishAnim;
	private TextMarqueeSprite marqueeSprite;
	private HotMarqueeSprite hotMarqueeSprite;

	private DailyTaskSprite dailyTaskSprite;
	
	public GameScene(Activity activity) {
		super(activity);
		this.activity = (GameActivity) activity;
	}

	@Override
	public void onLoadResources(Resources res, AssetManager assertManager) {
		bitmapRes = new FishGameRes(res);
		initSprite();
	}

	private void initSprite() {
		createSprite();
		managerChilds();
		managerTouchs();
		showPlayerLevel();
	}

	private void createSprite() {
		rechargeSprite = new RechargeSprite(bitmapRes, RechargeSprite.X,
				RechargeSprite.Y, RechargeSprite.WIDTH, RechargeSprite.HEIGHT);
		skillBoomSprite = new SkillBoomSprite(bitmapRes, SkillBoomSprite.X,
				SkillBoomSprite.Y, SkillBoomSprite.WIDTH,
				SkillBoomSprite.HEIGHT);
		cannonSprite = new CannonSprite(bitmapRes, 0, 0, 0, 0);
		fishHolder = new FishHolder(bitmapRes, 0, 0, 0, 0);
		bulletHoder = new BulletHoder(bitmapRes, 0, 0, 0, 0);
		playerGoldSprite = new PlayerGoldSprite(bitmapRes, PlayerGoldSprite.X,
				PlayerGoldSprite.Y, 0, 0);
		fishTaskSprite = new FishTaskSprite(bitmapRes, FishTaskSprite.X,
				FishTaskSprite.Y, FishTaskSprite.WIDTH, FishTaskSprite.HEIGHT);
		energySprite = new EnergySprite(bitmapRes, EnergySprite.X,
				EnergySprite.Y, EnergySprite.WIDTH, EnergySprite.HEIGHT);
		turretSprite = new TurretSprite(bitmapRes, 0, 0, 0, 0);
		cannonDownSprite = new CannonDownSprite(bitmapRes, CannonDownSprite.X,
				CannonDownSprite.Y, CannonDownSprite.WIDTH,
				CannonDownSprite.HEIGHT);
		cannonUpSprite = new CannonUpSprite(bitmapRes, CannonUpSprite.X,
				CannonUpSprite.Y, CannonUpSprite.WIDTH, CannonUpSprite.HEIGHT);
		playerLevelSprite = new PlayerLevelSprite(bitmapRes,
				PlayerLevelSprite.X, PlayerLevelSprite.Y,
				PlayerLevelSprite.WIDTH, PlayerLevelSprite.HEIGHT);
		almsSprite = new AlmsSprite(bitmapRes, AlmsSprite.X, AlmsSprite.Y,
				AlmsSprite.WIDTH, AlmsSprite.HEIGHT);
		newBeeAnim = new NewBeeAnim(bitmapRes, 0, 0, 0, 0);
		levelUpAnim = new LevelUpAnim(bitmapRes, 0, 0, 0, 0);
		settingSprite = new SettingSprite(bitmapRes, SettingSprite.X,
				SettingSprite.Y, SettingSprite.WIDTH, SettingSprite.HEIGHT);
		setViewSprite = new SetViewSprite(bitmapRes, 0, 0, 0, 0);
		MoreGameManager.init(activity.getApplicationContext(),
				new MoreAppCallback() {
					@Override
					public void result(boolean changed) {
						if (MoreGameManager.allowShowMoreApps(activity
								.getApplicationContext())) {
							setViewSprite.showMoreGame = true;
						}

					}
				});

		openWeaponAnim = new OpenWeaponAnim(bitmapRes, 0, 0, 0, 0);
		taskFinishAnim = new TaskFinishAnim(bitmapRes, 0, 0, 0, 0);
		marqueeSprite = new TextMarqueeSprite(bitmapRes, 0, 0, 0, 0);
		
		
		dailyTaskSprite = new DailyTaskSprite(bitmapRes);
		
		if (PxGameConstants.isShowHotActivity) {
			hotMarqueeSprite = new HotMarqueeSprite(bitmapRes,
					HotMarqueeSprite.X, HotMarqueeSprite.Y,
					HotMarqueeSprite.RECT_WIDTH, HotMarqueeSprite.RECT_HEIGHT);
		}
	}

	/**
	 * 添加精灵
	 */
	private void managerChilds() {
		attachChild(fishHolder);
		attachChild(marqueeSprite);
		if (PxGameConstants.isShowHotActivity) {
			attachChild(hotMarqueeSprite);
		}
		attachChild(settingSprite);
		attachChild(turretSprite);
		attachChild(almsSprite);
		attachChild(playerGoldSprite);
		attachChild(fishTaskSprite);
		attachChild(cannonDownSprite);
		attachChild(cannonUpSprite);
		attachChild(bulletHoder);
		attachChild(rechargeSprite);
		attachChild(skillBoomSprite);
		attachChild(cannonSprite);
		attachChild(energySprite);
		attachChild(playerLevelSprite);
		attachChild(newBeeAnim);
		attachChild(levelUpAnim);
		attachChild(openWeaponAnim);
		attachChild(setViewSprite);
		attachChild(taskFinishAnim);
		attachChild(dailyTaskSprite);
	}

	/**
	 * 注册点击事件
	 */
	private void managerTouchs() {
		registerTouch(rechargeSprite);
		if (PxGameConstants.isShowHotActivity) {
			registerTouch(hotMarqueeSprite);
		}
		registerTouch(skillBoomSprite);
		registerTouch(dailyTaskSprite);
		
		registerTouch(settingSprite);
		registerTouch(setViewSprite);
		registerTouch(cannonDownSprite);
		registerTouch(cannonUpSprite);
		registerTouch(turretSprite);
		registerTouch(bulletHoder);
	}

	@Override
	public void onUnloadResources() {
		//
	}

	@Override
	protected void onUpdateSelf(float secondsElapsed) {
		if (!fishTaskSprite.isVisible()) {
			elapsed += secondsElapsed;
		}
		// 炸弹动画播放结束
		if (animIndex > 7) {
			PxGameConstants.IS_IN_BOOM = false;
			myTimer.cancel();
			catchAllFishes();
			animIndex = 0;
		}
		// 每90秒触发一次任务
		if (elapsed > 120) {
			SoundRes.playSound(SoundRes.taskstart);
			showPlayerTask();
			elapsed -= 120;
		}
		if (PxGameConstants.playerGold < 200) {
			this.startAlms(true);
		} else {
			this.startAlms(false);
		}
		if (PxGameConstants.IS_PLAY_GOLD_ANIM) {
			playGoldAnim(new Point(EngineOptions.getScreenWidth() / 2,
					EngineOptions.getScreenHeight() / 2), 150);
			PxGameConstants.IS_PLAY_GOLD_ANIM = false;
		}
		if (PxGameConstants.IS_SHOW_SETTING) {
			setViewSprite.setVisible(true);
		} else {
			setViewSprite.setVisible(false);
		}
	}

	/**
	 * 渔网的展现
	 * 
	 * @param type
	 * @param px
	 * @param py
	 */
	public void showFishingNet(final int type, final int px, final int py) {
		activity.runOnUpdate(new Runnable() {
			public void run() {
				FishNetSprite fishNetSprite = new FishNetSprite(bitmapRes, 0,
						0, 0, 0, FishingNetManage.getFishNetByType(type),
						new Point(px, py));
				attachChild(fishNetSprite);
			}
		});
	}

	/**
	 * 子弹碰撞检查
	 * 
	 * @param shape
	 * @return
	 */
	public boolean isCollision(Shape shape) {
		return fishHolder.isCollision(shape);
	}

	/**
	 * 渔网碰撞检查
	 * 
	 * @param shape
	 * @return
	 */
	public void isNetCollision(Shape shape) {
		fishHolder.isNetCollision(shape);
	}

	/**
	 * 绘制炮塔
	 */
	public void drawCannon() {
		Debug.e("com.poxiao.fish cannon type=" + PxGameConstants.playerCannon);
		cannonSprite.setCannonBitmap(PxGameConstants.playerCannon);
	}

	/**
	 * 重新获取一次最大的炮塔等级
	 */
	public void getMaxCannonByLevel() {
		PlayerInfo info = PlayerInfo.getPlayerInfo();
		int level = ExpManage.getInstance().getLevelByExp(
				PxGameConstants.playerExp);
		switch (level) {
		case 0:
			PxGameConstants.playerMaxCannon = 6;
			break;
		case 1:
			PxGameConstants.playerMaxCannon = 6;
			break;
		case 2:
			PxGameConstants.playerMaxCannon = 7;
			break;
		case 3:
			PxGameConstants.playerMaxCannon = 8;
			break;
		case 4:
			PxGameConstants.playerMaxCannon = 9;
			break;
		default:
			PxGameConstants.playerMaxCannon = 9;
			break;
		}
		info.setMaxCannon(PxGameConstants.playerMaxCannon);
		PlayerInfo.setPlayerInfo(info);
	}

	/**
	 * 获取子弹发射点
	 */
	public Point getBulletStartPoint() {
		if (null == cannonSprite.getBulletStartPoint()) {
			Log.e("com.poxiao.fish", "point is null");
		}
		return cannonSprite.getBulletStartPoint();
	}

	/**
	 * 展示用户的等级
	 */
	public void showPlayerLevel() {
		int level = ExpManage.getInstance().getLevelByExp(
				PxGameConstants.playerExp);
		double rate = 0;
		if (level == 12) {
			rate = 1;
		} else {
			int hexp = ExpManage.getInstance().getHExpByLevel(level);
			int lexp = ExpManage.getInstance().getLExpByLevel(level);
			if (hexp == 0) {
				return;
			}
			rate = (double) (PxGameConstants.playerExp - lexp)
					/ (double) (hexp - lexp);
			// Log.i("com.poxiao.fish", "rate=" + rate + ";experience="
			// + PlayerInfo.getPlayerInfo().getExperience() + "exp" + hexp);
		}
		playerLevelSprite.setPlayerLevel(level, rate);
	}

	private void showPlayerTask() {
		// 任务的展现
		fishTaskSprite.setFishTask(FishTaskManger.getFishTaskByType((int) (Math
				.random() * 5 + 1)));
	}

	/**
	 * 设置捕获的数字
	 * 
	 * @param number
	 */
	public void setCatchFish(int type) {
		fishTaskSprite.setCatchFish(type);
	}

	/**
	 * 返回已捕获的值
	 * 
	 * @return
	 */
	public int getCatchNumber() {
		return fishTaskSprite.getCatchNumber();
	}

	/**
	 * 炮塔倾角
	 * 
	 * @param tp
	 */
	public void setCannonRotation(Point datumpoint, Point ap, Point bp) {
		cannonSprite.setRotation(ap);
		cannonSprite.playAnim(datumpoint, ap, bp);
	}

	/**
	 * 创建子弹
	 * 
	 * @param datumpoint
	 * @param ap
	 * @param bp
	 */
	public void createBullet(Point datumpoint, Point ap, Point bp) {
		bulletHoder.createBullet(datumpoint, ap, bp);
	}

	public void startAlms(boolean b) {
		almsSprite.setStart(b);
	}

	public void setEnergyProgress(int gold) {
		// Log.e("com.poxiao.fish", "energy" + playerInfo.getEnergy());
		if (PxGameConstants.playerEnergy >= PxGameConstants.MAX_ENERGY) {
			// 武器切换到激光
			PxGameConstants.playerEnergy = gold;
			playCannonOutAnim();
		} else {
			PxGameConstants.playerEnergy += gold;
		}
		float rate = (float) PxGameConstants.playerEnergy
				/ (float) PxGameConstants.MAX_ENERGY;
		energySprite.setProgress(rate);
	}

	public GameActivity getActivity() {
		return activity;
	}

	/**
	 * 播放NewBee动画
	 * 
	 */
	public void playNewBeeAnim() {
		newBeeAnim.playNewBee();
	}

	/**
	 * 播放升级动画
	 */
	public void playLevelUpAnim(int money) {
		levelUpAnim.playLevelUp(money);
	}

	public void playOpenWeaponAnim(int level) {
		openWeaponAnim.showOpenLockAnim(level);
	}

	/**
	 * 炮塔出场动画
	 * 
	 * @param money
	 */
	public void playCannonOutAnim() {
		cannonSprite.playOutAnim();
	}

	/**
	 * 炮塔进场动画
	 * 
	 * @param money
	 */
	public void playCannonEnterAnim() {
		cannonSprite.playEnterAnim();
	}

	/**
	 * 金币动画
	 * 
	 * @param point
	 * @param times
	 */
	public void playGoldAnim(final Point point, final int money) {
		activity.runOnUpdate(new Runnable() {
			public void run() {
				int length = money / 10;
				if (length == 0) {
					length = 1;
				} else if (length > 20) {
					length = 20;
				}
				for (int i = 0; i < length; i++) {
					goldAnimSprite = new GoldAnimSprite(bitmapRes, 0, 0,
							GoldAnimSprite.PNG_WIDTH, GoldAnimSprite.PNG_HEIGHT);
					goldAnimSprite.playGoldAnimtion(new Point(point.x
							+ (i % 7 - length / 2) * GoldAnimSprite.PNG_WIDTH,
							point.y + (i / 7) * GoldAnimSprite.PNG_HEIGHT), i);
					attachChild(goldAnimSprite);
				}
			}
		});
	}

	public void playTaskFinishAnim() {
		taskFinishAnim.playTaskFinish(150);
	}

	/**
	 * 绘制大数字
	 * 
	 * @param money
	 * @param point
	 */
	public void playNumAnim(final int money, final Point point) {
		activity.runOnUpdate(new Runnable() {
			public void run() {
				GoldNumAnim anim = new GoldNumAnim(bitmapRes, 0, 0, 0, 0, point);
				anim.playGoldNum(money);
				attachChild(anim);
			}
		});
	}

	/**
	 * 绘制小数字
	 * 
	 * @param money
	 */
	public void playSamllNumAnim(final int money) {
		activity.runOnUpdate(new Runnable() {

			@Override
			public void run() {
				SmallGoldNumAnim anim = new SmallGoldNumAnim(bitmapRes, 0, 0,
						0, 0);
				anim.playGoldNumSmall(money);
				attachChild(anim);
			}
		});
	}

	public void showSkillHint(boolean b) {
		skillBoomSprite.showSkillHint(b);
	}

	public void setSkillNum(int skillNum){
		skillBoomSprite.setSkillNum(skillNum);
	}
	
	private int animIndex = 0;
	private Timer myTimer;

	public void playBoomAnim() {
		PxGameConstants.IS_IN_BOOM = true;
		animIndex = 0;
		myTimer = new Timer();
		TimerTask timerTask = new TimerTask() {
			@Override
			public void run() {
				activity.runOnUpdate(new Runnable() {
					public void run() {
						BoomAnim anim = new BoomAnim(bitmapRes, 0, 0, 0, 0);
						attachChild(anim);
						anim.startPlayBoom(animIndex);
						animIndex++;
					}
				});
			}
		};
		myTimer.schedule(timerTask, 0, 300);
	}

	/**
	 * 捕获所有的鱼
	 */
	public void catchAllFishes() {
		activity.runOnUpdate(new Runnable() {
			public void run() {
				fishHolder.catchAllFishes();
			}
		});
	}

	/**
	 * 显示设置界面
	 */
	public void showSetting() {
		PxGameConstants.IS_SHOW_SETTING = true;
	}

	/**
	 * 文字跑马灯
	 * 
	 * @param info
	 */
	public void showTextMarquee(String info) {
		marqueeSprite.showInfo(info);
	}

	public void showLevelMarquee(int level) {
		int per = Rank.getRankPer(level);
		String info = "恭喜您升到了第" + level + "级,您已经超越了" + per + "%的玩家";
		marqueeSprite.showInfo(info);
	}

	/**
	 * 测试方法
	 */
	public void testFunc() {
	}
}
