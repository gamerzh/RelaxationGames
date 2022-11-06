#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class AnimationUtil{
public:
	static AnimationUtil* getInstance();
	static void destroyInstance();

	void addAnimationBySpriteFrameName(const char*plistpath,const char *filepath, const char *animatname, float time, int numOfpng);

	void addAnimationBySpriteName(const char *filepath, const char *animatname, float time, int numOfpng, bool isSetRestoreOriginalFrame=true);

	void removeAnimationByName(const char* animatname);

	Animate* getAnimate(const char *animatname);
	
	void init();
private:
	
	static AnimationUtil* _pInstance;
};