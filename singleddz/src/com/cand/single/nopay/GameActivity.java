package com.cand.single.nopay;

import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.ImageView;

import com.andy.canvasgame.util.ToastUtil;
import com.b.a.AppApplication;
import com.candy.futon.GameEngine;
import com.candy.futon.IFutonDdzApplication;
import com.candy.futon.domain.ChargeConfig;
import com.candy.futon.domain.GameConfig;
import com.candy.futon.domain.PrizePackageType;
import com.d.event.EventCallBack;
import com.d.event.EventResult;
import com.d.extend.quitgame.ExitGameInterface;
import com.dewgfuyasdvgh.sfauvtysdfegv.R;



public class GameActivity extends com.candy.futon.activitys.GameActivity{

	private boolean coin5WForFirstLose;
	
	private PayEnum payEnum;

	
	private static GameActivity instance;
	
	private ImageView moreGameView;
	
	private EventCallBack eventCallBack = new EventCallBack() {
		
		@Override
		public void setEventResult(final EventResult event) {
			GameActivity.this.runOnUiThread(new Runnable() {
				
				@Override
				public void run() {
					isDialogShowing = false;
					if(event.getPResult()){
						for(Integer tbuId:event.getReward().keySet()){
							rewardByTBU(false, tbuId, event.getReward().get(tbuId));
						}
					}else{
						onPayFail();
					}
				}
			});
			
			
		}
	};
	
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		
		AppApplication.getInstance().initOnFirstActivity(this);
		instance = this;
		moreGameView = (ImageView)findViewById(R.id.image_view_more_game);
		moreGameView.setVisibility(View.INVISIBLE);
		moreGameView.setOnClickListener(new OnClickListener() {
			
			@Override
			public void onClick(View v) {
				showMoreGame(v);
			}
		});
		GameConfig.getInstance().chargeConfigs = new ChargeConfig[]{
			new ChargeConfig(10,40000,10000),
			new ChargeConfig(4,16000,4000),
			new ChargeConfig(2,8000,2000)
		};
	}
	
	@Override
	protected void onResume() {
		super.onResume();
		if(AppApplication.isOpenMoreGame()){
			moreGameView.setVisibility(View.VISIBLE);
		}
	}
	
	public void showMoreGame(View view){
		AppApplication.showMoreGame(this);
	}
	
	@Override
	protected void showQuitGameDialog(String tipString) {
		if(tipString != null){
			ToastUtil.resultNotify(this, tipString);
		}
		AppApplication.quitGame(this, new ExitGameInterface() {
			@Override
			public void quitGame() {
				handler.sendEmptyMessage(MSG_MUST_QUIT);
			}
		});
	}
	
	@Override
	protected void onPayForBegAgain() {
		payEnum = PayEnum.BEG_AGAIN;
		doPay();
	}

	@Override
	protected void onPayForBeg() {
		payEnum = PayEnum.BEG_FOR_PAY;
		doPay();
	}

	@Override
	protected void buyGoodStart() {
		payEnum = PayEnum.GOOD_START;
		doPay();
	}

	@Override
	protected void buyCardRemainder() {
		payEnum = PayEnum.CARD_REMAINDER;
		doPay();
	}

	@Override
	protected void payWhileFirstLose() {
		coin5WForFirstLose = true;
		payEnum = PayEnum.COIN_5W_BIG;
		doPay();
	}

	@Override
	protected void pay10Yuan() {
		coin5WForFirstLose = true;
		payEnum = PayEnum.COIN_5W_BIG;
		doPay();
	}

	private void doPay() {
		isDialogShowing = true;
		AppApplication.getInstance().doPEvent(this, getEventId(), eventCallBack);
	}
	
	private String getEventId() {
		if(payEnum == PayEnum.FREE_1000){
			return "14";
		}
		if(payEnum == PayEnum.FREE_GOOD_START){
			return "15";
		}
		if(prizeType == null || payEnum != PayEnum.COIN_5W_BIG ){
			return doGetPayEventId();
		}
		if(prizeType == PrizePackageType.NORMAL){
			return doGetPayEventId();
		}
		return ""+(10 + prizeType.ordinal());
	}

	private String doGetPayEventId() {
		if(payEnum.ordinal() <= PayEnum.CHARGE_8.ordinal()){
			return (payEnum.ordinal() + 1) + "";
		}
		return (payEnum.ordinal() + 2) +"";
	}


	protected void onPaySuccess() {
		if(payEnum == PayEnum.BEG_FOR_PAY || payEnum == PayEnum.BEG_AGAIN){
			payForBegSuccess();
		}else if(payEnum == PayEnum.CARD_REMAINDER){
			buyCardRemainderSuccess();
		}else if(payEnum == PayEnum.COIN_5W_BIG){
			if(coin5WForFirstLose){
				payWhileFirstLoseSuccess();
			}else{
				pay10YuanSuccess();
			}
		}else if(payEnum == PayEnum.GOOD_START){
			buyGoodStartSuccess();
		}else if(payEnum == PayEnum.FREE_1000){
			free1000Payed();
		}else if(payEnum == PayEnum.FREE_GOOD_START){
			onConfirmFreeGoodStart();
		}
	}
	
	
	protected void onPayFail() {
		if(payEnum == PayEnum.BEG_FOR_PAY || payEnum == PayEnum.BEG_AGAIN){
			payForBegFail();
		}else if(payEnum == PayEnum.CARD_REMAINDER){
			buyCardRemainderFail();
		}else if(payEnum == PayEnum.COIN_5W_BIG){
			if(coin5WForFirstLose){
				payWhileFirstLoseFailed();
			}else{
				pay10YuanFail();
			}
		}else if(payEnum == PayEnum.GOOD_START){
			buyGoodStartFail();
		}else if(payEnum == PayEnum.FREE_1000){
			free1000Payed();
		}else if(payEnum == PayEnum.FREE_GOOD_START){
			onConfirmFreeGoodStart();
		}
	}

	private void free1000Payed() {
		IFutonDdzApplication application = (IFutonDdzApplication)getApplication();
		application.addCoin2Hero(1000, false);
		GameEngine.getInstance().playGetPrizeAnimation();
	}
	
	@Override
	protected void onBuyGoodStart() {
		buyGoodStart();
	}
	
	@Override
	protected void showBegForPayDialog() {
		onPayForBeg();
	}

	@Override
	protected void showBegForPayDialogAgain() {
		onPayForBegAgain();
	}
	
	@Override
	protected void onBuyCardRemainder() {
		buyCardRemainder();
	}
	

	
	@Override
	protected void onPay10Yuan() {
		pay10Yuan();
	}
	
	@Override
	protected void onPayWhileFirstLose() {
		payWhileFirstLose();
	}
	
	
	protected void onShowGetPrizePackage(){
		payEnum = PayEnum.FREE_1000;
		doPay();
	}
	
	@Override
	protected void showFreeGoodStartDialog() {
		payEnum = PayEnum.FREE_GOOD_START;
		doPay();
	}
	
	
	public static GameActivity getInstance() {
		return instance;
	}
	
	public void rewardByTBU(boolean inChargeDialog, int tbuId, int count){
		TBUPayENum payEnum = TBUPayENum.values()[tbuId - 1];
		switch(payEnum){
		case CARD_REMAINDER:
			buyCardRemainderSuccess();
			break;
		case GOOD_START:
			handler.sendEmptyMessage(MSG_CHECK_PAY_DIALOG);
			if(count > 1){
				GameConfig.getInstance().buyGoodStart = true;
			}
			goodStartBuyed(count);
			break;
		case COIN:
			handler.sendEmptyMessage(MSG_CHECK_PAY_DIALOG);
			IFutonDdzApplication futonDdzApplication = (IFutonDdzApplication)this.getApplication();
			futonDdzApplication.addCoin2Hero(count);
			if(!inChargeDialog){
				GameConfig.getInstance().changeGameRoom(futonDdzApplication.getPlayerInfo().getPoint());
			}
			GameConfig.getInstance().payedUser = true;
			GameConfig.getInstance().save(this);
			break;
		}
	}
}
