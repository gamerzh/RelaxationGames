/// 游戏场景类
// 生成一个 麻将游戏场景

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class GameScene :public Scene
{
public:
	static Scene* createScene();

	// MahjongScene::create会调用init来初始化自己
	CREATE_FUNC(GameScene); 
	bool init();
	void GameOver();
private:

};

#endif // end MahjongScene.h