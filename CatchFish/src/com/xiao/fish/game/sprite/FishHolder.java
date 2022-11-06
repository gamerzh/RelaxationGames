package com.xiao.fish.game.sprite;

import java.util.Map;
import java.util.Timer;
import java.util.TimerTask;

import android.content.Intent;
import android.graphics.Canvas;
import android.graphics.Point;
import android.os.Handler;
import android.util.Log;

import com.d.event.EventCallBack;
import com.d.event.EventResult;
import com.hifreshday.android.pge.engine.options.EngineOptions;
import com.hifreshday.android.pge.entity.IEntity;
import com.hifreshday.android.pge.entity.shape.Shape;
import com.hifreshday.android.pge.entity.shape.sprite.Sprite;
import com.hifreshday.android.pge.view.res.IBitmapRes;
import com.xiao.fish.FishCatchApplication;
import com.xiao.fish.PxGameConstants;
import com.xiao.fish.constants.BirthPosition;
import com.xiao.fish.domain.PlayerInfo;
import com.xiao.fish.domain.exp.ExpManage;
import com.xiao.fish.domain.fish.Fish;
import com.xiao.fish.domain.fish.FishManage;
import com.xiao.fish.game.GameScene;
import com.xiao.fish.game.res.SoundRes;

public class FishHolder extends Sprite {
	private float elapsedSingle;
	private float showGirlTime = 0;
	private float showItemTime = 20;
	
	private float currentBombIndex = 0;
	private boolean hongbao,bomb;
	
	public FishHolder(IBitmapRes bitmapRes, int pX, int pY, int width,
			int height) {
		super(bitmapRes, pX, pY, width, height);
	}

	@Override
	public void onDrawSelf(Canvas canvas) {
		// 绘制单鱼
		if (FishManage.getInstance().getFishes().size() < PxGameConstants.POOL_SIZE) {
			int positionType = (int) (Math.random() * 4);
			if (elapsedSingle > 0.5) {
				craeteSingleFish(positionType);
				elapsedSingle -= 0.5;
			}
		}
		// 绘制美人鱼
		if (showGirlTime > 40) {
			// Log.e("com.poxiao.fish", "beautiful girl");
			createBeautifulGirl();
			showGirlTime -= 40;
			((GameScene) getParent())
					.showTextMarquee(PxGameConstants.MARQUEE_BEAUTIFUL_GIRL);
			((GameScene) getParent()).getActivity().runOnUiThread(
					new Runnable() {
						public void run() {
							new Handler().postDelayed(new Runnable() {
								public void run() {
									((GameScene) getParent())
											.showSkillHint(true);
								}
							}, 2000);
						}
					});
		}
		if(showItemTime > 30){
			if(!hongbao){
				hongbao = true;
				createHongBao();
			}
		}
		if(showItemTime > 50){
			if(!bomb){
				bomb = true;
				createBombItem();
			}
			
		}
		if(showItemTime > 65){
			
			createHuafei();
			hongbao = false;
			bomb = false;
			showItemTime = 0;
		}
	}

	private void createBombItem() {
		((GameScene) getParent()).getActivity().runOnUpdate(new Runnable() {
			public void run() {
				
				createItem(Fish.FISHTYPE_8);
				
			}
		});
	}

	private void createHuafei() {
		((GameScene) getParent()).getActivity().runOnUpdate(new Runnable() {
			public void run() {
				
				createItem(Fish.FISHTYPE_10);
				
				
				
				
			}
		});
	}
	
	private void createHongBao(){
		((GameScene) getParent()).getActivity().runOnUpdate(new Runnable() {
			public void run() {
				
				createItem(Fish.FISHTYPE_9);
				
				
				
				
			}
		});
	}

