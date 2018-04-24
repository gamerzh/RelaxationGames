#include "MapNode.h"

MapNode* MapNode::create(Point pos) {
	auto mapnode = new MapNode();
	if (mapnode && mapnode->init(pos)) {
		mapnode->autorelease();
		return mapnode;
	}
	else {
		CC_SAFE_DELETE(mapnode);
		return NULL;
	}
}

bool MapNode::init(Point pos) {
	if (!Node::init()) {
		return false;
	}
	auto earth = Sprite::create("white.png");
	earth->setPosition(pos);
	earth->setScaleX(2.0f);
	addChild(earth);
	return true;
}