#include "Dream.h"
#include "DreamEvent.h"
#include "UserData.h"
#define JAVA_SRC getJniPath()

Dream* Dream::_instance = 0;

Dream::Dream() {
	_jniPath = "org/cocos2dx/cpp/AppActivity";
}

Dream* Dream::getInstance() {
	if (_instance == 0) {
		_instance = new Dream();
	}
	return _instance;
}

const char*  Dream::getJniPath()
{
	return _jniPath.c_str();
}





void Dream::requestEvent(int dreamId) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	auto path = String::createWithFormat("%s%s", JAVA_SRC, "");
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, path->getCString(), "dream", "(I)V");
	if (isHave) {
		JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, dreamId);
	}
#endif
}

void Dream::recordEvent(std::string dreamId, std::string action) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	auto path = String::createWithFormat("%s%s", JAVA_SRC, "");
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, path->getCString(), "recordDream", "(Ljava/lang/String;Ljava/lang/String;)V");
	if (isHave) {
		jstring dream_id = JniHelper::getEnv()->NewStringUTF(dreamId.c_str());
		jstring action_name = JniHelper::getEnv()->NewStringUTF(action.c_str());;
		JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, dream_id, action_name);
	}
#endif	
}

void Dream::quitGame() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	auto path = String::createWithFormat("%s%s", JAVA_SRC, "");
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, path->getCString(), "exit", "()V");
	if (isHave) {
		JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
	}
#endif
}

void Dream::getDreamTimes() {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo methodInfo;
	auto path = String::createWithFormat("%s%s", JAVA_SRC, "");
	bool isHave = JniHelper::getStaticMethodInfo(methodInfo, path->getCString(), "getDreamTime", "()Z");
	if (isHave) {
		jboolean result = JniHelper::getEnv()->CallStaticBooleanMethod(methodInfo.classID, methodInfo.methodID);
		if ((bool)result) {
			UserData::getInstance()->setDreamTimes(true);
		}
		else {
			UserData::getInstance()->setDreamTimes(false);
		}
	}
#endif
}