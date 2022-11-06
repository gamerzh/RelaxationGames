package com.xiao.fish.widget;

import android.app.Dialog;
import android.content.Context;
import android.view.MotionEvent;
import android.view.View;
import android.widget.EditText;
import android.widget.ImageButton;

import com.kx.byno.R;
import com.tbu.androidtools.Debug;
import com.xiao.fish.widget.CellPhoneNumberUpdater.CellPhoneUploadListener;

public class HotDialog extends Dialog {

	private ImageButton cancel;
	private ImageButton commit;
	private EditText text;
	private Context context;

	public HotDialog(Context context) {
		super(context, R.style.dialog_game_style);
		this.context = context;
		setContentView(R.layout.dialog_hot);
		MarqueeUpdater.getInstance().update(context);
		initView();
	}

	private void initView() {
		text = (EditText) findViewById(R.id.dialog_text);
		text.setOnTouchListener(new View.OnTouchListener() {

			@Override
			public boolean onTouch(View v, MotionEvent event) {
				if ("请输入手机号码".trim().equals(text.getText().toString().trim()))
					text.setText("");
				return false;
			}
		});
		cancel = (ImageButton) findViewById(R.id.dialog_cancel);
		cancel.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				dismiss();
			}
		});
		commit = (ImageButton) findViewById(R.id.dialog_commit);
		commit.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				CellPhoneNumberUpdater.getInstance().setListener(
						new CellPhoneUploadListener() {
							@Override
							public void onUploadDone(int result) {
								Debug.i("HotDialog HotDialog result = "
										+ result);

							}
						});
				CellPhoneNumberUpdater.getInstance().upload(context,
						text.getText().toString());
				dismiss();
			}
		});
	}
}
