#include "core/showFishLayer.h"
#include "fish/Fish.h"
#include "utill/Chinese.h"

showFishCell* showFishCell::createCell()
{
	auto cell = new showFishCell();
	if (cell&&cell->init())
	{
		cell->autorelease();
	}
	else
	{
		cell = nullptr;
		
	}
	return cell;

}

bool  showFishCell::init()
{
	Node::init();
	bool bRet = false;
	do
	{
		int type = 1;
		auto visibilesize = Director::getInstance()->getVisibleSize();
		auto sp = Sprite::create("showFishAniFrame.png");
		sp->setPosition(visibilesize.width*0.27, visibilesize.height*0.6);
		addChild(sp);
		sp = Sprite::create("showFishInfoFrame");
		sp->setPosition(visibilesize.width*0.7, visibilesize.height*0.6);
		addChild(sp);


		auto fish = Fish::create();
		fish->initFish(type);
		fish->setPosition(visibilesize.width*0.27, visibilesize.height*0.6);
		addChild(fish);

		//ID
		auto str = String::createWithFormat("fish_id %d", type);
		auto label = LabelTTF::create(str->getCString(), "Arial", 30);
		label->setPosition(visibilesize.width*0.27, visibilesize.height*0.2);
		addChild(label);
        //2??????¨º
	    str = String::createWithFormat("%s %f", ChineseWord("fish_probability").c_str(),fish->getGrabProbability());
		label = LabelTTF::create(str->getCString(), "Arial", 30);
		label->setPosition(visibilesize.width*0.7, visibilesize.height*0.15);
		addChild(label);
	   //?¨´¡ä??¡À¨¤?
		str = String::createWithFormat("%s %f", ChineseWord("fish_baseReward").c_str(), fish->getFishGold());
		label = LabelTTF::create(str->getCString(), "Arial", 30);
		label->setPosition(visibilesize.width*0.7, visibilesize.height*0.15);
		addChild(label);
		//¨¬¨´¨ª?ID
		str = String::createWithFormat("%s %f", ChineseWord("fish_ui_id").c_str(), fish->getuiId());
		label = LabelTTF::create(str->getCString(), "Arial", 30);
		label->setPosition(visibilesize.width*0.7, visibilesize.height*0.15);
		addChild(label);


	} while (0);


	return true


		;
}




bool showFishLayer::init(){
	if ( !Node::init() )
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	auto bg = Sprite::create("showfish.jpg");
	bg->setPosition(visibleSize / 2);
	addChild(bg);




	auto listenr1 = EventListenerTouchOneByOne::create();
	listenr1->onTouchBegan = CC_CALLBACK_2(showFishLayer::onTouchBegan, this);
	listenr1->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listenr1, this);


	auto close = MenuItemImage::create("X_1.png", "X_2.png", CC_CALLBACK_1(showFishLayer::closeButtonCallBack, this));
	close->setPosition(860, 496);



	auto menu = Menu::create(close, nullptr);
	menu->setPosition(Point::ZERO);
	addChild(menu);





	return true;

}

void showFishLayer::closeButtonCallBack(Ref*psend)
{
	removeFromParentAndCleanup(1);
}
