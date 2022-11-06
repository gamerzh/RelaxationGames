#include "lobby/bag/SetNameLayer.h"
#include "server/HttpMannger.h"
#include "domain/user/User.h"


SexHead* SexHead::create(int sex, int isChoose)
{
	auto head = new SexHead();
	if (head->init(sex,isChoose)&&head)
	{
		head->autorelease();
	}
	else
	{
		head = nullptr;
	}
	return head;

}

bool SexHead::init(int sex, int isChoose)
{
	if (sex)
	{
		initWithFile("bagFamale.png");
	}
	else
	{
		initWithFile("bagMale.png");
	}
	auto sp = Sprite::create("sexChooseFlag.png");
	sp->setPosition(80, 28);
	addChild(sp,0,10);
	if (isChoose)
	{
		sp->setVisible(true);
	}
	else
	{
		sp->setVisible(false);
	}
	return true;
}
void SexHead::setIsChoose(bool isChoose)
{
	getChildByTag(10)->setVisible(isChoose);
}







bool SetNameLayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}
	bool bRet = false;
	do 
	{
		auto layer = LayerColor::create();
		layer->setColor(Color3B::BLACK);
		layer->setOpacity(128);
		addChild(layer,-1);
		auto size = Director::getInstance()->getVisibleSize();
		auto bg = Sprite::create("setnameBg.png");
		bg->setPosition(size / 2);
		addChild(bg);


		sexBoy = SexHead::create(0, 1);
		sexBoy->setPosition(468, 357);
		addChild(sexBoy);

		sexGirl = SexHead::create(1 ,0);
		sexGirl->setPosition(628, 357);
		addChild(sexGirl);

		sex = 0;

		_editName = ui::EditBox::create(Size(270,48), ui::Scale9Sprite::create("setnameTxt.png"));
		_editName->setPosition(Vec2(522,266));
		_editName->setFontName("Arial");
		_editName->setFontSize(20);
		_editName->setFontColor(Color3B::WHITE);
		_editName->setPlaceHolder(ChineseWord("nichengTip").c_str());
		_editName->setPlaceholderFontColor(Color3B::GRAY);
		_editName->setPlaceholderFontSize(25);
		_editName->setMaxLength(16);
		_editName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
		_editName->setDelegate(this);
		addChild(_editName);

		auto bt = MenuItemImage::create("btn_queding.png", "btn_queding_2.png", CC_CALLBACK_1(SetNameLayer::quedingcallback, this));
		bt->setPosition(bg->getContentSize().width / 2, 120);
	



		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(SetNameLayer::closeButtonCallBack, this));
		close->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
		close->setPosition(bg->getContentSize());



		auto menu = Menu::create(bt, close, nullptr);
		menu->setPosition(0, 0);
		bg->addChild(menu);

		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->setSwallowTouches(true);
		touchListener->onTouchBegan = CC_CALLBACK_2(SetNameLayer::onTouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(SetNameLayer::onTouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(SetNameLayer::onTouchEnded, this);
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
bool SetNameLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
	auto pos = touch->getLocation();
	auto rect1 = sexBoy->getBoundingBox();
	auto rect2 = sexGirl->getBoundingBox();
	if (rect1.containsPoint(pos))
	{
		sexBoy->setIsChoose(true);
		sexGirl->setIsChoose(false);
		sex = 0;
	}
	else if (rect2.containsPoint(pos))
	{
		sexBoy->setIsChoose(false);
		sexGirl->setIsChoose(true);
		sex = 1;
	}
	return true;
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
	auto str = String::createWithFormat("%s", _editName->getText());
	_editName->setText(str->getCString());
	log("editBox %p was returned !", editBox);

}

void SetNameLayer::quedingcallback(Ref*)
{
	auto txt = _editName->getText();
	auto sessionid = User::getInstance()->getSessionid();
	checkTheName(txt);
	HttpMannger::getInstance()->HttpToPostRequestSetName(sessionid, txt, sex);
}

void SetNameLayer::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}

bool SetNameLayer::checkTheName(const char* name)
{
	CCLOG("%d", std::strlen(name));
	return true;
}