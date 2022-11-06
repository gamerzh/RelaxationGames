package com.xiao.fish.widget;

import android.app.Dialog;
import android.content.Context;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;

import com.kx.byno.R;
import com.tallbigup.android.gds.sign.SignManager;
import com.xiao.fish.PxGameConstants;
import com.xiao.fish.domain.PlayerInfo;
import com.xiao.fish.game.GameActivity;

public class SignInDialog extends Dialog {
	private TextView day_text_1;
	private TextView day_text_2;
	private TextView day_text_3;
	private TextView day_text_4;
	private TextView day_text_5;
	private TextView day_text_6;
	private TextView day_text_7;
	private ImageView day_1;
	private ImageView day_2;
	private ImageView day_3;
	private ImageView day_4;
	private ImageView day_5;
	private ImageView day_6;
	private ImageView day_7;
	private int currentDay;
	private ImageButton sign_getgift;
	private GameActivity activity;

	public SignInDialog(Context context) {
		super(context, R.style.dialog_game_style);
		this.activity = (GameActivity) context;
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		setContentView(R.layout.sing_in_dialog);
		initView();
		setCurrentDay(SignManager.getCurrentSignDays(activity));
		initData();
	}

	private void initView() {
		day_text_1 = (TextView) findViewById(R.id.one_day_text);
		day_text_2 = (TextView) findViewById(R.id.two_day_text);
		day_text_3 = (TextView) findViewById(R.id.three_day_text);
		day_text_4 = (TextView) findViewById(R.id.four_day_text);
		day_text_5 = (TextView) findViewById(R.id.five_day_text);
		day_text_6 = (TextView) findViewById(R.id.six_day_text);
		day_text_7 = (TextView) findViewById(R.id.seven_day_text);
		day_1 = (ImageView) findViewById(R.id.day_one);
		day_2 = (ImageView) findViewById(R.id.day_two);
		day_3 = (ImageView) findViewById(R.id.day_three);
		day_4 = (ImageView) findViewById(R.id.day_four);
		day_5 = (ImageView) findViewById(R.id.day_five);
		day_6 = (ImageView) findViewById(R.id.day_six);
		day_7 = (ImageView) findViewById(R.id.day_seven);
		sign_getgift = (ImageButton) findViewById(R.id.sing_btn);
	}

