#include "LoadScene.h"
#include "StartScene.h"

Scene* LoadScene::createScene()
{
	auto scene = Scene::create();

	auto layer = LoadScene::create();

	scene->addChild(layer);
	return scene;
}

bool LoadScene::init()
{

	if (!Layer::init())
	{
		return false;
	}
	loadView();
	return true;
}

void LoadScene::loadView() {
	auto win = Director::getInstance()->getWinSize();
	auto loadbg = Sprite::create("start_game.jpg");
	loadbg->setPosition(win.width / 2, win.height / 2);
	addChild(loadbg);

	

	//2秒后显示主界面
	auto node = Node::create();
	addChild(node);
	auto action = Sequence::create(DelayTime::create(1.5f), CallFunc::create([=]() {
		startGame();
	}),NULL);
	node->runAction(action);
}

void LoadScene::startGame() {
	Director::getInstance()->replaceScene(StartScene::createScene());
}