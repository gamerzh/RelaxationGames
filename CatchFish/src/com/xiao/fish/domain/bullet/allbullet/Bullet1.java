package com.xiao.fish.domain.bullet.allbullet;

import com.xiao.fish.domain.bullet.Bullet;
import com.xiao.fish.game.res.FishGameRes;

public class Bullet1 extends Bullet {

	public Bullet1() {
		super();
		this.bulletSpeed = 18;
		this.bulletType = 1;
		this.width = 24;
		this.height = 50;
		this.goldConsume = 1;
		this.bulletBitmap = FishGameRes.KEY_GAME_BULLET_1;
	}
}
