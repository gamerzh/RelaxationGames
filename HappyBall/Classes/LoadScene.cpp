#include "LoadScene.h"
#include "GameScene.h"
#include "Audio.h"

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
	Audio::getInstance()->playBGM();
	return true;
}

void LoadScene::loadView() {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();//只有NO_BOARD模式才会有值;

	auto sprite = Sprite::create("load_bg.png");
	sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(sprite, 0);

	//loading.png
	auto text = Sprite::create("loading.png");
	text->setPosition(visibleSize.width*0.45+origin.x, visibleSize.height * 0.40 + origin.y);
	addChild(text);

	auto point1 = Sprite::create("point.png");
	point1->setPosition(visibleSize.width*0.45 + 90, visibleSize.height * 0.4-10);
	addChild(point1);
	point1->setVisible(false);

	auto point2 = Sprite::create("point.png");
	point2->setPosition(visibleSize.width*0.45 + 105, visibleSize.height * 0.4 - 10);
	addChild(point2);
	point2->setVisible(false);

	auto point3 = Sprite::create("point.png");
	point3->setPosition(visibleSize.width*0.45 + 120, visibleSize.height * 0.4 - 10);
	addChild(point3);
	point3->setVisible(false);


	auto step1 = CallFunc::create([=](){
		point1->setVisible(true);
		point2->setVisible(false);
		point3->setVisible(false);
	});

	auto step2 = CallFunc::create([=]() {
		point1->setVisible(true);
		point2->setVisible(true);
		point3->setVisible(false);
	});

	auto step3 = CallFunc::create([=]() {
		point1->setVisible(true);
		point2->setVisible(true);
		point3->setVisible(true);
	});

	auto step4 = CallFunc::create([=]() {
		point1->setVisible(false);
		point2->setVisible(false);
		point3->setVisible(false);
	});
	auto del = DelayTime::create(0.3);
	auto seq = Sequence::create(step1, del, step2, del, step3, del,step4, del,NULL);
	auto rep = RepeatForever::create(seq);
	this->runAction(rep);

	auto bg = Sprite::create("progress_bg.png");
	bg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(bg);

	auto content = Sprite::create("progress.png");
	auto timer = ProgressTimer::create(content);
	timer->setPosition(visibleSize.width / 2+origin.x, visibleSize.height /2 + origin.y);
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
	Director::getInstance()->replaceScene(TransitionFade::create(0.5f,GameScene::create()));
}