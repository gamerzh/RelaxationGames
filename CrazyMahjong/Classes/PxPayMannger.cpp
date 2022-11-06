#include "PxPayMannger.h"
#include "User.h"
#include "platform\android\jni\JniHelper.h"
#include "MenuScenePayHandler.h"
#include "ToolTipMannger.h"
PxPayMannger* PxPayMannger::_instance = 0;
PxPayMannger::PxPayMannger(){
}
PxPayMannger* PxPayMannger::getInstance(){
	if(_instance == 0){
		_instance = new PxPayMannger();
	}
	return _instance;
}

void PxPayMannger::LaughPayLayer(PAYPOINT paypoint, Node*parents,  std::function<void(EventCustom*)> callback)
{
	auto layer = BasePayLayer::create(paypoint);
	layer->setPosition(0, 0);
	parents->addChild(layer,30);

	layer->setPayCallBack(callback);
	Jniutill::getInstance()->logEventShowPayPanel(paypoint,1);
}
//Be the king of the spiritual kingdom that is your heart.
void PxPayMannger::doWxPay(PAYPOINT paypoint,std::function<void(EventCustom*)> payCallBack)
{
	CCLOG("C++ do jni pay paypoint=%d", (int)paypoint);
	if (isOnPaying)
	{
		return;
	}
	isOnPaying = true;
	Director::getInstance()->getEventDispatcher()->setEnabled(false);
	auto payitem = getItemByPaypoint(paypoint);
	std::function<void(EventCustom*)> callback = [=](EventCustom*event)
	{
		PayResult*reslt = (PayResult*)(event->getUserData());
		if (*reslt == Pay_Success)
		{
			if (payitem.PPpropType == 1)
			{
				User::getInstance()->addCoin(payitem.PPropNum);
			}
			else
			{
				User::getInstance()->setisVip(true);
				User::getInstance()->setAvailableRole(9);
			}
			if (payitem.PPoint == FIRSTPAYGFIT)
			{
				User::getInstance()->setisPayFirstPayPoint(true);
			}
			ToolTipMannger::showDioag(Director::getInstance()->getRunningScene(),ToolTipMannger::Tip_PaySucceed);
		}
		else
		{
			ToolTipMannger::showDioag(Director::getInstance()->getRunningScene(), ToolTipMannger::Tip_PayFailed);
		}
		if (payCallBack != nullptr)
		{
			payCallBack(event);
		}
		Director::getInstance()->getEventDispatcher()->removeCustomEventListeners(event->getEventName());
		log("setisonpaying");
		isOnPaying = false;
	
	};
	Director::getInstance()->getEventDispatcher()->addCustomEventListener(MSG_PAYBASE, callback);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	Jniutill::getInstance()->doPay(payitem.PPoint);
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	auto node = Node::create();
	Director::getInstance()->getRunningScene()->addChild(node);
	node->runAction(Sequence::create(DelayTime::create(0.1f), CallFunc::create([=]{	MenuScenePayHandler::getInstance()->dealEventSuccess(); }), RemoveSelf::create(true), nullptr));
#endif
}

void PxPayMannger::LaughCoinPayLayer(Node* parents)
{
	PAYPOINT point;
	if (User::getInstance()->getisPayFirstPayPoint())
	{
		point = COINGIFT;
	}
	else
	{
		point = FIRSTPAYGFIT;
	}

	LaughPayLayer(point, parents, nullptr);
}



PayItem PxPayMannger::getItemByPaypoint(PAYPOINT point)
{
	static std::vector<PayItem> _items;
	if (_items.size() == 0)
	{
		_items.push_back(PayItem(COIN_18, 18, 230000, 1));
		_items.push_back(PayItem(COIN_28, 28, 380000, 1));
		_items.push_back(PayItem(COIN_58, 58, 860000, 1));
		_items.push_back(PayItem(COIN_88, 88, 1380000, 1));
		_items.push_back(PayItem(FIRSTPAYGFIT, 30, 328000, 1));
		_items.push_back(PayItem(VIPGIFT, 38, 30, 2));
		_items.push_back(PayItem(COINGIFT, 30, 300000, 1));
	}
	for (auto var : _items)
	{
		if (var.PPoint == point)
		{
			return var;
		}
	}
	return PayItem(INVALID, -1, -1, -1);
}
