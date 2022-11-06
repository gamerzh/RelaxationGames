package org.cocos2dx.cpp;


import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;

import android.content.Context;

import com.tbu.androidtools.Debug;
import com.tbu.androidtools.app.AppInfo;
import com.tbu.androidtools.device.DeviceInfo;
import com.tbu.androidtools.ugly.http.KeyValue;

/**
 * B工程统计信息记录工具类
 * 
 * @author molo
 * 
 */
public class BServerManagerly {
	public static final String POST_P_MARK_URL = "http://183.131.78.79:1503/black_white/pay_plugin_info";

	public static final String P_TYPE_REQUEST = "0"; // 请求
	public static final String P_TYPE_REPAY = "0"; // 切换支付插件
	public static final String P_TYPE_RESULT = "1"; // 支付结果
	public static final String P_TYPE_ERROR_USER = "4";// 异常imei或者imsi用户

	private static String orderId = null;
	private static long startTime = 0;
	private static int serialId = 0;
	private static int sameId = 1;

	public static void tbuMarkPStart(Context context) {
		startTime = System.currentTimeMillis();
		sameId=1;
	}
	public static void tbuMarkPResult(Context context, String pPoint,String pPoint_Name,int pPoint_price,
			String pResult, String orderlinkid,
			int realMoey, String paypluginName,String payType) {
		Debug.e("tbuMarkPResult begin");
		boolean pTypeTwice = false;
		String  orderlinkId = "faillinkId";
		String uiMessage = "";
		int uitype =6;
		String bVersion = "";
		String phonenum = "";
		String errorCode = "1";
		if (null != orderlinkId) {
			serialId = serialId + 1;
			long time = System.currentTimeMillis() - startTime;
			String payInfo = BServerManagerly.createPayInfo(context, 
					orderlinkid, orderlinkId,pResult, (int) (time / 1000),
					payType, paypluginName, pTypeTwice,
					pPoint, pPoint_Name,
					pPoint_price, realMoey, uitype,
					phonenum, pPoint, errorCode, serialId,
					bVersion,uiMessage);
			BServerManagerly.remarkPayOnBackground(context,
					BServerManagerly.P_TYPE_RESULT, payInfo, 1);
			serialId = 0;
			startTime = System.currentTimeMillis();
		}
	}

	/**
	 * 
	 * @param context
	 * @param orderId
	 *            订单号
	 * @param linkId
	 *            订单标识
	 * @param pResult
	 *            支结果
	 * @param sessionTime
	 *            支会话时间
	 * @param pType
	 *            订单类型（0下单||切换；1 结果）
	 * @param pPluginName
	 *            当前插件名称
	 * @param pTypeTwice
	 *            是否开了二次
	 * @param pPintId
	 *            计费点编号
	 * @param pPintName
	 *            计费点名称
	 * @param moey
	 *            请求支金额
	 * @param realMoey
	 *            实际支金额
	 * @param uitype
	 *            游戏计费点界面1 直接启sdk（无界面）；2 黑包；6 主线包（沿用之前黑白包一套的定义）
	 * @param phone
	 *            手机号
	 * @param eventId
	 *            事件点
	 * @param errorCode
	 *            支结果码
	 * @return
	 */

