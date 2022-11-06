package com.xiao.fish.domain.bullet.allbullet;

import com.xiao.fish.domain.bullet.Bullet;
import com.xiao.fish.game.res.FishGameRes;

public class Bullet5 extends Bullet {

	public Bullet5() {
		super();
		this.bulletSpeed = 18;
		this.bulletType = 5;
		this.width = 24;
		this.height = 50;
		this.goldConsume = 20;
		this.bulletBitmap=FishGameRes.KEY_GAME_BULLET_5;
	}
}
