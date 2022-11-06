#include "lobby/bag/ShowSkillLayer.h"
#include "domain/user/User.h"
#include "lobby/bag/BagCell.h"
#include "domain/bag/BagManager.h"
#include "utill/FunUtil.h"
#include "domain/skill/skillManager.h"
#include "lobby/viplayer/VipLayer.h"
#include "domain/ToolTip/TwiceSureDialog.h"
#include "utill/Chinese.h"
#include "lobby/shop/payLayer.h"
#include "lobby/bag/TwiceSureBuySkill.h"
#include "domain/logevent/LogEventPageChange.h"
ShowSkillLayer*ShowSkillLayer::create(int itemid)
{
	ShowSkillLayer *pRet = new ShowSkillLayer();
	if (pRet && pRet->init(itemid))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}

bool ShowSkillLayer::init(int itemid)
{
	if (!Layer::init())
	{
		return false;
	}
	bool bRet = false;
	do
	{
		m_itemId = itemid;
		auto layer = LayerColor::create();
		layer->setColor(Color3B::BLACK);
		layer->setOpacity(128);
		addChild(layer, -1);
		auto size = Director::getInstance()->getVisibleSize();
		auto bg = Sprite::create("showItemBg.png");
		bg->setPosition(size / 2);
		addChild(bg);

		BagItem item;
		item.itemId = itemid;
		item.num = BagManager::getInstance()->getItemNum(itemid);
		auto cell = BagCell::create();
		cell->setValue(item);
		cell->setPosition(480, 373);
		addChild(cell);

		Iitem = ConfigItem::getInstance()->getItemById(itemid);
		auto label = LabelTTF::create(Iitem.itemName.c_str(), "arial", 20);
		label->setPosition(480, 300);
		label->setAnchorPoint(Point::ANCHOR_MIDDLE);
		addChild(label);

		auto str = String::createWithFormat(ChineseWord("itemDanJia").c_str(), Iitem.buyPrice);
		label = LabelTTF::create(str->getCString(), "arail", 18);
		label->setColor(Color3B::YELLOW);
		label->setPosition(340, 250);
		label->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
		addChild(label);

		///购买条件
		float PosY = 0;
		auto info = skillManager::getInstance()->getSkillInfoByitemId(m_itemId);
		if (info.unlock_buy_vipLv>0)
		{
			str = String::createWithFormat(ChineseWord("bySkillNeedVIP").c_str(), info.unlock_buy_vipLv);
			label = LabelTTF::create(str->getCString(), "arail", 18);
			label->setPosition(340, 230);
			label->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
			addChild(label);
			PosY = 190;
			
		}
		else
		{
			PosY = 210;
			/*label = LabelTTF::create(ChineseWord("bySkillNoNeedVIP").c_str(), "arail", 18);*/
		}
			


		label = LabelTTF::create(Iitem.itemDesc.c_str(), "arail", 18);
		label->setPosition(340, PosY);
		label->setDimensions(Size(283, 0));
		label->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
		addChild(label);


		auto BtBuy = MenuItemImage::create("btn_goumai_1.png", "btn_goumai_2.png", CC_CALLBACK_1(ShowSkillLayer::quedingcallback, this));
		BtBuy->setPosition(480, 80);

		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(ShowSkillLayer::closeButtonCallBack, this));
		close->setPosition(644, 470);



		auto menu = Menu::create(BtBuy, close, nullptr);
		menu->setPosition(0, 0);
		addChild(menu);

		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->setSwallowTouches(true);
		touchListener->onTouchBegan = CC_CALLBACK_2(ShowSkillLayer::onTouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(ShowSkillLayer::onTouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(ShowSkillLayer::onTouchEnded, this);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
		//添加系统返回键监听
		auto listener = EventListenerKeyboard::create();
		listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
			switch (code)
			{
			case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
				removeFromParentAndCleanup(1);
				break;
			default:
				break;
			}
		};
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
		bRet = true;
	} while (0);


	return bRet;
}
bool ShowSkillLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	return true;
}

void ShowSkillLayer::quedingcallback(Ref*)
{

	int isSatisfy = skillManager::getInstance()->isSatisfyBuySkillInBag(skillManager::getInstance()->getSkillInfoByitemId(m_itemId).skill_id);
	auto price = skillManager::getInstance()->getSkillPriceById(skillManager::getInstance()->getSkillInfoByitemId(m_itemId).skill_id);
	if (isSatisfy == 1)
	{
		auto str = String::createWithFormat(ChineseWord("bySkillNoNeedVIPTIP").c_str(), skillManager::getInstance()->getSkillInfoByitemId(m_itemId).unlock_buy_vipLv, skillManager::getInstance()->getSkillInfoByitemId(m_itemId).unlock_buy_vipLv);
		auto layer = TwiceSureDialog::createDialog(str->getCString(), CC_CALLBACK_1(ShowSkillLayer::LackVipCallBack,this));
		layer->setPosition(Point::ZERO);
		addChild(layer, 30,"tip");
	}
	else /*if (isSatisfy == 2)
	{

		TwiceSureDialog* layer = TwiceSureDialog::createDialog(ChineseWord("bySkillNoNeedTurrentTIP").c_str(), CC_CALLBACK_1(ShowSkillLayer::LackTurrentCallBack, this));
		layer->setPosition(Point::ZERO);
		addChild(layer, 30,"tip");
	}
	else*/
	{
		auto diamond = User::getInstance()->getDiamonds();
		if (diamond>=200)
		{
			auto layer = TwiceSureBuySkill::createTwiceBuySkillTip(m_itemId);
			layer->setPosition(0,0);
			addChild(layer, 30);
		}
		else
		{
			auto name = ConfigItem::getInstance()->getItemById(m_itemId).itemName;
			auto str = String::createWithFormat(ChineseWord("lackOfdiamond").c_str(), name.c_str(), 200 / price);
			auto layer = TwiceSureDialog::createDialog(str->getCString(), CC_CALLBACK_1(ShowSkillLayer::satisfyCallBack,this));
			layer->setPosition(Point::ZERO);
			addChild(layer, 30,"tip");
		}
		//二次确认
	}


}

void ShowSkillLayer::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}



void ShowSkillLayer::LackVipCallBack(Ref*psend)
{

	removeChildByName("tip", 1);
	auto layer = payLayer::createLayer(2); 
	layer->setPosition(0, 0); 
	addChild(layer);
	layer->setEventPont(m_itemId - 996);
	LogEventPageChange::getInstance()->addEventItems(3, 13, skillManager::getInstance()->getSkillInfoByitemId(m_itemId).skill_id);
}
void ShowSkillLayer::LackTurrentCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);

}
void ShowSkillLayer::satisfyCallBack(Ref*psend)
{
	removeChildByName("tip", 1);
	auto layer = payLayer::createLayer(2); layer->setPosition(0, 0); addChild(layer);
	layer->setEventPont(m_itemId - 996);
	LogEventPageChange::getInstance()->addEventItems(3, 13, skillManager::getInstance()->getSkillInfoByitemId(m_itemId).skill_id);
}
