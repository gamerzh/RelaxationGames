package com.d.extend.quitgame;


import android.app.Activity;
import android.app.Dialog;
import android.content.Context;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageButton;

import com.qhbmj.one.mz.R;

public class QuitGameDialog extends Dialog {

	private Activity activity;
	private ExitGameInterface exitGameInterface;
	private ImageButton quit_game_continue;
	private ImageButton quit_game_quit;
	private ImageButton quit_game_cancel;

	public QuitGameDialog(Context context, ExitGameInterface exitGameInterface) {
		super(context, R.style.dialog_game_style);
		setContentView(R.layout.dialog_quit_game);
		this.activity = (Activity) context;
		this.exitGameInterface = exitGameInterface;
	}

	@Override
	public void onCreate(Bundle bundle) {
		super.onCreate(bundle);
		initView();
	}

	private void initView() {
		quit_game_cancel = (ImageButton) findViewById(R.id.qiut_game_cancel);
		quit_game_continue = (ImageButton) findViewById(R.id.quit_game_continue);
		quit_game_quit = (ImageButton) findViewById(R.id.qiut_game_quit);
		quit_game_cancel.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View view) {
				dismiss();
			}
		});
		quit_game_continue.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View view) {
				dismiss();
			}
		});
		quit_game_quit.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View view) {
				dismiss();
				activity.finish();
				exitGameInterface.quitGame();
			}
		});

	}

	@Override
	public void onBackPressed() {
		super.onBackPressed();
	}
}
