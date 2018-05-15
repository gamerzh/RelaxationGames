#include "StartScene.h"
#include "GameScene.h"

Scene* StartScene::createScene()
{
	auto scene = Scene::create();

	auto layer = StartScene::create();

	scene->addChild(layer);
	return scene;
}

bool StartScene::init()
{

	if (!Layer::init())
	{
		return false;
	}
	loadView();
	return true;
}

void StartScene::loadView() {
	auto win = Director::getInstance()->getWinSize();
	auto loadbg = Sprite::create("loading.jpg");
	loadbg->setPosition(win.width / 2, win.height / 2);
	addChild(loadbg);

	//start_game.png
	//auto start = MenuItemImage::create("start_game.png", "start_game.png", CC_CALLBACK_0(StartScene::startGame, this));
	//auto boxMenu = Menu::create(start, NULL);
	//boxMenu->setPosition(win.width / 2, win.height / 5);
	//addChild(boxMenu);

	//2秒后显示主界面
	auto node = Node::create();
	addChild(node);
	auto action = Sequence::create(DelayTime::create(1.5f), CallFunc::create([=]() {
		startGame();
	}),NULL);
	node->runAction(action);
}

void StartScene::startGame() {
	Director::getInstance()->replaceScene(GameScene::createScene());
}