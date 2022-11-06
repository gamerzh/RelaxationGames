package com.xiao.fish.domain.bullet.allbullet;

import com.xiao.fish.domain.bullet.Bullet;
import com.xiao.fish.game.res.FishGameRes;

public class Bullet2 extends Bullet {

	public Bullet2() {
		super();
		this.bulletSpeed = 18;
		this.bulletType = 2;
		this.width = 24;
		this.height = 50;
		this.goldConsume = 8;
		this.bulletBitmap=FishGameRes.KEY_GAME_BULLET_2;
	}
}
