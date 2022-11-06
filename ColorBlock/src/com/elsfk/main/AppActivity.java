package com.elsfk.main;



import org.cocos2dx.lib.Cocos2dxActivity;

import android.os.Bundle;

import com.b.a.AppApplication;
import com.d.avos.TbuCloudUtil;


public class AppActivity extends Cocos2dxActivity {
		
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		AppApplication.getInstance().initOnFirstActivity(AppActivity.this);
		PayService.init(this);
		NetWorkService.init(this);
	}
	
	@Override
	protected void onPause() {
		super.onPause();
		TbuCloudUtil.markOnPause(AppActivity.this);
	}

	@Override
	protected void onResume() {
		super.onResume();
		TbuCloudUtil.markOnResume(AppActivity.this);
	}
}
