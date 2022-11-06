package com.cand.single.nopay;

import com.b.a.AppApplication;
import com.candy.futon.FutonDdzApplication;
import com.candy.futon.domain.GameConfig;

public class SingleDdzApplication extends FutonDdzApplication{


	AppApplication application = new AppApplication();
	
	@Override
	public void onCreate() {
		super.onCreate();
		application.init(this);
		GameConfig.getInstance().noPromote = true;
		GameConfig.getInstance().showAILog = false;
		GameConfig.getInstance().uploadingStartupLogs = true;
	};
	
	@Override
	public Class<? extends GameActivity> getGameActivityClass() {
		return com.cand.single.nopay.GameActivity.class;
	}

	@Override
	public Class<? extends ChargeDialog> getChargeDialogClass() {
		return com.cand.single.nopay.ChargeDialog.class;
	}
	
}