	@Override
	protected void onUpdateSelf(float secondsElapsed) {
		elapsedSingle += secondsElapsed;
		showGirlTime += secondsElapsed;
		
		showItemTime += secondsElapsed;
		
		if (null == children) {
			return;
		}
		for (IEntity entity : children) {
			if (((FishSprite) entity).outOfScreen()) {
				entity.setVisible(false);
				entity.setNeedRemove(true);
				FishManage.getInstance().getFishes()
						.remove(((FishSprite) entity).getFish());
			}
		}
	}

	/**
	 * 创建单鱼
	 * 
	 * @param fishType
	 * @return
	 */
	private void craeteSingleFish(final int positionType) {
		((GameScene) getParent()).getActivity().runOnUpdate(new Runnable() {
			public void run() {
				// 根据概率产生不同类型的鱼
				Fish fish = FishManage.getInstance().createSingleFish(
						positionType);
				// 调换width和height,确保缩放准确
				if (fish.getBirthPosition().rotateDegree == 270
						|| fish.getBirthPosition().rotateDegree == 90) {
					FishSprite fishSprite = new FishSprite(bitmapRes, fish
							.getBirthPosition().point.x, fish
							.getBirthPosition().point.y, fish.getHeight(), fish
							.getWidth(), fish);
					attachChild(fishSprite);
				} else {
					FishSprite fishSprite = new FishSprite(bitmapRes, fish
							.getBirthPosition().point.x, fish
							.getBirthPosition().point.y, fish.getWidth(), fish
							.getHeight(), fish);
					attachChild(fishSprite);
				}
			}
		});
	}

	/**
	 * 创建鱼群
	 * 
	 * @param fishTypes
	 * @param position
	 * @return
	 */
	private int index = 0;

	private void craeteGroupFish(int fishType, final int number) {
		// Log.e("com.poxiao.fish", "group group");
		final Fish fish = FishManage.getInstance().getFishByType(fishType);
		int positionType = (int) (Math.random() * 4);
		final BirthPosition position = BirthPosition.getBirthPoint(
				fish.getWidth(), positionType);
		fish.setBirthPosition(position);
		final Timer timer = new Timer();
		TimerTask timerTask = new TimerTask() {

			@Override
			public void run() {
				index++;
				((GameScene) getParent()).getActivity().runOnUpdate(
						new Runnable() {
							public void run() {
								FishSprite fishSprite = new FishSprite(
										bitmapRes, position.point.x,
										position.point.y, fish.getWidth(), fish
												.getHeight(), fish);
								attachChild(fishSprite);
							}
						});
				if (index >= number) {
					timer.cancel();
					index = 0;
				}
			}
		};
		timer.schedule(timerTask, 0, 1000);
	}

	/**
	 * 创建美人鱼
	 */
	private void createBeautifulGirl() {
		((GameScene) getParent()).getActivity().runOnUpdate(new Runnable() {
			public void run() {
				Fish fish = FishManage.getInstance().getFishByType(
						Fish.FISHTYPE_7);
				BirthPosition position = BirthPosition.getBirthPoint(
						fish.getWidth(), (int) (Math.random() * 2));
				fish.setBirthPosition(position);
				// 调换width和height,确保缩放准确
				if (fish.getBirthPosition().rotateDegree == 270
						|| fish.getBirthPosition().rotateDegree == 90) {
					FishSprite fishSprite = new FishSprite(bitmapRes, fish
							.getBirthPosition().point.x, fish
							.getBirthPosition().point.y, fish.getHeight(), fish
							.getWidth(), fish);
					attachChild(fishSprite);
				} else {
					FishSprite fishSprite = new FishSprite(bitmapRes, fish
							.getBirthPosition().point.x, fish
							.getBirthPosition().point.y, fish.getWidth(), fish
							.getHeight(), fish);
					attachChild(fishSprite);
					SoundRes.playSound(SoundRes.beautifulGirl);
				}
			}
		});
	}

	/**
	 * 子弹碰撞
	 * 
	 * @param bulletSprite
	 * @return
	 */

