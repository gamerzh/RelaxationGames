package org.cocos2dx.cpp;

public class JniPayCallbackHelper {	
	public static native void eventSuccess();
	public static native void eventClose();
	public static native void eventFail();
	public static native void getHDstring(String info);
	public static native void HotOver();
}
