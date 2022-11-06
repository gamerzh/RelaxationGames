package com.poixao.crazyfarm.wxapi;





import org.cocos2dx.cpp.AppActivity;
import org.cocos2dx.cpp.JniPayCallbackHelper;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;

import com.poixao.crazyfarm.Constants;
import com.tencent.mm.sdk.constants.ConstantsAPI;
import com.tencent.mm.sdk.modelbase.BaseReq;
import com.tencent.mm.sdk.modelbase.BaseResp;
import com.tencent.mm.sdk.modelpay.PayResp;
import com.tencent.mm.sdk.openapi.IWXAPI;
import com.tencent.mm.sdk.openapi.IWXAPIEventHandler;
import com.tencent.mm.sdk.openapi.WXAPIFactory;

public class WXPayEntryActivity extends Activity implements IWXAPIEventHandler{
	
	private static final String TAG = "MicroMsg.SDKSample.WXPayEntryActivity";
	
    private IWXAPI api;
	
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.e("TBU_DEBUG", "pay wx onCreate ...");
        
    	api = WXAPIFactory.createWXAPI(this, Constants.APP_ID);
        api.handleIntent(getIntent(), this);
    }

	@Override
	protected void onNewIntent(Intent intent) {
		super.onNewIntent(intent);
		setIntent(intent);
        api.handleIntent(intent, this);
	}

	@Override
	public void onReq(BaseReq req) {
	}

	@Override
	public void onResp(final BaseResp resp) {


		if (resp.getType() == ConstantsAPI.COMMAND_PAY_BY_WX) {
			final PayResp payResp = (PayResp)resp;
			if(resp.errCode == BaseResp.ErrCode.ERR_OK)
			{
				WXPayEntryActivity.this.runOnUiThread(new Runnable() {
					@Override
					public void run() {
						JniPayCallbackHelper.payResultCallBack(0,"scuess",payResp.prepayId);	
					}
				});
								
			}
			else
			{
				WXPayEntryActivity.this.runOnUiThread(new Runnable() {
					@Override
					public void run() {
						JniPayCallbackHelper.payResultCallBack(resp.errCode,"failed",payResp.prepayId);	
					}
				});
				
			}
		}
		
		WXPayEntryActivity.this.finish();
	}
}