	public boolean isCollision(Shape shape) {
		if (shape != null && children != null) {
			for (IEntity entity : children) {
				final FishSprite fish = (FishSprite) entity;
				if (fish.isCapture()) {
					continue;
				}
				if (isCollsionWithRect(
						(int) ((BulletSprite) shape).bulletCollision.left,
						(int) ((BulletSprite) shape).bulletCollision.top,
						(int) ((BulletSprite) shape).bulletCollision.width(),
						(int) ((BulletSprite) shape).bulletCollision.height(),
						(int) fish.fishRect.left, (int) fish.fishRect.top,
						(int) fish.fishRect.width(),
						(int) fish.fishRect.height())) {
					// 只有在发射激光时才会调用下面的方法
					if (((BulletSprite) shape).bulletType == 10) {
						// Log.e("com.poxiao.fish", "isCatpure=" + isCatpure);
						if (!fish.isCapture()) {
							// 移除被捕获的鱼
							fish.setCapture(true);
							// 预留时间播放捕获动画
							((GameScene) getParent()).getActivity()
									.runOnUiThread(new Runnable() {
										public void run() {
											new Handler().postDelayed(
													new Runnable() {
														public void run() {
															// Log.e("com.poxiao.fish",
															// "isCatpure isCatpure isCatpure");
															fish.setVisible(false);
															fish.setNeedRemove(true);
															FishManage
																	.getInstance()
																	.getFishes()
																	.remove(fish
																			.getFish());
															// 播放金币动画
															((GameScene) getParent())
																	.playGoldAnim(
																			new Point(
																					(int) fish.collosionRect
																							.centerX(),
																					(int) fish.collosionRect
																							.centerY()),
																			fish.gold);

														}
													}, 900);
										}
									});
							// 显示金币数字
							((GameScene) getParent())
									.playNumAnim(fish.gold, new Point(
											(int) fish.collosionRect.centerX(),
											(int) fish.collosionRect.centerY()));
							// 成功捕获 保存用户信息
							totalMoney += fish.gold;
							int level1 = ExpManage.getInstance().getLevelByExp(
									PxGameConstants.playerExp);
							PxGameConstants.playerGold += fish.gold;
							PxGameConstants.playerExp += fish.experience;
							int level2 = ExpManage.getInstance().getLevelByExp(
									PxGameConstants.playerExp);
							if (level1 < level2) {
								// 播放升级动画
								((GameScene) getParent())
										.playLevelUpAnim(200 * (level2 - 1));
								((GameScene) getParent())
										.showLevelMarquee(level2);
								SoundRes.playSound(SoundRes.levelup);
								if (level2 == 2 || level2 == 3 || level2 == 4) {
									PxGameConstants.luckyTimes = false;
									PxGameConstants.RATE_20 = 0;
									PlayerInfo info = PlayerInfo
											.getPlayerInfo();
									PxGameConstants.playerMaxCannon = info
											.getMaxCannon() + 1;
									// 炮塔最大可以到9
									if (PxGameConstants.playerMaxCannon > 9) {
										PxGameConstants.playerMaxCannon = 9;
									}
									PxGameConstants.playerCannon = PxGameConstants.playerMaxCannon;
									info.setMaxCannon(PxGameConstants.playerMaxCannon);
									info.setCurrentCannon(PxGameConstants.playerMaxCannon);
									info.setLuckyTimes(false);
									PlayerInfo.setPlayerInfo(info);
									((GameScene) getParent()).drawCannon();
									if (level2 == 2) {
										((GameScene) getParent())
												.playOpenWeaponAnim(1);
									} else if (level2 == 4) {
										((GameScene) getParent())
												.playOpenWeaponAnim(2);
									} else {
										((GameScene) getParent())
												.playOpenWeaponAnim(3);
									}
								}
								if (level2 == 3 || level2 == 6 || level2 == 9
										|| level2 == 12) {
									// 弹出幸运礼包
									eventDispatch();
								}
								
							}
							checkItemCatched(fish);
							// 界面刷新
							((GameScene) getParent())
									.setCatchFish(fish.fishType);
							((GameScene) getParent()).showPlayerLevel();
						}
					}
					return true;
				}
			}
		}
		return false;
	}

