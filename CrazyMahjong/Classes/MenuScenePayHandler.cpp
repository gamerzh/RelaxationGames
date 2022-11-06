#include "MenuScenePayHandler.h"
#include "PayDefine.h"
#include "cocos2d.h"
#include "PxPayMannger.h"
#include "MahjongEvent.h"
USING_NS_CC;
#define PLAYINFO_PICKCARDSCOUNT "goodTimes"
static MenuScenePayHandler* _instance = nullptr;
MenuScenePayHandler* MenuScenePayHandler::getInstance()
{
	if (!_instance)
	{
		_instance = new MenuScenePayHandler();
	}
	return _instance;
}


void  MenuScenePayHandler::dealEventClose(){
	log("dealEventClose");
	Director::getInstance()->getEventDispatcher()->setEnabled(true);
	Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
		PayResult *result = new PayResult(Pay_Cancel);
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MSG_PAYBASE, result);
		CC_SAFE_DELETE(result);
	});
	
}
void MenuScenePayHandler::dealEventSuccess(){
	log("dealEventSuccess");
	Director::getInstance()->getEventDispatcher()->setEnabled(true);
	Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
		PayResult *result = new PayResult(Pay_Success);
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MSG_PAYBASE, result);
		CC_SAFE_DELETE(result);
		dispatchMahjongEvent(FLOW_NAME::Refresh_Coin,nullptr);
	});
}


void MenuScenePayHandler::dealEventFail(){
	log("dealEventFail");
	Director::getInstance()->getEventDispatcher()->setEnabled(true);
	Director::getInstance()->getScheduler()->performFunctionInCocosThread([=]{
		PayResult *result = new PayResult(Pay_Failed);
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(MSG_PAYBASE, result);
		CC_SAFE_DELETE(result);
	});
	
}
void MenuScenePayHandler::setHotDioagOver()
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("show_active_over");

}