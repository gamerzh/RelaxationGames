#include "TwiceSkillSureDialog.h"
#include "utill/AnimationUtil.h"
#include "utill/FunUtil.h"

#include "data/GameData.h"
#include "domain/skill/skillManager.h"
#include "domain/game/GameManage.h"
#include "domain/ToolTip/TwiceSureDialog.h"
#include "domain/logevent/LogEventPageChange.h"

TwiceSkillSureDialog* TwiceSkillSureDialog::createDialog()
{
	TwiceSkillSureDialog* ref = new TwiceSkillSureDialog();
	if (ref&&ref->init())
	{
		ref->autorelease();
	}
	else
	{
		ref = nullptr;
	}
	return ref;
}

void TwiceSkillSureDialog::setCloseButtonCallback(const ccMenuCallback& closecallback)
{
	close->setCallback(closecallback);
}

bool TwiceSkillSureDialog::init( )
{
	Layer::init();
	bool bRet = false;
	do
	{

		auto bg = Sprite::create("TwiceSureDialog.png");
		bg->setPosition(480, 270);
		addChild(bg, -1,"bg");

		close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(TwiceSkillSureDialog::closeButtonCallBack, this));
		close->setPosition(bg->getContentSize());
		
		
		sure = MenuItemImage::create("btn_queding.png", "btn_queding_2.png");
		sure->setPosition(bg->getContentSize().width / 2, 48);
		sure->setCallback(CC_CALLBACK_1(TwiceSkillSureDialog::sureButtonCallBack, this));
	

		auto menu = Menu::create(close, sure, nullptr);
		menu->setPosition(bg->getPosition()-bg->getContentSize()/2);
		addChild(menu);


		auto label = LabelTTF::create(ChineseWord("havenoSkillIsToBuy").c_str(), "arial", 20);
		label->setColor(Color3B(12, 64, 109));
		label->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
		label->setDimensions(Size(261, 0));
		label->setPosition(bg->getContentSize().width / 2, 198);
			bg->addChild(label);

			label = LabelTTF::create(ChineseWord("nextWithOutRemind").c_str(), "arial", 20);
			label->setColor(Color3B::RED);
			label->setAnchorPoint(Point::ANCHOR_MIDDLE);
			label->setPosition(bg->getContentSize().width / 2, 118);
			bg->addChild(label);
		
			CheckBox* checkBox = CheckBox::create("check_box_normal.png",
				"check_box_active_press.png",
				"check_box_active_press.png",
				"check_box_normal.png",
				"check_box_normal.png");
			checkBox->setPosition(Vec2(373,270));

			checkBox->addEventListener(CC_CALLBACK_2(TwiceSkillSureDialog::selectedEvent, this));
			addChild(checkBox);

		auto listenr1 = EventListenerTouchOneByOne::create();
		listenr1->onTouchBegan = CC_CALLBACK_2(TwiceSkillSureDialog::onTouchBegan, this);
		listenr1->setSwallowTouches(true);
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);

		//添加系统返回键监听
		auto listener = EventListenerKeyboard::create();
		listener->onKeyReleased = [=](EventKeyboard::KeyCode code, Event * e){
			switch (code)
			{
			case cocos2d::EventKeyboard::KeyCode::KEY_NONE:
				break;
			case cocos2d::EventKeyboard::KeyCode::KEY_BACK:
				break;
			default:
				break;
			}
		};
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
		/////////弹出动画
		setScale(0);
		runAction(Sequence::create(ScaleTo::create(0.2f, 1.0f), ScaleTo::create(0.07f, 0.8f), ScaleTo::create(0.07f, 1.0f), nullptr));
		showRandonBubbleAni();
		
		bRet = true;
	} while (0);


	return bRet;
}

void TwiceSkillSureDialog::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}
void TwiceSkillSureDialog::sureButtonCallBack(Ref*psend)
{
	auto price = skillManager::getInstance()->getSkillPriceById(m_skiilid);
	auto userdm = User::getInstance()->getDiamonds();
	if (userdm > price)
	{
		LogEventUseSkill::getInstance()->addUseSkillData(m_skiilid, 1, price);
		User::getInstance()->addDiamonds(-price);
		skillManager::getInstance()->useSkillById(m_skiilid,GameManage::getInstance()->getGameLayer()->GetMyTurret());
	}
	else
	{
		auto dialog = TwiceSureDialog::createDialog(ChineseWord("havanoDmToUseskill").c_str(), CC_CALLBACK_1(TwiceSkillSureDialog::ToPayShopCallBack, this));
		dialog->setPosition(Point::ZERO);
		GameManage::getInstance()->getGuiLayer()->addChild(dialog, 20);
	}
	removeFromParentAndCleanup(1);
}
void TwiceSkillSureDialog::ToPayShopCallBack(Ref*psend)
{
	auto nd = (Node*)psend;
	LogEventUseSkill::getInstance()->addUseSkillData(m_skiilid, 2, 0);
	LogEventPageChange::getInstance()->addEventItems(2, m_skiilid - 1, 13);
	auto layer = payLayer::createLayer(2);
	layer->setPosition(0, 0);
	layer->setEventPont(m_skiilid + 12);
	GameManage::getInstance()->getGuiLayer()->addChild(layer, 20);
	nd->getParent()->getParent()->removeFromParentAndCleanup(1);
}
void TwiceSkillSureDialog::showRandonBubbleAni()
{
	auto node = getChildByName("bg");

	auto aniNode = Sprite::create();
	aniNode->setPosition(20,100);
	node->addChild(aniNode, 5);
	aniNode->runAction(getForeverAcByNameAndInterval("aniBubble",0));

	aniNode = Sprite::create();
	aniNode->setPosition(node->getContentSize().width-20, 100);
	node->addChild(aniNode, 5);
	aniNode->runAction(getForeverAcByNameAndInterval("aniBubble", 0));
	
}

void TwiceSkillSureDialog::selectedEvent(Ref* pSender, CheckBox::EventType type)
{
	switch (type)
	{
	case CheckBox::EventType::SELECTED:
		GameData::getInstance()->setisDirectUseSkill(true);
		break;

	case CheckBox::EventType::UNSELECTED:
		GameData::getInstance()->setisDirectUseSkill(false);
		break;

	default:
		break;
	}

}