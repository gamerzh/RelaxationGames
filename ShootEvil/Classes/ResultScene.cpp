#include "ResultScene.h"
#include "ResultLayer.h"
USING_NS_CC;

bool ResultScene::init() {
	if (!Scene::init()) {
		return false;
	}
	addLayerToScene();
	return true;
}

void ResultScene::addLayerToScene() {
	//add game layer to scene
	auto gameLayer = ResultLayer::create();
	addChild(gameLayer);
}