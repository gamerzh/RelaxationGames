package com.d.extend.moreapp;

import java.util.ArrayList;
import java.util.List;
import android.annotation.SuppressLint;
import android.annotation.TargetApi;
import android.app.Activity;
import android.app.Dialog;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Color;
import android.graphics.drawable.ColorDrawable;
import android.graphics.drawable.Drawable;
import android.os.Build;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.BaseAdapter;
import android.widget.GridView;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;
import com.d.extend.moreapp.AsyncImageLoader.ImageCallback;
import com.tbu.android.moreapp.MoreGameManager;
import com.tbu.android.moreapp.domain.MoreApp;
import com.tbu.android.moreapp.domain.MoreAppCallback;
import com.tbu.androidtools.Debug;

public class MoreGameDialog extends Dialog {

	private Activity activity;

	private GridView gridView;
	private TextView noOtherGameTip;
	private ImageButton closeBtn;

	private List<MoreApp> recommends = new ArrayList<MoreApp>();

	private CrossRecommendAdapter adapter;

	public MoreGameDialog(Context context, Activity activity) {
		super(context, LayoutUtil.getMoreGamedialogStyleResId());
		this.activity = activity;
	}

	@Override
	public void onCreate(Bundle bundle) {
		super.onCreate(bundle);
		setContentView(LayoutUtil.getMoreGameLayoutResId());
		recommends = MoreGameManager.getMoreApps(activity
				.getApplicationContext());
		adapter = new CrossRecommendAdapter();
		noOtherGameTip = (TextView) findViewById(LayoutUtil
				.getMoreGameNoDataTipResId());
		closeBtn = (ImageButton) findViewById(LayoutUtil
				.getMoreGameCancelBtnResId());
		closeBtn.setOnClickListener(new View.OnClickListener() {

			@Override
			public void onClick(View v) {
				dismiss();
			}
		});
		gridView = (GridView) findViewById(LayoutUtil
				.getMoreGameGridViewResId());
		gridView.setSelector(new ColorDrawable(Color.TRANSPARENT));
		gridView.setOnItemClickListener(new OnItemClickListener() {
			@Override
			public void onItemClick(AdapterView<?> parent, View view,
					int position, long id) {
				MoreApp info = (MoreApp) parent.getItemAtPosition(position);
				MoreGameManager.doStartNewGame(
						activity.getApplicationContext(),
						info.getPackageName(), info.getDownloadUrl());
			}
		});
		gridView.setAdapter(adapter);

		initDatas(this.activity.getApplicationContext());
	}

	protected void initDatas(final Context context) {
		if (this.recommends != null && this.recommends.size() > 0) {
			Debug.i("MoreGameDialog->initDatas , recommends size = "
					+ recommends.size());
			adapter.updateDatas();
			return;
		}
		Debug.i("MoreGameDialog->initDatas start");
		MoreGameManager.init(context, new MoreAppCallback() {

			@Override
			public void result(boolean changed) {
				Debug.i("MoreGameDialog->initDatas , get result, changed = "
						+ changed);
				recommends = MoreGameManager.getMoreApps(context);

				if (recommends != null && recommends.size() > 0) {
					adapter.updateDatas();
				} else {
					Debug.i("MoreGameDialog->initDatas , get result, recommendList == null | size <=0");
					if (!changed) {
						setNoMoreGame();
					} else {
						getOtherGameList();
					}
				}

			}
		});
	}

	class CrossRecommendAdapter extends BaseAdapter {

		public CrossRecommendAdapter() {
		}

		@Override
		public int getCount() {
			if (recommends != null && recommends.size() > 0) {
				return recommends.size();
			}
			return 0;
		}

		@Override
		public Object getItem(int position) {
			if (recommends != null && recommends.size() > position) {
				return recommends.get(position);
			}
			return null;
		}

		@Override
		public long getItemId(int position) {
			return position;
		}

		@Override
		public View getView(int position, View convertView, ViewGroup parent) {
			ViewHolder holder = null;
			holder = new ViewHolder();
			LayoutInflater inflater = (LayoutInflater) activity
					.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
			convertView = inflater.inflate(
					LayoutUtil.getMoreGameViewItemLayoutResId(), null);
			holder.gameIcon = (ImageView) convertView.findViewById(LayoutUtil
					.getMoreGameViewItemGameIconResId());
			holder.gameName = (TextView) convertView.findViewById(LayoutUtil
					.getMoreGameViewItemGameNameResId());
			convertView.setTag(holder);

			if (recommends != null && recommends.size() > position) {
				MoreApp info = recommends.get(position);
				if (info != null) {
					holder.loadImage(info.getIconUrl());
					holder.gameName.setText(info.getAppName());
				}
			}

			return convertView;
		}

		public void updateDatas() {
			if (null != recommends && recommends.size() > 0) {
				activity.runOnUiThread(new Runnable() {
					public void run() {
						notifyDataSetChanged();
					}
				});
			}
		}
	}

	class ViewHolder {
		ImageView gameIcon;
		TextView gameName;

		boolean mIsLoadImage = false;
		AsyncImageLoader mAsyncImageLoader = new AsyncImageLoader();

		public void loadImage(final String iconUrl) {
			if (!mIsLoadImage && (null != gameIcon)) {
				mIsLoadImage = true;
				Drawable drawable = mAsyncImageLoader.loadDrawable(iconUrl,
						new ImageCallback() {

							@Override
							public void imageLoaded(Bitmap bitMap,
									String imageUrl) {
							}

							@Override
							public void imageLoaded(Drawable imageDrawable,
									String imageUrl) {
								gameIcon.setImageDrawable(imageDrawable);
							}
						});
				if (null != drawable) {
					gameIcon.setImageDrawable(drawable);
				}
			}
		}
	}

	private void getOtherGameList() {
		noOtherGameTip.setVisibility(View.VISIBLE);
	}

	private void setNoMoreGame() {
		Debug.w("QuitGameDialog->setNoMoreGame,没有交叉推荐");
		activity.runOnUiThread(new Runnable() {
			public void run() {
				noOtherGameTip.setText("暂时没有游戏推荐");
				noOtherGameTip.setVisibility(View.VISIBLE);
			}
		});
	}


	@TargetApi(Build.VERSION_CODES.ECLAIR)
	@Override
	public void onBackPressed() {
		super.onBackPressed();
	}
}
