package org.cocos2dx.cpp;

public class JniPayCallbackHelper {	
	public static native void payResultCallBack(int code,String msg,String prepayId);
	
	
	public static native void sendFeedback(String msg);
}
