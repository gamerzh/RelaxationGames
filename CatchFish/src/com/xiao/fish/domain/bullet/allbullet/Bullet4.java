package com.xiao.fish.domain.bullet.allbullet;

import com.xiao.fish.domain.bullet.Bullet;
import com.xiao.fish.game.res.FishGameRes;

public class Bullet4 extends Bullet {

	public Bullet4() {
		super();
		this.bulletSpeed = 18;
		this.bulletType = 4;
		this.width = 24;
		this.height = 50;
		this.goldConsume = 16;
		this.bulletBitmap=FishGameRes.KEY_GAME_BULLET_4;
	}
}
