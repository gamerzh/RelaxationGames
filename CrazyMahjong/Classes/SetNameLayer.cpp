#include "SetNameLayer.h"
#include "ChineseWorld.h"
#include "Room.h"
#include "PxPayMannger.h"
#include "User.h"
#include "Toast.h"
bool SetNameLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	bool bRet = false;
	do 
	{
		auto colorbg = LayerColor::create();
		colorbg->setPosition(0, 0);
		colorbg->setColor(Color3B::BLACK);
		colorbg->setOpacity(128);
		addChild(colorbg, -1);

		auto bg = Sprite::create("SetName/RegisterBg.png");
		bg->setPosition(400, 240);
		addChild(bg,0,"bg");

		auto size = bg->getContentSize();

		auto frame = Sprite::create("SetName/RegisterInputFrame.png");
		frame->setPosition(Vec2(size.width / 2, 170));
		bg->addChild(frame);

		_editNickname = ui::EditBox::create(Size(380, 73), ui::Scale9Sprite::create());
		_editNickname->setPosition(Vec2(size.width / 2+20, 170));
		_editNickname->setFontName("Arial");
		_editNickname->setFontSize(24);
		_editNickname->setFontColor(Color3B(202, 230, 248));
		_editNickname->setPlaceHolder(ChineseWord("USER_NAME_DEFAULT").c_str());
		_editNickname->setPlaceholderFontColor(Color3B::GRAY);
		_editNickname->setPlaceholderFontSize(24);
		_editNickname->setMaxLength(14);
		_editNickname->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
		_editNickname->setDelegate(this);
		bg->addChild(_editNickname);


		auto sureBt = MenuItemImage::create("SetName/Btn_SetName_1.png", "SetName/Btn_SetName_2.png", CC_CALLBACK_1(SetNameLayer::quedingcallback, this));
		sureBt->setPosition(size.width / 2, 60);
		sureBt->setName("sureBt");

		auto menu = Menu::create(sureBt, nullptr);
		menu->setPosition(0, 0);
		bg->addChild(menu, 1, "menu");
		scheduleUpdate();


		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->setSwallowTouches(true);
		touchListener->onTouchBegan = [=](Touch*touch, Event*event){return true; };
		Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
		bRet = true;
	} while (0);
	

	return bRet;
}


void SetNameLayer::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{
	log("editBox %p DidBegin !", editBox);
}

void SetNameLayer::editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)
{
	log("editBox %p DidEnd !", editBox);
}

void SetNameLayer::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)
{
	log("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void SetNameLayer::editBoxReturn(ui::EditBox* editBox)
{
	//auto str = String::createWithFormat("%s", editBox->getText());
	//editBox->setText(str->getCString());
	//log("editBox %p was returned !", editBox);

}

void SetNameLayer::quedingcallback(Ref*psend)
{
	if (checkTheName(_editNickname->getText()))
	{
		User::getInstance()->setMyName(_editNickname->getText());
	/*	PxPayMannger::getInstance()->LaughPayLayer(9, this->getParent());*/
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("setname");
		removeFromParentAndCleanup(1);
	}
	else
	{
		Toast::show(ChineseWord("SetNameWarning").c_str(), 3.0f, this);
	}

}

bool SetNameLayer::checkTheName(const char* name)
{
	int len = strlen(name);
	if (len<=0)
	{
		return false;
	}
	return true;
}
