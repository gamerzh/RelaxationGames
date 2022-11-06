#include "server/HttpClientUtill.h"

HttpClientUtill* HttpClientUtill::_pInstance = NULL;

HttpClientUtill* HttpClientUtill::getInstance(){
	if(_pInstance == NULL){
		_pInstance = new HttpClientUtill();
	}
	return _pInstance;
}

void HttpClientUtill::destroyInstance(){
	if(_pInstance != NULL){
		delete _pInstance;
		_pInstance = NULL;
	}
}


void HttpClientUtill::onGetHttp(const char* Url,const ccHttpRequestCallback& callback)
{

	HttpRequest* request = new (std::nothrow) HttpRequest();
	// required fields
	request->setUrl(Url);
	request->setRequestType(HttpRequest::Type::GET);
	request->setResponseCallback(callback);
	HttpClient::getInstance()->sendImmediate(request);

}


void HttpClientUtill::onPostHttp(std::string postData, const char* Url, const ccHttpRequestCallback& callback, void* userData)
{

	log("http post request = %s on %s", postData.c_str(), Url);
	HttpRequest* request = new (std::nothrow) HttpRequest();
	request->setUrl(Url);
	request->setUserData(userData);
	request->setRequestData(postData.c_str(), postData.size());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(callback);
	HttpClient::getInstance()->send(request);

}