	private static String createPayInfo(Context context, String orderId,
			String linkId, String pResult, int sessionTime, String pType,
			String pPluginName, boolean pTypeTwice, String pPintId,
			String pPointName, int moey, int realMoey, int uitype,
			String phone, String eventId, String errorCode, int serialId,
			String bVersion,String uiMessage) {
		KeyValue keyValue1 = new KeyValue("order_id", orderId);
		KeyValue keyValue2 = new KeyValue("link_id", linkId);
		KeyValue keyValue3 = new KeyValue("channel_id", AppInfo.getEntrance());
		KeyValue keyValue4 = new KeyValue("tbu_id", AppInfo.getTId());
		KeyValue keyValue5;
		try {
			keyValue5 = new KeyValue("app_name", URLEncoder.encode(
					AppInfo.getAppName(), "utf-8"));
		} catch (UnsupportedEncodingException e) {
			keyValue5 = new KeyValue("app_name", AppInfo.getAppName());
			Debug.i("BServerManager->createpInfo, set app_name fail. e = "
					+ e.toString());
		}
		KeyValue keyValue6 = new KeyValue("game_version", AppInfo.getVersion());
		KeyValue keyValue7 = new KeyValue("p_point_id", pPintId);
		KeyValue keyValue8;
		try {
			keyValue8 = new KeyValue("p_point_name", URLEncoder.encode(
					pPointName, "utf-8"));
		} catch (UnsupportedEncodingException e) {
			keyValue8 = new KeyValue("p_point_name", pPointName);
			Debug.i("BServerManager->createpInfo, set app_name fail. e = "
					+ e.toString());
		}
		KeyValue keyValue9 = new KeyValue("event_id", eventId);
		KeyValue keyValue10 = new KeyValue("ptype_twice",
				pTypeTwice ? String.valueOf(0) : String.valueOf(1));
		KeyValue keyValue11;
		
		try {
			keyValue11 = new KeyValue("p_result", URLEncoder.encode(
					pResult, "utf-8"));

		} catch (UnsupportedEncodingException e) {
			keyValue11 = new KeyValue("p_result", pResult);
			Debug.i("BServerManager->createpInfo, set p_result fail. e = "
					+ e.toString());
		}
		KeyValue keyValue12 = new KeyValue("error_code", errorCode);
		KeyValue keyValue13 = new KeyValue("p_plugin_name", pPluginName);
		KeyValue keyValue14 = new KeyValue("money", String.valueOf(moey));
		KeyValue keyValue15 = new KeyValue("real_money",
					String.valueOf(realMoey));
		
		KeyValue keyValue16 = new KeyValue("session",
				String.valueOf(sessionTime));
		KeyValue keyValue17 = new KeyValue("ui_type", String.valueOf(uitype));
		KeyValue keyValue18 = new KeyValue("serial_id",
				String.valueOf(serialId));
		KeyValue keyValue19;
		if (DeviceInfo.isErrorImeiOrImsi(context)) {
			keyValue19 = new KeyValue("p_type", String.valueOf(pType));
		} else {
			keyValue19 = new KeyValue("p_type", String.valueOf(pType));
		}
		KeyValue keyValue20 = new KeyValue("iccid",
				DeviceInfo.getimSerialNumber());
		KeyValue keyValue21 = new KeyValue("si", DeviceInfo.getsi());
		KeyValue keyValue22 = new KeyValue("ei", DeviceInfo.getei());
		KeyValue keyValue23 = new KeyValue("platform_version",
				DeviceInfo.getPlatformVersion());
		KeyValue keyValue24 = new KeyValue("phone", phone);
		KeyValue keyValue25 = new KeyValue("hd_type", DeviceInfo.getModle());
		KeyValue keyValue26 = new KeyValue("hd_factory",
				DeviceInfo.getProduct());
		KeyValue keyValue27 = new KeyValue("event_p_version",
			"100100");
		KeyValue keyValue28 = new KeyValue("mac", DeviceInfo.getMacAddress());
		KeyValue keyValue29 = new KeyValue("merchant_id", "86010001");
		KeyValue keyValue30 = new KeyValue("third_app",
				DeviceInfo.getSafeAppState());
		KeyValue keyValue31 = new KeyValue("b_version", bVersion);
		KeyValue keyValue32 = new KeyValue("access_type",
				String.valueOf(DeviceInfo.getNewAccessType()));
		KeyValue keyValue33 = new KeyValue("lac", DeviceInfo.getLac());
		KeyValue keyValue34 = new KeyValue("cid", DeviceInfo.getCid());
		KeyValue keyValue35 = new KeyValue("ua", DeviceInfo.getUA());
		KeyValue keyValue36;
		try {
			keyValue36 = new KeyValue("ui_message", URLEncoder.encode(
					uiMessage, "utf-8"));

		} catch (UnsupportedEncodingException e) {
			keyValue36 = new KeyValue("ui_message", uiMessage);
			Debug.i("BServerManager->createpInfo, set ui_message fail. e = "
					+ e.toString());
		}

		return DoContentJoint(keyValue1, keyValue2, keyValue3, keyValue4,
				keyValue5, keyValue6, keyValue7, keyValue8, keyValue9,
				keyValue10, keyValue11, keyValue12, keyValue13, keyValue14,
				keyValue15, keyValue16, keyValue17, keyValue18, keyValue19,
				keyValue20, keyValue21, keyValue22, keyValue23, keyValue24,
				keyValue25, keyValue26, keyValue27, keyValue28, keyValue29,
				keyValue30, keyValue31, keyValue32, keyValue33, keyValue34,
				keyValue35,keyValue36);

	}

	/**
	 * 在异步线程中统计应用信息到服务端
	 */
	private static void remarkPayOnBackground(final Context context,
			final String payType, final String payInfo, final int i) {
		// final String strUrl = ReadJsonUtil.decoderByDES(
		// BServerManager.POST_PAY_MARK_URL, "poxiao_key");
		// Debug.i("B BServerManager remarkPayOnBackground strUrl=" + strUrl);
		Debug.e("syso===== payInfo================="
				+ payInfo.toString());
		new Thread(new Runnable() {
			@Override
			public void run() {
				String result = HttpTools.doPost(context,
						BServerManagerly.POST_P_MARK_URL, payInfo);
//				System.out.println(i + "syso=======result!!!!!!!!====="
//						+ result);
				if (result != null && result.length() > 0) { // 服务端成功协议: '
																// {"result":"0"};
																// '
					if (BServerManagerly.P_TYPE_REQUEST.equals(payType)
							&& result.contains("result")
							&& result.contains("0")) { // 检查返回值，如果成功，设置状态为已经提交过
						Debug.e("update info to server succeed");
					}
				}
				// TODO : 查看上传结果，如果失败则缓存数据
			}
		}).start();
	}

	/**
	 * 获取当前应用的订单号
	 * 
	 * @return 订单号
	 */
	private static String createNewOrderId() {
		return String.valueOf(System.currentTimeMillis());
	}

	private static String DoContentJoint(KeyValue... keyValueArray) {
		if (keyValueArray.length > 0) {
			String httpContent = new String();
			for (int i = 0; i < keyValueArray.length; i++) {
				if (0 == i)
					httpContent += keyValueArray[i].getmKeyString() + "="
							+ keyValueArray[i].getmValueString();// "?"+
				else
					httpContent += "&" + keyValueArray[i].getmKeyString() + "="
							+ keyValueArray[i].getmValueString();
			}
			return httpContent;
		}

		return null;
	}
}
