package com.xiao.fish.domain.cannon.allcanon;

import com.xiao.fish.domain.cannon.Cannon;
import com.xiao.fish.domain.cannon.CannonManage;
import com.xiao.fish.game.res.FishGameRes;

public class Cannon2 extends Cannon {

	public Cannon2() {
		super();
		this.type = CannonManage.CANNON_TYPE_2;
		this.goldRate = 1;
		this.bitmapID = FishGameRes.KEY_GAME_CANNON_2;
		this.headBimapID=FishGameRes.KEY_GAME_CANNON_2_HEAD;
		this.width=83;
		this.height=66;
		this.head_width=32;
		this.head_height=30;
	}

}
