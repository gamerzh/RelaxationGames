package com.xiao.fish.domain.fish.allfish;

import com.xiao.fish.domain.fish.Fish;
import com.xiao.fish.game.res.FishGameRes;

public class Fish4 extends Fish {

	public Fish4() {
		super();
		this.fishType=Fish.FISHTYPE_4;
		this.width = 90;//图片的宽高
		this.height = 86;
		this.gold = 20;
		this.experience = 16;
		this.speed = 1+ Fish.getRandomNumber(0, 2);
		this.catchTime=0.2f;
		this.anims = new int[] { FishGameRes.KEY_FISH_4_1,
				FishGameRes.KEY_FISH_4_2, FishGameRes.KEY_FISH_4_3,
				FishGameRes.KEY_FISH_4_4, FishGameRes.KEY_FISH_4_5,
				FishGameRes.KEY_FISH_4_6, FishGameRes.KEY_FISH_4_7,
				FishGameRes.KEY_FISH_4_8, FishGameRes.KEY_FISH_4_9,
				FishGameRes.KEY_FISH_4_10 };
		this.animTime = new float[] { 
				0.15f,  0.15f,
				0.15f,  0.15f,
				0.15f,  0.15f,
				0.15f,  0.6f,
				0.15f,  0.15f, };
		this.catchAnims = new int[] { FishGameRes.KEY_CATCH_4_1,
				FishGameRes.KEY_CATCH_4_2 ,FishGameRes.KEY_CATCH_4_3};
	}

}
