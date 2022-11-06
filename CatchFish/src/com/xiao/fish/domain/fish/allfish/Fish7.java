package com.xiao.fish.domain.fish.allfish;

import com.xiao.fish.domain.fish.Fish;
import com.xiao.fish.game.res.FishGameRes;

public class Fish7 extends Fish {

	public Fish7() {
		super();
		this.fishType = Fish.FISHTYPE_7;
		this.width = 213;
		this.height = 123;
		this.gold = 300;
		this.experience = 0;
		this.speed = 2+ Fish.getRandomNumber(0, 1);
		this.catchTime = 0.2f;
		this.anims = new int[] { FishGameRes.KEY_GAME_BEAUTIFUL_GIRL_1,
				FishGameRes.KEY_GAME_BEAUTIFUL_GIRL_2,
				FishGameRes.KEY_GAME_BEAUTIFUL_GIRL_3,
				FishGameRes.KEY_GAME_BEAUTIFUL_GIRL_4,
				FishGameRes.KEY_GAME_BEAUTIFUL_GIRL_5,
				FishGameRes.KEY_GAME_BEAUTIFUL_GIRL_6,
				FishGameRes.KEY_GAME_BEAUTIFUL_GIRL_7,
				FishGameRes.KEY_GAME_BEAUTIFUL_GIRL_8,
				FishGameRes.KEY_GAME_BEAUTIFUL_GIRL_9,
				FishGameRes.KEY_GAME_BEAUTIFUL_GIRL_10,
				FishGameRes.KEY_GAME_BEAUTIFUL_GIRL_11,
				FishGameRes.KEY_GAME_BEAUTIFUL_GIRL_12,
				FishGameRes.KEY_GAME_BEAUTIFUL_GIRL_13 };
		this.animTime = new float[] { 
				0.4f,  0.2f,
				0.2f,  0.2f,
				0.2f,  0.2f,
				0.2f,  0.2f,
				0.2f,  0.2f,
				0.2f,  0.2f,
				0.2f};
		this.catchAnims = new int[] {
				FishGameRes.KEY_GAME_BEAUTIFUL_GIRL_CATCH_1,
				FishGameRes.KEY_GAME_BEAUTIFUL_GIRL_CATCH_2 };
	}

}
