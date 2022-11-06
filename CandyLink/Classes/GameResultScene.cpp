#include "GameResultScene.h"
#include "GameResultLayer.h"
#include "Audio.h"
#include "CallAndroidMethod.h"
#include "GameData.h"
Scene* GameResultScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = GameResultScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool GameResultScene::init(){
    if ( !Scene::init() )
    {
        return false;
    }
    //add layers to this scene
    Audio::getInstance()->playSound(GAME_FAIL);
    Layer* result_result = GameResultLayer::create();
    result_result->setAnchorPoint(Vec2(0, 0));
    result_result->setPosition(Vec2(0, 0));
    this->addChild(result_result);
    return true;
}
