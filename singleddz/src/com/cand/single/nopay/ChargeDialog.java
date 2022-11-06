package com.cand.single.nopay;

import com.b.a.AppApplication;
import com.d.event.EventCallBack;
import com.d.event.EventResult;



public class ChargeDialog extends com.candy.futon.dialog.ChargeDialog {

	private EventCallBack eventCallBack = new EventCallBack() {
		
		@Override
		public void setEventResult(final EventResult event) {
			GameActivity.getInstance().runOnUiThread(new Runnable() {
				
				@Override
				public void run() {
					if(event.getPResult()){
						for(Integer tbuId:event.getReward().keySet()){
							GameActivity.getInstance().rewardByTBU(true, tbuId, event.getReward().get(tbuId));
						}
					}
				}
			});
			
			
		}
	};
	
	protected void showConfirmChargeDialog() {
		onCharge();
	};
	
	@Override
	protected void onCharge() {
		doP();
	}

	private void doP() {
		AppApplication.getInstance().doPEvent(getActivityFailSafe(), getEventId(), eventCallBack);
	}
	
	private String getEventId() {
		if(currentChargeConfig.mPay == 10){
			return "16";
		}
		return (currentChargeConfig.mPay /2)+"";
	}
	
}
