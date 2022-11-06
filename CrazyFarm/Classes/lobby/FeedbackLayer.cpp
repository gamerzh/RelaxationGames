#include "lobby/FeedbackLayer.h"
#include "server/HttpMannger.h"
#include "domain/user/User.h"








bool FeedbackLayer::init()
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
		auto bg = Sprite::create("feedBackBg.png");
		bg->setPosition(size / 2);
		addChild(bg);


		sex = 0;

		_editName = ui::EditBox::create(Size(755,227), ui::Scale9Sprite::create("feedBackBox.png"));
		_editName->setPosition(Vec2(480,230));
		_editName->setFontName("Arial");
		_editName->setFontSize(25);
		_editName->setFontColor(Color3B::YELLOW);
		_editName->setPlaceHolder(ChineseWord("feedbackTip").c_str());
		_editName->setPlaceholderFontColor(Color3B::BLACK);
		_editName->setPlaceholderFontSize(25);
		_editName->setMaxLength(70);
		_editName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
		_editName->setDelegate(this);
		addChild(_editName);

		auto bt = MenuItemImage::create("btn_tijiao_1.png", "btn_tijiao_2.png", CC_CALLBACK_1(FeedbackLayer::quedingcallback, this));
		bt->setPosition(bg->getContentSize().width / 2, 60);
	



		auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(FeedbackLayer::closeButtonCallBack, this));
		close->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);
		close->setPosition(bg->getContentSize());



		auto menu = Menu::create(bt, close, nullptr);
		menu->setPosition(0, 0);
		bg->addChild(menu);

		auto touchListener = EventListenerTouchOneByOne::create();
		touchListener->setSwallowTouches(true);
		touchListener->onTouchBegan = CC_CALLBACK_2(FeedbackLayer::onTouchBegan, this);
		touchListener->onTouchMoved = CC_CALLBACK_2(FeedbackLayer::onTouchMoved, this);
		touchListener->onTouchEnded = CC_CALLBACK_2(FeedbackLayer::onTouchEnded, this);
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
bool FeedbackLayer::onTouchBegan(Touch *touch, Event *unused_event)
{

	return true;
}

void FeedbackLayer::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox)
{
	log("editBox %p DidBegin !", editBox);
}

void FeedbackLayer::editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox)
{
	log("editBox %p DidEnd !", editBox);
}

void FeedbackLayer::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text)
{
	log("editBox %p TextChanged, text: %s ", editBox, text.c_str());
}

void FeedbackLayer::editBoxReturn(ui::EditBox* editBox)
{
	auto str = String::createWithFormat("%s", _editName->getText());
	_editName->setText(str->getCString());
	log("editBox %p was returned !", editBox);

}

void FeedbackLayer::quedingcallback(Ref*)
{
	auto txt = _editName->getText();
	
	checkTheName(txt);
	if (strlen(txt)>0)
	{
		HttpMannger::getInstance()->HttpToPostRequestFeedback(txt);
	}
	
	removeFromParentAndCleanup(1);
}

void FeedbackLayer::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}

bool FeedbackLayer::checkTheName(const char* name)
{
	CCLOG("%d", std::strlen(name));
	return true;
}
