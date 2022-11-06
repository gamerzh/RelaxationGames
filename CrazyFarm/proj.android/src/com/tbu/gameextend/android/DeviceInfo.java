package com.tbu.gameextend.android;

import android.content.Context;
import android.telephony.TelephonyManager;

public class DeviceInfo {

	private static String imei;
	private static String hdFactory;
	private static String hdType;
	
	public static void initDeviceInfo(Context context) {
		TelephonyManager tm = (TelephonyManager) context
				.getSystemService(Context.TELEPHONY_SERVICE);
		imei = formatImei(tm.getDeviceId());
		hdFactory = initHdFactory();
		hdType = initHdType();
	}
	
	public static String getImei() {
		return imei;
	}
	
	public static String getHdFactory() {
		return hdFactory;
	}
	
	public static String getHdType() {
		return hdType;
	}

	/**
	 * 格式化IMEI
	 * 
	 * @param imei
	 * @return
	 */
	private static String formatImei(String imei) {
		if (StringUtils.isBlank(imei)) {
			imei = "111111111111111";
		} else if (imei.length() < 15) {
			int len = imei.length();
			int s = 15 - len;
			StringBuffer sb = new StringBuffer();
			for (int i = 0; i < s; i++) {
				sb.append("0");
			}
			imei += sb.toString();
		} else if (imei.length() > 15) {
			imei = imei.substring(0, 15);
		}
		return imei;
	}
	
	public static String initHdFactory() {
		String pro = android.os.Build.MANUFACTURER;
		if (StringUtils.isBlank(pro)) {
			pro = "unknow";
		}
		return pro;
	}

	public static String initHdType() {
		String modle = android.os.Build.MODEL;
		if (StringUtils.isBlank(modle)) {
			modle = "unknow";
		}
		return modle;
	}
}
