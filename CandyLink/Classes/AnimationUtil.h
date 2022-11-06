#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class AnimationUtil{
public:
	static AnimationUtil* getInstance();
	static void destroyInstance();


	void initAnimationBySplitIMG(const char* filename,float time,int numOfpng);

	void addAnimationBySpriteFrameName(const char *animatname,float time,int numOfpng);

	void addAnimationBySpriteName(const char *filepath , const char *animatname, float time, int numOfpng);

	void removeAnimationByName(const char* animatname);

	Animate* getAnimate(const char *animatname);
	

	Sprite* getSpriteBySplitIMG(const char* filename,int index,int totalNum);

	
private:
	static AnimationUtil* _pInstance;
};