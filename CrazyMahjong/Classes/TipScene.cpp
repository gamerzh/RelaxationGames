#include "TipScene.h"
#include "HallScene.h"

USING_NS_CC;

Scene* TipScene::createScene()
{
    auto scene = Scene::create();
    auto layer = TipScene::create(); 
    scene->addChild(layer);
    return scene;
}
bool TipScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
   ;
    auto sprite = Sprite::create("tips.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);

	
	this->scheduleOnce(schedule_selector(TipScene::goHallScene),1.0f);

    return true;
}

void TipScene::goHallScene(float dt)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, HallScene::createScene()));
}

