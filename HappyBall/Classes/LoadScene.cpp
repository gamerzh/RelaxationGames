#include "LoadScene.h"
#include "GameScene.h"


USING_NS_CC;

Scene* LoadScene::createScene()
{
	return LoadScene::create();
}

bool LoadScene::init()
{

	if (!Scene::init())
	{
		return false;
	}

	loadView();
	return true;
}

void LoadScene::loadView() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//只有NO_BOARD模式才会有值;

	/*auto sprite = Sprite::create("HelloWorld.png");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);*/

	//loading.png
	auto text = Sprite::create("loading.png");
	text->setPosition(visibleSize.width / 2+origin.x, visibleSize.height / 6 + origin.y);
	addChild(text);

	auto bg = Sprite::create("progress_bg.png");
	bg->setPosition(visibleSize.width / 2+origin.x, visibleSize.height / 8 + origin.y);
	addChild(bg);

	auto content = Sprite::create("progress.png");
	auto timer = ProgressTimer::create(content);
	timer->setPosition(visibleSize.width / 2+origin.x, visibleSize.height / 8 + origin.y);
	timer->setPercentage(0);
	timer->setMidpoint(Vec2(0, 1));
	timer->setBarChangeRate(Point(1, 0));
	timer->setType(ProgressTimer::Type::BAR);
	addChild(timer);
	auto progress = ProgressFromTo::create(1.5f, 0, 100);
	timer->runAction(progress);

	//delay time goto game scene
	auto node = Node::create();
	addChild(node);
	auto action = Sequence::create(DelayTime::create(delayTime), CallFunc::create([=]() {
		gotoGameScene();
	}), NULL);
	node->runAction(action);
}

void LoadScene::gotoGameScene() {
	Director::getInstance()->replaceScene(TransitionMoveInT::create(1.0f,GameScene::create()));
}