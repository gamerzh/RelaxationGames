package org.cocos2dx.cpp.tbuAnalysis;


import com.tbu.androidtools.app.AppInfo;
import com.tbu.androidtools.device.DeviceInfo;
import com.tbu.androidtools.ugly.http.KeyValue;


public class HttpManage
{
  public static final String POST_MARK_URL = "http://183.131.151.228:1371/gamemark";

  public static void uploadData(String eventPayVersion, String event, String eventExtend, String sessionTime)
  {
    final String info = createPayInfo(eventPayVersion, event, eventExtend, 
      sessionTime);
    new Thread(new Runnable() {
      public void run() {
        HttpUtil.doPost("http://183.131.151.228:1371/gamemark", info);
      }
    }).start();
  }

  private static String createPayInfo(String eventPayVersion, String event, String eventExtend, String sessionTime)
  {
    KeyValue keyValue1 = new KeyValue("tbu_id", AppInfo.getTId());
    KeyValue keyValue2 = new KeyValue("imsi", DeviceInfo.getsi());
    KeyValue keyValue3 = new KeyValue("event_pay_version", eventPayVersion);
    KeyValue keyValue4 = new KeyValue("event", event);
    KeyValue keyValue5 = new KeyValue("event_extend", eventExtend);
    KeyValue keyValue6 = new KeyValue("session_time", sessionTime);
    KeyValue keyValue7 = new KeyValue("channel_id", AppInfo.getEntrance());

    return HttpUtil.DoContentJoint(new KeyValue[] { keyValue1, keyValue2, keyValue3, 
      keyValue4, keyValue5, keyValue6, keyValue7 });
  }
}