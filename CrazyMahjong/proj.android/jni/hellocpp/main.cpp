#include "AppDelegate.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>
#include "MenuScenePayHandler.h"

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;

void cocos_android_app_init (JNIEnv* env, jobject thiz) {
    LOGD("cocos_android_app_init");
    AppDelegate *pAppDelegate = new AppDelegate();
}
extern "C" JNIEXPORT void JNICALL
Java_org_cocos2dx_cpp_JniPayCallbackHelper_eventSuccess(JNIEnv* env, jclass jcl)
{
		MenuScenePayHandler::getInstance()->dealEventSuccess();
}

extern "C" JNIEXPORT void JNICALL
Java_org_cocos2dx_cpp_JniPayCallbackHelper_eventClose(JNIEnv* env, jclass jcl){
	MenuScenePayHandler::getInstance()->dealEventClose();
}

extern "C" JNIEXPORT void JNICALL
Java_org_cocos2dx_cpp_JniPayCallbackHelper_eventFail(JNIEnv* env, jclass jcl){

	MenuScenePayHandler::getInstance()->dealEventFail();
}
