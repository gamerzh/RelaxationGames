package com.tbu.gameextend.android;

import android.content.Context;

public class GameExtend {

	public static GameExtend instance;
	
	private GameExtend(){
	}
	
	public static GameExtend getInstance() {
		if(instance == null) {
			instance = new GameExtend();
		}
		return instance;
	}
	
	public static void init(Context context) {
		DeviceInfo.initDeviceInfo(context);
		AppInfo.init(context);
	}
	
	public static String getImei() {
		return DeviceInfo.getImei();
	}
	
	public static String getHdFactory() {
		return DeviceInfo.getHdFactory();
	}
	
	public static String getHdType() {
		return DeviceInfo.getHdType();
	}
	
	public static String getChannelId() {
		return AppInfo.getChannelId();
	}
}
