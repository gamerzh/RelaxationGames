package com.xiao.fish.domain.cannon;

import android.util.Log;

import com.xiao.fish.domain.cannon.allcanon.Cannon1;
import com.xiao.fish.domain.cannon.allcanon.Cannon10;
import com.xiao.fish.domain.cannon.allcanon.Cannon2;
import com.xiao.fish.domain.cannon.allcanon.Cannon3;
import com.xiao.fish.domain.cannon.allcanon.Cannon4;
import com.xiao.fish.domain.cannon.allcanon.Cannon5;
import com.xiao.fish.domain.cannon.allcanon.Cannon6;
import com.xiao.fish.domain.cannon.allcanon.Cannon7;
import com.xiao.fish.domain.cannon.allcanon.Cannon8;
import com.xiao.fish.domain.cannon.allcanon.Cannon9;

public class CannonManage {

	public static final int CANNON_TYPE_1 = 1;
	public static final int CANNON_TYPE_2 = 2;
	public static final int CANNON_TYPE_3 = 3;
	public static final int CANNON_TYPE_4 = 4;
	public static final int CANNON_TYPE_5 = 5;
	public static final int CANNON_TYPE_6 = 6;
	public static final int CANNON_TYPE_7 = 7;
	public static final int CANNON_TYPE_8 = 8;
	public static final int CANNON_TYPE_9 = 9;
	public static final int CANNON_TYPE_10 = 10;

	public static Cannon getCannonByType(int type) {
		switch (type) {
		case CANNON_TYPE_1:
			return new Cannon1();
		case CANNON_TYPE_2:
			return new Cannon2();
		case CANNON_TYPE_3:
			return new Cannon3();
		case CANNON_TYPE_4:
			return new Cannon4();
		case CANNON_TYPE_5:
			return new Cannon5();
		case CANNON_TYPE_6:
			return new Cannon6();
		case CANNON_TYPE_7:
			return new Cannon7();
		case CANNON_TYPE_8:
			return new Cannon8();
		case CANNON_TYPE_9:
			return new Cannon9();
		case CANNON_TYPE_10:
			return new Cannon10();
		default:
			Log.e("com.poxiao.fish", "cannon type is error;type=" + type);
			return new Cannon6();
		}
	}

}
