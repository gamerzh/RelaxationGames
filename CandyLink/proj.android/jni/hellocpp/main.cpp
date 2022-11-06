#include <memory>
#include <android/log.h>
#include <jni.h>
#include "DreamCallback.h"

#include "AppDelegate.h"

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

namespace {
std::unique_ptr<AppDelegate> appDelegate;
}

void cocos_android_app_init(JNIEnv* env) {
    LOGD("cocos_android_app_init");
    appDelegate.reset(new AppDelegate());
}

extern "C" JNIEXPORT void JNICALL
Java_org_cocos2dx_cpp_AppActivity_dreamCallBack(JNIEnv* env,jclass jcl,jint code,jint result)
{
	DreamCallback::getInstance()->jniCallBack(code,result);
}
