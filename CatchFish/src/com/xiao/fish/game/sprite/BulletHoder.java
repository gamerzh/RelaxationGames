package com.xiao.fish.game.sprite;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

import android.content.Intent;
import android.graphics.Canvas;
import android.graphics.Point;
import android.util.Log;
import android.view.MotionEvent;

import com.d.event.EventCallBack;
import com.d.event.EventResult;
import com.hifreshday.android.pge.engine.options.EngineOptions;
import com.hifreshday.android.pge.entity.IEntity;
import com.hifreshday.android.pge.entity.shape.Shape;
import com.hifreshday.android.pge.entity.shape.sprite.Sprite;
import com.hifreshday.android.pge.view.res.IBitmapRes;
import com.tbu.androidtools.Debug;
import com.xiao.fish.FishCatchApplication;
import com.xiao.fish.PxGameConstants;
import com.xiao.fish.constants.MoveUtils;
import com.xiao.fish.domain.PlayerInfo;
import com.xiao.fish.domain.bullet.Bullet;
import com.xiao.fish.domain.bullet.BulletManger;
import com.xiao.fish.game.GameScene;
import com.xiao.fish.game.res.SoundRes;

public class BulletHoder extends Sprite {
	private List<BulletSprite> bulletSprites;
	// 控制子弹发射的间隔
	private float deltime;
	private boolean isfire = true;

	public BulletHoder(IBitmapRes bitmapRes, int pX, int pY, int width,
			int height) {
		super(bitmapRes, pX, pY, width, height);
		bulletSprites = new ArrayList<BulletSprite>();
	}

	@Override
	public void onDrawSelf(Canvas canvas) {

	}

	/**
	 * 创建子弹
	 * 
	 * @param datumpoint
	 * @param ap
	 * @param bp
	 */
	public void createBullet(Point datumpoint, Point ap, Point bp) {
		Bullet bullet = BulletManger
				.getBulletByType(PxGameConstants.playerCannon);
		bullet.setRotatetion(MoveUtils.getInstance().getRotation(datumpoint,
				ap, bp));
		if (PxGameConstants.playerGold < bullet.getGoldConsume()) {
			// TODO 弹出计费框
			eventDispatch();
		} else {
			SoundRes.playSound(SoundRes.bullet);
			if (bullet.getBulletType() != 10) {
				BulletSprite bulletSprite = new BulletSprite(bitmapRes, 0, 0,
						0, 0, bullet,
						((GameScene) getParent()).getBulletStartPoint());
				bulletSprite.setTouchPoint(ap);
				bulletSprites.add(bulletSprite);
				attachChild(bulletSprite);
				// 消耗金币
				PxGameConstants.playerGold = (int) (PxGameConstants.playerGold - bullet
						.getGoldConsume());
			} else {
				BulletSprite bulletSprite = new BulletSprite(bitmapRes, 0, 0,
						0, 0, bullet,
						((GameScene) getParent()).getBulletStartPoint());
				bulletSprite.setTouchPoint(ap);
				bulletSprites.add(bulletSprite);
				attachChild(bulletSprite);
			}
		}
	}

	private void eventDispatch() {
		if (PlayerInfo.getPlayerInfo().getProtectedPaySuccessTimes() == 0) {
			Debug.e("BulletHolder->eventDispatch doEvent1");
			doEvent1();
		} else if (PlayerInfo.getPlayerInfo().getProtectedPaySuccessTimes() == 1) {
			Debug.e("BulletHolder->eventDispatch doEvent2");
			doEvent2();
		} else if (PlayerInfo.getPlayerInfo().getProtectedPaySuccessTimes() >= 2) {
			Debug.e("BulletHolder->eventDispatch doEvent3");
			PlayerInfo playerInfo = PlayerInfo.getPlayerInfo();
			if (playerInfo.getPayRequestTimes() == 0) {
				doEvent3();
				playerInfo
						.setPayRequestTimes(playerInfo.getPayRequestTimes() + 1);
				PlayerInfo.setPlayerInfo(playerInfo);
			} else {
				if (playerInfo.getPayRequestTimes() % 2 == 1) {
					Debug.e("BulletHolder->eventDispatch doEvent4");
					playerInfo.setPayRequestTimes(playerInfo
							.getPayRequestTimes() + 1);
					PlayerInfo.setPlayerInfo(playerInfo);
					doEvent4();
				} else {
					Debug.e("BulletHolder->eventDispatch doEvent5");
					playerInfo.setPayRequestTimes(playerInfo
							.getPayRequestTimes() + 1);
					PlayerInfo.setPlayerInfo(playerInfo);
					doEvent5();
				}
			}
			PlayerInfo.setPlayerInfo(playerInfo);
		}
	}

