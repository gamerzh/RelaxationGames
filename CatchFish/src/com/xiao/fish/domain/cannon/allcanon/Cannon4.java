package com.xiao.fish.domain.cannon.allcanon;

import com.xiao.fish.domain.cannon.Cannon;
import com.xiao.fish.domain.cannon.CannonManage;
import com.xiao.fish.game.res.FishGameRes;

public class Cannon4 extends Cannon {

	public Cannon4() {
		super();
		this.type = CannonManage.CANNON_TYPE_4;
		this.goldRate = 1;
		this.bitmapID = FishGameRes.KEY_GAME_CANNON_4;
		this.headBimapID=FishGameRes.KEY_GAME_CANNON_4_HEAD;
		this.width=83;
		this.height=66;
		this.head_width=32;
		this.head_height=30;
	}

}