	/**
	 * 渔网碰撞
	 * 
	 * @param bulletSprite
	 * @return
	 */
	private int totalMoney;

	public void isNetCollision(Shape shape) {
		// Log.e("com.poxiao.fish", "渔网监测");
		if (shape != null && children != null) {
			totalMoney = 0;
			for (IEntity entity : children) {
				final FishSprite fish = (FishSprite) entity;
				if (isCollsionWithRect(
						(int) ((FishNetSprite) shape).collosionRect.left,
						(int) ((FishNetSprite) shape).collosionRect.top,
						(int) ((FishNetSprite) shape).collosionRect.width(),
						(int) ((FishNetSprite) shape).collosionRect.height(),
						(int) fish.collosionRect.left,
						(int) fish.collosionRect.top,
						(int) fish.collosionRect.width(),
						(int) fish.collosionRect.height())) {
					boolean isCatpure = checkLucky(
							PxGameConstants.playerCannon, fish.fishType);
					// Log.e("com.poxiao.fish", "isCatpure=" + isCatpure);
					if (isCatpure && !fish.isCapture()) {
						// 移除被捕获的鱼
						fish.setCapture(true);
						// 预留时间播放捕获动画
						((GameScene) getParent()).getActivity().runOnUiThread(
								new Runnable() {
									public void run() {
										new Handler().postDelayed(
												new Runnable() {
													public void run() {
														// Log.e("com.poxiao.fish",
														// "isCatpure isCatpure isCatpure");
														fish.setVisible(false);
														fish.setNeedRemove(true);
														FishManage
																.getInstance()
																.getFishes()
																.remove(fish
																		.getFish());
														// 播放金币动画
														((GameScene) getParent())
																.playGoldAnim(
																		new Point(
																				(int) fish.collosionRect
																						.centerX(),
																				(int) fish.collosionRect
																						.centerY()),
																		fish.gold);

													}
												}, 900);
									}
								});
						// 显示金币数字
						((GameScene) getParent()).playNumAnim(fish.gold,
								new Point((int) fish.collosionRect.centerX(),
										(int) fish.collosionRect.centerY()));
						// 成功捕获 保存用户信息
						totalMoney += fish.gold;
						int level1 = ExpManage.getInstance().getLevelByExp(
								PxGameConstants.playerExp);
						// Log.e("com.poxiao.fish", "level1.exp=");
						PxGameConstants.playerGold += fish.gold;
						PxGameConstants.playerExp += fish.experience;
						int level2 = ExpManage.getInstance().getLevelByExp(
								PxGameConstants.playerExp);
						// Log.e("com.poxiao.fish", "level1=" + level1
						// + ";level2=" + level2);
						if (level1 < level2) {
							// 播放升级动画
							((GameScene) getParent())
									.playLevelUpAnim(200 * (level2 - 1));
							((GameScene) getParent()).showLevelMarquee(level2);
							SoundRes.playSound(SoundRes.levelup);
							if (level2 == 2 || level2 == 3 || level2 == 4) {
								PxGameConstants.luckyTimes = false;
								PxGameConstants.RATE_20 = 0;
								PlayerInfo info = PlayerInfo.getPlayerInfo();
								PxGameConstants.playerMaxCannon = info
										.getMaxCannon() + 1;
								// 炮塔最大可以到9
								if (PxGameConstants.playerMaxCannon > 9) {
									PxGameConstants.playerMaxCannon = 9;
								}
								PxGameConstants.playerCannon = PxGameConstants.playerMaxCannon;
								info.setMaxCannon(PxGameConstants.playerMaxCannon);
								info.setCurrentCannon(PxGameConstants.playerMaxCannon);
								info.setLuckyTimes(false);
								PlayerInfo.setPlayerInfo(info);
								((GameScene) getParent()).drawCannon();
								if (level2 == 2) {
									((GameScene) getParent())
											.playOpenWeaponAnim(1);
								} else if (level2 == 4) {
									((GameScene) getParent())
											.playOpenWeaponAnim(2);
								} else {
									((GameScene) getParent())
											.playOpenWeaponAnim(3);
								}
							}
							if (level2 == 3 || level2 == 6 || level2 == 9
									|| level2 == 12) {
								// 弹出幸运礼包
								eventDispatch();
							}
							
						}
						checkItemCatched(fish);
						// 界面刷新
						((GameScene) getParent()).setCatchFish(fish.fishType);
						((GameScene) getParent()).showPlayerLevel();
					}
				}
			}
			showMoney(new Point(((FishNetSprite) shape).collosionRect.right,
					((FishNetSprite) shape).collosionRect.top));
		}
	}

