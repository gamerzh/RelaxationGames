package com.d.extend.moreapp;

import android.app.ProgressDialog;
import android.content.Context;
import android.os.Bundle;
import android.view.WindowManager;
import android.widget.TextView;

public class TipDialog extends ProgressDialog {

	private CharSequence text;

	public TipDialog(Context context, String text) {
		super(context, LayoutUtil.getTipDialogStyleId());
		this.text = text;
	}

	public TipDialog(Context context) {
		super(context, LayoutUtil.getTipDialogStyleId());
	}


	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(LayoutUtil.getTipDialogLayoutResId());

		TextView textView = (TextView) this.findViewById(LayoutUtil.getTipDialogTxtResId());
		textView.setText(text);

		WindowManager.LayoutParams lp = this.getWindow().getAttributes();
		lp.alpha = 0.9f;
		this.getWindow().setAttributes(lp);

	}

	public static TipDialog show(Context context, CharSequence message) {
		TipDialog dialog = new TipDialog(context);
		dialog.setText(message);
		dialog.setCancelable(true);
		dialog.show();
		return dialog;
	}

	public void setText(CharSequence text) {
		this.text = text;
		TextView textView = (TextView) this.findViewById(LayoutUtil.getTipDialogTxtResId());
		if(textView != null){
			textView.setText(text);
		}
		
	}
}
