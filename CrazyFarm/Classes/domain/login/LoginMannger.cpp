#include "LoginMannger.h"
#include "domain/user/User.h"
#include "domain/user/DeviceInfo.h"
#include "server/HttpMannger.h"


LoginMannger* LoginMannger::_instance = NULL;

LoginMannger::LoginMannger(){

}


LoginMannger* LoginMannger::getInstance(){
	if (_instance == NULL){
		_instance = new LoginMannger();
	}
	return _instance;
}
void LoginMannger::login()
{
	auto name = User::getInstance()->getUserId();
	if (name == "guest")
	{
		HttpMannger::getInstance()->HttpToPostRequestRegisterInfo(DeviceInfo::getChannel_id(), DeviceInfo::getImei(), DeviceInfo::getHd_type(), DeviceInfo::getHd_factory());
	}
	else
	{
		HttpMannger::getInstance()->HttpToPostRequestLogInInfo(DeviceInfo::getChannel_id(), name, DeviceInfo::getImei(), DeviceInfo::getHd_type(), DeviceInfo::getHd_factory());
	}
}