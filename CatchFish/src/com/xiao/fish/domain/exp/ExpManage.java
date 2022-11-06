package com.xiao.fish.domain.exp;

import java.util.ArrayList;
import java.util.List;

import android.util.Log;

public class ExpManage {
	private List<Experience> levels;
	private static ExpManage instance;

	private ExpManage() {
		levels = getDefaultLevels();
	}

	public static ExpManage getInstance() {
		if (null == instance) {
			return new ExpManage();
		} else {
			return instance;
		}
	}

	public int getLevelByExp(int exp) {
		for (int i = 0; i < levels.size(); i++) {
			if (exp >= levels.get(i).getLowerExp()
					&& exp <= levels.get(i).getHighExp()) {
				return levels.get(i).getLevel();
			}
		}
		Log.e("com.poxiao.fish", "exp is error,exp=" + exp);
		return 0;
	}

	public int getHExpByLevel(int level) {
		for (int i = 0; i < levels.size(); i++) {
			if (level == levels.get(i).getLevel()) {
				return levels.get(i).getHighExp();
			}
		}
		Log.e("com.poxiao.fish", "level is error,level=" + level);
		return 0;
	}

	public int getLExpByLevel(int level) {
		for (int i = 0; i < levels.size(); i++) {
			if (level == levels.get(i).getLevel()) {
				return levels.get(i).getLowerExp();
			}
		}
		Log.e("com.poxiao.fish", "level is error,level=" + level);
		return 0;
	}

	/**
	 * 等级，经验配置
	 * 
	 * @return
	 */
	private List<Experience> getDefaultLevels() {
		List<Experience> levels = new ArrayList<Experience>();
		Experience exp1 = new Experience(1, 0, 300);
		levels.add(exp1);
		Experience exp2 = new Experience(2, 301, 600);
		levels.add(exp2);
		Experience exp3 = new Experience(3, 601, 1200);
		levels.add(exp3);
		Experience exp4 = new Experience(4, 1201, 2400);
		levels.add(exp4);
		Experience exp5 = new Experience(5, 2401, 4800);
		levels.add(exp5);
		Experience exp6 = new Experience(6, 4801, 9600);
		levels.add(exp6);
		Experience exp7 = new Experience(7, 9601, 19200);
		levels.add(exp7);
		Experience exp8 = new Experience(8, 19201, 38400);
		levels.add(exp8);
		Experience exp9 = new Experience(9, 76801, 153600);
		levels.add(exp9);
		Experience exp10 = new Experience(10, 153601, 307200);
		levels.add(exp10);
		Experience exp11 = new Experience(11, 307201, 614400);
		levels.add(exp11);
		Experience exp12 = new Experience(12, 614401, 0);
		levels.add(exp12);
		return levels;
	}
}
