#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "GameLayer.h"

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
	

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
private:
	Size win = Director::getInstance()->getWinSize();
	//bool allowMove = true;
	GameLayer* mapLayer;
	Camera* playerCamera;
	void initView();
	void pauseMove();
	void update(float dt);
};

#endif // __GAME_SCENE_H__
