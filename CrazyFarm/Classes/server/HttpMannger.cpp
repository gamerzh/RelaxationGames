#include "server/HttpMannger.h"
#include "utill/FunUtil.h"
#include "domain/user/User.h"
#include "domain/user/DeviceInfo.h"
#include "domain/logevent/LogEventMannger.h"
#include "domain/pay/Pay.h"
#include "domain/ToolTip/ToolTipMannger.h"
#include "domain/pay/WaitCircle.h"


HttpMannger* HttpMannger::_instance = NULL;

HttpMannger::HttpMannger(){
    this->init();
}

void HttpMannger::init(){
}

HttpMannger* HttpMannger::getInstance(){
    if(_instance == NULL){
		_instance = new HttpMannger();
    }
    return _instance;
}


void HttpMannger::HttpToPostRequestRegisterInfo(std::string channelId, const char* imei, const char* hd_type, const char* hd_factory)
{
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_REGISTER);
	auto requstData = String::createWithFormat("channel_id=%s&imei=%s&hd_type=%s&hd_factory=%s", channelId.c_str(),imei, hd_type, hd_factory);
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForRegisterInfo, this));
}
void HttpMannger::onHttpRequestCompletedForRegisterInfo(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		return;
	}
	if (!response->isSucceed())
	{
		return;
	}
	long statusCode = response->getResponseCode();
	// dump data
	std::vector<char> *buffer = response->getResponseData();
	auto temp = std::string(buffer->begin(), buffer->end());
	log("http back register info  info: %s", temp.c_str());
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
	if (doc.HasParseError())
	{
		log("get json data err!");;
	}
	User::getInstance()->setUserID(doc["user_name"].GetString());
	User::getInstance()->setSessionid(doc["session_id"].GetString());
	CCLOG("register success");
}




void HttpMannger::HttpToPostRequestLogInInfo(std::string channelId, std::string username, const char* imei, const char*  hd_type, const char*  hd_factory)
{
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_LOGIN);
	auto requstData = String::createWithFormat("channel_id=%s&user_name=%s&imei=%s&hd_type=%s&hd_factory=%s", channelId.c_str(),username.c_str(), imei, hd_type, hd_factory);
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForLogInInfo, this));
}
void HttpMannger::onHttpRequestCompletedForLogInInfo(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		return;
	}
	if (!response->isSucceed())
	{
		return;
	}
	long statusCode = response->getResponseCode();
	// dump data
	std::vector<char> *buffer = response->getResponseData();
	auto temp = std::string(buffer->begin(), buffer->end());
	log("http  login back info: %s", temp.c_str());
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
	if (doc.HasParseError())
	{
		log("get json data err!");;
	}
	if (doc["errorcode"].GetInt() == 301)
	{
		HttpToPostRequestRegisterInfo(DeviceInfo::getChannel_id(), DeviceInfo::getImei(), DeviceInfo::getHd_type(), DeviceInfo::getHd_factory());
		User::getInstance()->resetInfo();
		return;
	}
	User::getInstance()->setSessionid(doc["session_id"].GetString());

	CCLOG("login success");

}


void HttpMannger::HttpToPostRequestBeforePay(std::string sessionid, int pay_and_Event_version, int pay_event_id, int pay_point_id, std::string channel_id, std::string  pay_point_desc, int price, int result, const char* orderid, int paytype)
{
	payRequest* quest = new payRequest();
	quest->pay_and_Event_version = pay_and_Event_version;
	quest->channel_id = channel_id;
	quest->sessionid = sessionid;
	quest->pay_point_id = pay_point_id;
	quest->pay_event_id = pay_event_id;
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_PAY);
	auto requstData = String::createWithFormat("session_id=%s&pay_and_event_version=%d&pay_event_id=%d&pay_point_id=%d&channel_id=%s&price=%d&pay_type=%d&result=%d&order_id=%s&third_type=%d&pay_point_desc=%s",
		quest->sessionid.c_str(), quest->pay_and_Event_version, quest->pay_event_id, quest->pay_point_id, quest->channel_id.c_str(),price, paytype,result,orderid,quest->third_payType,pay_point_desc.c_str());

	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForBeforePay, this), quest);



}
void HttpMannger::onHttpRequestCompletedForBeforePay(HttpClient *sender, HttpResponse *response)
{
	if (!response||!response->isSucceed())
	{
		log("http back  before pay info falied");
		Pay::getInstance()->setPayState(UnDoing);
		ToolTipMannger::ShowPayTimeoutTip();
		return;
	}
	long statusCode = response->getResponseCode();
	// dump data
	std::vector<char> *buffer = response->getResponseData();
	auto temp = std::string(buffer->begin(), buffer->end());
	log("http back  before pay info: %s", temp.c_str());
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
	if (doc.HasParseError())
	{
		log("get json data err!");;
	}
	int result = doc["errorcode"].GetInt();
	
	if (result == 0)
	{
		const char* orderId = doc["order_id"].GetString();

		auto userdata = (payRequest*)response->getHttpRequest()->getUserData();
		userdata->orderID = orderId;
		if (userdata->third_payType==1)
		{
			userdata->wx_prepayid = doc["wx_prepayid"].GetString();
			userdata->wx_sign = doc["wx_sign"].GetString();
			userdata->wx_timestamp = doc["wx_timestamp"].GetString();
			userdata->wx_nonceStr = doc["wx_nonce_str"].GetString();
			log("pay http errormsg = %s", doc["errormsg"].GetString());
		}
	
		Pay::getInstance()->pay(userdata);
	}
	else
	{
		Pay::getInstance()->setPayState(UnDoing);
		ToolTipMannger::ShowPayTimeoutTip();

	}
}
void HttpMannger::HttpToPostRequestAfterPay(std::string sessionid, int pay_and_Event_version, int pay_event_id, int pay_point_id, std::string channel_id, int price,int result, const char* orderid, int paytype )
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	return;
#endif

	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_PAY);
	auto requstData = String::createWithFormat("session_id=%s&pay_and_event_version=%d&pay_event_id=%d&pay_point_id=%d&channel_id=%s&price=%d&pay_type=%d&result=%d&order_id=%s",
		sessionid.c_str(), pay_and_Event_version, pay_event_id, pay_point_id, channel_id.c_str(),price, paytype, result, orderid);
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForAfterPay, this));
}

