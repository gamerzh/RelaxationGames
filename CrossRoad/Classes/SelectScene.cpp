#include "SelectScene.h"

Scene* SelectScene::createScene()
{
	auto scene = Scene::create();

	auto layer = SelectScene::create();

	scene->addChild(layer);
	return scene;
}

bool SelectScene::init()
{

	if (!Layer::init())
	{
		return false;
	}
	loadView();
	return true;
}

void SelectScene::loadView() {

}

void SelectScene::startGame() {

}