	@Override
	public boolean onTouchEvent(MotionEvent event) {
		if (event.getAction() == MotionEvent.ACTION_DOWN
				|| event.getAction() == MotionEvent.ACTION_MOVE) {
			if (isfire && !PxGameConstants.IS_CHANGE_CANNON) {
				Point datumpoint = new Point(
						EngineOptions.getScreenWidth() / 2,
						EngineOptions.getScreenHeight());
				Point ap = new Point((int) event.getX(), (int) event.getY());
				Point bp = new Point(EngineOptions.getRealScreenWidth(),
						EngineOptions.getRealScreenHeight());
				// 设置炮塔转角
				((GameScene) getParent()).setCannonRotation(datumpoint, ap, bp);
				isfire = false;
			}
			return true;
		}
		return false;
	}

	@Override
	protected void onUpdateSelf(float secondsElapsed) {
		deltime += secondsElapsed;
		// 子弹最快0.5秒一发
		if (deltime > 0.10) {
			if (PxGameConstants.playerCannon != 10) {
				isfire = true;
				deltime -= 0.10;
			}
		}
		for (int i = 0; i < bulletSprites.size(); i++) {
			if (bulletSprites.get(i).outOfScreeen()) {
				bulletSprites.remove(i);
			}
		}
		updateFishCollosion(secondsElapsed);
	}

	private void updateFishCollosion(float secondsElapsed) {
		if (children != null && children.size() > 0) {
			for (IEntity entity : children) {
				if (entity.isVisible()) {
					// 模式1:碰撞检测后打开网
					if (!((BulletSprite) entity).isCollsion) {
						return;
					}
					if (((GameScene) getParent()).isCollision((Shape) entity)) {
						if (PxGameConstants.playerCannon != 10) {
							// 打开网
							SoundRes.playSound(SoundRes.fishnet);
							((GameScene) getParent()).showFishingNet(
									PxGameConstants.playerCannon,
									(int) ((BulletSprite) entity).bulletRect
											.centerX(),
									(int) ((BulletSprite) entity).bulletRect
											.centerY());
							Log.i("com.poxaio.fish", "catchfish success ... ");
							// 移除子弹
							entity.setVisible(false);
							entity.setNeedRemove(true);
							bulletSprites.remove(entity);
						}
					}
				}
			}
		}
	}

