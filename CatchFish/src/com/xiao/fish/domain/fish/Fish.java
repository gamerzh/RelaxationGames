package com.xiao.fish.domain.fish;

import java.util.Random;

import com.xiao.fish.constants.BirthPosition;

public class Fish {
	protected int fishType;
	protected int width;
	protected int height;
	protected int speed;
	protected int gold;
	protected int experience;
	protected int[] anims;
	protected int[] catchAnims;
	protected BirthPosition birthPosition;
	protected float[] animTime;
	protected float catchTime;

	public static final int FISHTYPE_1 = 1;
	public static final int FISHTYPE_2 = 2;
	public static final int FISHTYPE_3 = 3;
	public static final int FISHTYPE_4 = 4;
	public static final int FISHTYPE_5 = 5;
	public static final int FISHTYPE_6 = 6;
	public static final int FISHTYPE_7 = 7;

	 public static final int FISHTYPE_8 = 8;
	 public static final int FISHTYPE_9 = 9;
	 public static final int FISHTYPE_10 = 10;
	// public static final int FISHTYPE_11 = 11;

	public int getFishType() {
		return fishType;
	}

	public int getWidth() {
		return width;
	}

	public void setWidth(int width) {
		this.width = width;
	}

	public int getHeight() {
		return height;
	}

	public void setHeight(int height) {
		this.height = height;
	}

	public int getSpeed() {
		return speed;
	}

	public void setSpeed(int speed) {
		this.speed = speed;
	}

	public int getGold() {
		return gold;
	}

	public void setGold(int gold) {
		this.gold = gold;
	}

	public int getExperience() {
		return experience;
	}

	public void setExperience(int experience) {
		this.experience = experience;
	}

	public int[] getAnims() {
		return anims;
	}

	public void setAnims(int[] anims) {
		this.anims = anims;
	}

	public BirthPosition getBirthPosition() {
		return birthPosition;
	}

	public void setBirthPosition(BirthPosition birthPosition) {
		this.birthPosition = birthPosition;
	}

	public int[] getCatchAnims() {
		return catchAnims;
	}

	public void setCatchAnims(int[] catchAnims) {
		this.catchAnims = catchAnims;
	}

	public float[] getAnimTime() {
		return animTime;
	}

	public void setAnimTime(float[] animTime) {
		this.animTime = animTime;
	}

	public float getCatchTime() {
		return catchTime;
	}

	public void setCatchTime(float catchTime) {
		this.catchTime = catchTime;
	}

	
	/**
	 * 
	 * @param start
	 * @param between 要求>0
	 * @return
	 */
	public static int getRandomNumber(int start, int between) {
		if(between < 0) {
			return 0;
		}
		Random random = new Random();
		return start + random.nextInt(between);
	}
	
}
