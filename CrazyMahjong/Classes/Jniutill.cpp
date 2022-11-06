#include "Jniutill.h"
#include "platform\android\jni\JniHelper.h"
#include "json/document.h"
#include "json/stringbuffer.h"
#include "json/writer.h"
#define JAVA_SRC getJniPath()
Jniutill* Jniutill::_instance = 0;
Jniutill::Jniutill(){

	std::string filename = "ConfigJnipath.json";
	rapidjson::Document doc;
	std::string data = FileUtils::getInstance()->getStringFromFile(filename);
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
	_jniPath = doc["JniPath"].GetString();
}
Jniutill* Jniutill::getInstance(){
	if(_instance == 0){
		_instance = new Jniutill();
	}
	return _instance;
}
const char*  Jniutill::getJniPath()
{
	return _jniPath.c_str();
}
void Jniutill::showMoreGame(){
	CCLOG(">>>>>>>>>>>>>>showMoreGame");
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	    log("android platform");
		JniMethodInfo methodInfo;
		auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/NetWorkService");
		bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"showMoreGame","()V");
		if(isHave){
			JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID);
		}
	#endif
}

void Jniutill::quit(){
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	log("android platform");
		JniMethodInfo methodInfo;
		auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/NetWorkService");
		bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"quit","()V");
		if(isHave){
			JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID);
		}
	#endif
}

void  Jniutill::requestEvent(int eventId){

	
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		JniMethodInfo methodInfo;
		auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/PayService");
		bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"pay","(I)V");
		jint pay_point = eventId;
		//jint reviveNum = GAMEDATA::getInstance()->getReviveNum();
		if(isHave){
			jobject jobj;
			JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID,pay_point);
		}
#endif	

}

void  Jniutill::queryOrder(){


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/PayService");
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"queryOrder","()V");
	//jint reviveNum = GAMEDATA::getInstance()->getReviveNum();
	if(isHave){
		jobject jobj;
		JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
}
#endif	

}

void  Jniutill::doPay(int paypoint){


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	auto path  = String::createWithFormat("%s%s",JAVA_SRC,"/PayService");
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo,path->getCString(),"doPay","(I)V");
	jint jpaypoint = paypoint;
	if(isHave){
		jobject jobj;
		JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID,methodInfo.methodID,jpaypoint);
	}
#endif	

}

bool Jniutill::IsHdOpen()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CCLOG("android platform");
	JniMethodInfo methodInfo;
	auto path = String::createWithFormat("%s%s", JAVA_SRC, "/NetWorkService");
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, path->getCString(), "isHdOpen", "()Z");
	if (isHave){
		return JniHelper::getEnv()->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID);
	}
	else{
		return false;
	}
#endif
	return true;
}
void Jniutill::showHdDialog()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	CCLOG("android platform");
	JniMethodInfo methodInfo;
	auto path = String::createWithFormat("%s%s", JAVA_SRC, "/NetWorkService");
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, path->getCString(), "showHdDialog", "()V");
	if (isHave){
		JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
	}
#endif
}

std::string  Jniutill::JniGetHDname()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	auto path = String::createWithFormat("%s%s", JAVA_SRC, "/NetWorkService");
	if (JniHelper::getStaticMethodInfo(t, path->getCString(), "getlocalstring", "()Ljava/lang/String;")) {
		jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
		CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
		ret->autorelease();
		t.env->DeleteLocalRef(str);
		return ret->getCString();
	}
	return "";
#endif
	return "";
}



bool Jniutill::isSignToday(){
	CCLOG(">>>>>>>>>>>>>>isSignToday");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	CCLOG("android platform");
	JniMethodInfo methodInfo;
	auto path = String::createWithFormat("%s%s", JAVA_SRC, "/SignInService");
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, path->getCString(), "isSignToday", "()Z");
	if (isHave){
		return JniHelper::getEnv()->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID);
	}
	else{
		return false;
	}
#endif
	return false;
}



bool Jniutill::notSignToday(){
	CCLOG(">>>>>>>>>>>>>>notSignToday");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	CCLOG("android platform");
	JniMethodInfo methodInfo;
	auto path = String::createWithFormat("%s%s", JAVA_SRC, "/SignInService");
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, path->getCString(), "notSignToday", "()Z");
	if (isHave){
		return JniHelper::getEnv()->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID);
	}
	else{
		return false;
	}
#endif
	return false;
}

int Jniutill::getCurrentSignDayas(){
	CCLOG(">>>>>>>>>>>>>>getCurrentSignDayas");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	CCLOG("android platform");
	JniMethodInfo methodInfo;
	auto path = String::createWithFormat("%s%s", JAVA_SRC, "/SignInService");
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, path->getCString(), "getCurrentSignDays", "()I");
	if (isHave){
		return JniHelper::getEnv()->CallStaticIntMethod(methodInfo.classID, methodInfo.methodID);
	}
	else{
		return 0;
	}
#endif
	return 4;
}

void Jniutill::sign(){
	CCLOG(">>>>>>>>>>>>>>sign");
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	CCLOG("android platform");
	JniMethodInfo methodInfo;
	auto path = String::createWithFormat("%s%s", JAVA_SRC, "/SignInService");
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, path->getCString(), "sign", "()V");
	if (isHave){
		JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
	}
#endif
}

void Jniutill::logEvent(std::string eventName, std::string  tag){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	CCLOG("android platform");
	JniMethodInfo methodInfo;
	auto path = String::createWithFormat("%s%s", JAVA_SRC, "/NetWorkService");
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, path->getCString(), "logEvent","(Ljava/lang/String;Ljava/lang/String;)V");
	jstring jeventName = methodInfo.env->NewStringUTF(eventName.c_str());
	jstring jtag = methodInfo.env->NewStringUTF(tag.c_str());
	if (isHave){
		JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, jeventName, jtag);
	}
#endif
}
std::string  Jniutill::getImei()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	auto path = String::createWithFormat("%s%s", JAVA_SRC, "/NetWorkService");
	if (JniHelper::getStaticMethodInfo(t, path->getCString(), "getImei", "()Ljava/lang/String;")) {
		jstring str = (jstring)t.env->CallStaticObjectMethod(t.classID, t.methodID);
		t.env->DeleteLocalRef(t.classID);
		CCString *ret = new CCString(JniHelper::jstring2string(str).c_str());
		ret->autorelease();
		t.env->DeleteLocalRef(str);
		return ret->getCString();
	}
	return "";
#endif
	return "";
}


void  Jniutill::logEventShowPayPanel(int paypoint , int state){


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	auto path = String::createWithFormat("%s%s", JAVA_SRC, "/NetWorkService");
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, path->getCString(), "logEventShowPayPanel", "(II)V");
	jint jpaypoint = paypoint;
	jint jstate = state;
	if (isHave){
		jobject jobj;
		JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, jpaypoint,jstate);
	}
#endif	

}