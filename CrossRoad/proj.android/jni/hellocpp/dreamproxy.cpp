#include "cocos2d.h"
#include <jni.h>
#include "platform\android\jni\JniHelper.h"
#include "../../../Classes/DreamCallback.h"
using namespace cocos2d;


extern "C" JNIEXPORT void JNICALL
Java_org_cocos2dx_cpp_JniDreamCallbackHelper_dreamCallBack(JNIEnv* env,jclass jcl,jint code,jint result)
{
	DreamCallback::getInstance()->jniCallBack(code,result);
}
