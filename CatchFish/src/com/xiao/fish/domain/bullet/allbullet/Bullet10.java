package com.xiao.fish.domain.bullet.allbullet;

import com.xiao.fish.domain.bullet.Bullet;
import com.xiao.fish.game.res.FishGameRes;

public class Bullet10 extends Bullet {

	public Bullet10() {
		super();
		this.bulletSpeed = 18;
		this.bulletType = 10;
		this.width = 157;
		this.height = 575;
		this.goldConsume = 0;
		this.bulletBitmap = FishGameRes.KEY_GAME_LASER_1;
	}
}
