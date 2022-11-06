#include "core/GameScene.h"
#include "core/GameLayer.h"
#include "core/GameGuiLayer.h"
#include "domain/game/GameManage.h"
bool GameScene::init(){
	if ( !Scene::init() )
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//add gui layer to this scene
	GameGuiLayer* gui_layer = GameGuiLayer::create();
	gui_layer->setPosition(0,0);
	gui_layer->setAnchorPoint(ccp(0,0));
	this->addChild(gui_layer,1,888);
	GameManage::getInstance()->setGuilayer(gui_layer);
	//add layers to this scene
	GameLayer* game_layer = GameLayer::create();
	game_layer->setPosition(0, 0);
	game_layer->setAnchorPoint(ccp(0, 0));
	this->addChild(game_layer, 0, 777);
	
	return true;
}