	private void doEvent1() {
		if (PxGameConstants.IS_ON_PAY) {
			return;
		}
		PxGameConstants.IS_ON_PAY = true;
		boolean result = FishCatchApplication.getInstance().doMyPayEvent(
				((GameScene) getParent()).getActivity(), "1",
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
						info.setProtectedPaySuccessTimes(info
								.getProtectedPaySuccessTimes() + 1);
						PlayerInfo.setPlayerInfo(info);
						PxGameConstants.IS_ON_PAY = false;

					}
				});
		if (!result) {
			doEvent3();
		}
	}

	private void doEvent2() {
		if (PxGameConstants.IS_ON_PAY) {
			return;
		}
		PxGameConstants.IS_ON_PAY = true;
		FishCatchApplication.getInstance().doMyPayEvent(
				((GameScene) getParent()).getActivity(), "4",
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
							// 保护计费点支付成功次数+1
							info.setProtectedPaySuccessTimes(info
									.getProtectedPaySuccessTimes() + 1);
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
						} else {
							for (int i = 0; i < PxGameConstants.playerMaxCannon; i++) {
								if (PxGameConstants.playerGold == 0) {
									PxGameConstants.playerCannon = 1;
									((GameScene) getParent()).drawCannon();
									break;
								}
								if (PxGameConstants.playerGold >= BulletManger
										.getBulletByType(
												PxGameConstants.playerMaxCannon
														- i).getGoldConsume()) {
									PxGameConstants.playerCannon = PxGameConstants.playerMaxCannon
											- i;
									((GameScene) getParent()).drawCannon();
									break;
								}
							}
						}
						PxGameConstants.IS_ON_PAY = false;
					}
				});

	}

	private void doEvent3() {
		if (PxGameConstants.IS_ON_PAY) {
			return;
		}
		PxGameConstants.IS_ON_PAY = true;
		FishCatchApplication.getInstance().doMyPayEvent(
				((GameScene) getParent()).getActivity(), "3",
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
							// 保护计费点支付成功次数+1
							info.setProtectedPaySuccessTimes(info
									.getProtectedPaySuccessTimes() + 1);
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
						} else {
							for (int i = 0; i < PxGameConstants.playerMaxCannon; i++) {
								if (PxGameConstants.playerGold == 0) {
									PxGameConstants.playerCannon = 1;
									((GameScene) getParent()).drawCannon();
									break;
								}
								if (PxGameConstants.playerGold >= BulletManger
										.getBulletByType(
												PxGameConstants.playerMaxCannon
														- i).getGoldConsume()) {
									PxGameConstants.playerCannon = PxGameConstants.playerMaxCannon
											- i;
									((GameScene) getParent()).drawCannon();
									break;
								}
							}
						}
						PxGameConstants.IS_ON_PAY = false;
					}
				});
	}

	private void doEvent4() {
		if (PxGameConstants.IS_ON_PAY) {
			return;
		}
		PxGameConstants.IS_ON_PAY = true;
		FishCatchApplication.getInstance().doMyPayEvent(
				((GameScene) getParent()).getActivity(), "4",
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
							// 保护计费点支付成功次数+1
							info.setProtectedPaySuccessTimes(info
									.getProtectedPaySuccessTimes() + 1);
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
						} else {
							for (int i = 0; i < PxGameConstants.playerMaxCannon; i++) {
								if (PxGameConstants.playerGold == 0) {
									PxGameConstants.playerCannon = 1;
									((GameScene) getParent()).drawCannon();
									break;
								}
								if (PxGameConstants.playerGold >= BulletManger
										.getBulletByType(
												PxGameConstants.playerMaxCannon
														- i).getGoldConsume()) {
									PxGameConstants.playerCannon = PxGameConstants.playerMaxCannon
											- i;
									((GameScene) getParent()).drawCannon();
									break;
								}
							}
						}
						PxGameConstants.IS_ON_PAY = false;
					}
				});
	}

	private void doEvent5() {
		if (PxGameConstants.IS_ON_PAY) {
			return;
		}
		PxGameConstants.IS_ON_PAY = true;
		FishCatchApplication.getInstance().doMyPayEvent(
				((GameScene) getParent()).getActivity(), "3",
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
							// 保护计费点支付成功次数+1
							info.setProtectedPaySuccessTimes(info
									.getProtectedPaySuccessTimes() + 1);
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
						} else {
							for (int i = 0; i < PxGameConstants.playerMaxCannon; i++) {
								if (PxGameConstants.playerGold == 0) {
									PxGameConstants.playerCannon = 1;
									((GameScene) getParent()).drawCannon();
									break;
								}
								if (PxGameConstants.playerGold >= BulletManger
										.getBulletByType(
												PxGameConstants.playerMaxCannon
														- i).getGoldConsume()) {
									PxGameConstants.playerCannon = PxGameConstants.playerMaxCannon
											- i;
									((GameScene) getParent()).drawCannon();
									break;
								}
							}
						}
						PxGameConstants.IS_ON_PAY = false;
					}
				});
	}
}
