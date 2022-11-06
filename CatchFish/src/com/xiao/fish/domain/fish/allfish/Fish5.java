package com.xiao.fish.domain.fish.allfish;

import com.xiao.fish.domain.fish.Fish;
import com.xiao.fish.game.res.FishGameRes;

public class Fish5 extends Fish {

	public Fish5() {
		super();
		this.fishType = Fish.FISHTYPE_5;
		this.width = 161;// 图片的宽高
		this.height = 159;
		this.gold = 40;
		this.experience = 32;
		this.speed = 2 + Fish.getRandomNumber(-1, 3);
		this.catchTime = 0.2f;
		this.anims = new int[] { FishGameRes.KEY_FISH_5_1,
				FishGameRes.KEY_FISH_5_2, FishGameRes.KEY_FISH_5_3,
				FishGameRes.KEY_FISH_5_4, FishGameRes.KEY_FISH_5_5,
				FishGameRes.KEY_FISH_5_6, FishGameRes.KEY_FISH_5_7,
				FishGameRes.KEY_FISH_5_8, FishGameRes.KEY_FISH_5_9,
				FishGameRes.KEY_FISH_5_10 };
		this.animTime = new float[] { 
				0.2f,  0.2f,
				0.2f,  0.2f,
				0.2f,  0.2f,
				0.2f,  0.2f,
				0.2f,  0.8f };
		this.catchAnims = new int[] { FishGameRes.KEY_CATCH_5_1,
				FishGameRes.KEY_CATCH_5_2, FishGameRes.KEY_CATCH_5_3,
				FishGameRes.KEY_CATCH_5_4 };
	}

}
