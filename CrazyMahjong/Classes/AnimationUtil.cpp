#include "AnimationUtil.h"

AnimationUtil* AnimationUtil::_pInstance = NULL;

AnimationUtil* AnimationUtil::getInstance(){
	if(_pInstance == NULL){
		_pInstance = new AnimationUtil();
	}
	return _pInstance;
}

void AnimationUtil::destroyInstance(){
	if(_pInstance != NULL){
		delete _pInstance;
		_pInstance = NULL;
	}
}
void AnimationUtil::init()
{
	addAnimationBySpriteName("MJAnim/zhuaniao/zhuaniao_%d.png", "ani_zhuaniao",0.7f,19, false);
	addAnimationBySpriteName("MJAnim/fanzhuan/MJfanzhuan_%d.png", "ani_MJfanzhuan", 0.2f, 4, false);
	addAnimationBySpriteName("MJAnim/huaguang/huaguang_%d.png", "ani_huaguang", 1.3f, 10, false);
	addAnimationBySpriteName("MJAnim/quickStartAni/quickStartAni_%d.png", "ani_quickstart", 1.0f, 8, false);
	addAnimationBySpriteName("MJAnim/piaoguang/piaoguang_%d.png", "ani_piaoguang",1.2f, 10, false);
	addAnimationBySpriteName("MJAnim/shanguang/shanguang_%.4d.png", "ani_shanguang", 1.2f, 10, false);
	addAnimationBySpriteName("MJAnim/thunder/ani_thunder_%d.png", "ani_thunder", 0.5f, 8, false);
}


void AnimationUtil::addAnimationBySpriteFrameName(const char*plistpath, const char *filepath, const char *animatname, float time, int numOfpng){
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistpath);
	if (AnimationCache::getInstance()->getAnimation(animatname) != NULL){
		return;
	}
	char str[100] = { 0 };

	Animation* animation = Animation::create();
	animation->setDelayPerUnit(time / numOfpng);
	for (int i = 1; i <= numOfpng; i++){
		sprintf(str, filepath, i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		animation->addSpriteFrame(frame);
	}

	AnimationCache::getInstance()->addAnimation(animation, animatname);
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile(plistpath);
}

void AnimationUtil::addAnimationBySpriteName(const char *filepath, const char *animatname, float time, int numOfpng, bool isSetRestoreOriginalFrame){
	if (AnimationCache::getInstance()->getAnimation(animatname) != NULL){
		return;
	}
	char str[50] = { 0 };
	Animation* animation = Animation::create();
	animation->setRestoreOriginalFrame(isSetRestoreOriginalFrame);
	animation->setDelayPerUnit(time / numOfpng);
	for (int i = 1; i <= numOfpng; i++){
		sprintf(str, filepath, i);
		animation->addSpriteFrameWithFile(str);
	}
	AnimationCache::getInstance()->addAnimation(animation, animatname);
}

Animate* AnimationUtil::getAnimate(const char *animatname){
	Animation* animation = AnimationCache::getInstance()->getAnimation(animatname);
	Animate* animate = Animate::create(animation);
	return animate;
}


void AnimationUtil::removeAnimationByName(const char* animatname)
{
	if (AnimationCache::getInstance()->getAnimation(animatname) == NULL){
		return;
	}

	AnimationCache::getInstance()->removeAnimationByName(animatname);
}