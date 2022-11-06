package com.xiao.fish.domain.fish;

import java.util.ArrayList;
import java.util.List;

import com.xiao.fish.constants.BirthPosition;
import com.xiao.fish.domain.fish.allfish.Fish1;
import com.xiao.fish.domain.fish.allfish.Fish10;
import com.xiao.fish.domain.fish.allfish.Fish2;
import com.xiao.fish.domain.fish.allfish.Fish3;
import com.xiao.fish.domain.fish.allfish.Fish4;
import com.xiao.fish.domain.fish.allfish.Fish5;
import com.xiao.fish.domain.fish.allfish.Fish6;
import com.xiao.fish.domain.fish.allfish.Fish7;
import com.xiao.fish.domain.fish.allfish.Fish8;
import com.xiao.fish.domain.fish.allfish.Fish9;

public class FishManage {
	public static List<Fish> fishes = new ArrayList<Fish>();
	private static FishManage instance;
	private int fish5Num = 0;
	private int fish6Num = 0;
	private int fish4Num = 0;

	public static FishManage getInstance() {
		if (null != instance) {
			return instance;
		} else {
			return new FishManage();
		}
	}

	private FishManage() {
	}

	public Fish getFishByType(int type) {
		switch (type) {
		case Fish.FISHTYPE_1:
			return new Fish1();
		case Fish.FISHTYPE_2:
			return new Fish2();
		case Fish.FISHTYPE_3:
			return new Fish3();
		case Fish.FISHTYPE_4:
			return new Fish4();
		case Fish.FISHTYPE_5:
			return new Fish5();
		case Fish.FISHTYPE_6:
			return new Fish6();
		case Fish.FISHTYPE_7:
			return new Fish7();
		case Fish.FISHTYPE_8:
			return new Fish8();
		case Fish.FISHTYPE_9:
			return new Fish9();
		case Fish.FISHTYPE_10:
			return new Fish10();
		default:
			return null;
		}
	}

	int lucky = (int) (Math.random() * 100);

	public Fish createSingleFish(int positionType) {
		int fishType = Fish.FISHTYPE_1;
		if (lucky > 0 && lucky <= 40) {
			fishType = Fish.FISHTYPE_1;
		} else if (lucky > 40 && lucky <= 65) {
			fishType = Fish.FISHTYPE_2;
		} else if (lucky > 65 && lucky <= 75) {
			fishType = Fish.FISHTYPE_3;
		} else if (lucky > 75 && lucky <= 85) {
			fishType = Fish.FISHTYPE_4;
		} else if (lucky > 85 && lucky <= 95) {
			fishType = Fish.FISHTYPE_5;
		} else if (lucky > 95 && lucky <= 99) {
			fishType = Fish.FISHTYPE_6;
		} else {
			fishType = Fish.FISHTYPE_1;// 默认为最小的鱼
		}
		if (null != fishes && fishes.size() > 0) {
			fish5Num = 0;
			fish6Num = 0;
			for (Fish fish : fishes) {
				if (fish.getFishType() == Fish.FISHTYPE_4) {
					++fish4Num;
				}
				if (fish.getFishType() == Fish.FISHTYPE_5) {
					++fish5Num;
				}
				if (fish.getFishType() == Fish.FISHTYPE_6) {
					++fish6Num;
				}
			}
			// Log.e("com.poxiao.fish", "fish5Num=" + fish5Num);
			// Log.e("com.poxiao.fish", "fish6Num=" + fish6Num);
		}
		if (fish5Num + fish6Num == 0 && fishType != 5 && fishType != 6) {
			fishType = Math.random() > 0.7 ? Fish.FISHTYPE_5 : Fish.FISHTYPE_6;
		}
		if (fish4Num >= 3 && fishType == 4) {
			fishType = (int) (Math.random() * 3 + 1);
		}
		if (fish5Num >= 1 && fishType == 5) {
			fishType = (int) (Math.random() * 3 + 1);
		}
		if (fish6Num >= 1 && fishType == 6) {
			fishType = (int) (Math.random() * 3 + 1);
		}
		Fish fish = getFishByType(fishType);
		BirthPosition position = BirthPosition.getBirthPoint(fish.getWidth(),
				positionType);
		fish.setBirthPosition(position);
		fishes.add(fish);
		return fish;
	}

	public List<Fish> getFishes() {
		return fishes;
	}
}