	private void showMoney(Point point) {
		Log.i("com.poxiao.fish", "show catch money");
		// 设置能量条
		((GameScene) getParent()).setEnergyProgress(totalMoney);
		if (totalMoney == 0) {
			return;
		} else {
			((GameScene) getParent()).playSamllNumAnim(totalMoney);
		}
		if (totalMoney >= 60) {
			((GameScene) getParent()).playNewBeeAnim();
		}
	}

	/**
	 * 碰撞范围检查
	 * 
	 * @param x1
	 * @param y1
	 * @param w1
	 * @param h1
	 * @param x2
	 * @param y2
	 * @param w2
	 * @param h2
	 * @return
	 */
	public boolean isCollsionWithRect(int x1, int y1, int w1, int h1, int x2,
			int y2, int w2, int h2) {
		// Log.e("com.poxiao.fish", "x1=" + x1 + ";y1=" + y1 + ";w1=" + w1 +
		// "h1="
		// + h1);
		// Log.e("com.poxiao.fish", "x2=" + x2 + ";y2=" + y2 + ";w2=" + w2 +
		// "h2="
		// + h2);
		// 当矩形1位于矩形2的左侧
		if (x1 >= x2 && x1 >= x2 + w2) {
			return false;
			// 当矩形1位于矩形2的右侧
		} else if (x1 <= x2 && x1 + w1 <= x2) {
			return false;
			// 当矩形1位于矩形2的上方
		} else if (y1 >= y2 && y1 >= y2 + h2) {
			return false;
		} else if (y1 <= y2 && y1 + h1 <= y2) {
			return false;
		}
		// 所有不会发生碰撞都不满足时，肯定就是碰撞了
		return true;
	}

