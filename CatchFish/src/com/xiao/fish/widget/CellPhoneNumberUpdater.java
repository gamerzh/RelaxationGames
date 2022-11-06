package com.xiao.fish.widget;

import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;

import org.apache.http.HttpResponse;
import org.apache.http.HttpStatus;
import org.apache.http.StatusLine;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.params.BasicHttpParams;
import org.apache.http.params.HttpConnectionParams;
import org.apache.http.params.HttpParams;

import android.app.Activity;
import android.content.Context;
import android.os.Build;
import android.telephony.TelephonyManager;
import android.util.Log;

import com.tbu.androidtools.Debug;
import com.tbu.androidtools.app.AppInfo;

public class CellPhoneNumberUpdater {

	private final static String TAG = "CellPhoneNumberUpdater";

	private static CellPhoneNumberUpdater instance;

	private boolean inWorkProcess = false;

	private final static String LOG_SERVER_URL = "http://115.236.18.198:8088/fn/recordPrizeInfo.htm";

	private SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

	public interface CellPhoneUploadListener {
		public void onUploadDone(int result);
	}

	private CellPhoneUploadListener listener;

	private CellPhoneNumberUpdater() {

	}

	public static CellPhoneNumberUpdater getInstance() {
		if (instance == null) {
			instance = new CellPhoneNumberUpdater();
		}
		return instance;
	}

	public void upload(final Context context, final String phone) {
		if (inWorkProcess == true) {
			return;
		}
		inWorkProcess = true;
		Thread thread = new Thread() {
			@Override
			public void run() {

				doUpload(context, phone);
				inWorkProcess = false;

			}
		};
		thread.setDaemon(true);
		thread.start();

	}

	protected void doUpload(Context context, String phone) {

		String imsi = "";
		try {
			TelephonyManager tm = (TelephonyManager) context
					.getSystemService(Activity.TELEPHONY_SERVICE);
			imsi = tm.getSubscriberId();
		} catch (SecurityException e) {
			// e.printStackTrace();
		}
		String imei = "";
		try {
			TelephonyManager tm = (TelephonyManager) context
					.getSystemService(Activity.TELEPHONY_SERVICE);
			imei = tm.getDeviceId();
		} catch (SecurityException e) {
			// e.printStackTrace();
		}
		String param = "gameId=" + "9980" + "&channelId=" + AppInfo.getEntrance()
				+ "&appId=" + "7002646" + "&imei=" + imei + "&imsi=" + imsi
				+ "&submit_time=" + df.format(new Date()) + "&hsman="
				+ Build.MANUFACTURER + "&hstype=" + Build.DISPLAY + "_"
				+ Build.MODEL + "&content=游戏累计5分钟就送1000金币，还有机会赢实物大奖"
				+ "&phone=" + phone;

		if (param == null || param.trim().equals("")) {
			Log.d(TAG, "no record to upload");
			return;
		}

		HttpParams httpParameters = new BasicHttpParams();
		// Set the timeout in milliseconds until a connection is established.
		// The default value is zero, that means the timeout is not used.
		int timeoutConnection = 3000;
		HttpConnectionParams.setConnectionTimeout(httpParameters,
				timeoutConnection);
		// Set the default socket timeout (SO_TIMEOUT)
		// in milliseconds which is the timeout for waiting for data.
		HttpConnectionParams.setSoTimeout(httpParameters, timeoutConnection);
		HttpClient httpclient = new DefaultHttpClient(httpParameters);

		HttpResponse response = null;
		try {
			String url = param;
			url = url.replaceAll(" ", "%20");
			Debug.i("cellphone param:" + url);
			HttpGet httpRequest = new HttpGet(LOG_SERVER_URL + "?" + url);
			// Post运作传送变数必须用NameValuePair[]阵列储存
			// 传参数 服务端获取的方法为request.getParameter("name")
			response = httpclient.execute(httpRequest);
			StatusLine statusLine = response.getStatusLine();
			if (statusLine.getStatusCode() == HttpStatus.SC_OK) {
				if (listener != null) {
					listener.onUploadDone(0);
					listener = null;
				}
			}
		} catch (ClientProtocolException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			if (response != null) {
				try {
					response.getEntity().getContent().close();
				} catch (IllegalStateException e) {
					e.printStackTrace();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}

		}
		if (listener != null) {
			listener.onUploadDone(1);
			listener = null;
		}

	}

	public boolean isInWorkProcess() {
		return inWorkProcess;
	}

	public void setListener(CellPhoneUploadListener listener) {
		this.listener = listener;
	}

}