void HttpMannger::onHttpRequestCompletedForAfterPay(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		return;
	}
	if (!response->isSucceed())
	{
		return;
	}
	long statusCode = response->getResponseCode();
	// dump data
	std::vector<char> *buffer = response->getResponseData();
	auto temp = std::string(buffer->begin(), buffer->end());
	log("http back afterpay info: %s", temp.c_str());
}
void HttpMannger::onHttpRequestCompletedForSyncInfo(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		return;
	}
	if (!response->isSucceed())
	{
		return;
	}
	long statusCode = response->getResponseCode();
	// dump data
	std::vector<char> *buffer = response->getResponseData();
	auto temp = std::string(buffer->begin(), buffer->end());
	log("http back syncinfo  info: %s", temp.c_str());
}

void HttpMannger::HttpToPostRequestSyncInfo(std::string sessionid, int coin, int diamond, int exp, int maxTurretLevel, int PayRMB, int nobillityCount)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	return;
#endif
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_SYNCINFO);
	auto requstData = String::createWithFormat("session_id=%s&coins=%d&diamonds=%d&exp=%d&turrent_level=%d&mo=%d&nobility_time=%d", sessionid.c_str(), coin, diamond, exp, maxTurretLevel, PayRMB, nobillityCount);
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForSyncInfo, this));
}

void HttpMannger::onHttpRequestCompletedForSetName(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		return;
	}
	if (!response->isSucceed())
	{
		return;
	}
	long statusCode = response->getResponseCode();
	// dump data
	std::vector<char> *buffer = response->getResponseData();
	auto temp = std::string(buffer->begin(), buffer->end());
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
	if (doc.HasParseError())
	{
		log("get json data err!");;
	}
	int result = doc["errorcode"].GetInt();
	if (result == 0)
	{
		auto data = (setNameRequest*)response->getHttpRequest()->getUserData();
		User::getInstance()->setUserName(data->nickname);
		User::getInstance()->setUserGender(data->gender);
		User::getInstance()->setHaveSetName();
		Director::getInstance()->getRunningScene()->getChildByTag(50)->getChildByName("setnamelayer")->removeFromParentAndCleanup(1);
		delete data;
	}
	log("http back setname info: %s", temp.c_str());
}

void HttpMannger::HttpToPostRequestSetName(std::string sessionid,const char* nickname, int gender)
{
	setNameRequest*data = new setNameRequest();
	data->gender = gender;
	data->nickname = nickname;
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_SETNAME);
	auto requstData = String::createWithFormat("session_id=%s&nickname=%s&gender=%d", sessionid.c_str(), nickname, gender);
	
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForSetName, this),data);

}

void HttpMannger::onHttpRequestCompletedForFeedback(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		log("http back feedback info: %ld", response->getResponseCode());
		return;
	}
	if (!response->isSucceed())
	{
		log("http back feedback info: %s", response->getErrorBuffer());
		return;
	}
	long statusCode = response->getResponseCode();
	// dump data
	std::vector<char> *buffer = response->getResponseData();
	auto temp = std::string(buffer->begin(), buffer->end());
	log("http back feedback info: %s", temp.c_str());
}

