#include "Pillar.h"
USING_NS_CC;

bool Pillar::init() {
	if (!Node::init()) {
		return false;
	}
	auto pillar = CSLoader::createNode("zhuzi.csb");
	pillar->setPosition(0, 0);
	this->addChild(pillar);
	return true;
}