package org.cocos2dx.cpp;

import android.app.Activity;
import android.util.Log;

import com.poxiao.pay.xbll.GamePay;
import com.tallbigup.android.AppApplication;
import com.tallbigup.android.event.EventCallBack;
import com.tallbigup.android.event.EventResult;
import com.tbu.androidtools.Debug;

public class PayService {
	
	private static Activity activity;

	public static void init(Activity activity) {
		PayService.activity = activity;
	}

	public static void pay(final int id) {
		Debug.e("event id="+id);
		boolean result=GamePay.getInstance().doPayEvent(activity, id+"", new EventCallBack(){
			@Override
			public void setEventResult(EventResult eventResult) {
				// TODO Auto-generated method stub
				Log.i("LLK",eventResult.getPayResult()?"true":"false");
				if(eventResult.getPayResult()){
					if(eventResult.getReward()==null){
						Log.i("LLK","getReward is null");
					}else{
						Integer[] propIds = eventResult.getReward().keySet().toArray(new Integer[] {});  
						Log.i("LLK",propIds.length+"");
						int[] propNum=new int[propIds.length];
						int[] propId=new int[propIds.length];
						for(int i=0;i<propIds.length;i++){
							propId[i]=propIds[i];
							propNum[i]=eventResult.getReward().get(propIds[i]);
						}
						JniPayCallbackHelper.eventSuccess(id,propId,propNum);
					}
				
				}else{
					Debug.e("event pay false id="+id);
					JniPayCallbackHelper.eventFail(id);
				}
		}});
//				
		if(!result){
			Debug.e("event pay is close id="+id);
			JniPayCallbackHelper.eventClose(id);
		}
	}
	
	
}
