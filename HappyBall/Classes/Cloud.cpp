#include "Cloud.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

bool Cloud::init() {
	if (!Node::init()) {
		return false;
	}
	auto yun = CSLoader::createNode("yun.csb");
	yun->setPosition(0, 0);
	this->addChild(yun);
	auto line = CSLoader::createTimeline("yun.csb");
	line->play("animation0", false);
	yun->runAction(line);
	return true;
}