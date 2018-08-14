#include "LobbyScene.h"
#include "LobbyLayer.h"
#include "StartLayer.h"
USING_NS_CC;

bool LobbyScene::init() {
	if (!Scene::init()) {
		return false;
	}
	auto lobby = LobbyLayer::create();
	addChild(lobby);

	return true;
}
