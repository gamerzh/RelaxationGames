package com.xiao.fish.domain.bullet.allbullet;

import com.xiao.fish.domain.bullet.Bullet;
import com.xiao.fish.game.res.FishGameRes;

public class Bullet9 extends Bullet {

	public Bullet9() {
		super();
		this.bulletSpeed = 18;
		this.bulletType = 9;
		this.width = 29;
		this.height = 50;
		this.goldConsume = 140;
		this.bulletBitmap = FishGameRes.KEY_GAME_BULLET_6;
	}
}
