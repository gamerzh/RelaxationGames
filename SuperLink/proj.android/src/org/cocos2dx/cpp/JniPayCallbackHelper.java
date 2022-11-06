package org.cocos2dx.cpp;

public class JniPayCallbackHelper {	
	public static native void eventSuccess(int eventId, int[] propIds,int[] propNums);
	public static native void eventClose(int eventId);
	public static native void eventFail(int eventId);
	public static native void showMoreGameNative(boolean open);
	public static native void showTehui(boolean open);
}
