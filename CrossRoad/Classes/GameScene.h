#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "MapNode.h"
USING_NS_CC;

class GameScene : public cocos2d::Layer
{
	enum Gesture
	{
		straight,
		left,
		right
	};

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

	void addTouchListener();
	bool onTouchBegan(Touch *touch, Event  *event) override;
	void onTouchMoved(Touch *touch, Event  *event) override;
	void onTouchEnded(Touch *touch, Event  *event) override;

private:
	Player* player;
	Vec2 preTouchPoint;
	Gesture playerGesture;
};

#endif // __GAME_SCENE_H__
