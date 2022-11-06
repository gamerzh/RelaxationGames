package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.os.Bundle;

import com.avos.avoscloud.AVAnalytics;
import com.avos.avoscloud.AVOSCloud;
import com.tbu.androidtools.app.AppInfo;
import com.tbu.androidtools.device.DeviceInfo;



public class AppActivity extends Cocos2dxActivity {
		
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		initTbuTools();
		PayService.init(this);
		NetWorkService.init(this);

	}
	private void  initTbuTools() {
		DeviceInfo.getUA();
		DeviceInfo.getCid();
		DeviceInfo.getLac();
		AppInfo.getEntrance();
	}
	protected void onPause()
	{
		super.onPause();
		AVAnalytics.onPause(this);
	}
	protected void onResume() {
	    super.onResume();
	    AVAnalytics.onResume(this);
	}
	
}
