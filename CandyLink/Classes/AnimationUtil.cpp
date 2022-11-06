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

void AnimationUtil::initAnimationBySplitIMG(const char* filename,float time,int numOfpng){

	if(AnimationCache::getInstance()->getAnimation(filename) != NULL){
		return;
	}
	auto big = Sprite::create(filename);

	float width = big->getContentSize().width / numOfpng;
	float height = big->getContentSize().height;

	Animation* animation = Animation::create();
	animation->setDelayPerUnit(time / numOfpng);

	for(int i = 0; i < numOfpng; i++){
		auto frame = SpriteFrame::create(filename,Rect(i*width,0,width,height));
		animation->addSpriteFrame(frame);
	}
	
	AnimationCache::getInstance()->addAnimation(animation,filename);	
	
	
}



void AnimationUtil::addAnimationBySpriteFrameName(const char *animatname, float time, int numOfpng){


	if (AnimationCache::getInstance()->getAnimation(animatname) != NULL){
		return;
	}

	

	char str[30] = {0};

	Animation* animation = Animation::create();
	animation->setDelayPerUnit(time / numOfpng);
	for(int i = 1; i <= numOfpng; i++ ){
		sprintf(str, "%s%d.png", animatname, i);
		auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
		animation->addSpriteFrame(frame);
	}
	
	AnimationCache::getInstance()->addAnimation(animation, animatname);
}

void AnimationUtil::addAnimationBySpriteName(const char *filepath, const char *animatname, float time, int numOfpng){


	if (AnimationCache::getInstance()->getAnimation(animatname) != NULL){
		return;
	}
	char str[30] = { 0 };

	Animation* animation = Animation::create();
	animation->setDelayPerUnit(time / numOfpng);
	for (int i = 1; i <= numOfpng; i++){
		sprintf(str, "%s%d.png", filepath, i);
		animation->addSpriteFrameWithFile(str);
	}

	AnimationCache::getInstance()->addAnimation(animation, animatname);
}

Animate* AnimationUtil::getAnimate(const char *animatname){

	Animation* animation = AnimationCache::getInstance()->getAnimation(animatname);

	Animate* animate = Animate::create(animation);
	return animate;

}

Sprite* AnimationUtil::getSpriteBySplitIMG(const char* filename,int index,int totalNum){

	auto big = Sprite::create(filename);

	Size size = big->getContentSize();

	int width = size.width / totalNum;
	int startX = (index - 1) * width; 

	Sprite* sprite = Sprite::create(filename,Rect(startX,0,width,size.height));
	return sprite;

}

void AnimationUtil::removeAnimationByName(const char* animatname)
{
	if (AnimationCache::getInstance()->getAnimation(animatname) == NULL){
		return;
	}

	AnimationCache::getInstance()->removeAnimationByName(animatname);
}