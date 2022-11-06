package com.xiao.fish.domain.fish.allfish;

import com.xiao.fish.domain.fish.Fish;
import com.xiao.fish.game.res.FishGameRes;

public class Fish3 extends Fish {

	public Fish3() {
		super();
		this.fishType=Fish.FISHTYPE_3;
		this.width = 68;
		this.height = 64;
		this.gold = 12;
		this.experience = 8;
		this.speed = 4 + Fish.getRandomNumber(-1, 2);
		this.catchTime=0.2f;
		this.anims = new int[] { FishGameRes.KEY_FISH_3_1,
				FishGameRes.KEY_FISH_3_2, FishGameRes.KEY_FISH_3_3,
				FishGameRes.KEY_FISH_3_4, FishGameRes.KEY_FISH_3_5,
				FishGameRes.KEY_FISH_3_6, FishGameRes.KEY_FISH_3_7,
				FishGameRes.KEY_FISH_3_8 };
		this.animTime = new float[] { 
				0.1f,  0.1f,
				0.1f,  0.1f,
				0.2f,  0.1f,
				0.1f,  0.1f,};
		this.catchAnims = new int[] { FishGameRes.KEY_CATCH_3_1,
				FishGameRes.KEY_CATCH_3_2, FishGameRes.KEY_CATCH_3_3,
				FishGameRes.KEY_CATCH_3_4, FishGameRes.KEY_CATCH_3_5,
				FishGameRes.KEY_CATCH_3_6, FishGameRes.KEY_CATCH_3_7,
				FishGameRes.KEY_CATCH_3_8 };
	}

}
