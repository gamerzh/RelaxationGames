package com.xiao.fish.domain.fish.allfish;

import com.xiao.fish.domain.fish.Fish;
import com.xiao.fish.game.res.FishGameRes;

public class Fish2 extends Fish {

	public Fish2() {
		super();
		this.fishType=Fish.FISHTYPE_2;
		this.width = 63;
		this.height = 43;
		this.gold = 8;
		this.experience = 4;
		this.speed = 4 + Fish.getRandomNumber(-3, 6);
		this.catchTime=0.2f;
		this.anims = new int[] { FishGameRes.KEY_FISH_2_1,
				FishGameRes.KEY_FISH_2_2, FishGameRes.KEY_FISH_2_3,
				FishGameRes.KEY_FISH_2_4, FishGameRes.KEY_FISH_2_5,
				FishGameRes.KEY_FISH_2_6, FishGameRes.KEY_FISH_2_7,
				FishGameRes.KEY_FISH_2_8, FishGameRes.KEY_FISH_2_9,
				FishGameRes.KEY_FISH_2_10 };
		this.animTime = new float[] { 
				0.06f,  0.06f,
				0.06f,  0.06f,
				0.06f,  0.06f,
				0.06f,  0.06f,
				0.06f,  0.06f, };
		this.catchAnims = new int[] { FishGameRes.KEY_CATCH_2_1,
				FishGameRes.KEY_CATCH_2_2 };
	}

}
