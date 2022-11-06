package com.xiao.fish.domain.fishnet.allnet;

import com.xiao.fish.domain.fishnet.FishingNet;
import com.xiao.fish.game.res.FishGameRes;

public class FishingNet8 extends FishingNet {

	public FishingNet8() {
		super();
		this.netType = 8;
		this.width = 181;
		this.height = 174;
		this.fishNetBitmap = FishGameRes.KEY_GAME_NET_7;
	}

}
