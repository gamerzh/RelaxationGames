package com.xiao.fish.domain.task;

import android.util.Log;

import com.xiao.fish.domain.task.alltask.FishTask1;
import com.xiao.fish.domain.task.alltask.FishTask2;
import com.xiao.fish.domain.task.alltask.FishTask3;
import com.xiao.fish.domain.task.alltask.FishTask4;
import com.xiao.fish.domain.task.alltask.FishTask5;

public class FishTaskManger {
	public static FishTask getFishTaskByType(int type) {
		switch (type) {
		case 1:
			return new FishTask1();
		case 2:
			return new FishTask2();
		case 3:
			return new FishTask3();
		case 4:
			return new FishTask4();
		case 5:
			return new FishTask5();
		default:
			Log.e("com.poxiao.fish", "FishTask type is error,type=" + type);
			return null;
		}
	}
}