void HttpMannger::HttpToPostRequestFeedback(const char* feedback)
{
	if (strlen(feedback)<= 3)
	{
		return;

	}
	auto sessionid = User::getInstance()->getSessionid();
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_FEEDBACK);
	auto requstData = String::createWithFormat("session_id=%s&info=%s", sessionid.c_str(), feedback);
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForFeedback, this));
}


void HttpMannger::HttpToPostRequestDemandEntry(std::string prepayid, int reqNum)
{
	auto orderid = Pay::getInstance()->getOrderIdByprepayid(prepayid);
	auto sessionid = User::getInstance()->getSessionid();
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_DEMANDENTRY);
	auto requstData = String::createWithFormat("session_id=%s&order_id=%s", sessionid.c_str(), orderid.c_str());

	prepayidAndReqNum* reqData = new prepayidAndReqNum();
	reqData->reqnum = reqNum;
	reqData->prepayid = prepayid;
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForDemandEntry, this), reqData);
}

void HttpMannger::onHttpRequestCompletedForCancelOrder(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		return;
	}
	auto data = response->getHttpRequest()->getUserData();
	std::string *reqdata = (std::string*)data;
	if (!response->isSucceed())
	{
		return;
	}
	long statusCode = response->getResponseCode();
	// dump data
	std::vector<char> *buffer = response->getResponseData();
	auto temp = std::string(buffer->begin(), buffer->end());
	log("http back cancelorder info: %s", temp.c_str());
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
	if (doc.HasParseError())
	{
		log("get json data err!");
	}
	int result = doc["errorcode"].GetInt();
	if (result == 0)
	{	
		Pay::getInstance()->payCallBack(1, "", Pay::getInstance()->getPrepayIdByOrderid(*reqdata));
		
	}
	
	delete reqdata;
	return;
}


void HttpMannger::HttpToPostRequestCancelOrder(std::string orderid)
{
	auto sessionid = User::getInstance()->getSessionid();
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_CANCELORDER);
	auto requstData = String::createWithFormat("session_id=%s&order_id=%s", sessionid.c_str(), orderid.c_str());

	std::string* reqData = new std::string(orderid);
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForCancelOrder, this), reqData);
}

void HttpMannger::onHttpRequestCompletedForDemandEntry(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		Pay::getInstance()->payCallBack(1, "failed", "");
		return;
	}
	auto data = response->getHttpRequest()->getUserData();
	prepayidAndReqNum *reqdata = (prepayidAndReqNum*)data;
	if (!response->isSucceed())
	{
		Pay::getInstance()->payCallBack(1, "failed", reqdata->prepayid);
		return;
	}
	long statusCode = response->getResponseCode();
	// dump data
	std::vector<char> *buffer = response->getResponseData();
	auto temp = std::string(buffer->begin(), buffer->end());
	log("http back logevent info: %s", temp.c_str());
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
	if (doc.HasParseError())
	{
		log("get json data err!");
	}
	int result = doc["errorcode"].GetInt();
	if (result == 0)
	{
		Pay::getInstance()->payCallBack(result, doc["success"].GetString(), reqdata->prepayid);
	}
	else
	{
		if (reqdata->reqnum >= 2)
		{
			Pay::getInstance()->payCallBack(1, "failed", reqdata->prepayid);
		}
		else
		{
			WaitCircle::sendRequestWaitCirCle(reqdata->prepayid);
		}
	}

	delete reqdata;
}


void HttpMannger::HttpToPostRequestLogEvent(std::string jsonString,int type)
{
	int *userdata = new int();
	*userdata = type;
	
	auto sessionid = User::getInstance()->getSessionid();
	auto url = String::createWithFormat("%s%s", URL_HEAD, URL_LOGEVENTFISH);
	auto requstData = String::createWithFormat("session_id=%s&data_str=%s&game_version=%d", sessionid.c_str(), jsonString.c_str(),DeviceInfo::getVesion());
	HttpClientUtill::getInstance()->onPostHttp(requstData->getCString(), url->getCString(), CC_CALLBACK_2(HttpMannger::onHttpRequestCompletedForLogEventCommon, this),userdata);
}
void HttpMannger::onHttpRequestCompletedForLogEventCommon(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		return;
	}
	if (!response->isSucceed())
	{
		return;
	}
	long statusCode = response->getResponseCode();
	// dump data
	std::vector<char> *buffer = response->getResponseData();
	auto temp = std::string(buffer->begin(), buffer->end());
	rapidjson::Document doc;
	doc.Parse<rapidjson::kParseDefaultFlags>(temp.c_str());
	if (doc.HasParseError())
	{
		log("get json data err!");;
	}
	int result = doc["errorcode"].GetInt();
	if (result == 0)
	{
		auto userdata = (int*)response->getHttpRequest()->getUserData();
		LogEventMannger::getInstance()->clearData(*userdata);
		delete userdata;
	}
}
