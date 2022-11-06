#include "JniFunUtill.h"


JniFunUtill* JniFunUtill::_instance = 0;
JniFunUtill::JniFunUtill(){
}
JniFunUtill* JniFunUtill::getInstance(){
	if(_instance == 0){
		_instance = new JniFunUtill();
	}
	return _instance;
}

const char * JniFunUtill::getSDcardpath()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "org/cocos2dx/cpp/AppActivity", "getSDPath", "()Ljava/lang/String;")) {
		jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
		CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
		ret->autorelease();
		t.env->DeleteLocalRef(str);
		return ret->getCString();
	}
	return "";
#endif
	return " ";
}

const char* JniFunUtill::getChannelId(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "com/tbu/gameextend/android/GameExtend", "getChannelId", "()Ljava/lang/String;")) {
		jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
		CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
		ret->autorelease();
		t.env->DeleteLocalRef(str);
		return ret->getCString();
	}
	return "";
#endif
	return " ";
}

const char* JniFunUtill::getImei()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "com/tbu/gameextend/android/GameExtend", "getImei", "()Ljava/lang/String;")) {
		jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
		CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
		ret->autorelease();
		t.env->DeleteLocalRef(str);
		return ret->getCString();
	}
	return "";
#endif
	return " ";
}
const char*JniFunUtill::getHdFactory()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "com/tbu/gameextend/android/GameExtend", "getHdFactory", "()Ljava/lang/String;")) {
		jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
		CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
		ret->autorelease();
		t.env->DeleteLocalRef(str);
		return ret->getCString();
	}
	return "";
#endif
	return " ";
}
const char*JniFunUtill::getHdType()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t, "com/tbu/gameextend/android/GameExtend", "getHdType", "()Ljava/lang/String;")) {
		jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
		CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
		ret->autorelease();
		t.env->DeleteLocalRef(str);
		return ret->getCString();
	}
	return "";
#endif
	return " ";
}

void JniFunUtill::showFeedBackDialog()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "showFeedDialogOnUiThread", "()V");
	if (isHave){
		jobject jobj;
		JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
	}
#endif
}

void JniFunUtill::SKYPay(int price, const char* orderid)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo,"org/cocos2dx/cpp/AppActivity","pay","(ILjava/lang/String;)V");
	jstring jorderid = methodInfo.env->NewStringUTF(orderid);
	jint jprice = price;
	if(isHave){
		jobject jobj;
		JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID,jprice,jorderid);
}
#endif
}


void JniFunUtill::WXPay(const char* prepayId, const char* nonceStr, const char* timeStamp, const char* sign)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/cpp/AppActivity", "WXpay",  "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");;
	jstring jprepayId = methodInfo.env->NewStringUTF(prepayId);
	jstring jnonceStr = methodInfo.env->NewStringUTF(nonceStr);
	jstring jtimeStamp = methodInfo.env->NewStringUTF(timeStamp);
	jstring jsign = methodInfo.env->NewStringUTF(sign);
	if (isHave){
		jobject jobj;
		JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, jprepayId, jnonceStr, jtimeStamp, jsign);
	}
#endif
}

bool JniFunUtill::isWXAppInstalled()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	jboolean r = false;
	JniMethodInfo t;
	if (JniHelper::getStaticMethodInfo(t,"org/cocos2dx/cpp/AppActivity", "isWXAppInstalled", "()Z")) {
		r = t.env->CallStaticBooleanMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
	}
	return r;
#endif
	return true;
}