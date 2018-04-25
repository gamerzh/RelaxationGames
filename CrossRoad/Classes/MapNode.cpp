#include "MapNode.h"

MapNode* MapNode::create(MapNodeType type) {
	auto mapnode = new MapNode();
	if (mapnode && mapnode->init(type)) {
		mapnode->autorelease();
		return mapnode;
	}
	else {
		CC_SAFE_DELETE(mapnode);
		return NULL;
	}
}

bool MapNode::init(MapNodeType type) {
	if (!Node::init()) {
		return false;
	}
	setMapNodeType(type);
	Size win = Director::getInstance()->getWinSize();

	auto earth = Sprite::create(getFileNameByType(type));
	earth->setPosition(0,0);
	earth->setScaleX(2.0f);
	earth->setTag(1);
	earth->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
	addChild(earth);

	setContentSize(earth->getContentSize());
	setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);

	scheduleUpdate();

	return true;
}

string  MapNode::getFileNameByType(MapNodeType type) {
	switch (type)
	{

	case 0:
		return "white.png";
	case 1:
		return "green.png";
	default:
		return "";
	}
}


void MapNode::update(float dt) {

}