package com.xiao.fish.widget;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.text.SimpleDateFormat;

import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.params.BasicHttpParams;
import org.apache.http.params.HttpConnectionParams;
import org.apache.http.params.HttpParams;

import android.content.Context;
import android.util.Log;

import com.tbu.androidtools.app.AppInfo;

public class MarqueeUpdater {

	private final static String TAG = "MarqueeUpdater";

	private static MarqueeUpdater instance;

	private boolean inWorkProcess = false;

	private final static String LOG_SERVER_URL = "http://115.236.18.198:8088/fn/getMarqueeInfo.htm";

	private SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

	private String marquee;

	public interface MarqueeListener {
		public void onUpdate();
	}

	private MarqueeListener listener;

	private MarqueeUpdater() {

	}

	public static MarqueeUpdater getInstance() {
		if (instance == null) {
			instance = new MarqueeUpdater();
		}
		return instance;
	}

	public void update(final Context context) {
		if (inWorkProcess == true) {
			return;
		}
		inWorkProcess = true;
		Thread thread = new Thread() {
			@Override
			public void run() {

				doUpload(context);
				inWorkProcess = false;

			}
		};
		thread.setDaemon(true);
		thread.start();

	}

	protected void doUpload(Context context) {
		// TODO
		String param = "appId=" + "7002646" + "&&channelId="
				+ AppInfo.getEntrance();

		if (param == null || param.trim().equals("")) {
			Log.d(TAG, "no record to upload");
			return;
		}

		HttpParams httpParameters = new BasicHttpParams();
		// Set the timeout in milliseconds until a connection is established.
		// The default value is zero, that means the timeout is not used.
		int timeoutConnection = 4000;
		HttpConnectionParams.setConnectionTimeout(httpParameters,
				timeoutConnection);
		// Set the default socket timeout (SO_TIMEOUT)
		// in milliseconds which is the timeout for waiting for data.
		HttpConnectionParams.setSoTimeout(httpParameters, timeoutConnection);
		HttpClient httpclient = new DefaultHttpClient(httpParameters);
		HttpGet target = new HttpGet(LOG_SERVER_URL + "?" + "channelId="
				+ AppInfo.getEntrance() + "&appId=" + "7002646");
		HttpResponse resp = null;
		InputStream is = null;
		try {

			resp = httpclient.execute(target);

			if (resp != null && resp.getStatusLine() != null
					&& resp.getStatusLine().getStatusCode() == 200) {
				is = resp.getEntity().getContent();
				String text = getStringFromInputStream(is);
				Log.e("Marquee", "marquee content=" + text);
				if (text != null && text.length() > 0) {
					marquee = text;
					if (listener != null) {
						listener.onUpdate();
					}
				}

			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			try {
				if (is != null) {
					is.close();
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

	}

	public boolean isInWorkProcess() {
		return inWorkProcess;
	}

	public static String getStringFromInputStream(InputStream in)
			throws IOException {

		InputStreamReader is = new InputStreamReader(in);
		StringBuilder sb = new StringBuilder();
		BufferedReader br = new BufferedReader(is);
		String read = br.readLine();

		while (read != null) {
			// System.out.println(read);
			sb.append(read);
			read = br.readLine();

		}

		return sb.toString();
	}

	public void setListener(MarqueeListener listener) {
		this.listener = listener;
	}

	public String getMarquee() {
		return marquee;
	}

}
