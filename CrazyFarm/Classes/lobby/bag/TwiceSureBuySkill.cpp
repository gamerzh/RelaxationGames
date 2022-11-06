#include "TwiceSureBuySkill.h"
#include "domain/skill/skillManager.h"
#include "utill/Chinese.h"
#include "domain/bag/BagManager.h"
#include "domain/ToolTip/TwiceSureDialog.h"
TwiceSureBuySkill*TwiceSureBuySkill::createTwiceBuySkillTip(int itemid)
{
	TwiceSureBuySkill*ref = new TwiceSureBuySkill();
	if (ref&&ref->init(itemid))
	{
		ref->autorelease();
	}
	else
	{
		ref = nullptr;
	}
	return ref;
}





bool TwiceSureBuySkill::init(int itemid)
{
	Layer::init();
	bool bRet = false;
	do 
	{
		auto colorlayer = LayerColor::create();
		colorlayer->setColor(ccc3(0, 0, 0));
		colorlayer->setOpacity(180);
		colorlayer->setPosition(0,0);
		addChild(colorlayer, -1);
		auto bg = Sprite::create("TwiceSureDialog.png");
		bg->setPosition(480, 270);
		addChild(bg, -1);
		
		m_itemid = itemid;
		auto price = skillManager::getInstance()->getSkillPriceById(skillManager::getInstance()->getSkillInfoByitemId(m_itemid).skill_id);
		auto spPath = String::createWithFormat("item_%d.png", itemid);
		auto sp = Sprite::create(spPath->getCString());
		sp->setPosition(76, 150);
		bg->addChild(sp);
		//道具名称
		auto str = String::createWithFormat("propName_%d",m_itemid);
		auto label = LabelTTF::create(ChineseWord(str->getCString()).c_str(), "arial", 20);
		label->setColor(Color3B(12, 64, 109));
		label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		label->setPosition(141, 195);
		bg->addChild(label);
		//购买数量	
		 str = String::createWithFormat(ChineseWord("buyPropNum").c_str(), 200/price);
		label = LabelTTF::create(str->getCString(), "arial", 20);
		label->setColor(Color3B(12, 64, 109));
		label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		label->setPosition(141, 165);
		bg->addChild(label);
		//购买条件
		str = String::createWithFormat(ChineseWord("propPrice").c_str(), 200);
		label = LabelTTF::create(str->getCString(), "arial", 20);
		label->setColor(Color3B(12, 64, 109));
		label->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		label->setPosition(141, 135);
		bg->addChild(label);




		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(TwiceSureBuySkill::closeButtonCallBack, this));
		close->setPosition(bg->getContentSize());

		auto sure = MenuItemImage::create("btn_goumai_1.png", "btn_goumai_2.png", CC_CALLBACK_1(TwiceSureBuySkill::sureButtonCallBack,this));
		sure->setPosition(bg->getContentSize().width / 2, 40);

		auto menu = Menu::create(close, sure, nullptr);
		menu->setPosition(bg->getPosition() - bg->getContentSize() / 2);
		addChild(menu);




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

void TwiceSureBuySkill::sureButtonCallBack(Ref*psend)
{
	if (User::getInstance()->getDiamonds()>=200)
	{
		if (User::getInstance()->getMaxTurrentLevel()>300)
		{
			User::getInstance()->addDiamonds(-200);
			BagManager::getInstance()->changeItemCount(m_itemid, 200 / skillManager::getInstance()->getSkillPriceById(skillManager::getInstance()->getSkillInfoByitemId(m_itemid).skill_id));
		}
		else
		{
			auto layer = TwiceSureDialog::createDialog(ChineseWord("bySkillNoNeedTurrentTIP").c_str(), nullptr);
			layer->setPosition(0, 0);
			getParent()->getParent()->addChild(layer, 10);
		}
		
	}
	getParent()->removeFromParentAndCleanup(1);
}

void TwiceSureBuySkill::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}