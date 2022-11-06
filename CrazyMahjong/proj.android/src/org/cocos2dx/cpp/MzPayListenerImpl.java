package org.cocos2dx.cpp;

import android.os.Bundle;

import com.meizu.gamesdk.model.callback.MzPayListener;
import com.meizu.gamesdk.model.model.MzPayParams;
import com.meizu.gamesdk.model.model.PayResultCode;
import com.tbu.androidtools.Debug;

public class MzPayListenerImpl implements MzPayListener  {

	@Override
	public void onPayResult(int code, Bundle info, String errorMsg) {
		String orderid = null;
		if (info != null) {
			orderid = info.getString(MzPayParams.ORDER_KEY_ORDER_ID);
		}
		if (code == PayResultCode.PAY_SUCCESS) {
			Debug.e("支付成功:" + orderid);
			
			JniPayCallbackHelper.eventSuccess();
			NetWorkService.logEventShowPayPanel(
					PayService.nowPayPointEnum.getPayPoint(), 4);
		} else if (code == PayResultCode.PAY_USE_SMS) {
			Debug.e("短信支付:" + orderid);
			JniPayCallbackHelper.eventFail();
			NetWorkService.logEventShowPayPanel(
					PayService.nowPayPointEnum.getPayPoint(), 5);
		} else if (code == PayResultCode.PAY_ERROR_CANCEL) {
			Debug.e("用户取消:" + orderid);
			JniPayCallbackHelper.eventFail();
			NetWorkService.logEventShowPayPanel(
					PayService.nowPayPointEnum.getPayPoint(), 5);
		} else if (code == PayResultCode.PAY_ERROR_CODE_DUPLICATE_PAY) {
			Debug.e("重复支付:" + orderid);
			JniPayCallbackHelper.eventFail();
			NetWorkService.logEventShowPayPanel(
					PayService.nowPayPointEnum.getPayPoint(), 5);
		} else if (code == PayResultCode.PAY_ERROR_GAME_VERIFY_ERROR) {
			Debug.e(errorMsg);
			JniPayCallbackHelper.eventFail();
			NetWorkService.logEventShowPayPanel(
					PayService.nowPayPointEnum.getPayPoint(), 5);
		} else {
			Debug.e("支付失败:" + code + "," + errorMsg);
			JniPayCallbackHelper.eventFail();
			NetWorkService.logEventShowPayPanel(
					PayService.nowPayPointEnum.getPayPoint(), 5);
		}

		Debug.e("MzGameSDK"+ errorMsg + code);
	}


}
