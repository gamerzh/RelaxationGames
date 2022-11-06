package com.xiao.fish.domain.bullet;

public class Bullet {
	protected int bulletType;
	protected int bulletSpeed;
	protected int rotatetion;
	protected int width;
	protected int height;
	protected int goldConsume;
	protected int bulletBitmap;

	public void setBulletBitmap(int bulletBitmap) {
		this.bulletBitmap = bulletBitmap;
	}

	public int getBulletType() {
		return bulletType;
	}

	public void setBulletType(int bulletType) {
		this.bulletType = bulletType;
	}

	public int getBulletSpeed() {
		return bulletSpeed;
	}

	public void setBulletSpeed(int bulletSpeed) {
		this.bulletSpeed = bulletSpeed;
	}

	public int getRotatetion() {
		return rotatetion;
	}

	public void setRotatetion(int rotatetion) {
		this.rotatetion = rotatetion;
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

	public int getGoldConsume() {
		return goldConsume;
	}

	public void setGoldConsume(int goldConsume) {
		this.goldConsume = goldConsume;
	}

	public int getBulletBitmap() {
		return bulletBitmap;
	}

}
