package com.xiao.fish.domain.bullet.allbullet;

import com.xiao.fish.domain.bullet.Bullet;
import com.xiao.fish.game.res.FishGameRes;

public class Bullet7 extends Bullet {

	public Bullet7() {
		super();
		this.bulletSpeed = 18;
		this.bulletType = 7;
		this.width = 29;
		this.height = 50;
		this.goldConsume = 60;
		this.bulletBitmap = FishGameRes.KEY_GAME_BULLET_6;
	}
}
