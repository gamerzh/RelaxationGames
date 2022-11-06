package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;
import android.os.Bundle;
import com.poxiao.pay.xbll.GamePay;

public class AppActivity extends Cocos2dxActivity {
		
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		GamePay.getInstance().initOnFirstActivity(AppActivity.this);
		SignInService.init(this);
		PayService.init(this);
		NetWorkService.init(this);
	}
}