	private void initData() {
		day_text_1.setText("150");
		day_text_2.setText("200");
		day_text_3.setText("250");
		day_text_4.setText("300");
		day_text_5.setText("350");
		day_text_6.setText("400");
		day_text_7.setText("1000");
		sign_getgift.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View arg0) {
				switch (currentDay) {
				case 0:
					SignManager.sign(activity);
					PlayerInfo info0 = PlayerInfo.getPlayerInfo();
					PxGameConstants.playerGold += 150;
					info0.setGold(PxGameConstants.playerGold);
					PlayerInfo.setPlayerInfo(info0);
					Log.e("com.poxiao.fish", "GameConstants.playerGold "
							+ PxGameConstants.playerGold);
					PxGameConstants.IS_PLAY_GOLD_ANIM = true;
					break;
				case 1:
					SignManager.sign(activity);
					PlayerInfo info1 = PlayerInfo.getPlayerInfo();
					PxGameConstants.playerGold += 200;
					info1.setGold(PxGameConstants.playerGold);
					PlayerInfo.setPlayerInfo(info1);
					PxGameConstants.IS_PLAY_GOLD_ANIM = true;
					break;
				case 2:
					SignManager.sign(activity);
					PlayerInfo info2 = PlayerInfo.getPlayerInfo();
					PxGameConstants.playerGold += 250;
					info2.setGold(PxGameConstants.playerGold);
					PlayerInfo.setPlayerInfo(info2);
					PxGameConstants.IS_PLAY_GOLD_ANIM = true;
					break;
				case 3:
					SignManager.sign(activity);
					PlayerInfo info3 = PlayerInfo.getPlayerInfo();
					PxGameConstants.playerGold += 300;
					info3.setGold(PxGameConstants.playerGold);
					PlayerInfo.setPlayerInfo(info3);
					PxGameConstants.IS_PLAY_GOLD_ANIM = true;
					break;
				case 4:
					SignManager.sign(activity);
					PlayerInfo info4 = PlayerInfo.getPlayerInfo();
					PxGameConstants.playerGold += 350;
					info4.setGold(PxGameConstants.playerGold);
					PlayerInfo.setPlayerInfo(info4);
					PxGameConstants.IS_PLAY_GOLD_ANIM = true;
					break;
				case 5:
					SignManager.sign(activity);
					PlayerInfo info5 = PlayerInfo.getPlayerInfo();
					PxGameConstants.playerGold += 400;
					info5.setGold(PxGameConstants.playerGold);
					PlayerInfo.setPlayerInfo(info5);
					PxGameConstants.IS_PLAY_GOLD_ANIM = true;
					break;
				case 6:
					// 先发放金币
					SignManager.sign(activity);
					PlayerInfo info6 = PlayerInfo.getPlayerInfo();
					PxGameConstants.playerGold += 1000;
					info6.setGold(PxGameConstants.playerGold);
					PlayerInfo.setPlayerInfo(info6);
					PxGameConstants.IS_PLAY_GOLD_ANIM = true;
					SignManager.cleanSignDays(activity);
					break;
				}
				activity.removeDialog(GameActivity.SHOW_SING_DIALOG);
			}
		});
	}

	public void setCurrentDay(int day) {
		currentDay = day;
		Log.e("com.poxiao.fish", "currentDay" + currentDay);
		switch (day) {
		case 0:
			day_1.setBackgroundResource(R.drawable.object_current);
			day_text_1.setTextColor(Color.parseColor("#863200"));
			break;
		case 1:
			day_1.setBackgroundResource(R.drawable.object_unclick);
			day_2.setBackgroundResource(R.drawable.object_current);
			day_text_2.setTextColor(Color.parseColor("#863200"));
			break;
		case 2:
			day_1.setBackgroundResource(R.drawable.object_unclick);
			day_2.setBackgroundResource(R.drawable.object_unclick);
			day_3.setBackgroundResource(R.drawable.object_current);
			day_text_3.setTextColor(Color.parseColor("#863200"));
			break;
		case 3:
			day_1.setBackgroundResource(R.drawable.object_unclick);
			day_2.setBackgroundResource(R.drawable.object_unclick);
			day_3.setBackgroundResource(R.drawable.object_unclick);
			day_4.setBackgroundResource(R.drawable.object_current);
			day_text_4.setTextColor(Color.parseColor("#863200"));
			break;

		case 4:
			day_1.setBackgroundResource(R.drawable.object_unclick);
			day_2.setBackgroundResource(R.drawable.object_unclick);
			day_3.setBackgroundResource(R.drawable.object_unclick);
			day_4.setBackgroundResource(R.drawable.object_unclick);
			day_5.setBackgroundResource(R.drawable.object_current);
			day_text_5.setTextColor(Color.parseColor("#863200"));
			break;

		case 5:
			day_1.setBackgroundResource(R.drawable.object_unclick);
			day_2.setBackgroundResource(R.drawable.object_unclick);
			day_3.setBackgroundResource(R.drawable.object_unclick);
			day_4.setBackgroundResource(R.drawable.object_unclick);
			day_5.setBackgroundResource(R.drawable.object_unclick);
			day_6.setBackgroundResource(R.drawable.object_current);
			day_text_6.setTextColor(Color.parseColor("#863200"));
			break;

		case 6:
			day_1.setBackgroundResource(R.drawable.object_unclick);
			day_2.setBackgroundResource(R.drawable.object_unclick);
			day_3.setBackgroundResource(R.drawable.object_unclick);
			day_4.setBackgroundResource(R.drawable.object_unclick);
			day_5.setBackgroundResource(R.drawable.object_unclick);
			day_6.setBackgroundResource(R.drawable.object_unclick);
			day_7.setBackgroundResource(R.drawable.object_current);
			day_text_7.setTextColor(Color.parseColor("#863200"));
			break;
		}
	}

	@Override
	public void onBackPressed() {

		switch (currentDay) {
		case 0:
			SignManager.sign(activity);
			PlayerInfo info0 = PlayerInfo.getPlayerInfo();
			PxGameConstants.playerGold += 150;
			info0.setGold(PxGameConstants.playerGold);
			PlayerInfo.setPlayerInfo(info0);
			Log.e("com.poxiao.fish", "GameConstants.playerGold "
					+ PxGameConstants.playerGold);
			PxGameConstants.IS_PLAY_GOLD_ANIM = true;
			break;
		case 1:
			SignManager.sign(activity);
			PlayerInfo info1 = PlayerInfo.getPlayerInfo();
			PxGameConstants.playerGold += 200;
			info1.setGold(PxGameConstants.playerGold);
			PlayerInfo.setPlayerInfo(info1);
			PxGameConstants.IS_PLAY_GOLD_ANIM = true;
			break;
		case 2:
			SignManager.sign(activity);
			PlayerInfo info2 = PlayerInfo.getPlayerInfo();
			PxGameConstants.playerGold += 250;
			info2.setGold(PxGameConstants.playerGold);
			PlayerInfo.setPlayerInfo(info2);
			PxGameConstants.IS_PLAY_GOLD_ANIM = true;
			break;
		case 3:
			SignManager.sign(activity);
			PlayerInfo info3 = PlayerInfo.getPlayerInfo();
			PxGameConstants.playerGold += 300;
			info3.setGold(PxGameConstants.playerGold);
			PlayerInfo.setPlayerInfo(info3);
			PxGameConstants.IS_PLAY_GOLD_ANIM = true;
			break;
		case 4:
			SignManager.sign(activity);
			PlayerInfo info4 = PlayerInfo.getPlayerInfo();
			PxGameConstants.playerGold += 350;
			info4.setGold(PxGameConstants.playerGold);
			PlayerInfo.setPlayerInfo(info4);
			PxGameConstants.IS_PLAY_GOLD_ANIM = true;
			break;
		case 5:
			SignManager.sign(activity);
			PlayerInfo info5 = PlayerInfo.getPlayerInfo();
			PxGameConstants.playerGold += 400;
			info5.setGold(PxGameConstants.playerGold);
			PlayerInfo.setPlayerInfo(info5);
			PxGameConstants.IS_PLAY_GOLD_ANIM = true;
			break;
		case 6:
			// 先发放金币
			SignManager.sign(activity);
			PlayerInfo info6 = PlayerInfo.getPlayerInfo();
			PxGameConstants.playerGold += 1000;
			info6.setGold(PxGameConstants.playerGold);
			PlayerInfo.setPlayerInfo(info6);
			PxGameConstants.IS_PLAY_GOLD_ANIM = true;
			SignManager.cleanSignDays(activity);
			break;
		}
		activity.removeDialog(GameActivity.SHOW_SING_DIALOG);

	}
}
