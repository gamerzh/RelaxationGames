#include "GameLayer.h"
#include "ResultScene.h"
#include "Rocker.h"
USING_NS_CC;

bool GameLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto black = LayerColor::create(Color4B(200, 200, 200, 204), visibleSize.width, visibleSize.height);
	addChild(black);

	auto roc = Rocker::create(Vec2(200, 200));
	roc->openRocker();
	addChild(roc);

	auto node = Node::create();
	addChild(node);
	auto action = Sequence::create(DelayTime::create(5), CallFunc::create([=]() {
		//Director::getInstance()->replaceScene(TransitionMoveInT::create(1.0f, ResultScene::create()));
	}), NULL);
	node->runAction(action);

	return true;
}