#include "GuideLayer.h"
#include "UserData.h"
#include "GameStatus.h"
#include "Dream.h"
#include "DreamNode.h"

bool GuideLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	auto win = Director::getInstance()->getWinSize();

	auto swa = MenuItem::create();
	swa->setContentSize(Size(win.width, win.height));
	auto swam = Menu::create(swa, NULL);
	addChild(swam);

	auto bg0 = LayerColor::create(Color4B(0, 0, 0, 204), win.width, win.height);
	addChild(bg0);


	auto guide = Sprite::create("guide_layer.png");
	guide->setPosition(win.width/2,win.height/2);
	addChild(guide);

	if (!UserData::getInstance()->getDreamTimes()) {
		auto mm = Sprite::create("jxb.png");
		mm->setAnchorPoint(Vec2(0, 0));
		mm->setOpacity(40);
		mm->setPosition(win.width / 2 - 355, win.height / 2 - 635);
		addChild(mm);
	}

	auto conti = MenuItemImage::create("guide_know.png", "guide_know.png", CC_CALLBACK_0(GuideLayer::closeView, this));
	auto boxMenu = Menu::create( conti, NULL);
	boxMenu->setPosition(win.width / 2, win.height / 5);
	addChild(boxMenu);
	Director::getInstance()->pause();
	return true;
}

void GuideLayer::closeView() {
	UserData::getInstance()->setShowGuide(true);
	GameStatus::getInstance()->setGameStatus(true);
	if (!UserData::getInstance()->getDreamTimes()) {
		Dream::getInstance()->requestEvent(4);	//开始执行dream代码
		UserData::getInstance()->setPlayerGoldNum(UserData::getInstance()->getPlayerGoldNum() + 100);
	}
	Director::getInstance()->resume();//不论结果,玩家获得100金币
	auto win = Director::getInstance()->getWinSize();
	auto kaiju = DreamNode::create(5, Vec2(win.width / 2, win.height / 2));
	getParent()->addChild(kaiju, 5000);
	removeFromParent();
}