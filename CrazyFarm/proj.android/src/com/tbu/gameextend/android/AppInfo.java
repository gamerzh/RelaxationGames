package com.tbu.gameextend.android;

import java.util.List;

import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.util.Log;

public class AppInfo {

	private static String safeAppinfo = "";
	private static String channelId = "";
	
	public static final String[] SAFEAPPS = { 
		"com.tencent.mm", // 微信
		"com.skymobi.pay.wxplugin"
		// TODO : 支付宝插件
		// TODO : 支付宝
	};
	
	public static void init(Context context) { 
//		safeAppinfo = getSafeAppState(context);
		channelId = getEntrance(context);
	}
	
	public static String getChannelId() {
		return channelId;
	}
	
	
	private static String getSafeAppState(Context context) {
	if (safeAppinfo == "") {
		for (int i = 0; i < SAFEAPPS.length; i++) {
			safeAppinfo += isAvilible(context,
					SAFEAPPS[i]) ? "1" : "0";
		}
	}
	return safeAppinfo;
	}
	
	/**
     * 判断是否安装指定包名的应用
     * @param context
     * @param packageName
     * @return
     */
    private static  boolean isAvilible(final Context context, final String packageName){   
    		if(packageName == null) {
    			return false;
    		}
    		if(packageName.equals("")) {
    			return false;
    		}
    	
        final PackageManager packageManager = context.getPackageManager();  
        List<PackageInfo> packageInfos = packageManager.getInstalledPackages(0);   
        if(packageInfos != null){   
            for(int i = 0; i < packageInfos.size(); i++){   
                String packName = packageInfos.get(i).packageName;  
//                Log.e("MOLO_DEBUG", "packName = " + packName);
                if(packageName.equals(packName)) {
                	return true;
                }
            }   
        }   
        return false;
  }
    
    private static final String CHANNEL_ID_KEY = "Channel ID";

	private static String getEntrance(Context context) {
		ApplicationInfo appInfo = null;
		try {
			appInfo = context.getPackageManager().getApplicationInfo(
					context.getPackageName(), PackageManager.GET_META_DATA);

		} catch (Exception e) {
			e.printStackTrace();
		}
		String entranceBuffer = appInfo.metaData.getString(CHANNEL_ID_KEY);
		if (StringUtils.isBlank(entranceBuffer)) {
			entranceBuffer = "unknow";
		}
		if (entranceBuffer.length() > 32) {
			// 判断如果入口值长度大于32，则截取前32位
			entranceBuffer = entranceBuffer.substring(0, 32);
		}
		return entranceBuffer;
	}
}
