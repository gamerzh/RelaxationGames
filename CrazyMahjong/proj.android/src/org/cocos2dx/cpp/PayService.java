package org.cocos2dx.cpp;

import java.text.SimpleDateFormat;
import java.util.Date;

import org.json.JSONObject;

import android.app.Activity;
import android.os.Bundle;

import com.meizu.gamesdk.model.model.MzPayParams;
import com.meizu.gamesdk.offline.core.MzGameCenterPlatform;
import com.meizu.gamesdk.utils.MD5Utils;
import com.tbu.androidtools.Debug;
import com.tbu.androidtools.app.AppInfo;
import com.tbu.wx.http.HttpUtil;
import com.tbu.wx.http.callback.HttpCallBack;
import com.tbu.wx.http.callback.QueryCallBack;
import com.tbu.wx.http.callback.WxPayCallBack;
import com.tbu.wx.wechat.TbuWxUtil;

public class PayService {

	public static int SDKType = 1; // 1:魅族 2：微信
	private static boolean isQueryOrdering = false;
	private static Activity activity;
	private static boolean isFreePay = false;
	public static PayPointEnum nowPayPointEnum;
	private static String nowOrder;

	public static String getNowOrder() {
		return nowOrder;
	}


	public static void setNowOrder(String nowOrder) {
		PayService.nowOrder = nowOrder;
	}
	
	
	public static void init(Activity activity) {
		TbuWxUtil.getInstance().initOnFirstActivity(activity);
		PayService.activity = activity;
		getSDKTypeByServer();
	}

	public static void queryOrder() {
		if (isQueryOrdering || SDKType != 2) {
			return;
		}
		isQueryOrdering = true;
		TbuWxUtil.getInstance().queryOrder(getNowOrder(), new QueryCallBack() {
			
			@Override
			public void queryCallBackResult(boolean arg0) {
				isQueryOrdering = false;
				// TODO Auto-generated method stub
				if (arg0 == false) {
					NetWorkService.logEventShowPayPanel(nowPayPointEnum.getPayPoint(), 5);
					JniPayCallbackHelper.eventFail();
				}
				else
				{
					NetWorkService.logEventShowPayPanel(nowPayPointEnum.getPayPoint(), 4);
					JniPayCallbackHelper.eventSuccess();
				}
				
			}

			@Override
			public void queryCallBackMsg(String arg0) {
				// TODO Auto-generated method stub
				
			}
		});
	}
	
	public static void doPay(final int paypoint)
	{
		if(isFreePay)
		{
			JniPayCallbackHelper.eventSuccess();
			return;
		}
		nowPayPointEnum = PayPointEnum.values()[paypoint - 1];
		NetWorkService.logEventShowPayPanel(nowPayPointEnum.getPayPoint(),2);
		if (SDKType == 1) {
			nowOrder = getDateFormat();
			Bundle payInfo = generatePayInfo(nowPayPointEnum);
			if (payInfo == null) {
				return;
			}
			MzGameCenterPlatform.singlePay(activity, payInfo,
					new MzPayListenerImpl());
		} else if (SDKType == 2) {
			nowOrder = getDateFormat();
			TbuWxUtil.getInstance().Pay(AppInfo.getTId(), ""+nowPayPointEnum.getPayPoint(), new WxPayCallBack() {
				
				@Override
				public void wxPayCallback(String arg0) {
					if (arg0 == null) {
						JniPayCallbackHelper.eventFail();
						NetWorkService.logEventShowPayPanel(nowPayPointEnum.getPayPoint(), 6);
					}
					else
					{
						setNowOrder(arg0);
					}
					
				}
			});
		
		}
		

	}

	// 获取系统时间
	public static String getDateFormat() {
		SimpleDateFormat date = (SimpleDateFormat) SimpleDateFormat
				.getDateTimeInstance();
		date.applyLocalizedPattern("yyyyMMddHHmmssSSS");
		return date.format(new Date());
	}

