/// ��Ϸ������
// ����һ�� �齫��Ϸ����

#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class GameScene :public Scene
{
public:
	static Scene* createScene();

	// MahjongScene::create�����init����ʼ���Լ�
	CREATE_FUNC(GameScene); 
	bool init();
	void GameOver();
private:

};

#endif // end MahjongScene.h