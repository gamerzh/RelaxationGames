#include "ResultLayer.h"
USING_NS_CC;

bool ResultLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	auto black = LayerColor::create(Color4B(255, 100, 100, 255), 1280, 720);
	addChild(black);



	return true;
}