#include "GameLayer.h"
USING_NS_CC;

bool GameLayer::init() {
	if (!Layer::init()) {
		return false;
	}


	auto black = LayerColor::create(Color4B(200, 200, 200, 204), 720, 1280);
	addChild(black);

	auto node = Node::create();
	addChild(node);
	auto action = Sequence::create(DelayTime::create(5), CallFunc::create([=]() {
//        Director::getInstance()->replaceScene(TransitionMoveInT::create(1.0f, ResultScene::create()));
	}), NULL);
	node->runAction(action);

	return true;
}