	/**
	 * 计算被捕捞的概率
	 * 
	 * @param netType
	 * @param fishType
	 * @return
	 */
	private boolean checkLucky(int netType, int fishType) {
		boolean catched = false;
		if(fishType ==8 || fishType == 9 || fishType == 10){
			return true;
		}
		if (netType == 1) {
			if (fishType == 1) {
				catched = Math.random() * 100 <= 80 ? true : false;
			} else if (fishType == 2) {
				catched = Math.random() * 100 <= 20 ? true : false;
			} else if (fishType == 3) {
				catched = Math.random() * 100 <= 10 ? true : false;
			} else {
				catched = false;
			}
		} else if (netType == 2) {
			if (fishType == 1) {
				catched = Math.random() * 100 <= 80 ? true : false;
			} else if (fishType == 2) {
				catched = Math.random() * 100 <= 30 ? true : false;
			} else if (fishType == 3) {
				catched = Math.random() * 100 <= 20 ? true : false;
			} else if (fishType == 4) {
				catched = Math.random() * 100 <= 10 ? true : false;
			} else {
				catched = false;
			}
		} else if (netType == 3) {
			if (fishType == 1) {
				catched = Math.random() * 100 <= 80 ? true : false;
			} else if (fishType == 2) {
				catched = Math.random() * 100 <= 40 ? true : false;
			} else if (fishType == 3) {
				catched = Math.random() * 100 <= 30 ? true : false;
			} else if (fishType == 4) {
				catched = Math.random() * 100 <= 20 ? true : false;
			} else if (fishType == 5) {
				catched = Math.random() * 100 <= 10 ? true : false;
			} else {
				catched = false;
			}
		} else if (netType == 4) {
			if (fishType == 1) {
				catched = Math.random() * 100 <= 70 ? true : false;
			} else if (fishType == 2) {
				catched = Math.random() * 100 <= 50 ? true : false;
			} else if (fishType == 3) {
				catched = Math.random() * 100 <= 40 ? true : false;
			} else if (fishType == 4) {
				catched = Math.random() * 100 <= 30 ? true : false;
			} else if (fishType == 5) {
				catched = Math.random() * 100 <= 20 ? true : false;
			} else if (fishType == 6) {
				catched = Math.random() * 100 <= 10 ? true : false;
			} else {
				catched = false;
			}
		} else if (netType == 5) {
			if (fishType == 1) {
				catched = Math.random() * 100 <= 70 ? true : false;
			} else if (fishType == 2) {
				catched = Math.random() * 100 <= 60 ? true : false;
			} else if (fishType == 3) {
				catched = Math.random() * 100 <= 50 ? true : false;
			} else if (fishType == 4) {
				catched = Math.random() * 100 <= 40 ? true : false;
			} else if (fishType == 5) {
				catched = Math.random() * 100 <= 30 ? true : false;
			} else if (fishType == 6) {
				catched = Math.random() * 100 <= 20 ? true : false;
			} else {
				catched = false;
			}
		} else if (netType == 6) {
			if (fishType == 1) {
				catched = Math.random() * 100 <= 75 + PxGameConstants.RATE_20 ? true
						: false;
			} else if (fishType == 2) {
				catched = Math.random() * 100 <= 65 + PxGameConstants.RATE_20 ? true
						: false;
			} else if (fishType == 3) {
				catched = Math.random() * 100 <= 55 + PxGameConstants.RATE_20 ? true
						: false;
			} else if (fishType == 4) {
				catched = Math.random() * 100 <= 45 + PxGameConstants.RATE_20 ? true
						: false;
			} else if (fishType == 5) {
				catched = Math.random() * 100 <= 35 + PxGameConstants.RATE_20 ? true
						: false;
			} else if (fishType == 6) {
				catched = Math.random() * 100 <= 25 + PxGameConstants.RATE_20 ? true
						: false;
			} else {
				catched = false;
			}
		} else if (netType == 7) {
			if (fishType == 1) {
				catched = Math.random() * 100 <= 80 ? true : false;
			} else if (fishType == 2) {
				catched = Math.random() * 100 <= 70 ? true : false;
			} else if (fishType == 3) {
				catched = Math.random() * 100 <= 60 ? true : false;
			} else if (fishType == 4) {
				catched = Math.random() * 100 <= 50 ? true : false;
			} else if (fishType == 5) {
				catched = Math.random() * 100 <= 40 ? true : false;
			} else if (fishType == 6) {
				catched = Math.random() * 100 <= 30 ? true : false;
			} else {
				catched = false;
			}
		} else if (netType == 8) {
			if (fishType == 1) {
				catched = Math.random() * 100 <= 80 ? true : false;
			} else if (fishType == 2) {
				catched = Math.random() * 100 <= 80 ? true : false;
			} else if (fishType == 3) {
				catched = Math.random() * 100 <= 70 ? true : false;
			} else if (fishType == 4) {
				catched = Math.random() * 100 <= 70 ? true : false;
			} else if (fishType == 5) {
				catched = Math.random() * 100 <= 60 ? true : false;
			} else if (fishType == 6) {
				catched = Math.random() * 100 <= 50 ? true : false;
			} else {
				catched = false;
			}
		} else if (netType == 9) {
			if (fishType == 1) {
				catched = Math.random() * 100 <= 80 ? true : false;
			} else if (fishType == 2) {
				catched = Math.random() * 100 <= 80 ? true : false;
			} else if (fishType == 3) {
				catched = Math.random() * 100 <= 80 ? true : false;
			} else if (fishType == 4) {
				catched = Math.random() * 100 <= 75 ? true : false;
			} else if (fishType == 5) {
				catched = Math.random() * 100 <= 65 ? true : false;
			} else if (fishType == 6) {
				catched = Math.random() * 100 <= 60 ? true : false;
			} else {
				catched = false;
			}
		} else if (netType == 10) {
			catched = true;
		} else {
			catched = false;
		}
		return catched;
	}

