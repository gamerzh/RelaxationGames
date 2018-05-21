#include "Dream.h"
#define JAVA_SRC getJniPath()

Dream* Dream::_instance = 0;

Dream::Dream() {
	_jniPath = "org/cocos2dx/cpp/payment";
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

void Dream::requestEvent(std::string dreamId) {


}

void Dream::quitGame() {

}

void Dream::recordEvent(std::string dreamId, std::string action){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	//JniMethodInfo methodInfo;
	//auto path = String::createWithFormat("%s%s", JAVA_SRC, "/Payment");
	//bool isHave = JniHelper::getStaticMethodInfo(methodInfo, path->getCString(), "requestEvent", "(Ljava/lang/String;Ljava/lang/String;)V");
	//if (isHave) {
	//	jstring poxiao_id = JniHelper::getEnv()->NewStringUTF(gameId.c_str());
	//	jstring pay_point = JniHelper::getEnv()->NewStringUTF(dreamId.c_str());;
	//	JniHelper::getEnv()->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, poxiao_id, pay_point);
	//}
#endif	
}