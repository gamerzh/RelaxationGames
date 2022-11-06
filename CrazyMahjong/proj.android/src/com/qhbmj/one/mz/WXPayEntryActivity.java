package com.qhbmj.one.mz;

import org.cocos2dx.cpp.JniPayCallbackHelper;
import org.cocos2dx.cpp.NetWorkService;
import org.cocos2dx.cpp.PayService;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Debug;

import com.tbu.wx.util.WxAppInfo;
import com.tencent.mm.sdk.constants.ConstantsAPI;
import com.tencent.mm.sdk.modelbase.BaseReq;
import com.tencent.mm.sdk.modelbase.BaseResp;
import com.tencent.mm.sdk.modelpay.PayResp;
import com.tencent.mm.sdk.openapi.IWXAPI;
import com.tencent.mm.sdk.openapi.IWXAPIEventHandler;
import com.tencent.mm.sdk.openapi.WXAPIFactory;

public class WXPayEntryActivity extends Activity implements IWXAPIEventHandler {

	private IWXAPI api;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		api = WXAPIFactory.createWXAPI(this,WxAppInfo.getWxInfo().getAppId());
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
	public void onResp(BaseResp resp) {
		com.tbu.androidtools.Debug.e("resp.errCode"+resp.errCode);
		if (resp.getType() == ConstantsAPI.COMMAND_PAY_BY_WX) {
			PayResp payResp = (PayResp) resp;
			if (resp.errCode == BaseResp.ErrCode.ERR_OK) {
				com.tbu.androidtools.Debug.e("wxpay scuess");
				PayService.queryOrder();
				//  TODO 支付成功
			} else {
				com.tbu.androidtools.Debug.e("wxpay failed");
				PayService.queryOrder();
//				JniPayCallbackHelper.eventFail();
//				NetWorkService.logEvent(PayService.nowPayPointEnum.getPropName(), "支付取消");
				// TODO 支付失败
			}
		}
		WXPayEntryActivity.this.finish();
	}
}