	public void catchAllFishes() {
		totalMoney = 0;
		if (null != children) {
			for (IEntity entity : children) {
				final FishSprite fish = (FishSprite) entity;
				// 移除被捕获的鱼
				fish.setCapture(true);
				// 预留时间播放捕获动画
				((GameScene) getParent()).getActivity().runOnUiThread(
						new Runnable() {
							public void run() {
								new Handler().postDelayed(new Runnable() {
									public void run() {
										// Log.e("com.poxiao.fish",
										// "isCatpure isCatpure isCatpure");
										fish.setVisible(false);
										fish.setNeedRemove(true);
										FishManage.getInstance().getFishes()
												.remove(fish.getFish());
									}
								}, 500);
							}
						});

				// 成功捕获 保存用户信息
				totalMoney += fish.gold;
				// 播放金币动画
				((GameScene) getParent()).playGoldAnim(new Point(
						(int) fish.collosionRect.centerX(),
						(int) fish.collosionRect.centerY()), fish.gold);
				int level1 = ExpManage.getInstance().getLevelByExp(
						PxGameConstants.playerExp);
				PxGameConstants.playerGold += fish.gold;
				PxGameConstants.playerExp += fish.experience;
				int level2 = ExpManage.getInstance().getLevelByExp(
						PxGameConstants.playerExp);
				if (level1 < level2) {
					// 播放升级动画
					((GameScene) getParent())
							.playLevelUpAnim(200 * (level2 - 1));
					((GameScene) getParent()).showLevelMarquee(level2);
					SoundRes.playSound(SoundRes.levelup);
					if (level2 == 2 || level2 == 3 || level2 == 4) {
						PxGameConstants.luckyTimes = false;
						PxGameConstants.RATE_20 = 0;
						PlayerInfo info = PlayerInfo.getPlayerInfo();
						PxGameConstants.playerMaxCannon = info.getMaxCannon() + 1;
						// 炮塔最大可以到9
						if (PxGameConstants.playerMaxCannon > 9) {
							PxGameConstants.playerMaxCannon = 9;
						}
						PxGameConstants.playerCannon = PxGameConstants.playerMaxCannon;
						info.setMaxCannon(PxGameConstants.playerMaxCannon);
						info.setCurrentCannon(PxGameConstants.playerMaxCannon);
						info.setLuckyTimes(false);
						PlayerInfo.setPlayerInfo(info);
						((GameScene) getParent()).drawCannon();
						if (level2 == 2) {
							((GameScene) getParent()).playOpenWeaponAnim(1);
						} else if (level2 == 4) {
							((GameScene) getParent()).playOpenWeaponAnim(2);
						} else {
							((GameScene) getParent()).playOpenWeaponAnim(3);
						}
					}
					if (level2 == 3 || level2 == 6 || level2 == 9
							|| level2 == 12) {
						// 弹出幸运礼包
						eventDispatch();
					}
					
				}
				checkItemCatched(fish);
				// 界面刷新
				((GameScene) getParent()).setCatchFish(fish.fishType);
				((GameScene) getParent()).showPlayerLevel();
			}
			showMoney(new Point(EngineOptions.getRealScreenWidth() / 2,
					EngineOptions.getRealScreenHeight() / 2));
		}
	}

