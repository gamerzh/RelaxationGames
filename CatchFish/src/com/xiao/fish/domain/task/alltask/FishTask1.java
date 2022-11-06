package com.xiao.fish.domain.task.alltask;

import com.xiao.fish.domain.fish.allfish.Fish1;
import com.xiao.fish.domain.task.FishTask;

public class FishTask1 extends FishTask {

	public FishTask1() {
		super();
		this.fish = new Fish1();
		this.catchNumber = 5;
		this.passTime = 60;
		this.pride = 150;
	}

}
