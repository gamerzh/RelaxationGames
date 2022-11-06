package com.elsfk.main;



import com.b.a.AppApplication;


public class GameApplication extends AppApplication{
	private static GameApplication instance;
		
	@Override
	public void onCreate() {
		super.onCreate();
		instance = this;
	}
	public static GameApplication getInstance(){
		return instance;
	}

}
