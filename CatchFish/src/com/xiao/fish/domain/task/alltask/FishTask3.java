package com.xiao.fish.domain.task.alltask;

import com.xiao.fish.domain.fish.allfish.Fish3;
import com.xiao.fish.domain.task.FishTask;

public class FishTask3 extends FishTask {

	public FishTask3() {
		super();
		this.fish = new Fish3();
		this.catchNumber = 3;
		this.passTime = 60;
		this.pride = 150;
	}

}
