package com.xiao.fish.domain.fishnet;

import android.util.Log;

import com.xiao.fish.domain.fishnet.allnet.FishingNet1;
import com.xiao.fish.domain.fishnet.allnet.FishingNet2;
import com.xiao.fish.domain.fishnet.allnet.FishingNet3;
import com.xiao.fish.domain.fishnet.allnet.FishingNet4;
import com.xiao.fish.domain.fishnet.allnet.FishingNet5;
import com.xiao.fish.domain.fishnet.allnet.FishingNet6;
import com.xiao.fish.domain.fishnet.allnet.FishingNet7;
import com.xiao.fish.domain.fishnet.allnet.FishingNet8;
import com.xiao.fish.domain.fishnet.allnet.FishingNet9;

public class FishingNetManage {

	public static FishingNet getFishNetByType(int type) {
		switch (type) {
		case 1:
			return new FishingNet1();
		case 2:
			return new FishingNet2();
		case 3:
			return new FishingNet3();
		case 4:
			return new FishingNet4();
		case 5:
			return new FishingNet5();
		case 6:
			return new FishingNet6();
		case 7:
			return new FishingNet7();
		case 8:
			return new FishingNet8();
		case 9:
			return new FishingNet9();
		default:
			Log.e("com.poxiao.fish", "FishNet Type is error,type=" + type);
			return null;
		}
	}

}
