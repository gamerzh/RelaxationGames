package com.xiao.fish.domain.cannon.allcanon;

import com.xiao.fish.domain.cannon.Cannon;
import com.xiao.fish.domain.cannon.CannonManage;
import com.xiao.fish.game.res.FishGameRes;

public class Cannon9 extends Cannon {

	public Cannon9() {
		super();
		this.type = CannonManage.CANNON_TYPE_9;
		this.goldRate = 60;
		this.bitmapID = FishGameRes.KEY_GAME_CANNON_9;
		this.headBimapID = FishGameRes.KEY_GAME_CANNON_9_HEAD;
		this.width = 83;
		this.height = 87;
		this.head_width = 33;
		this.head_height = 40;
	}
}
