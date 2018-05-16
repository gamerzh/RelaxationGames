#include "GameOver.h"
#include "GameScene.h"
#include "StartScene.h"

bool GameOver::init() {
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

	auto box = Sprite::create("result_bg.png");
	box->setPosition(win.width / 2, win.height / 2);
	addChild(box);

	auto prideGold = LabelAtlas::create("1234", "num_yellow.png", 16, 24, '0');
	prideGold->setAnchorPoint(Point::ANCHOR_MIDDLE);
	prideGold->setPosition(win.width * 0.52, win.height*0.555f);
	addChild(prideGold);

	auto step = LabelAtlas::create("1234", "num_white.png", 16, 24, '0');
	step->setAnchorPoint(Point::ANCHOR_MIDDLE);
	step->setPosition(win.width * 0.52, win.height*0.50f);
	addChild(step);

	auto extraGold = LabelAtlas::create("100", "num_yellow.png", 16, 24, '0');
	extraGold->setAnchorPoint(Point::ANCHOR_MIDDLE);
	extraGold->setPosition(win.width * 0.52, win.height*0.445f);
	addChild(extraGold);

	auto goback = MenuItemImage::create("go_to_load.png", "go_to_load.png", CC_CALLBACK_0(GameOver::goLoading, this));
	auto resultCon = MenuItemImage::create("result_continue.png", "result_continue.png", CC_CALLBACK_0(GameOver::continueGame, this));
	auto closeMenu = Menu::create(goback, resultCon, NULL);
	closeMenu->alignItemsHorizontallyWithPadding(100);
	closeMenu->setPosition(win.width / 2, win.height*0.36f);
	addChild(closeMenu);

	return true;
}

void GameOver::continueGame() {
	((GameScene*)getParent())->cleanup();//GameScene��ת��GameScene���п���,����������
	Director::getInstance()->replaceScene(GameScene::createScene());
}

void GameOver::goLoading() {
	Director::getInstance()->replaceScene(StartScene::createScene());
}