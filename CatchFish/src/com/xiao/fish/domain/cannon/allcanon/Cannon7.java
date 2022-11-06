package com.xiao.fish.domain.cannon.allcanon;

import com.xiao.fish.domain.cannon.Cannon;
import com.xiao.fish.domain.cannon.CannonManage;
import com.xiao.fish.game.res.FishGameRes;

public class Cannon7 extends Cannon {

	public Cannon7() {
		super();
		this.type = CannonManage.CANNON_TYPE_7;
		this.goldRate = 20;
		this.bitmapID = FishGameRes.KEY_GAME_CANNON_7;
		this.headBimapID=FishGameRes.KEY_GAME_CANNON_7_HEAD;
		this.width=83;
		this.height=87;
		this.head_width=33;
		this.head_height=40;
	}

}
