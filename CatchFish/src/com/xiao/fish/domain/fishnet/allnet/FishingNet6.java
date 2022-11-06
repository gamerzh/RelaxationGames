package com.xiao.fish.domain.fishnet.allnet;

import com.xiao.fish.domain.fishnet.FishingNet;
import com.xiao.fish.game.res.FishGameRes;

public class FishingNet6 extends FishingNet {

	public FishingNet6() {
		super();
		this.netType = 6;
		this.width = 173;
		this.height = 163;
		this.fishNetBitmap = FishGameRes.KEY_GAME_NET_6;
	}

}
