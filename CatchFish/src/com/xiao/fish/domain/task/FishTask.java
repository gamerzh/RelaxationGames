package com.xiao.fish.domain.task;

import com.xiao.fish.domain.fish.Fish;

public class FishTask {
	protected Fish fish;
	protected int catchNumber;
	protected int passTime;
	protected int pride;


	public Fish getFish() {
		return fish;
	}

	public void setFish(Fish fish) {
		this.fish = fish;
	}

	public int getCatchNumber() {
		return catchNumber;
	}

	public void setCatchNumber(int catchNumber) {
		this.catchNumber = catchNumber;
	}

	public int getPassTime() {
		return passTime;
	}

	public void setPassTime(int passTime) {
		this.passTime = passTime;
	}

	public int getPride() {
		return pride;
	}

	public void setPride(int pride) {
		this.pride = pride;
	}

}
