package com.xiao.fish.domain.cannon.allcanon;

import com.xiao.fish.domain.cannon.Cannon;
import com.xiao.fish.domain.cannon.CannonManage;
import com.xiao.fish.game.res.FishGameRes;

public class Cannon10 extends Cannon {
	public Cannon10() {
		super();
		this.type = CannonManage.CANNON_TYPE_10;
		this.goldRate = 100;
		this.bitmapID = FishGameRes.KEY_GAME_CANNON_10;
		this.headBimapID = -999;
		this.width=63;
		this.height=130;
		this.head_width=0;
		this.head_height=0;
	}
}
