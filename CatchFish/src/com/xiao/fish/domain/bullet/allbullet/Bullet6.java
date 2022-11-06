package com.xiao.fish.domain.bullet.allbullet;

import com.xiao.fish.domain.bullet.Bullet;
import com.xiao.fish.game.res.FishGameRes;

public class Bullet6 extends Bullet {

	public Bullet6() {
		super();
		this.bulletSpeed = 18;
		this.bulletType = 6;
		this.width = 24;
		this.height = 50;
		this.goldConsume = 24;
		this.bulletBitmap = FishGameRes.KEY_GAME_BULLET_6;
	}
}
