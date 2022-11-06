package org.cocos2dx.cpp;



import java.io.UnsupportedEncodingException;
import java.net.URLEncoder;
import java.util.Random;

import org.cocos2dx.cpp.tbuAnalysis.HttpManage;

import android.app.Activity;
import android.content.Context;
import android.telephony.TelephonyManager;

import com.avos.avoscloud.AVAnalytics;
import com.tbu.androidtools.Debug;




public class NetWorkService {

	private static Activity activity;


	public static void init(final Activity activity) {
		NetWorkService.activity = activity;
	}
	public static void quit() {
//		AppApplication.quitGame(activity, new ExitGameInterface() {
//			@Override
//			public void quitGame() {
//				GameApplication.getInstance().fullExitApplication();
//		
//		}
//		});
	}
	public static boolean isHdOpen() {
		return false;
//		return HdConfig.isHdOpen();
	}
	public static void showHdDialog() {
//		HdUtils.showHdDialog(activity,new  HotCallback() {
//			
//			@Override
//			public void update() {
//				JniPayCallbackHelper.HotOver();
//				
//			}
//		});
	}
	public static void getstring() {
//		HdUtils.getHdTextInfo(new HdCallback() {
//			
//			@Override
//			public void setHdTextInfo(String info) {
//				JniPayCallbackHelper.getHDstring(info);
//			}
//		});
	}
	public static String getlocalstring() {
		return "";
//		return HdUtils.getHdTaskInfo();
	}
	public static void showMoreGame() {
		GameApplication.getInstance().showMoreGame(activity);
	}
	
	public static void logEvent(String eventName, String  tag) throws UnsupportedEncodingException
	{
		Debug.e("avos log custom event = "+"eventName="+eventName+"*************tag="+tag);
		AVAnalytics.onEvent(activity,eventName,tag);
		
		logEventByTBUanalysis(eventName,tag,"");
	}
	public static void logEvent(String eventName) throws UnsupportedEncodingException
	{
		Debug.e("avos log custom event = "+"eventName="+eventName);
		AVAnalytics.onEvent(activity,eventName);
		
		logEventByTBUanalysis(eventName,"","");
	}
	public static String getImei()
	{
		TelephonyManager tm = (TelephonyManager)activity
				.getSystemService(Context.TELEPHONY_SERVICE);
		return tm.getDeviceId();
	}

	public static void logEventShowPayPanel(int paypoint,int state)
	{
		String _state = null;
		int paytype = -1;
		int resulttype = -1;
		switch (state) {
		case 1:
			_state = "展示";
			break;
		case 2:
			_state = "确认";
			break;
		case 3:
			_state = "取消 ";
			resulttype = -3;
			paytype = 0;
			break;
		case 4:
			_state = "成功";
			resulttype = 0;
			paytype = 1;
		
			break;
		case 5:
			_state = "失败";
			resulttype = 1;
			paytype = 1;
			
			break;
		case 6:
			_state = "下单失败 ";
			break;
		default:
			return;
		}
		if(paypoint==-1)
		{
			try {
				logEvent("计费_商城"+""+_state);
			} catch (UnsupportedEncodingException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		else
		{
			PayPointEnum temp = PayPointEnum.values()[paypoint - 1];
			
			//poxiao pay update
			BServerManagerly.tbuMarkPStart(activity);
			String orderlink = "";
			if(_state == "取消 ")
			{
				orderlink = getRandomString(3)+System.currentTimeMillis();
			}
			else
			{
				orderlink  = PayService.getNowOrder();
			}
			if(resulttype!=-1&&paytype!=-1)
			{
				if(orderlink == "")
				{
					orderlink = getRandomString(3)+System.currentTimeMillis();
				}
				Debug.e("BServerManagerly.tbuMarkPResult");
				BServerManagerly.tbuMarkPResult(activity, ""+temp.getPayPoint(), temp.getPropName(), temp.getPrice(), ""+resulttype, orderlink,temp.getPrice(), "mz", ""+paytype);
			}
			//poxiao mask update
			try {
				logEvent("计费_"+paypoint+"_"+temp.getPropName()+"_"+_state);
			} catch (UnsupportedEncodingException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
	}
	private static void logEventByTBUanalysis( String event, String eventExtend, String sessionTime) throws UnsupportedEncodingException
	{	
		Debug.e("TBUanalysis = "+event+eventExtend+sessionTime);
		String eventPayVersion ="11";  //11
		event = new String(event.toString().getBytes("UTF-8"));  
		event = URLEncoder.encode(event, "UTF-8"); 
		HttpManage.uploadData(eventPayVersion, event, eventExtend, sessionTime);
	}
	public static String getRandomString(int length) { // length表示生成字符串的长度
		String base = "abcdefghijklmnopqrstuvwxyz";
		Random random = new Random();
		StringBuffer sb = new StringBuffer();
		for (int i = 0; i < length; i++) {
			int number = random.nextInt(base.length());
			sb.append(base.charAt(number));
		}
		return sb.toString();
	}
}
