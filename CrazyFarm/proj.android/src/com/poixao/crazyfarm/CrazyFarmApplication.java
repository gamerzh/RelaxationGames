package com.poixao.crazyfarm;

import android.app.Application;

import com.avos.avoscloud.AVAnalytics;
import com.avos.avoscloud.AVOSCloud;
import com.tbu.gameextend.android.GameExtend;


public class CrazyFarmApplication extends Application {

	@Override
	public void onCreate() {
		super.onCreate();
		GameExtend.init(getApplicationContext()); // 设备环境变量初始化		
		
//		AVOSCloud.initialize(this, 
//				"QboLa9qa1f9GUcHDGSc4c80v-gzGzoHsz", 
//			"T073vt0MSU1BGOe2KJcJgqUG");
		//FM 正式
		AVOSCloud.initialize(this, 
				"FMmrXq8mMagQj6vDFnBtTaHr-gzGzoHsz", 
				"FoOVWWpQeL4IjJ7SJIOyk7if");
		AVAnalytics.enableCrashReport(this, true);
	}
}
