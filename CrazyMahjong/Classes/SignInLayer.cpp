#include"SignInLayer.h"
#include"GameScene.h"
#include "SignManager.h"
#include "Toast.h"
#include "User.h"
using namespace cocos2d;


SignCell* SignCell::create(int day, int propnum, int signtype)
{
	SignCell* bRet = new SignCell();
	if (bRet&&bRet->init(day, propnum, signtype))
	{
		bRet->autorelease();
		return bRet;
	}
	else
	{
		delete bRet;
		bRet = NULL;
		return NULL;
	}
}
////signtype  1可以签 2点击签过  3不能签
bool SignCell::init(int day, int propnum, int signtype)
{

	bool bRet = false;
	while (!bRet)
	{
		char* XXdayPath;
		char* fntDayPath;
		if (signtype == 3)
		{

			XXdayPath = "sign_XXday_unlock.png";
			fntDayPath = "Account/numBigLose.png";
		}
		else
		{

			XXdayPath = "sign_XXday_lock.png";
			fntDayPath = "Account/numBigWin.png";
		}
		//bg
		auto bg = Sprite::create("sign_unlockbg.png");
		bg->setPosition(Point::ZERO);
		auto bgsize = bg->getContentSize();
		addChild(bg);

		
		//num
		if (signtype == 3)
		{
			auto propsprite = Sprite::create("sign_unlock.png");
			propsprite->setPosition(bgsize.width / 2, bgsize.height*0.55);
			bg->addChild(propsprite);
		}
		else
		{
			auto frame = Sprite::create("sign_lockbg.png");
			frame->setPosition(bg->getContentSize() / 2);
			bg->addChild(frame);
			auto propsprite = Sprite::create("sign_coinheap.png");
			propsprite->setPosition(bgsize.width / 2, bgsize.height*0.55);
			bg->addChild(propsprite);

			auto nLabel = Label::createWithSystemFont((String::createWithFormat("%d", propnum))->getCString(), "arial", 14);
			nLabel->setColor(Color3B(240, 203, 79));
			nLabel->setPosition(13, bgsize.height*0.35);
			nLabel->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
			nLabel->enableOutline(Color4B(65, 46, 27, 255), 3);
			bg->addChild(nLabel);


			for (int i = 0; i < nLabel->getString().size(); i++)
			{
			/*	nLabel->getChildByTag(i)->setSkewX(20);*/
			}
			auto fntjinbi = Sprite::create("sign_fntjinbi.png");
			fntjinbi->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
			fntjinbi->setPosition(nLabel->getPositionX() + nLabel->getContentSize().width - 5, nLabel->getPositionY());
			bg->addChild(fntjinbi);

			if (signtype == 1)
			{
				auto signSign = Sprite::create("sing_fntkelingqu.png");
				signSign->setPosition(bg->getContentSize().width / 2, 28);
				bg->addChild(signSign);
			}
			else
			{
				auto signSign = Sprite::create("sing_fntyilingqu.png");
				signSign->setPosition(bg->getContentSize().width / 2, 28);
				bg->addChild(signSign);

			}
		}

		//day
		auto daysprite = Sprite::create(XXdayPath);
		daysprite->setPosition(bgsize.width / 2, bgsize.height*0.93);
		bg->addChild(daysprite);
		auto daylabel = LabelAtlas::create(Value(day).asString().c_str(), fntDayPath, 34, 42, '0');
		daylabel->setPosition(daysprite->getContentSize() / 2+Size(0,5));
		daylabel->setAnchorPoint(Point::ANCHOR_MIDDLE);
		daysprite->addChild(daylabel);

		
		

		bRet = true;

	}
	return bRet;
}

SignInLayer* SignInLayer::create(int day)
{
	SignInLayer* bRet = new SignInLayer();
	if (bRet&&bRet->init(day))
	{
		bRet->autorelease();
		return bRet;
	}
	else
	{
		delete bRet;
		bRet = NULL;
		return NULL;
	}
}

bool SignInLayer::init(int day)
{
	if (!Layer::init()){
		return false;
	}
	_currentDay = day;



	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();


	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(SignInLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(SignInLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(SignInLayer::onTouchEnded, this);
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	LayerColor* layerColor = CCLayerColor::create();
	layerColor->setColor(ccc3(0, 0, 0));
	layerColor->setOpacity(180);
	layerColor->setContentSize(CCSizeMake(visibleSize.width, visibleSize.height));
	this->addChild(layerColor);

	//BG
	auto background = Sprite::create("Rule/Rule_Bottom.png");
	background->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height * 0.5 + origin.y);
	addChild(background);
	bgsize = background->getContentSize();
	initsigndate();
	//title
	auto title = Sprite::create("sign_title.png");
	title->setPosition(bgsize.width / 2, bgsize.height*1.0+20);
	background->addChild(title);
	title->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);

	//cell
	auto menu = Menu::create();
	for (auto cell : cells)
	{
		SignCell *signincellnor;

		if (cell.day < _currentDay)
		{
			signincellnor = SignCell::create(cell.day, cell.num, 2);
		}
		else if (cell.day == _currentDay)
		{
			signincellnor = SignCell::create(cell.day, cell.num, 1);
		}
		else
		{
			signincellnor = SignCell::create(cell.day, cell.num, 3);
		}
		signincellnor->setPosition(cell.pos);
		background->addChild(signincellnor);
	}
	menu->setPosition(Point::ZERO);
	auto queding = MenuItemImage::create("btn_lingqu_1.png", "btn_lingqu_2.png", CC_CALLBACK_1(SignInLayer::geteveryGift, this));
	queding->setPosition(Point(bgsize.width / 2, bgsize.height*0.17));
	menu->addChild(queding);

	auto vip = Sprite::create("sign_context.png");
	vip->setPosition(bgsize.width / 2, 330);
	background->addChild(vip);

	background->addChild(menu);
	return true;

}

void SignInLayer::initsigndate()
{
	float startx = 20 + 44;
	float difx = (bgsize.width - 40.0f) / 7.0f;
	SignCellDate date;
	date.day = 1;
	date.num = 2000;
	date.pos = Point(startx, bgsize.height*0.5);
	cells.push_back(date);

	startx += difx;
	date.day = 2;
	date.num = 2500;
	date.pos = Point(startx, bgsize.height*0.5);
	cells.push_back(date);

	startx += difx;
	date.day = 3;
	date.num = 2500;
	date.pos = Point(startx, bgsize.height*0.5);
	cells.push_back(date);

	startx += difx;
	date.day = 4;
	date.num = 3000;
	date.pos = Point(startx, bgsize.height*0.5);
	cells.push_back(date);

	startx += difx;
	date.day = 5;
	date.num = 3500;
	date.pos = Point(startx, bgsize.height*0.5);
	cells.push_back(date);

	startx += difx;
	date.day = 6;
	date.num = 4000;
	date.pos = Point(startx, bgsize.height*0.5);
	cells.push_back(date);

	startx += difx;
	date.day = 7;
	date.num = 5000;
	date.pos = Point(startx, bgsize.height*0.5);
	cells.push_back(date);

}



void SignInLayer::geteveryGift(Ref* psender){

	int rewardnum = cells.at(_currentDay - 1).num;
	User::getInstance()->addCoin(rewardnum);
	SignManager::getInstance()->sign(_currentDay);
	Toast::show(String::createWithFormat("Wish you get %d coins by sign", rewardnum)->getCString(), 3, getParent());
	removeFromParentAndCleanup(1);
}

//触摸函数ccTouchBegan，返回true
bool SignInLayer::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	return true;
}

