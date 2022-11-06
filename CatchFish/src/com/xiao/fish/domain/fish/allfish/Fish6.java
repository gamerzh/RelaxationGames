package com.xiao.fish.domain.fish.allfish;

import com.xiao.fish.domain.fish.Fish;
import com.xiao.fish.game.res.FishGameRes;

public class Fish6 extends Fish {

	public Fish6() {
		super();
		this.fishType = Fish.FISHTYPE_6;
		this.width = 161;// 图片的宽高
		this.height = 118;
		this.gold = 100;
		this.experience = 64;
		this.speed = 2 + Fish.getRandomNumber(0, 2);
		this.catchTime = 0.2f;
		this.anims = new int[] { FishGameRes.KEY_FISH_6_1,
				FishGameRes.KEY_FISH_6_2, FishGameRes.KEY_FISH_6_3,
				FishGameRes.KEY_FISH_6_4, FishGameRes.KEY_FISH_6_5,
				FishGameRes.KEY_FISH_6_6, FishGameRes.KEY_FISH_6_7,
				FishGameRes.KEY_FISH_6_8, FishGameRes.KEY_FISH_6_9,
				FishGameRes.KEY_FISH_6_10, FishGameRes.KEY_FISH_6_11,
				FishGameRes.KEY_FISH_6_12, FishGameRes.KEY_FISH_6_13,
				FishGameRes.KEY_FISH_6_14 };
		this.animTime = new float[] { 
				0.1f,  0.1f,
				0.1f,  0.1f,
				0.1f,  0.1f,
				0.1f,  0.1f,
				0.1f,  0.1f,
				0.1f,  0.1f,
				0.1f,  0.1f};
		this.catchAnims = new int[] { FishGameRes.KEY_CATCH_6_1,
				FishGameRes.KEY_CATCH_6_2, FishGameRes.KEY_CATCH_6_3,
				FishGameRes.KEY_CATCH_6_4, FishGameRes.KEY_CATCH_6_5,
				FishGameRes.KEY_CATCH_6_6 };
	}

}
