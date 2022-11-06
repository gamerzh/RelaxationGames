package com.xiao.fish.domain.bullet.allbullet;

import com.xiao.fish.domain.bullet.Bullet;
import com.xiao.fish.game.res.FishGameRes;

public class Bullet3 extends Bullet {

	public Bullet3() {
		super();
		this.bulletSpeed = 18;
		this.bulletType = 3;
		this.width = 24;
		this.height = 50;
		this.goldConsume = 12;
		this.bulletBitmap=FishGameRes.KEY_GAME_BULLET_3;
	}
}
