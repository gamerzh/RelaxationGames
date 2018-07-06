#include "LobbyScene.h"
#include "StartLayer.h"
USING_NS_CC;

bool LobbyScene::init() {
	if (!Scene::init()) {
		return false;
	}
	StartLayer* start = StartLayer::create();
	addChild(start);
	return true;
}