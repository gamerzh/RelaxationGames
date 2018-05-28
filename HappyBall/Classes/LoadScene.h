#ifndef __LOAD_SCENE_H__
#define __LOAD_SCENE_H__

#include "cocos2d.h"

class LoadScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(LoadScene);
private:
	const float delayTime = 1.5f;
	void loadView();
	void gotoGameScene();
};

#endif // __LOAD_SCENE_H__
