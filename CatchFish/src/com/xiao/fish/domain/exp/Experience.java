package com.xiao.fish.domain.exp;

public class Experience {
	private int level;
	private int lowerExp;
	private int highExp;

	public Experience(int level, int lowerExp, int highExp) {
		this.level = level;
		this.lowerExp = lowerExp;
		this.highExp = highExp;
	}

	public int getLevel() {
		return level;
	}

	public void setLevel(int level) {
		this.level = level;
	}

	public int getLowerExp() {
		return lowerExp;
	}

	public void setLowerExp(int lowerExp) {
		this.lowerExp = lowerExp;
	}

	public int getHighExp() {
		return highExp;
	}

	public void setHighExp(int highExp) {
		this.highExp = highExp;
	}
}