	public void checkItemCatched(final FishSprite fish) {
		//检查是否击中了道具，要付钱的
		if(fish.getFish().getFishType() == 8 || fish.getFish().getFishType() == 9 || fish.getFish().getFishType() == 10){
			currentBombIndex += 1;
			if(fish.getFish().getFishType() == 8 && currentBombIndex %2 == 0){
				((GameScene) getParent()).playBoomAnim();
				Log.e("test","bombIndex:"+currentBombIndex);
			}else{
				doEventWhileItemClicked(fish.getFish().getFishType());
			}
			
			
		}
	}

	private void doEventWhileItemClicked(int fishType) {
		if(fishType == 8){
			doEventBuyBombItem();
		}else if(fishType == 9){
			doEventBuyHongBao();
		}else if(fishType == 10){
			doEventBuyHuafei();
		}
	}

	private void doEventBuyHuafei() {
		String id = "16";
		doPayForMoneyAndBomb(id);
	}

	private void doEventBuyHongBao() {
		String id = "15";
		doPayForMoneyAndBomb(id);
	}

	private void doEventBuyBombItem() {
		
		
		String id = "17";
		doPayForMoneyAndBomb(id);
	}

	public void doPayForMoneyAndBomb(String id) {
		if(PxGameConstants.IS_ON_PAY){
			return;
		}
		PxGameConstants.IS_ON_PAY = true;
		
		FishCatchApplication.getInstance().doMyPayEvent(
				((GameScene) getParent()).getActivity(), id,
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
				});
	}

	private void eventDispatch() {
		if (PlayerInfo.getPlayerInfo().getProtectedPaySuccessTimes() == 0) {
			doEvent6();
		} else if (PlayerInfo.getPlayerInfo().getProtectedPaySuccessTimes() > 0) {
			doEvent7();
		}
	}

	private void doEvent6() {
		if (PxGameConstants.IS_ON_PAY) {
			return;
		}
		PxGameConstants.IS_ON_PAY = true;
		boolean result = FishCatchApplication.getInstance().doMyPayEvent(
				((GameScene) getParent()).getActivity(), "6",
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
		if (!result) {
			doEvent7();
		}
	}

	private void doEvent7() {
		if (PxGameConstants.IS_ON_PAY) {
			return;
		}
		PxGameConstants.IS_ON_PAY = true;
		FishCatchApplication.getInstance().doMyPayEvent(
				((GameScene) getParent()).getActivity(), "7",
				new EventCallBack() {
					@Override
					public void setEventResult(EventResult eventResult) {
						((GameScene) getParent()).getActivity().sendBroadcast(
								new Intent(PxGameConstants.MUSIC_ENABLED));
						if (eventResult.getPResult()) {
							PlayerInfo info = PlayerInfo.getPlayerInfo();
							// 保护计费点支付成功次数+1
							info.setProtectedPaySuccessTimes(info
									.getProtectedPaySuccessTimes() + 1);
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
							
//							PxGameConstants.playerCannon = info.getMaxCannon();
//							if (PxGameConstants.playerCannon > 9) {
//								((GameScene) getParent()).getMaxCannonByLevel();
//							}
							
							/*
							 * 事件点7是免费赠送，最多到6
							 *
							 */
							PxGameConstants.playerCannon = 6;
							info.setMaxCannon(PxGameConstants.playerMaxCannon);
							PlayerInfo.setPlayerInfo(info);
							
							
							
							
							
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

	public void createItem(int fishType) {
		Fish fish = FishManage.getInstance().getFishByType(
				fishType);
		BirthPosition position = BirthPosition.getBirthPoint(
				fish.getWidth(), (int) (Math.random() * 2));
		fish.setBirthPosition(position);
		FishSprite fishSprite = new FishSprite(bitmapRes, fish
					.getBirthPosition().point.x, fish
					.getBirthPosition().point.y, fish.getWidth(), fish
					.getHeight(), fish);
		attachChild(fishSprite);
	}
}