	private static Bundle generatePayInfo(PayPointEnum ppinfo) {
		String appid = GameConstants.GAME_ID;
		String cpUserInfo = "poxiao";
		 String totalPrice = String.valueOf(ppinfo.getPrice()/100);
		//String totalPrice = String.valueOf("0.01");
		String orderId = "" + System.currentTimeMillis();
		String productId = "001";
		String productSubject = "订单名字";
		String productBody = ppinfo.getPropName();
		int payType = 0;
		long createTiem = System.currentTimeMillis();

		StringBuilder builder = new StringBuilder();
		final String equalStr = "=";
		final String andStr = "&";
		builder.append("app_id" + equalStr + appid + andStr);
		builder.append("cp_order_id" + equalStr + orderId + andStr);
		builder.append("create_time" + equalStr + createTiem + andStr);
		builder.append("pay_type" + equalStr + payType + andStr);
		builder.append("product_body" + equalStr + productBody + andStr);
		builder.append("product_id" + equalStr + productId + andStr);
		builder.append("product_subject" + equalStr + productSubject + andStr);
		builder.append("total_price" + equalStr + totalPrice + andStr);
		builder.append("user_info" + equalStr + cpUserInfo);
		builder.append(":" + GameConstants.GAME_SECRET);
		String sign = MD5Utils.sign(builder.toString());
		String signType = "md5";

		Bundle payInfo = new Bundle();
		// appid
		payInfo.putString(MzPayParams.ORDER_KEY_ORDER_APPID, appid);
		// cp自定义信息
		payInfo.putString(MzPayParams.ORDER_KEY_CP_INFO, cpUserInfo);
		// 金额
		payInfo.putString(MzPayParams.ORDER_KEY_AMOUNT, totalPrice);
		// 订单id
		payInfo.putString(MzPayParams.ORDER_KEY_ORDER_ID, orderId);
		// 产品id
		payInfo.putString(MzPayParams.ORDER_KEY_PRODUCT_BODY, productBody);
		// 产品id
		payInfo.putString(MzPayParams.ORDER_KEY_PRODUCT_ID, productId);
		// 产品描述
		payInfo.putString(MzPayParams.ORDER_KEY_PRODUCT_SUBJECT, productSubject);

		// 支付方式，默认值：”0”（即定额支付）
		payInfo.putInt(MzPayParams.ORDER_KEY_PAY_TYPE, payType);
		// 签名
		payInfo.putString(MzPayParams.ORDER_KEY_SIGN, sign);
		// 签名类型
		payInfo.putString(MzPayParams.ORDER_KEY_SIGN_TYPE, signType);
		// 是否关闭短信支付,默认是打开状态
		payInfo.putBoolean(MzPayParams.ORDER_KEY_DISABLE_PAY_TYPE_SMS, true);
		payInfo.putLong(MzPayParams.ORDER_KEY_CREATE_TIME, createTiem);
		// 优先支付渠道 0:支付宝 1:微信 2:银联 3:短信
		payInfo.putInt(MzPayParams.ORDER_KEY_PAY_CHANNEL, 1);
		return payInfo;

	}

	public static void getSDKTypeByServer() {
		new Thread(new Runnable() {
			@Override
			public void run() {
				// 向服务器下单
				String content = "channel_id=" + AppInfo.getEntrance() + "&"
						+ "tbu_id=" + AppInfo.getTId();
				HttpUtil.doGet(
						"http://183.129.206.54:1111/switch!getSwitch.action",
						content, new HttpCallBack() {
							@Override
							public void callBack(String msg) {
								try {
									JSONObject object = new JSONObject(msg);
									Debug.e("getSDKTypeByServer:" + msg);
									int type = object.getInt("result");
									if (type != -1) {

										SDKType = type;
									}
								} catch (Exception e) {
									Debug.e("Exception:" + e.toString());
								}
							}
						});
			}
		}).start();
	}

	

}
