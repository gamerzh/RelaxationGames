package com.xiao.fish.game;

import android.app.Activity;

import com.hifreshday.android.pge.entity.scene.BitmapBgScreen;

public abstract class BaseGameScene extends BitmapBgScreen {
	private Activity activity;
	public BaseGameScene(Activity activity) {
		super();
		this.activity = activity;
	}
}
