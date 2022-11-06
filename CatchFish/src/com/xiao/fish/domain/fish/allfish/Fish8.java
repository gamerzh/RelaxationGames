package com.xiao.fish.domain.fish.allfish;

import com.xiao.fish.domain.fish.Fish;
import com.xiao.fish.game.res.FishGameRes;

public class Fish8 extends Fish {

	public Fish8() {
		super();
		this.fishType = Fish.FISHTYPE_8;
		this.width = 115;
		this.height = 115;
		this.gold = 10;
		this.experience = 0;
		this.speed = 2+ Fish.getRandomNumber(0, 1);
		this.catchTime = 0.2f;
		this.anims = new int[] { FishGameRes.KEY_FISH_ITEM_BOMB_1,
				FishGameRes.KEY_FISH_ITEM_BOMB_2,
				FishGameRes.KEY_FISH_ITEM_BOMB_3,
				FishGameRes.KEY_FISH_ITEM_BOMB_4,
				FishGameRes.KEY_FISH_ITEM_BOMB_5,
				FishGameRes.KEY_FISH_ITEM_BOMB_6,
				FishGameRes.KEY_FISH_ITEM_BOMB_7};
		this.animTime = new float[] { 
				0.15f,
				0.15f,
				0.15f,
				0.15f,
				0.15f,
				0.15f,
				0.15f
				};
		this.catchAnims = new int[] {
				FishGameRes.KEY_FISH_ITEM_BOMB_1};
	}

}
