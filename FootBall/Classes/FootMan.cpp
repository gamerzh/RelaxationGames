#include "FootMan.h"
USING_NS_CC;

bool FootMan::init() {
	if (!Node::init()) {
		return false;
	}
	auto people = Sprite::create("timg.jpg");
	people->setAnchorPoint(Point::ANCHOR_MIDDLE);
	people->setPosition(0, 0);
	addChild(people);
	return true;
}