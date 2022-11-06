#ifndef __TIP_SCENE_H__
#define __TIP_SCENE_H__

#include "cocos2d.h"

class	TipScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

	void goHallScene(float dt);

	CREATE_FUNC(TipScene);
};

#endif 
