#include "LoadScene.h"
#include "StartScene.h"
#include "Audio.h"

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
	Audio::getInstance()->playBGM();
	return true;
}

void LoadScene::loadView() {
	auto win = Director::getInstance()->getWinSize();
	auto loadbg = Sprite::create("start_game.jpg");
	loadbg->setPosition(win.width / 2, win.height / 2);
	addChild(loadbg);

	//loading.png
	auto text = Sprite::create("loading.png");
	text->setPosition(win.width / 2, win.height / 6);
	addChild(text);

	auto bg = Sprite::create("progress_bg.png");
	bg->setPosition(win.width / 2, win.height / 8);
	addChild(bg);

	auto content = Sprite::create("progress.png");
	auto timer = ProgressTimer::create(content);
	timer->setPosition(win.width / 2, win.height / 8);
	timer->setPercentage(0);
	timer->setMidpoint(Vec2(0, 1));
	timer->setBarChangeRate(Point(1, 0));
	timer->setType(ProgressTimer::Type::BAR);
	addChild(timer);
	auto progress = ProgressFromTo::create(1.5f, 0, 100);
	timer->runAction(progress);

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