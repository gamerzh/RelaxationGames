package com.xiao.fish.domain.fish.allfish;

import com.xiao.fish.domain.fish.Fish;
import com.xiao.fish.game.res.FishGameRes;

public class Fish9 extends Fish {

	public Fish9() {
		super();
		this.fishType = Fish.FISHTYPE_9;
		this.width = 83;
		this.height = 136;
		this.gold = 10;
		this.experience = 0;
		this.speed = 2+ Fish.getRandomNumber(0, 1);
		this.catchTime = 0.2f;
		this.anims = new int[] { FishGameRes.KEY_FISH_ITEM_HONGBAO};
		this.animTime = new float[] { 
				1f};
		this.catchAnims = new int[] {
				FishGameRes.KEY_FISH_ITEM_HONGBAO};
	}

}
