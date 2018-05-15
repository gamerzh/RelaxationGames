#include "PauseLayer.h"
#include "GameScene.h"

bool PauseLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	initView();
	return true;
}

void PauseLayer::initView() {
	auto win = Director::getInstance()->getWinSize();

	auto black = LayerColor::create(Color4B(0, 0, 0, 204), win.width, win.height);
	black->setTag(1024);
	addChild(black);

	auto box = Sprite::create("box_bg.png");
	box->setPosition(win.width/2,win.height/2);
	addChild(box);

	auto goBack = MenuItemImage::create("go_home.png","go_home.png",CC_CALLBACK_0(PauseLayer::goBackHome,this));
	auto restart = MenuItemImage::create("start_re.png", "start_re.png", CC_CALLBACK_0(PauseLayer::gameResart, this));
	auto conti = MenuItemImage::create("play_continue.png", "play_continue.png", CC_CALLBACK_0(PauseLayer::continueGame, this));
	auto boxMenu = Menu::create(goBack, restart, conti,NULL);
	boxMenu->alignItemsVerticallyWithPadding(win.height / 8);
	boxMenu->setPosition(win.width / 2, win.height / 2);
	addChild(boxMenu);
}


void PauseLayer::goBackHome() {
	//TODO
}


void PauseLayer::gameResart() {
	Director::getInstance()->replaceScene(GameScene::createScene());
}


void PauseLayer::continueGame() {
	((GameScene*)getParent())->continueMove();
	removeFromParent();
}
