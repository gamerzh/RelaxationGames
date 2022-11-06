package com.xiao.fish.domain.fish.allfish;

import com.xiao.fish.domain.fish.Fish;
import com.xiao.fish.game.res.FishGameRes;

public class Fish1 extends Fish {

	public Fish1() {
		super();
		this.fishType = Fish.FISHTYPE_1;
		this.width = 40;// 图片的宽高
		this.height = 21;
		this.gold = 4;
		this.experience = 2;
		this.speed = 6 + Fish.getRandomNumber(-1, 5);
		this.catchTime = 0.2f;
		this.anims = new int[] { FishGameRes.KEY_FISH_1_1,
				FishGameRes.KEY_FISH_1_2, FishGameRes.KEY_FISH_1_3,
				FishGameRes.KEY_FISH_1_4, FishGameRes.KEY_FISH_1_5,
				FishGameRes.KEY_FISH_1_6, FishGameRes.KEY_FISH_1_7,
				FishGameRes.KEY_FISH_1_8, FishGameRes.KEY_FISH_1_9,
				FishGameRes.KEY_FISH_1_10 };
		this.animTime = new float[] { 
				 0.04f, 0.04f,
				 0.04f, 0.04f,
				 0.04f, 0.04f,
				 0.04f, 0.04f,
				 0.04f, 0.04f };
		this.catchAnims = new int[] { FishGameRes.KEY_CATCH_1_1,
				FishGameRes.KEY_CATCH_1_2 };
	}

}
