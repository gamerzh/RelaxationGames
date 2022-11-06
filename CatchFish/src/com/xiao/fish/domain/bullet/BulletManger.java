package com.xiao.fish.domain.bullet;

import android.util.Log;

import com.xiao.fish.domain.bullet.allbullet.Bullet1;
import com.xiao.fish.domain.bullet.allbullet.Bullet10;
import com.xiao.fish.domain.bullet.allbullet.Bullet2;
import com.xiao.fish.domain.bullet.allbullet.Bullet3;
import com.xiao.fish.domain.bullet.allbullet.Bullet4;
import com.xiao.fish.domain.bullet.allbullet.Bullet5;
import com.xiao.fish.domain.bullet.allbullet.Bullet6;
import com.xiao.fish.domain.bullet.allbullet.Bullet7;
import com.xiao.fish.domain.bullet.allbullet.Bullet8;
import com.xiao.fish.domain.bullet.allbullet.Bullet9;

public class BulletManger {

	public static final int BULLET_TYPE_1 = 1;
	public static final int BULLET_TYPE_2 = 2;
	public static final int BULLET_TYPE_3 = 3;
	public static final int BULLET_TYPE_4 = 4;
	public static final int BULLET_TYPE_5 = 5;
	public static final int BULLET_TYPE_6 = 6;
	public static final int BULLET_TYPE_7 = 7;
	public static final int BULLET_TYPE_8 = 8;
	public static final int BULLET_TYPE_9 = 9;
	public static final int BULLET_TYPE_10 = 10;

	public static Bullet getBulletByType(int type) {
		switch (type) {
		case BULLET_TYPE_1:
			return new Bullet1();
		case BULLET_TYPE_2:
			return new Bullet2();
		case BULLET_TYPE_3:
			return new Bullet3();
		case BULLET_TYPE_4:
			return new Bullet4();
		case BULLET_TYPE_5:
			return new Bullet5();
		case BULLET_TYPE_6:
			return new Bullet6();
		case BULLET_TYPE_7:
			return new Bullet7();
		case BULLET_TYPE_8:
			return new Bullet8();
		case BULLET_TYPE_9:
			return new Bullet9();
		case BULLET_TYPE_10:
			return new Bullet10();
		default:
			Log.e("com.poxiao.fish", "Bullet type is  null ,type =" + type);
			return null;
		}
	}

}
